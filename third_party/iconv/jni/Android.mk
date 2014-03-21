LOCAL_PATH := $(call my-dir)
$(warning  $(LOCAL_PATH))
LOCAL_MODULE := iconv
LOCAL_MODULE_FILENAME := libiconv
#LOCAL_STATIC_LIBRARIES := iconv_static
LOCAL_SRC_FILES := ../lib/iconv.c\
			../lib/relocatable.c\
			../libcharset/lib/localcharset.c
LOCAL_C_INCLUDES :=$(LOCAL_PATH)/../include\
								$(LOCAL_PATH)/../lib\
								$(LOCAL_PATH)/../libcharset/include  						
LOCAL_CFLAGS := -Wno-multichar -D_ANDROID -DLIBDIR=\"c\" -DBUILDING_LIBICONV -DIN_LIBRARY   
#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
