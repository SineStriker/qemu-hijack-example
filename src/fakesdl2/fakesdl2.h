#ifndef FAKESDL2_H
#define FAKESDL2_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DECLSPEC
#define DECLSPEC __attribute__((visibility("default")))
#endif

#define API_HELPER(X) DECLSPEC void my_##X(void *args, void *ret)

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

#ifdef __cplusplus
}
#endif

#endif // FAKESDL2_H
