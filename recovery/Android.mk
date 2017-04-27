
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := librecovery_updater_mofd
LOCAL_SRC_FILES := recovery_updater.cpp fw_version_check.cpp
LOCAL_C_INCLUDES += bootable/recovery

include $(BUILD_STATIC_LIBRARY)
