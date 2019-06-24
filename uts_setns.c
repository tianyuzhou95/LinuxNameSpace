#define _GNU_SOURCE
#include <fcntl.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int fd;

    if (argc < 3) {
        fprintf(stderr, "%s /proc/PID/ns/FILE cmd args...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 打开一个现存的 UTS namespace 文件
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        errExit("open");

    // 把当前进程的 UTS namespace 设置为命令行参数传入的 namespace
    if (setns(fd, 0) == -1)        
        errExit("setns");

    // 在新的 UTS namespace 中运行用户指定的程序
    execvp(argv[2], &argv[2]);
    errExit("execvp");
    return 0;
}