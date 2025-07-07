/**
 * @file    syscalls.c
 * @brief   系统调用存根函数
 * @version 1.0
 * @date    2024-12-19
 * @author  Bob (架构师)
 * 
 * @note    提供newlib需要的系统调用存根函数，解决链接错误
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

/* 环境变量 */
char *__env[1] = { 0 };
char **environ = __env;

/* 程序结束 */
void _exit(int status)
{
    (void)status;
    while (1);
}

/* 关闭文件 */
int _close(int file)
{
    (void)file;
    return -1;
}

/* 执行程序 */
int _execve(char *name, char **argv, char **env)
{
    (void)name;
    (void)argv;
    (void)env;
    errno = ENOMEM;
    return -1;
}

/* 创建子进程 */
int _fork(void)
{
    errno = EAGAIN;
    return -1;
}

/* 获取文件状态 */
int _fstat(int file, struct stat *st)
{
    (void)file;
    st->st_mode = S_IFCHR;
    return 0;
}

/* 获取进程ID */
int _getpid(void)
{
    return 1;
}

/* 检查是否为终端 */
int _isatty(int file)
{
    (void)file;
    return 1;
}

/* 终止进程 */
int _kill(int pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = EINVAL;
    return -1;
}

/* 创建链接 */
int _link(char *old, char *new)
{
    (void)old;
    (void)new;
    errno = EMLINK;
    return -1;
}

/* 文件定位 */
int _lseek(int file, int ptr, int dir)
{
    (void)file;
    (void)ptr;
    (void)dir;
    return 0;
}

/* 打开文件 */
int _open(const char *name, int flags, int mode)
{
    (void)name;
    (void)flags;
    (void)mode;
    return -1;
}

/* 读取文件 */
int _read(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return 0;
}

/* 获取状态 */
caddr_t _sbrk(int incr)
{
    extern char end asm("end");
    extern char _estack asm("_estack");
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
        heap_end = &end;

    prev_heap_end = heap_end;

    if (heap_end + incr > &_estack) {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

/* 获取状态 */
int _stat(const char *filepath, struct stat *st)
{
    (void)filepath;
    st->st_mode = S_IFCHR;
    return 0;
}

/* 获取时间 */
int _times(struct tms *buf)
{
    (void)buf;
    return -1;
}

/* 删除链接 */
int _unlink(char *name)
{
    (void)name;
    errno = ENOENT;
    return -1;
}

/* 等待 */
int _wait(int *status)
{
    (void)status;
    errno = ECHILD;
    return -1;
}

/* 写入文件 */
int _write(int file, char *ptr, int len)
{
    (void)file;
    (void)ptr;
    (void)len;
    return len;
}
