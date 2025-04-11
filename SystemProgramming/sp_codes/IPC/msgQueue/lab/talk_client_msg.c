#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

void cleanup(int signo) {
    int msgid = msgget((key_t)1234, 0666);
    if (msgid != -1) {
        struct my_msg_st disconnect_msg;
        disconnect_msg.my_msg_type = 1; // client 發送給 server 的類型
        strcpy(disconnect_msg.some_text, "\nclient_disconnected");
        msgsnd(msgid, (void *)&disconnect_msg, MAX_TEXT, IPC_NOWAIT); // 非阻塞send
    }
    printf("\nclient disconnected\n"); // 換行顯示
    exit(EXIT_SUCCESS);
}

int main() {
    int running = 1;
    int msgid;
    struct my_msg_st send_data, recv_data;
    char buffer[MAX_TEXT];

    // 檢查 server 是否存在，若不存在則不建
    msgid = msgget((key_t)1234, 0666);
    if (msgid == -1) {
        if (errno == ENOENT) { // 若 msg queue 不存在
            fprintf(stderr, "Sorry, no server\n");
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "無法連接到 server: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("可以開始輸入訊息囉!\n");

    // ctrl+c 結束程式
    signal(SIGINT, cleanup);

    while (running) {
        printf("enter msg: ");
        fgets(buffer, MAX_TEXT, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // 移除\n
        printf("client: %s\n", buffer);

        // 準備發送 msg (類型設為 1)
        send_data.my_msg_type = 1;
        strcpy(send_data.some_text, buffer);

        // 發送 msg 給 server
        if (msgsnd(msgid, (void *)&send_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msg 發送失敗\n");
            exit(EXIT_FAILURE);
        }

        // 檢查是否輸入 "bye"
        if (strncmp(buffer, "bye", 3) == 0) {
            running = 0;
            continue;
        }

        // 接收 server 的回覆 (類型設為 2)
        if (msgrcv(msgid, (void *)&recv_data, MAX_TEXT, 2, 0) == -1) {
            fprintf(stderr, "msg 接收失敗: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        // 檢查是否為 server 斷線
        if (strcmp(recv_data.some_text, "\nserver_disconnected") == 0) {
            printf("\nserver disconnected\n"); // 換行顯示
            running = 0;
            continue;
        }

        printf("server: %s\n", recv_data.some_text);

        // 檢查是否收到 "bye"
        if (strncmp(recv_data.some_text, "bye", 3) == 0) {
            running = 0;
        }
    }

    exit(EXIT_SUCCESS);
}
