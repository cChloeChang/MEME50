#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "rc522.h"

#define SPI_CHANNEL 0
#define RST_PIN 25

// SPI 寫入寄存器
void write_reg(uint8_t reg, uint8_t value) {
    uint8_t buf[2] = { (reg << 1) & 0x7E, value };
    wiringPiSPIDataRW(SPI_CHANNEL, buf, 2);
}

// SPI 讀取寄存器
uint8_t read_reg(uint8_t reg) {
    uint8_t buf[2] = { ((reg << 1) & 0x7E) | 0x80, 0 };
    wiringPiSPIDataRW(SPI_CHANNEL, buf, 2);
    return buf[1];
}

// 軟重置 RC522
void rc522_reset(void) {
    digitalWrite(RST_PIN, LOW);
    delay(50);
    digitalWrite(RST_PIN, HIGH);
    delay(50);
    write_reg(CommandReg, PCD_RESETPHASE);
    delay(50);
    printf("RC522 重置完成\n");
}

// 初始化 RC522
void rc522_init(void) {
    if (wiringPiSetupGpio() < 0) {
        printf("WiringPi 初始化失敗\n");
        return;
    }

    pinMode(RST_PIN, OUTPUT);
    digitalWrite(RST_PIN, HIGH);

    // 初始化 SPI
    if (wiringPiSPISetup(SPI_CHANNEL, 500000) < 0) { // 降低 SPI 速度至 500kHz
        printf("SPI 初始化失敗\n");
        return;
    }

    rc522_reset();

    // 配置 RC522
    write_reg(TxASKReg, 0x40);      // 啟用 100% ASK
    write_reg(ModeReg, 0x3D);       // CRC 初始化
    write_reg(TxControlReg, 0x03);  // 啟用天線
    write_reg(0x2B, 0xB7);         // 設置 RxGain 為最大（增強感應）
    write_reg(ComIEnReg, 0x80);     // 啟用中斷
    write_reg(FIFOLevelReg, 0x80);  // 清空 FIFO

    // 檢查模組狀態
    uint8_t status = read_reg(TxControlReg);
    if (status != 0x03) {
        printf("RC522 初始化失敗，TxControlReg: 0x%02X\n", status);
    } else {
        printf("RC522 初始化成功\n");
    }
}

// 發送命令到卡片
uint8_t rc522_request(uint8_t *data, uint8_t *len) {
    write_reg(ComIrqReg, 0x7F);    // 清除所有中斷
    write_reg(BitFramingReg, 0x07); // 7 位傳輸
    data[0] = PICC_REQIDL;
    *len = 1;

    write_reg(FIFOLevelReg, 0x80); // 清空 FIFO
    for (uint8_t i = 0; i < *len; i++) {
        write_reg(FIFODataReg, data[i]);
    }

    write_reg(CommandReg, PCD_TRANSCEIVE);
    write_reg(BitFramingReg, 0x87); // 啟動傳輸

    // 等待最多 30ms
    for (int i = 0; i < 30; i++) {
        if (read_reg(ComIrqReg) & 0x30) { // RxIRq 或 IdleIRq
            break;
        }
        delay(1);
    }

    if (!(read_reg(ComIrqReg) & 0x30)) {
        write_reg(CommandReg, PCD_IDLE);
        return 1; // 超時
    }

    uint8_t error = read_reg(ErrorReg);
    if (error & 0x13) { // BufferOvfl, CollErr, ParityErr
        write_reg(CommandReg, PCD_IDLE);
        return 1;
    }

    *len = read_reg(FIFOLevelReg);
    for (uint8_t i = 0; i < *len; i++) {
        data[i] = read_reg(FIFODataReg);
    }

    write_reg(CommandReg, PCD_IDLE);
    return 0;
}

// 防衝突並選擇卡片
uint8_t rc522_anticoll(uint8_t *uid) {
    write_reg(ComIrqReg, 0x7F);    // 清除中斷
    write_reg(BitFramingReg, 0x00);
    uint8_t buf[2] = { PICC_ANTICOLL, 0x20 };
    write_reg(FIFOLevelReg, 0x80);
    write_reg(FIFODataReg, buf[0]);
    write_reg(FIFODataReg, buf[1]);

    write_reg(CommandReg, PCD_TRANSCEIVE);
    write_reg(BitFramingReg, 0x80);

    // 等待最多 30ms
    for (int i = 0; i < 30; i++) {
        if (read_reg(ComIrqReg) & 0x30) {
            break;
        }
        delay(1);
    }

    if (!(read_reg(ComIrqReg) & 0x30)) {
        write_reg(CommandReg, PCD_IDLE);
        return 1;
    }

    uint8_t fifo_len = read_reg(FIFOLevelReg);
    if (fifo_len >= 4) {
        for (uint8_t i = 0; i < 4; i++) {
            uid[i] = read_reg(FIFODataReg);
        }
        write_reg(CommandReg, PCD_IDLE);
        return 0;
    }

    write_reg(CommandReg, PCD_IDLE);
    return 1;
}

// 讀取卡片 UID
uint8_t rc522_read_card(uint8_t *uid, uint8_t *uid_len) {
    uint8_t data[2], len = 2;
    if (rc522_request(data, &len) == 0) {
        if (rc522_anticoll(uid) == 0) {
            *uid_len = 4;
            return 0;
        }
    }
    return 1;
}
