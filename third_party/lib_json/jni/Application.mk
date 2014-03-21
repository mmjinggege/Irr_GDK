#这个STL库完整才能支持异常
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti -fexceptions
#APP_MODULES := fsm
APP_PLATFORM := android-8
APP_ABI := armeabi
#NDK_TOOLCHAIN_VERSION =clang