/* Support files for GNU libc.  Files in the system namespace go here.
   Files in the C namespace (ie those that do not start with an
   underscore) go in .c.  */

/**
 * @file syscalls.c
 * @author Alexis Marquet
 * @date 28 Apr 2015
 * @brief this file contains implementations for the system calls (syscalls) on which stdlib relies on.
 * Implementation is not definitive, it will be completed everytime something new is needed
 **/


#include <_ansi.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include "../proc/UART.h"
#include <string.h>


// #define STRACE


#ifdef STRACE
#define STRACE(x,y,z)      UART_putString(x,y,z);
#else
#define STRACE(x,y,z)      ;
#endif

void _exit (int n);
int _close (int file);
int _execve(char *name, char **argv, char **env);
int _fork (void);
int _fstat (int file, struct stat * st);
int _getpid (void);
int _isatty (int fd);
int _kill (int pid, int sig);
int _link (char *old, char *new);
int _lseek (int file, int ptr, int dir);
int _open (const char * path, int flags, int mode);
int _read (int file, char * ptr, int len);
caddr_t _sbrk (int incr);
int _stat (const char *fname, struct stat *st);
clock_t _times (struct tms * buf);
int _unlink (char *name);
int _wait (int*status);
int _write (int file, char * ptr, int len);

extern int errno;


void _exit (int n)
{
   STRACE(UART0,"_exit\n",6);
	while(1);
}
int _close (int file)
{
   STRACE(UART0,"_close\n",7);
	return -1;
}
int _execve(char *name, char **argv, char **env)
{
   STRACE(UART0,"_execve\n",8);
	errno = ENOMEM;
	return -1;
}

int _fork (void)
{
   STRACE(UART0,"_fork\n",6);
	errno = EAGAIN;
	return -1;
}

int _fstat (int file, struct stat * st)
{
   STRACE(UART0,"_fstat\n",7);
	st->st_mode = S_IFCHR;
	return 0;
}

int _getpid (void)
{
   STRACE(UART0,"_getpid\n",8);
	return 1;
}

int _isatty (int fd)
{
   STRACE(UART0,"_isatty\n",8);
   // TODO: implement stdin stdout stderr
	return fd==1;	//only stdout;
}

int _kill (int pid, int sig)
{
   STRACE(UART0,"_kill\n",6);
	errno = EINVAL;
	return -1;
}

int _link (char *old, char *new)
{
   STRACE(UART0,"_link\n",6);
	errno = EMLINK;
	return -1;
}

int _lseek (int file, int ptr, int dir)
{
   STRACE(UART0,"_lseek\n",7);
	return 0;
}

int _open (const char * path, int flags, int mode)
{
   STRACE(UART0,"_open\n",6);
	return -1;
}

int _read (int file, char * ptr, int len)
{
   STRACE(UART0,"_read\n",6);
	return 0;
}

caddr_t _sbrk (int incr)
{
   extern char _end;		// Defined by the linker
   extern char stack_ptr;
   static char *heap_end = NULL;
   char *prev_heap_end = NULL;
   
   STRACE(UART0,"_sbrk\n",6);

   if (heap_end == 0) {
      heap_end = &_end;
   }
   
   
   prev_heap_end = heap_end;
   if (heap_end + incr > &stack_ptr) {
      _write (1, "Heap and stack collision\n", 26);
      errno = ENOMEM;
   }
   
   heap_end += incr;
   return (caddr_t) prev_heap_end;
}

int _stat (const char *fname, struct stat *st)
{
   STRACE(UART0,"_stat\n",6);
	st->st_mode = S_IFCHR;
	return 0;
}

clock_t _times (struct tms * buf)
{
   STRACE(UART0,"_times\n",7);
	return -1;
}

int _unlink (char *name)
{
   STRACE(UART0,"_unlink\n",8);
	errno = ENOENT;
	return -1;
}

int _wait (int*status)
{
   STRACE(UART0,"_wait\n",6);
	errno = ECHILD;
	return -1;
}

int _write (int file, char * ptr, int len)
{
   STRACE(UART0,"_write\n",7);
   if((file == 1) || (file == 2))
   {
      return UART_putString(UART0,ptr,len);
   }
   return 0;
}
