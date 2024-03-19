#ifndef FAKESDL_H
#define FAKESDL_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DECLSPEC
#define DECLSPEC __attribute__((visibility("default")))
#endif

#define SDLCALL

//===========================================================================
// Common
typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;

#define SDL_INIT_AUDIO 0x00000010u

#define SDL_PRINTF_FORMAT_STRING
#define SDL_PRINTF_VARARG_FUNC(fmtargnumber)                                                       \
    __attribute__((format(__printf__, fmtargnumber, fmtargnumber + 1)))

#define SDL_OUT_BYTECAP(x)

extern DECLSPEC void *SDLCALL SDL_memset(SDL_OUT_BYTECAP(len) void *dst, int c, size_t len);

extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);
extern DECLSPEC void SDLCALL SDL_Quit(void);
//===========================================================================





//===========================================================================
// SDL_timer.h
extern DECLSPEC void SDLCALL SDL_Delay(Uint32 ms);
//===========================================================================





//===========================================================================
// SDL_error.h
extern DECLSPEC const char *SDLCALL SDL_GetError(void);
//===========================================================================





//===========================================================================
// SDL_version.h
typedef struct SDL_version {
    Uint8 major; /**< major version */
    Uint8 minor; /**< minor version */
    Uint8 patch; /**< update version */
} SDL_version;

extern DECLSPEC void SDLCALL SDL_GetVersion(SDL_version *ver);
//===========================================================================





//===========================================================================
// SDL_log.h
typedef enum {
    SDL_LOG_CATEGORY_APPLICATION,
    SDL_LOG_CATEGORY_ERROR,
    SDL_LOG_CATEGORY_ASSERT,
    SDL_LOG_CATEGORY_SYSTEM,
    SDL_LOG_CATEGORY_AUDIO,
    SDL_LOG_CATEGORY_VIDEO,
    SDL_LOG_CATEGORY_RENDER,
    SDL_LOG_CATEGORY_INPUT,
    SDL_LOG_CATEGORY_TEST,

    /* Reserved for future SDL library use */
    SDL_LOG_CATEGORY_RESERVED1,
    SDL_LOG_CATEGORY_RESERVED2,
    SDL_LOG_CATEGORY_RESERVED3,
    SDL_LOG_CATEGORY_RESERVED4,
    SDL_LOG_CATEGORY_RESERVED5,
    SDL_LOG_CATEGORY_RESERVED6,
    SDL_LOG_CATEGORY_RESERVED7,
    SDL_LOG_CATEGORY_RESERVED8,
    SDL_LOG_CATEGORY_RESERVED9,
    SDL_LOG_CATEGORY_RESERVED10,

    /* Beyond this point is reserved for application use, e.g.
       enum {
           MYAPP_CATEGORY_AWESOME1 = SDL_LOG_CATEGORY_CUSTOM,
           MYAPP_CATEGORY_AWESOME2,
           MYAPP_CATEGORY_AWESOME3,
           ...
       };
     */
    SDL_LOG_CATEGORY_CUSTOM
} SDL_LogCategory;

typedef enum {
    SDL_LOG_PRIORITY_VERBOSE = 1,
    SDL_LOG_PRIORITY_DEBUG,
    SDL_LOG_PRIORITY_INFO,
    SDL_LOG_PRIORITY_WARN,
    SDL_LOG_PRIORITY_ERROR,
    SDL_LOG_PRIORITY_CRITICAL,
    SDL_NUM_LOG_PRIORITIES
} SDL_LogPriority;

extern DECLSPEC void SDLCALL SDL_LogSetPriority(int category, SDL_LogPriority priority);
extern DECLSPEC void SDLCALL SDL_LogError(int category, SDL_PRINTF_FORMAT_STRING const char *fmt,
                                          ...) SDL_PRINTF_VARARG_FUNC(2);
extern DECLSPEC void SDLCALL SDL_Log(SDL_PRINTF_FORMAT_STRING const char *fmt, ...)
    SDL_PRINTF_VARARG_FUNC(1);
//===========================================================================





//===========================================================================
// SDL_mutex.h

