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
  {                                                                                                \
    p##NAME = reinterpret_cast<decltype(p##NAME)>(qge_GetProcAddress(dll, "my_" #NAME));           \
    if (!p##NAME) {                                                                                \
      printf("FakeSDL: API %s cannot be resolved!\n", #NAME);                                      \
      std::abort();                                                                                \
    }                                                                                              \
    printf("Resolve %s: %p\n", #NAME, p##NAME);                                                    \
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
    auto ret = create_empty_ret(SDL_memset);
    auto a = get_addresses_of_parameters(dst, c, len);
    qge_CallNativeProc(DynamicApis::instance().pSDL_memset, a.data(), &ret);
    return ret;
}

int SDL_Init(Uint32 flags) {
    auto ret = create_empty_ret(SDL_Init);
    auto a = get_addresses_of_parameters(flags);
    qge_CallNativeProc(DynamicApis::instance().pSDL_Init, a.data(), &ret);
    return ret;
}

void SDL_Quit(void) {
    qge_CallNativeProc(DynamicApis::instance().pSDL_Quit, nullptr, nullptr);
}

void SDL_Delay(Uint32 ms) {
    auto a = get_addresses_of_parameters(ms);
    qge_CallNativeProc(DynamicApis::instance().pSDL_Delay, a.data(), nullptr);
}

const char *SDL_GetError(void) {
    auto ret = create_empty_ret(SDL_GetError);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetError, nullptr, &ret);
    return ret;
}

void SDL_GetVersion(SDL_version *ver) {
    auto a = get_addresses_of_parameters(ver);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetVersion, a.data(), nullptr);
}

void SDL_LogSetPriority(int category, SDL_LogPriority priority) {
    auto a = get_addresses_of_parameters(category, priority);
    qge_CallNativeProc(DynamicApis::instance().pSDL_LogSetPriority, a.data(), nullptr);
}

void SDL_LogError(int category, const char *fmt, ...) {
}

void SDL_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...) {
}

SDL_mutex *SDL_CreateMutex(void) {
    auto ret = create_empty_ret(SDL_CreateMutex);
    qge_CallNativeProc(DynamicApis::instance().pSDL_CreateMutex, nullptr, &ret);
    return ret;
}

void SDL_DestroyMutex(SDL_mutex *mutex) {
    auto a = get_addresses_of_parameters(mutex);
    qge_CallNativeProc(DynamicApis::instance().pSDL_DestroyMutex, a.data(), nullptr);
}

int SDL_LockMutex(SDL_mutex *mutex) {
    auto ret = create_empty_ret(SDL_LockMutex);
    auto a = get_addresses_of_parameters(mutex);
    qge_CallNativeProc(DynamicApis::instance().pSDL_LockMutex, a.data(), &ret);
    return ret;
}

int SDL_UnlockMutex(SDL_mutex *mutex) {
    auto ret = create_empty_ret(SDL_UnlockMutex);
    auto a = get_addresses_of_parameters(mutex);
    qge_CallNativeProc(DynamicApis::instance().pSDL_UnlockMutex, a.data(), &ret);
    return ret;
}

int SDL_PushEvent(SDL_Event *event) {
    auto ret = create_empty_ret(SDL_PushEvent);
    auto a = get_addresses_of_parameters(event);
    qge_CallNativeProc(DynamicApis::instance().pSDL_PushEvent, a.data(), &ret);
    return ret;
}

int SDL_PollEvent(SDL_Event *event) {
    auto ret = create_empty_ret(SDL_PollEvent);
    auto a = get_addresses_of_parameters(event);
    qge_CallNativeProc(DynamicApis::instance().pSDL_PollEvent, a.data(), &ret);
    return ret;
}

void SDL_MixAudioFormat(Uint8 *dst, const Uint8 *src, SDL_AudioFormat format, Uint32 len,
                        int volume) {
    auto a = get_addresses_of_parameters(dst, src, format, len, volume);
    qge_CallNativeProc(DynamicApis::instance().pSDL_MixAudioFormat, a.data(), nullptr);
}

int SDL_GetNumAudioDevices(int iscapture) {
    auto ret = create_empty_ret(SDL_GetNumAudioDevices);
    auto a = get_addresses_of_parameters(iscapture);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetNumAudioDevices, a.data(), &ret);
    return ret;
}

const char *SDL_GetAudioDeviceName(int index, int iscapture) {
    auto ret = create_empty_ret(SDL_GetAudioDeviceName);
    auto a = get_addresses_of_parameters(index, iscapture);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetAudioDeviceName, a.data(), &ret);
    return ret;
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained) {
    auto ret = create_empty_ret(SDL_OpenAudio);
    auto a = get_addresses_of_parameters(desired, obtained);
    qge_CallNativeProc(DynamicApis::instance().pSDL_OpenAudio, a.data(), &ret);
    return ret;
}

SDL_AudioDeviceID SDL_OpenAudioDevice(const char *device, int iscapture,
                                      const SDL_AudioSpec *desired, SDL_AudioSpec *obtained,
                                      int allowed_changes) {
    auto ret = create_empty_ret(SDL_OpenAudioDevice);
    auto a = get_addresses_of_parameters(device, iscapture, desired, obtained, allowed_changes);
    qge_CallNativeProc(DynamicApis::instance().pSDL_OpenAudioDevice, a.data(), &ret);
    return ret;
}

int SDL_GetNumAudioDrivers(void) {
    auto ret = create_empty_ret(SDL_GetNumAudioDrivers);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetNumAudioDrivers, nullptr, &ret);
    return ret;
}

const char *SDL_GetAudioDriver(int index) {
    auto ret = create_empty_ret(SDL_GetAudioDriver);
    auto a = get_addresses_of_parameters(index);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetAudioDriver, a.data(), &ret);
    return ret;
}

const char *SDL_GetCurrentAudioDriver(void) {
    auto ret = create_empty_ret(SDL_GetCurrentAudioDriver);
    qge_CallNativeProc(DynamicApis::instance().pSDL_GetCurrentAudioDriver, nullptr, &ret);
    return ret;
}

void SDL_PauseAudio(int pause_on) {
    auto a = get_addresses_of_parameters(pause_on);
    qge_CallNativeProc(DynamicApis::instance().pSDL_PauseAudio, a.data(), nullptr);
}

void SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on) {
    auto a = get_addresses_of_parameters(dev, pause_on);
    qge_CallNativeProc(DynamicApis::instance().pSDL_PauseAudioDevice, a.data(), nullptr);
}

void SDL_CloseAudioDevice(SDL_AudioDeviceID dev) {
    auto a = get_addresses_of_parameters(dev);
    qge_CallNativeProc(DynamicApis::instance().pSDL_CloseAudioDevice, a.data(), nullptr);
}