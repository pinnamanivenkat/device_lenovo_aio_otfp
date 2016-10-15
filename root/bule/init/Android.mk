LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE                  := bule
LOCAL_MODULE_TAGS             := optional
LOCAL_SRC_FILES               := main.c
LOCAL_SHARED_LIBRARIES        := \
	libcutils \
	liblog
include $(BUILD_EXECUTABLE)
