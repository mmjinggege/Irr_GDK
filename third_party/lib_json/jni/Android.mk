LOCAL_PATH := $(call my-dir)
$(warning  $(LOCAL_PATH))
LOCAL_MODULE := json
LOCAL_MODULE_FILENAME := libjson
LOCAL_SRC_FILES := ../json_reader.cpp\
			../json_value.cpp\
			../json_writer.cpp
			
LOCAL_C_INCLUDES :=$(LOCAL_PATH)/../
								

include $(BUILD_STATIC_LIBRARY)
