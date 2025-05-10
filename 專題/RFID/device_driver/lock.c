#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mariadb/mysql.h>

#define FIFO_PATH "/tmp/smart_lock_fifo"
#define DEVICE_PATH "/dev/rfid"

// 授權 UID 字串（十六進位）
#define AUTHORIZED_UID_HEX "A3D6BA13DC"

// 資料庫資訊
#define DB_HOST "192.168.0.27"
// #define DB_HOST "192.168.51.140"
#define DB_USER "groupuser"
#define DB_PASS "group1234"
#define DB_NAME "groupdb"

int main(void) {
    int fifo_fd, dev_fd;
    unsigned char uid_buf[16];
    char hex_buf[32];
    int count = 0;

    // 初始化 MariaDB
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() 失敗\n");
        return 1;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "資料庫連線失敗: %s\n", mysql_error(conn));
        return 1;
    }

    // 建立 FIFO
    mkfifo(FIFO_PATH, 0666);
    fifo_fd = open(FIFO_PATH, O_WRONLY | O_NONBLOCK);
    if (fifo_fd < 0) {
        perror("無法開啟 FIFO 進行寫入");
        exit(1);
    }

    // 開啟 /dev/rfid
    dev_fd = open(DEVICE_PATH, O_RDONLY);
    if (dev_fd < 0) {
        perror("無法開啟 /dev/rfid");
        exit(1);
    }

    printf("開始讀取卡片...\n");

    while (1) {
        memset(uid_buf, 0, sizeof(uid_buf));
        ssize_t len = read(dev_fd, uid_buf, sizeof(uid_buf));
        if (len > 0 && uid_buf[0] != '\0') {
            // 將 UID 轉換成十六進位字串
            memset(hex_buf, 0, sizeof(hex_buf));
            for (int i = 0; i < len; i++) {
                snprintf(&hex_buf[i * 2], 3, "%02X", uid_buf[i]);
            }

            printf("讀取到 UID: %s\n", hex_buf);

            char query[512];

            // 判斷是否為授權卡
            if (strcmp(hex_buf, AUTHORIZED_UID_HEX) == 0) {
                write(fifo_fd, "22", 2);
                count++;
                if (count % 2 == 1) {
                    printf("授權卡，傳送 22\n進入\n");
                    snprintf(query, sizeof(query),
                        "INSERT INTO sensor_data(device_id, value, status) VALUES('rfid', '%s', 'pass_entry')",
                        hex_buf);
                } else {
                    printf("授權卡，傳送 22\n離開\n");
                    snprintf(query, sizeof(query),
                        "INSERT INTO sensor_data(device_id, value, status) VALUES('rfid', '%s', 'pass_exit')",
                        hex_buf);
                }
            } else {
                write(fifo_fd, "11", 2);
                printf("未授權卡，傳送 11\n");
                snprintf(query, sizeof(query),
                    "INSERT INTO sensor_data(device_id, value, status) VALUES('rfid', '%s', 'nopass')",
                    hex_buf);
            }

            if (mysql_query(conn, query)) {
                fprintf(stderr, "SQL 錯誤: %s\n", mysql_error(conn));
            }
        }

        usleep(500000); // 500ms
    }

    mysql_close(conn);
    close(dev_fd);
    close(fifo_fd);
    return 0;
}