#if defined(SDL_THREAD_SAFETY_ANALYSIS) && defined(__clang__) && (!defined(SWIG))
#  define SDL_THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))
#else
#  define SDL_THREAD_ANNOTATION_ATTRIBUTE__(x) /* no-op */
#endif

#define SDL_RELEASE(x) SDL_THREAD_ANNOTATION_ATTRIBUTE__(release_capability(x))

#define SDL_ACQUIRE(x) SDL_THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(x))

struct SDL_mutex;
typedef struct SDL_mutex SDL_mutex;

extern DECLSPEC SDL_mutex *SDLCALL SDL_CreateMutex(void);
extern DECLSPEC void SDLCALL SDL_DestroyMutex(SDL_mutex *mutex);
extern DECLSPEC int SDLCALL SDL_LockMutex(SDL_mutex *mutex) SDL_ACQUIRE(mutex);
extern DECLSPEC int SDLCALL SDL_UnlockMutex(SDL_mutex *mutex) SDL_RELEASE(mutex);
//===========================================================================





//===========================================================================
// SDL_events.h
typedef enum {
    SDL_FIRSTEVENT = 0, /**< Unused (do not remove) */

    /* Application events */
    SDL_QUIT = 0x100, /**< User-requested quit */

    /* These application events have special meaning on iOS, see README-ios.md for details */
    SDL_APP_TERMINATING,         /**< The application is being terminated by the OS
                                      Called on iOS in applicationWillTerminate()
                                      Called on Android in onDestroy()
                                 */
    SDL_APP_LOWMEMORY,           /**< The application is low on memory, free memory if possible.
                                      Called on iOS in applicationDidReceiveMemoryWarning()
                                      Called on Android in onLowMemory()
                                 */
    SDL_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
                                     Called on iOS in applicationWillResignActive()
                                     Called on Android in onPause()
                                */
    SDL_APP_DIDENTERBACKGROUND,  /**< The application did enter the background and may not get CPU
                                    for some time  Called on iOS in applicationDidEnterBackground()
                                      Called on Android in onPause()
                                 */
    SDL_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
                                     Called on iOS in applicationWillEnterForeground()
                                     Called on Android in onResume()
                                */
    SDL_APP_DIDENTERFOREGROUND,  /**< The application is now interactive
                                      Called on iOS in applicationDidBecomeActive()
                                      Called on Android in onResume()
                                 */

    SDL_LOCALECHANGED, /**< The user's locale preferences have changed. */

    /* Display events */
    SDL_DISPLAYEVENT = 0x150, /**< Display state change */

    /* Window events */
    SDL_WINDOWEVENT = 0x200, /**< Window state change */
    SDL_SYSWMEVENT,          /**< System specific event */

    /* Keyboard events */
    SDL_KEYDOWN = 0x300, /**< Key pressed */
    SDL_KEYUP,           /**< Key released */
    SDL_TEXTEDITING,     /**< Keyboard text editing (composition) */
    SDL_TEXTINPUT,       /**< Keyboard text input */
    SDL_KEYMAPCHANGED,   /**< Keymap changed due to a system event such as an
                              input language or keyboard layout change.
                         */
    SDL_TEXTEDITING_EXT, /**< Extended keyboard text editing (composition) */

    /* Mouse events */
    SDL_MOUSEMOTION = 0x400, /**< Mouse moved */
    SDL_MOUSEBUTTONDOWN,     /**< Mouse button pressed */
    SDL_MOUSEBUTTONUP,       /**< Mouse button released */
    SDL_MOUSEWHEEL,          /**< Mouse wheel motion */

    /* Joystick events */
    SDL_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
    SDL_JOYBALLMOTION,         /**< Joystick trackball motion */
    SDL_JOYHATMOTION,          /**< Joystick hat position change */
    SDL_JOYBUTTONDOWN,         /**< Joystick button pressed */
    SDL_JOYBUTTONUP,           /**< Joystick button released */
    SDL_JOYDEVICEADDED,        /**< A new joystick has been inserted into the system */
    SDL_JOYDEVICEREMOVED,      /**< An opened joystick has been removed */
    SDL_JOYBATTERYUPDATED,     /**< Joystick battery level change */

    /* Game controller events */
    SDL_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
    SDL_CONTROLLERBUTTONDOWN,         /**< Game controller button pressed */
    SDL_CONTROLLERBUTTONUP,           /**< Game controller button released */
    SDL_CONTROLLERDEVICEADDED,    /**< A new Game controller has been inserted into the system */
    SDL_CONTROLLERDEVICEREMOVED,  /**< An opened Game controller has been removed */
    SDL_CONTROLLERDEVICEREMAPPED, /**< The controller mapping was updated */
    SDL_CONTROLLERTOUCHPADDOWN,   /**< Game controller touchpad was touched */
    SDL_CONTROLLERTOUCHPADMOTION, /**< Game controller touchpad finger was moved */
    SDL_CONTROLLERTOUCHPADUP,     /**< Game controller touchpad finger was lifted */
    SDL_CONTROLLERSENSORUPDATE,   /**< Game controller sensor was updated */
    SDL_CONTROLLERUPDATECOMPLETE_RESERVED_FOR_SDL3,
    SDL_CONTROLLERSTEAMHANDLEUPDATED, /**< Game controller Steam handle has changed */

    /* Touch events */
    SDL_FINGERDOWN = 0x700,
    SDL_FINGERUP,
    SDL_FINGERMOTION,

    /* Gesture events */
    SDL_DOLLARGESTURE = 0x800,
    SDL_DOLLARRECORD,
    SDL_MULTIGESTURE,

    /* Clipboard events */
    SDL_CLIPBOARDUPDATE = 0x900, /**< The clipboard or primary selection changed */

    /* Drag and drop events */
    SDL_DROPFILE = 0x1000, /**< The system requests a file open */
    SDL_DROPTEXT,          /**< text/plain drag-and-drop event */
    SDL_DROPBEGIN,         /**< A new set of drops is beginning (NULL filename) */
    SDL_DROPCOMPLETE,      /**< Current set of drops is now complete (NULL filename) */

    /* Audio hotplug events */
    SDL_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
    SDL_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

    /* Sensor events */
    SDL_SENSORUPDATE = 0x1200, /**< A sensor was updated */

    /* Render events */
    SDL_RENDER_TARGETS_RESET =
        0x2000, /**< The render targets have been reset and their contents need to be updated */
    SDL_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

    /* Internal events */
    SDL_POLLSENTINEL = 0x7F00, /**< Signals the end of an event poll cycle */

    /** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
     *  and should be allocated with SDL_RegisterEvents()
     */
    SDL_USEREVENT = 0x8000,

    /**
     *  This last event is only for bounding internal arrays
     */
    SDL_LASTEVENT = 0xFFFF
} SDL_EventType;

