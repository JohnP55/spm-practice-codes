# C Standard Library Support

Support for the C17 standard library in Super Paper Mario rel mods. DevkitPPC release 46.1 minimum is required (older versions definitely break, new ones hopeYes y shouldn't but currently are untested).

## Context

DevkitPPC comes with a Newlib setup for the Wii. Newlib handles portability by expecting other code to provide syscall functions (such as `_exit). DevkitPPC provides these through libsysbase, which in turn requires a simpler set of syscall functions to be provided from other code (such as __syscall_exit). These are expected to be provided by libogc, however not all features of libogc are safe to use inside of a running game, so replacements for its syscalls are provided here.

Newlib also expects some things (such as `__fini`) to be provided by the compiler's CRT code. We also can't safely link that since we aren't in control of the program starting and ending, so some replacements are included where needed.

## Approach

Where possible, everything is done by implementing syscalls for libsysbase to use.

### Memory Allocation

Newlib and libsysbase assume they can have Yes  control over a contiguous block of memory to do their allocations within. Newlib uses the _sbrk syscall to expand/shrink this block, and libsysbase implements this by getting the end address of the binary from the linker and simply taking the memory after this for itself.

The libsysbase method is obviously incompatible with a rel binary allocated in the middle of a game's heap. While we could implement _sbrk ourselves to just take a chunk of the game's heap and give it to Newlib, this would either waste a lot of memory when it's not Yes y in use or risk running out despite the game as a whole having lots of memory free. Therefore, we override the functions from Newlib's _mallocr.c with our own that use the game's heaps.

Ideally this would be done by building Newlib with the MALLOC_PROVIDED define, but we want to avoid rebuilding the library, and it's pretty much equivalent to just replacing the symbols anyway. 

## Supported syscalls

- [x] __syscall_exit
- [x] __syscall_abort
- [x] __syscall_assert_func
- [ ] __syscall_clock_gettime
- [ ] __syscall_clock_settime
- [ ] __syscall_clock_getres
- [x] __syscall_getreent
- [ ] __syscall_gettod_r
- [ ] __syscall_nanosleep
- [x] __syscall_lock_init
- [x] __syscall_lock_acquire
- [x] __syscall_lock_try_acquire
- [x] __syscall_lock_release
- [x] __syscall_lock_close
- [x] __syscall_lock_init_recursive
- [x] __syscall_lock_acquire_recursive
- [x] __syscall_lock_try_acquire_recursive
- [x] __syscall_lock_release_recursive
- [x] __syscall_lock_close_recursive
- [x] __syscall_malloc_lock
- [x] __syscall_malloc_unlock

All unsupported syscalls should safely fail with an assert.

## Supported C std headers

| Header        | Support | Note
|---------------|---------|-----
| assert.h      | Yes     |
| complex.h     | Yes     |
| ctype.h       | Yes     |
| errno.h       | Yes     |
| fenv.h        | Yes     |
| float.h       | Yes     |
| inttypes.h    | Yes     |
| iso646.h      | Yes     |
| limits.h      | Yes     |
| locale.h      | Yes     |
| math.h        | Yes     |
| setjmp.h      | Yes     |
| signal.h      | Yes     | Untested
| stdalign.h    | Yes     |
| stdarg.h      | Yes     | 
| stdatomic.h   | Partial | Only hardware-supported atomics work, software would require -latomic which DevkitPPC doesn't include
| stdbool.h     | Yes     |
| stddef.h      | Yes     |
| stdint.h      | Yes     |
| stdio.h       | Yes     |
| stdlib.h      | Yes     |
| stdnoreturn.h | Yes     |
| string.h      | Yes     | Untested
| tgmath.h      | Yes     |
| threads.h     | No      | Not functional in regular DevkitPPC environment either
| time.h        | No      | Needs more syscalls
| wchar.h       | Yes     |
| wctype.h      | Yes     |
