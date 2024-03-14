#include <iostream>

#define SDL_MAIN_HANDLED

_EXTERN_C

#include "SDL.h"

_END_EXTERN_C

enum SDL_UserEventType {
    SDL_EVENT_BUFFER_END = SDL_USEREVENT + 1,
};

class SDLPlaybackData {
public:
    // Playback Exchange Data
    uint8_t *audio_chunk;
    uint32_t audio_len;
    uint8_t *audio_pos;

    // Constants
    size_t buf_size;
    uint16_t fmt;

    SDLPlaybackData() {
        audio_chunk = nullptr;
        audio_len = 0;
        audio_pos = nullptr;
        buf_size = 0;
        fmt = 0;

        m = SDL_CreateMutex();
    }

    ~SDLPlaybackData() {
        SDL_DestroyMutex(m);
    }

    int lock() {
        return SDL_LockMutex(m);
    }

    int unlock() {
        return SDL_UnlockMutex(m);
    }

protected:
    SDL_mutex *m;
};

void notifyGetAudioFrame() {
    SDL_Event sdlEvent;
    sdlEvent.type = SDL_EVENT_BUFFER_END;
    SDL_PushEvent(&sdlEvent);
}

//回调函数，音频设备需要更多数据的时候会调用该回调函数
void read_audio_data(void *udata, Uint8 *stream, int len) {
    auto args = (SDLPlaybackData *) udata;

    // 上锁
    args->lock();

    SDL_memset(stream, 0, len);
    if (args->audio_len > 0) {

        len = std::min<int>(len, args->audio_len);

        // 将缓冲区中的声音写入流
        SDL_MixAudioFormat(stream, args->audio_pos, args->fmt, len, SDL_MIX_MAXVOLUME);

        args->audio_pos += len;
        args->audio_len -= len;

        // 判断是否完毕
        if (args->audio_len == 0) {
            notifyGetAudioFrame();
        }
    }

    // 放锁
    args->unlock();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <audio file>\n", argv[0]);
        return 0;
    }
    char *input_file = argv[1];

    SDL_version ver;
    SDL_GetVersion(&ver);
    std::cout << int(ver.major) << "," << int(ver.minor) << "," << int(ver.patch) << std::endl;

    printf("\n");

    //设置显示application的log信息
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    //设置sdl要初始化的模块
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "couldn't initialize SDL:%s\n", SDL_GetError());
        return -1;
    }

    SDL_Log("available audio drivers");
    //打印音频驱动
    for (int i = 0; i < SDL_GetNumAudioDrivers(); i++) {
        SDL_Log("%i:%s", i, SDL_GetAudioDriver(i));
    }

    //查看当前使用的音频驱动
    SDL_Log("Using audio driver: %s\n", SDL_GetCurrentAudioDriver());

    printf("\n");

    SDL_Log("available audio devices");

    //打印音频设备
    int n_devs = SDL_GetNumAudioDevices(0);
    for (int i = 0; i < SDL_GetNumAudioDevices(0); i++) {
        SDL_Log("%i: %s", i, SDL_GetAudioDeviceName(i, 0));
    }

    SDLPlaybackData args;
    args.buf_size = 4096;
    args.fmt = AUDIO_S16SYS;

    // 播放
    SDL_AudioSpec spec;
    spec.freq = 44100; //根据你录制的PCM采样率决定
    spec.format = args.fmt;
    spec.channels = 2; //单声道
    spec.silence = 0;
    spec.samples = 1024; //缓冲区字节数/单个采样字节数/声道数
    spec.callback = read_audio_data;
    spec.userdata = &args;

#define USE_DEFAULT_DEVICE 0

#if USE_DEFAULT_DEVICE
    // 使用默认音频设备
    if (SDL_OpenAudio(&spec, NULL) < 0) {
        printf("can't open audio device.\n");
        return -1;
    }
#else
    // 选择音频设备
    int idx;
    do {
        std::cin >> idx;
    } while (idx >= n_devs || idx < 0);

    const char *dev_name = SDL_GetAudioDeviceName(idx, 0);
    SDL_AudioDeviceID id;

    //不允许任何格式改变
    if ((id = SDL_OpenAudioDevice(dev_name, 0, &spec, NULL, 0)) == 0) {
        printf("can't open audio device.\n");
        return -1;
    }
    SDL_Log("Device id: %d.\n", id);
#endif

    FILE *fp = fopen(input_file, "rb+");
    if (fp == NULL) {
        printf("cannot open this file\n");
        return -1;
    }

    char *pcm_buffer = (char *) malloc(args.buf_size);

    //播放
#if USE_DEFAULT_DEVICE
    SDL_PauseAudio(0);
#else
    SDL_PauseAudioDevice(id, 0);
#endif

    printf("Play\n");

    // 第一次事件
    notifyGetAudioFrame();

    while (true) {
        SDL_Event e;
        bool over = false;

        // 不停地获取事件
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_BUFFER_END: {
                    // 上锁
                    args.lock();

                    if (fread(pcm_buffer, 1, args.buf_size, fp) != args.buf_size) {
                        // 从文件中读取数据，剩下的就交给音频设备去完成了
                        // 它播放完一段数据后会执行回调函数，获取等多的数据
                        over = true;
                        break;
                    }
                    // 重置缓冲区
                    args.audio_chunk = (Uint8 *) pcm_buffer;
                    args.audio_len = args.buf_size; // 长度为读出数据长度，在read_audio_data中做减法
                    args.audio_pos = args.audio_chunk; // 设置当前位置为缓冲区头部

                    // 放锁
                    args.unlock();
                    break;
                }
                case SDL_AUDIODEVICEREMOVED: {
                    auto dev = (SDL_AudioDeviceID) e.adevice.which;
                    if (dev == id) {
                        printf("Audio device has been removed.\n");
                        over = true;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        if (over) {
            break;
        }

        SDL_Delay(1);
    }

    free(pcm_buffer);

    SDL_CloseAudioDevice(id);
    SDL_Quit();

    fclose(fp);

    printf("OK\n");

    return 0;
}
