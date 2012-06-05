#
<<<<<<< HEAD
#libusbip
#
$(warning ######  cmd Start  ######)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := libusbip
LOCAL_SRC_FILES := stub_server.c \
	usbip_network.c \
	usbip_network.h \
	dlist.h \
	dlist.c \
	libsysfs.h
=======
#usbipd
#
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := usbipd
LOCAL_SRC_FILES := stub_server.c \
	usbip_network.c \
	usbip_network.h
>>>>>>> 32b9b5b78a981ff968bee1945204b998b840a24f
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/../glib \
	$(LOCAL_PATH)/../sysfslib \
	$(call include-path-for, glib) \
	$(call include-path-for, glib)/glib \
	$(call include-path-for, sysfslib) \
	$(call include-path-for, sysfslib)/sysfslib
LOCAL_CFLAGS := -Wall -W -Wstrict-prototypes -std=gnu99
LOCAL_MODULE_TAGS := eng
<<<<<<< HEAD
LOCAL_PRELINK_MODULE:=false
=======
LOCAL_PRELINK_MODULE := false
>>>>>>> 32b9b5b78a981ff968bee1945204b998b840a24f
LOCAL_SHARED_LIBRARIES := libc
LOCAL_STATIC_LIBRARIES := libusbipd \
			libglib_static \
			libsysfsd
<<<<<<< HEAD
include $(BUILD_SHARED_LIBRARY)

#usbipd
include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := libusbip
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := usbipd
=======
>>>>>>> 32b9b5b78a981ff968bee1945204b998b840a24f
include $(BUILD_EXECUTABLE)
$(warning ######   cmd end   ######)

<<<<<<< HEAD
$(warning ######   cmd end   ######)

=======
#
#usbip_bind_driver
#
$(warning ######  cmd Start  ######)
include $(CLEAR_VARS)
LOCAL_MODULE := usbip_bind_driver
LOCAL_SRC_FILES := bind-driver.c \
	utils.c \
	utils.h \
	usbip_network.h \
	usbip_network.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/../glib \
	$(LOCAL_PATH)/../sysfslib \
	$(call include-path-for, glib) \
	$(call include-path-for, glib)/glib \
	$(call include-path-for, sysfslib) \
	$(call include-path-for, sysfslib)/sysfslib
LOCAL_CFLAGS := -Wall -W -Wstrict-prototypes -std=gnu99
LOCAL_MODULE_TAGS := eng
LOCAL_PRELINK_MODULE:=false
LOCAL_SHARED_LIBRARIES := libc
LOCAL_STATIC_LIBRARIES := libusbipd \
		libglib_static \
		libsysfsd
include $(BUILD_EXECUTABLE)
$(warning ######   cmd end   ######)
>>>>>>> 32b9b5b78a981ff968bee1945204b998b840a24f
