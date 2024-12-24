#include <common.h>

#include <wii/os/OSTime.h>

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

extern "C" {

int __syscall_gettod_r(struct _reent *ptr, struct timeval *tp, struct timezone *tz)
{
    (void)ptr;
	u64 now;
	if (tp != NULL) {
		now = wii::os::OSGetTime();
		tp->tv_sec = OSTicksToSeconds(now) + 946684800;
		tp->tv_usec = OSTicksToMicroseconds(now);
	}
	if (tz != NULL) {
		tz->tz_minuteswest = 0;
		tz->tz_dsttime = 0;

	}
	return 0;
}

}