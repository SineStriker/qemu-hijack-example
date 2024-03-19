#include "fakesdl.h"

#include <cstdlib>
#include <cstdio>

#include <dlfcn.h>

#include <qemu-guest-entry.h>

#include "wrapper_helper.h"

namespace {

    constexpr const char SDL_LIBRARY_NAME[] = "libfakesdl2.so";

    struct DynamicApis {

        static const DynamicApis &instance() {
            static const DynamicApis inst;
            return inst;
        }

        // #define API_HELPER(NAME) decltype(&::NAME) p##NAME = nullptr

#define API_HELPER(NAME) void *p##NAME = nullptr

        API_HELPER(SDL_memset);
        API_HELPER(SDL_Init);
        API_HELPER(SDL_Quit);
        API_HELPER(SDL_Delay);
        API_HELPER(SDL_GetError);
        API_HELPER(SDL_GetVersion);
        API_HELPER(SDL_LogSetPriority);
        API_HELPER(SDL_LogError);
        API_HELPER(SDL_Log);
        API_HELPER(SDL_CreateMutex);
        API_HELPER(SDL_DestroyMutex);
        API_HELPER(SDL_LockMutex);
        API_HELPER(SDL_UnlockMutex);
        API_HELPER(SDL_PushEvent);
        API_HELPER(SDL_PollEvent);
        API_HELPER(SDL_MixAudioFormat);
        API_HELPER(SDL_GetNumAudioDevices);
        API_HELPER(SDL_GetAudioDeviceName);
        API_HELPER(SDL_OpenAudio);
        API_HELPER(SDL_OpenAudioDevice);
        API_HELPER(SDL_GetNumAudioDrivers);
        API_HELPER(SDL_GetAudioDriver);
        API_HELPER(SDL_GetCurrentAudioDriver);
        API_HELPER(SDL_PauseAudio);
        API_HELPER(SDL_PauseAudioDevice);
        API_HELPER(SDL_CloseAudioDevice);

#undef API_HELPER

    private:
        DynamicApis() {

            auto dll = qge_LoadLibrary(SDL_LIBRARY_NAME, RTLD_NOW);
            if (!dll) {
                printf("FakeSDL: Load %s error: %s\n", SDL_LIBRARY_NAME, qge_GetErrorMessage());
                std::abort();
            }

            _hDll = dll;

            printf("Library Handle: %p\n", dll);

#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(qge_GetProcAddress(dll, "my_" #NAME));       \
        if (!p##NAME) {                                                                            \
            printf("FakeSDL: API %s cannot be resolved!\n", #NAME);                                \
            std::abort();                                                                          \
        }                                                                                          \
        printf("Resolve %s: %p\n", #NAME, p##NAME);                                                \
    }

            API_HELPER(SDL_memset);
            API_HELPER(SDL_Init);
            API_HELPER(SDL_Quit);
            API_HELPER(SDL_Delay);
            API_HELPER(SDL_GetError);
            API_HELPER(SDL_GetVersion);
            API_HELPER(SDL_LogSetPriority);
            API_HELPER(SDL_LogError);
            API_HELPER(SDL_Log);
            API_HELPER(SDL_CreateMutex);
            API_HELPER(SDL_DestroyMutex);
            API_HELPER(SDL_LockMutex);
            API_HELPER(SDL_UnlockMutex);
            API_HELPER(SDL_PushEvent);
            API_HELPER(SDL_PollEvent);
            API_HELPER(SDL_MixAudioFormat);
            API_HELPER(SDL_GetNumAudioDevices);
            API_HELPER(SDL_GetAudioDeviceName);
            API_HELPER(SDL_OpenAudio);
            API_HELPER(SDL_OpenAudioDevice);
            API_HELPER(SDL_GetNumAudioDrivers);
            API_HELPER(SDL_GetAudioDriver);
            API_HELPER(SDL_GetCurrentAudioDriver);
            API_HELPER(SDL_PauseAudio);
            API_HELPER(SDL_PauseAudioDevice);
            API_HELPER(SDL_CloseAudioDevice);

#undef API_HELPER
        }

        ~DynamicApis() {
            qge_FreeLibrary(_hDll);
        }

        void *_hDll;
    };

}

void *SDL_memset(void *dst, int c, size_t len) {
    void *a[] = {
        to_ptr(dst),
        to_ptr(c),
        to_ptr(len),
    };
    void *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_memset, a, &ret);
    return ret;
}