typedef struct SDL_AudioDeviceEvent
{
    Uint32 type;        /**< ::SDL_AUDIODEVICEADDED, or ::SDL_AUDIODEVICEREMOVED */
    Uint32 timestamp;   /**< In milliseconds, populated using SDL_GetTicks() */
    Uint32 which;       /**< The audio device index for the ADDED event (valid until next SDL_GetNumAudioDevices() call), SDL_AudioDeviceID for the REMOVED event */
    Uint8 iscapture;    /**< zero if an output device, non-zero if a capture device. */
    Uint8 padding1;
    Uint8 padding2;
    Uint8 padding3;
} SDL_AudioDeviceEvent;

typedef union SDL_Event {
    Uint32 type;
    SDL_AudioDeviceEvent adevice;           /**< Audio device event data */

    Uint8 padding[sizeof(void *) <= 8 ? 56 : sizeof(void *) == 16 ? 64 : 3 * sizeof(void *)];
} SDL_Event;

extern DECLSPEC int SDLCALL SDL_PushEvent(SDL_Event *event);
extern DECLSPEC int SDLCALL SDL_PollEvent(SDL_Event *event);
//===========================================================================





//===========================================================================
// SDL_audio.h

/**
 *  \name Audio format flags
 *
 *  Defaults to LSB byte order.
 */
