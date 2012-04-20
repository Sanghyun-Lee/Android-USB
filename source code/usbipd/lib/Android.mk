LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := libusbip
LOCAL_SRC_FILES := names.c names.h stub_driver.c stub_driver.h usbip.h usbip_common.c usbip_common.h vhci_driver.c vhci_driver.h

LOCAL_STATIC_LIBRARIES := libusip


LOCAL_SYSTEM_SHARED_LIBRARIES := libc


LOCAL_C_INCLUDES := external/usbipd/lib/
LOCAL_CFLAGS := -Wall -W -Wstrict-prototypes -std=gnu99
LOCAL_MODULE_TAGS := eng
include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)



