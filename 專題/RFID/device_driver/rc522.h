#ifndef RC522_H
#define RC522_H

#include <stdint.h>

// MFRC522 寄存器定義（部分）
#define CommandReg        0x01
#define ComIEnReg         0x02
#define ComIrqReg         0x04
#define ErrorReg          0x06
#define FIFODataReg       0x09
#define FIFOLevelReg      0x0A
#define ControlReg        0x0C
#define BitFramingReg     0x0D
#define CollReg           0x0E
#define ModeReg           0x11
#define TxControlReg      0x14
#define TxASKReg          0x15
#define Status2Reg        0x08

// MFRC522 命令
#define PCD_IDLE          0x00
#define PCD_AUTHENT       0x0E
#define PCD_RECEIVE       0x08
#define PCD_TRANSMIT      0x04
#define PCD_TRANSCEIVE    0x0C
#define PCD_RESETPHASE    0x0F
#define PCD_CALCCRC       0x03

// MIFARE 命令
#define PICC_REQIDL       0x26
#define PICC_ANTICOLL     0x93
#define PICC_SElECTTAG    0x93

// 函數原型
void rc522_init(void);
void rc522_reset(void);
uint8_t rc522_read_card(uint8_t *uid, uint8_t *uid_len);

#endif
