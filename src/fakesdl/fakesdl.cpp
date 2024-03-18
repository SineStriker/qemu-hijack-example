#include "fakesdl.h"

#include <cstdlib>
#include <cstdio>

#include <dlfcn.h>

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
                printf("Load %s error: %s\n", SDL_LIBRARY_NAME, dlerror());
                std::abort();
            }

#define API_HELPER(NAME)                                                                           \
    {                                                                                              \
        p##NAME = reinterpret_cast<decltype(p##NAME)>(dlsym(dll, #NAME));                          \
        if (!p##NAME) {                                                                            \
            printf("API %s cannot be resolved!\n", #NAME);                                         \
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
    };

}

void *SDL_memset(void *dst, int c, size_t len) {
    return DynamicApis::instance().pSDL_memset(dst, c, len);
}

int SDL_Init(Uint32 flags) {
    return DynamicApis::instance().pSDL_Init(flags);
}

void SDL_Quit(void) {
    return DynamicApis::instance().pSDL_Quit();
}

void SDL_Delay(Uint32 ms) {
    return DynamicApis::instance().pSDL_Delay(ms);
}

const char *SDL_GetError(void) {
    return DynamicApis::instance().pSDL_GetError();
}

void SDL_GetVersion(SDL_version *ver) {
    return DynamicApis::instance().pSDL_GetVersion(ver);
}

void SDL_LogSetPriority(int category, SDL_LogPriority priority) {
    return DynamicApis::instance().pSDL_LogSetPriority(category, priority);
}

void SDL_LogError(int category, const char *fmt, ...) {
}

void SDL_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...) {
}

SDL_mutex *SDL_CreateMutex(void) {
    return DynamicApis::instance().pSDL_CreateMutex();
}

void SDL_DestroyMutex(SDL_mutex *mutex) {
    return DynamicApis::instance().pSDL_DestroyMutex(mutex);
}

int SDL_LockMutex(SDL_mutex *mutex) {
    return DynamicApis::instance().pSDL_LockMutex(mutex);
}

int SDL_UnlockMutex(SDL_mutex *mutex) {
    return DynamicApis::instance().pSDL_UnlockMutex(mutex);
}

int SDL_PushEvent(SDL_Event *event) {
    return DynamicApis::instance().pSDL_PushEvent(event);
}

int SDL_PollEvent(SDL_Event *event) {
    return DynamicApis::instance().pSDL_PollEvent(event);
}

void SDL_MixAudioFormat(Uint8 *dst, const Uint8 *src, SDL_AudioFormat format, Uint32 len,
                        int volume) {
    return DynamicApis::instance().pSDL_MixAudioFormat(dst, src, format, len, volume);
}

int SDL_GetNumAudioDevices(int iscapture) {
    return DynamicApis::instance().pSDL_GetNumAudioDevices(iscapture);
}

const char *SDL_GetAudioDeviceName(int index, int iscapture) {
    return DynamicApis::instance().pSDL_GetAudioDeviceName(index, iscapture);
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
    return DynamicApis::instance().pSDL_OpenAudio(desired, obtained);
}

SDL_AudioDeviceID SDL_OpenAudioDevice(const char *device, int iscapture,
                                      const SDL_AudioSpec *desired, SDL_AudioSpec *obtained,
                                      int allowed_changes) {
    return DynamicApis::instance().pSDL_OpenAudioDevice(device, iscapture, desired, obtained,
                                                        allowed_changes);
}

int SDL_GetNumAudioDrivers(void) {
    return DynamicApis::instance().pSDL_GetNumAudioDrivers();
}

const char *SDL_GetAudioDriver(int index) {
    return DynamicApis::instance().pSDL_GetAudioDriver(index);
}

const char *SDL_GetCurrentAudioDriver(void) {
    return DynamicApis::instance().pSDL_GetCurrentAudioDriver();
}

void SDL_PauseAudio(int pause_on) {
    return DynamicApis::instance().pSDL_PauseAudio(pause_on);
}

void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on) {
    return DynamicApis::instance().pSDL_PauseAudioDevice(dev, pause_on);
}

void SDL_CloseAudioDevice(SDL_AudioDeviceID dev) {
    return DynamicApis::instance().pSDL_CloseAudioDevice(dev);
}