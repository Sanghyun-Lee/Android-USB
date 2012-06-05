LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := sysfsd
LOCAL_SRC_FILES :=  dlist.c \
   sysfs.h \
   sysfs_attr.c \
   sysfs_bus.c \
   sysfs_class.c \
   sysfs_device.c \
   sysfs_driver.c \
   sysfs_module.c \
   sysfs_utils.c
LOCAL_CFLAGS := -Wall -W -Wstrict-prototypes -std=gnu99
LOCAL_MODULE_TAGS := eng
include $(BUILD_STATIC_LIBRARY)



