#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    char ch;
    int in;
    long count = 0;

    // 檢查是否提供了檔案名稱
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    in = open(argv[1], O_RDONLY);
    if(in == -1){
        printf("Cannot open %s\n", argv[1]);
        exit(1);
    }

    while(read(in, &ch, 1) > 0){
        write(STDOUT_FILENO, &ch, 1);
        count++;
    }

    close(in);
    printf("File %s has %ld characters\n", argv[1], count);

    return 0;
}
