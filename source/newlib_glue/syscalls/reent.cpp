#include <common.h>
#include <wii/os.h>

#include <sys/iosupport.h>
#include <map>

extern "C" {

std::map<wii::os::OSThread *, struct _reent*> reentMap;

struct _reent* __syscall_getreent()
{
    wii::os::OSThread * thread = wii::os::OSGetCurrentThread();

    if (reentMap.count(thread) == 0)
    {
        struct _reent * reent = new struct _reent();
        _REENT_INIT_PTR(reent);
        reentMap[thread] = reent;
    }

    return reentMap[thread];
}

}
