LOCAL_PATH := $(call my-dir)

$(warning ######  Start  ######)
#libusbipd
include $(CLEAR_VARS)
LOCAL_SRC_FILES := bind-driver.c \
		utils.c utils.h \
		usbip_network.h \
		usbip_network.c	
LOCAL_C_INCLUDES :=  \
	$(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/../glib \
	$(call include-path-for, glib) \
	$(call include-path-for, glib)/glib
LOCAL_CFLAGS := -Wall -W -Wstrict-prototypes -std=gnu99
LOCAL_MODULE := usbipd_bind_driver
LOCAL_MODULE_TAGS := eng
#LOCAL_SYSTEM_SHARED_LIBRARIES := libc
LOCAL_SHARED_LIBRARIES := libc
LOCAL_STATIC_LIBRARIES := libusbip \
	libglib_static
include $(BUILD_SHARED_LIBRARY)

#usbipd
include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := usbipd_bind_driver
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE:=usbip_bind_driver
include $(BUILD_EXECUTABLE)

$(warning ######   end   ######)


