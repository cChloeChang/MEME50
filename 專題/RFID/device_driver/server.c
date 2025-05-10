#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/smart_lock_fifo"

int main(void) {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds, testfds;
    int fifo_fd;
    
    // 開啟FIFO進行讀取
    printf("正在開啟FIFO進行讀取...\n");
    mkfifo(FIFO_PATH, 0666);  // create FIFO（如果不存在）
    fifo_fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fifo_fd < 0) {
        perror("無法開啟FIFO進行讀取");
        exit(1);
    }
    printf("FIFO開啟成功\n");
    
    // create and set up server socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(5090);
    server_len = sizeof(server_address);
    
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    
    // 創建連接queue並初始化readfds
    listen(server_sockfd, 5);
    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);
    FD_SET(fifo_fd, &readfds);  // 添加FIFO到集合
    
    printf("伺服器等待連接和FIFO輸入...\n");
    
    while(1) {
        char buffer[100];
        int fd;
        int nread;
        
        testfds = readfds;
        
        // 等待socket或FIFO上的活動
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *) 0);
        
        if(result < 1) {
            perror("select");
            exit(1);
        }
        
        // 檢查每個file descriptor
        for(fd = 0; fd < FD_SETSIZE; fd++) {
            if(FD_ISSET(fd, &testfds)) {
                // 伺服器socket上的活動 - new connection
                if(fd == server_sockfd) {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, 
                                         (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds);
                    printf("添加 client 端於 fd %d\n", client_sockfd);
                }
                // FIFO上的活動 - 來自smart_lock.c的訊息
                else if(fd == fifo_fd) {
                    memset(buffer, 0, sizeof(buffer));
                    nread = read(fifo_fd, buffer, sizeof(buffer)-1);
                    
                    if(nread > 0) {
                        buffer[nread] = '\0';
                        printf("從FIFO接收: %s\n", buffer);
                        
                        // 將訊息發送給所有連接的client
                        for(int i = 0; i < FD_SETSIZE; i++) {
                            if((i != server_sockfd) && (i != fifo_fd) && FD_ISSET(i, &readfds)) {
								// test start
								char sendbuf[16];
								snprintf(sendbuf, sizeof(sendbuf), "%s\n", buffer);
								printf("發送 %s 給 client 端 fd %d\n", buffer, i);
								write(i, sendbuf, strlen(sendbuf));

								// test end
                                // printf("發送 %s 給 client 端 fd %d\n", buffer, i);
                                // write(i, buffer, strlen(buffer));
                            }
                        }
                    }
                }
                // client socket上的活動
                else {
                    ioctl(fd, FIONREAD, &nread);
                    
                    // 客戶端已關閉連接
                    if(nread == 0) {
                        close(fd);
                        FD_CLR(fd, &readfds);
                        printf("移除 client 端於fd %d\n", fd);
                    }
                    // 客戶端發送數據
                    else {
                        memset(buffer, 0, sizeof(buffer));
                        read(fd, buffer, 99);
                        printf("從 client 端接收: %s\n", buffer);
                        // 目前 pico w 不需要回傳
                    }
                }
            }
        }
    }
    
    close(fifo_fd);
    return 0;
}