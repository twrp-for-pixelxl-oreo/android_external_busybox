/*
 * Copyright 2012, Denys Vlasenko
 *
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */

//kbuild:lib-y += missing_syscalls.o

/*#include <linux/timex.h> - for struct timex, but may collide with <time.h> */
#include <sys/syscall.h>
#include "libbb.h"

#ifndef __NR_shmget
#define __NR_shmget 29
#endif

#ifndef __NR_shmat
#define __NR_shmat 30
#endif

#ifndef __NR_shmctl
#define __NR_shmctl 31
#endif

#ifndef __NR_semget
#define __NR_semget 64
#endif

#ifndef __NR_semop
#define __NR_semop 65
#endif

#ifndef __NR_semctl
#define __NR_semctl 66
#endif

#ifndef __NR_shmdt
#define __NR_shmdt 67
#endif

#ifndef __NR_msgget
#define __NR_msgget 68
#endif

#ifndef __NR_msgsnd
#define __NR_msgsnd 69
#endif

#ifndef __NR_msgrcv
#define __NR_msgrcv 70
#endif

#ifndef __NR_msgctl
#define __NR_msgctl 71
#endif

#if defined(ANDROID) || defined(__ANDROID__)
pid_t getsid(pid_t pid)
{
	return syscall(__NR_getsid, pid);
}

int stime(const time_t *t)
{
	struct timeval tv;
	tv.tv_sec = *t;
	tv.tv_usec = 0;
	return settimeofday(&tv, NULL);
}

int sethostname(const char *name, size_t len)
{
	return syscall(__NR_sethostname, name, len);
}

struct timex;
int adjtimex(struct timex *buf)
{
	return syscall(__NR_adjtimex, buf);
}

int pivot_root(const char *new_root, const char *put_old)
{
	return syscall(__NR_pivot_root, new_root, put_old);
}
#endif
