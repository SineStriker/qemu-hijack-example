#include "fakesdl2.h"

#include <cstdlib>
#include <cstdio>

#include <dlfcn.h>

#include "call_helper.h"

#include "../fakesdl/fakesdl.h"

namespace {

    constexpr const char SDL_LIBRARY_NAME[] = "libSDL2.so";

    struct DynamicApis {

        static const DynamicApis &instance() {
            static const DynamicApis inst;
            return inst;
        }

#define API_HELPER(NAME) decltype(&::NAME) p##NAME = nullptr

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

            auto dll = dlopen(SDL_LIBRARY_NAME, RTLD_NOW);
            if (!dll) {
                printf("FakeSDL2: Load %s error: %s\n", SDL_LIBRARY_NAME, dlerror());
                std::abort();
            }

            _hDll = dll;

#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(dlsym(dll, #NAME));                          \
        if (!p##NAME) {                                                                            \
            printf("FakeSDL2: API %s cannot be resolved!\n", #NAME);                               \
            std::abort();                                                                          \
        }                                                                                          \
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
            dlclose(_hDll);
        }

        void *_hDll;
    };

}

void my_SDL_memset(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_memset, (void **) args, ret);
}
void my_SDL_Init(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_Init, (void **) args, ret);
}
void my_SDL_Quit(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_Quit, (void **) args, ret);
}
void my_SDL_Delay(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_Delay, (void **) args, ret);
}
void my_SDL_GetError(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetError, (void **) args, ret);
}
void my_SDL_GetVersion(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetVersion, (void **) args, ret);
}
void my_SDL_LogSetPriority(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_LogSetPriority, (void **) args, ret);
}
void my_SDL_LogError(void *args, void *ret) {
}
void my_SDL_Log(void *args, void *ret) {
}
void my_SDL_CreateMutex(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_CreateMutex, (void **) args, ret);
}
void my_SDL_DestroyMutex(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_DestroyMutex, (void **) args, ret);
}
void my_SDL_LockMutex(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_LockMutex, (void **) args, ret);
}
void my_SDL_UnlockMutex(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_UnlockMutex, (void **) args, ret);
}
void my_SDL_PushEvent(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_PushEvent, (void **) args, ret);
}
void my_SDL_PollEvent(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_PollEvent, (void **) args, ret);
}
void my_SDL_MixAudioFormat(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_MixAudioFormat, (void **) args, ret);
}
void my_SDL_GetNumAudioDevices(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetNumAudioDevices, (void **) args, ret);
}
void my_SDL_GetAudioDeviceName(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetAudioDeviceName, (void **) args, ret);
}
void my_SDL_OpenAudio(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_OpenAudio, (void **) args, ret);
}
void my_SDL_OpenAudioDevice(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_OpenAudioDevice, (void **) args, ret);
}
void my_SDL_GetNumAudioDrivers(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetNumAudioDrivers, (void **) args, ret);
}
void my_SDL_GetAudioDriver(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetAudioDriver, (void **) args, ret);
}
void my_SDL_GetCurrentAudioDriver(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_GetCurrentAudioDriver, (void **) args, ret);
}
void my_SDL_PauseAudio(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_PauseAudio, (void **) args, ret);
}
void my_SDL_PauseAudioDevice(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_PauseAudioDevice, (void **) args, ret);
}
void my_SDL_CloseAudioDevice(void *args, void *ret) {
    call_function2(DynamicApis::instance().pSDL_CloseAudioDevice, (void **) args, ret);
}