int SDL_Init(Uint32 flags) {
    void *a[] = {
        to_ptr(flags),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_Init, a, &ret);
    return ret;
}

void SDL_Quit(void) {
    qge_CallNativeProc(DynamicApis::instance().pSDL_Quit, nullptr, nullptr);
}

void SDL_Delay(Uint32 ms) {
    void *a[] = {
        to_ptr(ms),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_Delay, a, nullptr);
}

const char *SDL_GetError(void) {
    char *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetError, nullptr, &ret);
    return ret;
}

void SDL_GetVersion(SDL_version *ver) {
    void *a[] = {
        to_ptr(ver),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetVersion, a, nullptr);
}

void SDL_LogSetPriority(int category, SDL_LogPriority priority) {
    void *a[] = {
        to_ptr(category),
        to_ptr(priority),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_LogSetPriority, a, nullptr);
}

void SDL_LogError(int category, const char *fmt, ...) {
}

void SDL_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...) {
}

SDL_mutex *SDL_CreateMutex(void) {
    SDL_mutex *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_CreateMutex, nullptr, &ret);
    return ret;
}

void SDL_DestroyMutex(SDL_mutex *mutex) {
    void *a[] = {
        to_ptr(mutex),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_DestroyMutex, a, nullptr);
}

int SDL_LockMutex(SDL_mutex *mutex) {
    void *a[] = {
        to_ptr(mutex),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_LockMutex, a, &ret);
    return ret;
}

int SDL_UnlockMutex(SDL_mutex *mutex) {
    void *a[] = {
        to_ptr(mutex),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_UnlockMutex, a, &ret);
    return ret;
}

int SDL_PushEvent(SDL_Event *event) {
    void *a[] = {
        to_ptr(event),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_PushEvent, a, &ret);
    return ret;
}

int SDL_PollEvent(SDL_Event *event) {
    void *a[] = {
        to_ptr(event),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_PollEvent, a, &ret);
    return ret;
}

void SDL_MixAudioFormat(Uint8 *dst, const Uint8 *src, SDL_AudioFormat format, Uint32 len,
                        int volume) {
    void *a[] = {
        to_ptr(dst), to_ptr(src), to_ptr(format), to_ptr(len), to_ptr(volume),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_MixAudioFormat, a, nullptr);
}

int SDL_GetNumAudioDevices(int iscapture) {
    void *a[] = {
        to_ptr(iscapture),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetNumAudioDevices, a, &ret);
    return ret;
}

const char *SDL_GetAudioDeviceName(int index, int iscapture) {
    void *a[] = {
        to_ptr(index),
        to_ptr(iscapture),
    };
    char *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetAudioDeviceName, a, &ret);
    return ret;
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
    void *a[] = {
        to_ptr(desired),
        to_ptr(obtained),
    };
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_OpenAudio, a, &ret);
    return ret;
}

SDL_AudioDeviceID SDL_OpenAudioDevice(const char *device, int iscapture,
                                      const SDL_AudioSpec *desired, SDL_AudioSpec *obtained,
                                      int allowed_changes) {
    void *a[] = {
        to_ptr(device),   to_ptr(iscapture),       to_ptr(desired),
        to_ptr(obtained), to_ptr(allowed_changes),
    };
    SDL_AudioDeviceID ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_OpenAudioDevice, a, &ret);
    return ret;
}

int SDL_GetNumAudioDrivers(void) {
    int ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetNumAudioDrivers, nullptr, &ret);
    return ret;
}

const char *SDL_GetAudioDriver(int index) {
    void *a[] = {
        to_ptr(index),
    };
    char *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetAudioDriver, a, &ret);
    return ret;
}

const char *SDL_GetCurrentAudioDriver(void) {
    char *ret{};
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetCurrentAudioDriver, nullptr, &ret);
    return ret;
}

void SDL_PauseAudio(int pause_on) {
    void *a[] = {
        to_ptr(pause_on),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_PauseAudio, a, nullptr);
}

void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on) {
    void *a[] = {
        to_ptr(dev),
        to_ptr(pause_on),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_PauseAudioDevice, a, nullptr);
}

void SDL_CloseAudioDevice(SDL_AudioDeviceID dev) {
    void *a[] = {
        to_ptr(dev),
    };
    qge_CallNativeProc(DynamicApis::instance().pSDL_CloseAudioDevice, a, nullptr);
}