/* @{ */
#define AUDIO_U8     0x0008 /**< Unsigned 8-bit samples */
#define AUDIO_S8     0x8008 /**< Signed 8-bit samples */
#define AUDIO_U16LSB 0x0010 /**< Unsigned 16-bit samples */
#define AUDIO_S16LSB 0x8010 /**< Signed 16-bit samples */
#define AUDIO_U16MSB 0x1010 /**< As above, but big-endian byte order */
#define AUDIO_S16MSB 0x9010 /**< As above, but big-endian byte order */
#define AUDIO_U16    AUDIO_U16LSB
#define AUDIO_S16    AUDIO_S16LSB
/* @} */

/**
 *  \name int32 support
 */
/* @{ */
#define AUDIO_S32LSB 0x8020 /**< 32-bit integer samples */
#define AUDIO_S32MSB 0x9020 /**< As above, but big-endian byte order */
#define AUDIO_S32    AUDIO_S32LSB
/* @} */

/**
 *  \name float32 support
 */
/* @{ */
#define AUDIO_F32LSB 0x8120 /**< 32-bit floating point samples */
#define AUDIO_F32MSB 0x9120 /**< As above, but big-endian byte order */
#define AUDIO_F32    AUDIO_F32LSB
/* @} */

/**
 *  \name Native audio byte ordering
 */
/* @{ */
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#  define AUDIO_U16SYS AUDIO_U16LSB
#  define AUDIO_S16SYS AUDIO_S16LSB
#  define AUDIO_S32SYS AUDIO_S32LSB
#  define AUDIO_F32SYS AUDIO_F32LSB
#else
#  define AUDIO_U16SYS AUDIO_U16MSB
#  define AUDIO_S16SYS AUDIO_S16MSB
#  define AUDIO_S32SYS AUDIO_S32MSB
#  define AUDIO_F32SYS AUDIO_F32MSB
#endif

#define SDL_MIX_MAXVOLUME 128

typedef Uint16 SDL_AudioFormat;
typedef Uint32 SDL_AudioDeviceID;

typedef void(SDLCALL *SDL_AudioCallback)(void *userdata, Uint8 *stream, int len);

typedef struct SDL_AudioSpec {
    int freq;               /**< DSP frequency -- samples per second */
    SDL_AudioFormat format; /**< Audio data format */
    Uint8 channels;         /**< Number of channels: 1 mono, 2 stereo */
    Uint8 silence;          /**< Audio buffer silence value (calculated) */
    Uint16
        samples; /**< Audio buffer size in sample FRAMES (total samples divided by channel count) */
    Uint16 padding; /**< Necessary for some compile environments */
    Uint32 size;    /**< Audio buffer size in bytes (calculated) */
    SDL_AudioCallback
        callback;   /**< Callback that feeds the audio device (NULL to use SDL_QueueAudio()). */
    void *userdata; /**< Userdata passed to callback (ignored for NULL callbacks). */
} SDL_AudioSpec;

extern DECLSPEC void SDLCALL SDL_MixAudioFormat(Uint8 *dst, const Uint8 *src,
                                                SDL_AudioFormat format, Uint32 len, int volume);
extern DECLSPEC int SDLCALL SDL_GetNumAudioDevices(int iscapture);
extern DECLSPEC const char *SDLCALL SDL_GetAudioDeviceName(int index, int iscapture);
extern DECLSPEC int SDLCALL SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained);
extern DECLSPEC SDL_AudioDeviceID SDLCALL SDL_OpenAudioDevice(const char *device, int iscapture,
                                                              const SDL_AudioSpec *desired,
                                                              SDL_AudioSpec *obtained,
                                                              int allowed_changes);
extern DECLSPEC int SDLCALL SDL_GetNumAudioDrivers(void);
extern DECLSPEC const char *SDLCALL SDL_GetAudioDriver(int index);
extern DECLSPEC const char *SDLCALL SDL_GetCurrentAudioDriver(void);

extern DECLSPEC void SDLCALL SDL_PauseAudio(int pause_on);
extern DECLSPEC void SDLCALL SDL_PauseAudioDevice(SDL_AudioDeviceID dev, int pause_on);
extern DECLSPEC void SDLCALL SDL_CloseAudioDevice(SDL_AudioDeviceID dev);
//===========================================================================

#ifdef __cplusplus
}
#endif

#endif // FAKESDL_H
