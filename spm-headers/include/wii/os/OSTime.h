#pragma once

#include <common.h>

CPP_WRAPPER(wii::os)

#define OSClockSpeed ((*(u32 *) 0x800000F8) / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OSClockSpeed / 1000))
#define OSMillisecondsToTicks(ms) ((ms) * (OSClockSpeed / 1000))
#define OSTicksToSeconds(ticks) ((ticks) / (OSClockSpeed))
#define OSSecondsToTicks(s) ((s) * (OSClockSpeed))
#define OSTicksToMicroseconds(x) (((x) * 8) / (OSClockSpeed / 125000))
#define OSMicrosecondsToTicks(x) ((x) * (OSClockSpeed / 125000) / 8)

typedef s64 OSTime;
typedef u32 OSTick;

OSTime OSGetTime();
OSTick OSGetTick();

UNKNOWN_FUNCTION(__OSGetSystemTime);
UNKNOWN_FUNCTION(__OSTimeToSystemTime);
UNKNOWN_FUNCTION(GetDates);
UNKNOWN_FUNCTION(OSTicksToCalendarTime);

CPP_WRAPPER_END()
