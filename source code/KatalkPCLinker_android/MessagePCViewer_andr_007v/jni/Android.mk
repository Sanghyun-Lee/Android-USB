LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := ndk-chat
LOCAL_SRC_FILES := TCPconnect.c
include $(BUILD_SHARED_LIBRARY)