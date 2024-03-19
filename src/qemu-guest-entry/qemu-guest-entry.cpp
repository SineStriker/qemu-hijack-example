#include "qemu-guest-entry.h"

#include "syscall_helper.h"

enum MagicCallType {
    LoadLibrary,
    FreeLibrary,
    GetProcAddress,
    GetErrorMessage,
    CallNativeProc,

    UserCall = 0x1000,
};

void *qge_LoadLibrary(const char *path, int flags) {
    void *a[] = {
        const_cast<char *>(path),
        &flags,
    };
    return (void *) syscall2(MagicCallNumber, (void *) LoadLibrary, a);
}

void qge_FreeLibrary(void *handle) {
    void *a[] = {
        handle,
    };
    syscall2(MagicCallNumber, (void *) FreeLibrary, a);
}

void *qge_GetProcAddress(void *handle, const char *name) {
    void *a[] = {
        handle,
        const_cast<char *>(name),
    };
    return (void *) syscall2(MagicCallNumber, (void *) GetProcAddress, a);
}

char *qge_GetErrorMessage() {
    return (char *) syscall1(MagicCallNumber, (void *) GetErrorMessage);
}

int qge_CallNativeProc(void *func, void *args, void *ret) {
    void *a[] = {
        func,
        args,
        ret,
    };
    return (int) syscall2(MagicCallNumber, (void *) CallNativeProc, a);
}