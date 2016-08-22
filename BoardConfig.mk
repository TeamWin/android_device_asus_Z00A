#
# Copyright 2013 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

TARGET_ARCH := x86
TARGET_ARCH_VARIANT := silvermont
TARGET_CPU_ABI := x86
TARGET_CPU_ABI2 := armeabi-v7a
TARGET_CPU_ABI_LIST := x86,armeabi-v7a,armeabi
TARGET_CPU_ABI_LIST_32_BIT := x86,armeabi-v7a,armeabi
TARGET_KERNEL_CROSS_COMPILE_PREFIX := x86_64-linux-android-
TARGET_BOARD_PLATFORM := moorefield
TARGET_BOOTLOADER_BOARD_NAME := moorefield
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

TARGET_DROIDBOOT_LIBS := libintel_droidboot

# Adb
BOARD_FUNCTIONFS_HAS_SS_COUNT := true

# Binder API version
TARGET_USES_64_BIT_BINDER := true

# Bootloader
TARGET_OTA_ASSERT_DEVICE := Z00A,Z008
# bootstub as 2nd bootloader
TARGET_BOOTLOADER_IS_2ND := true

# Charger
BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_CHARGER_SHOW_PERCENTAGE := true
BOARD_HEALTHD_CUSTOM_CHARGER_RES := device/asus/zenfone2/charger/images

# EGL
BOARD_EGL_CFG := device/asus/mofd-common/configs/egl.cfg

# Init
TARGET_UNIFIED_DEVICE := true
TARGET_INIT_VENDOR_LIB := libinit_mofd
TARGET_LIBINIT_DEFINES_FILE := device/asus/zenfone2/init/init_mofd.cpp

# Inline kernel building
TARGET_KERNEL_SOURCE := kernel/asus/moorefield
TARGET_KERNEL_ARCH := x86_64
BOARD_KERNEL_IMAGE_NAME := bzImage
TARGET_KERNEL_CONFIG := cyanogenmod_zenfone2_defconfig

# Kernel cmdline
BOARD_KERNEL_CMDLINE := init=/init pci=noearly console=logk0 loglevel=0 vmalloc=256M androidboot.hardware=mofd_v1 watchdog.watchdog_thresh=60 androidboot.spid=xxxx:xxxx:xxxx:xxxx:xxxx:xxxx androidboot.serialno=01234567890123456789 gpt snd_pcm.maximum_substreams=8 ptrace.ptrace_can_access=1 panic=15 ip=50.0.0.2:50.0.0.1::255.255.255.0::usb0:on debug_locks=0 n_gsm.mux_base_conf=\"ttyACM0,0 ttyXMM0,1\" bootboost=1'
BOARD_KERNEL_CMDLINE += androidboot.selinux=permissive

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# Mkbootimg
BOARD_CUSTOM_BOOTIMG_MK := device/asus/zenfone2/mkbootimg.mk
BOARD_BOOT_KEY := device/asus/zenfone2/keys/boot_z00a.sig
BOARD_RECOVERY_KEY := device/asus/zenfone2/keys/recovery_z00a.sig

# Partitions
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2415919104
BOARD_FLASH_BLOCK_SIZE := 2048
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 1677721600
BOARD_CACHEIMAGE_PARTITION_SIZE := 268435456
BOARD_USERDATAIMAGE_PARTITION_SIZE := 59261286400

# PowerHAL
TARGET_POWERHAL_VARIANT := mofd_v1

# Recovery
BOARD_CANT_BUILD_RECOVERY_FROM_BOOT_PATCH := true
TARGET_RECOVERY_PIXEL_FORMAT := "BGRA_8888"
COMMON_GLOBAL_CFLAGS += -DNO_SECURE_DISCARD
TARGET_RECOVERY_FSTAB := device/asus/zenfone2/recovery/root/etc/twrp.fstab
TARGET_RECOVERY_DEVICE_MODULES := libinit_mofd librecovery_updater_mofd


# SELinux
#BOARD_SEPOLICY_DIRS += device/asus/zenfone2/sepolicy

# TWRP
TW_THEME := portrait_hdpi
RECOVERY_GRAPHICS_USE_LINELENGTH := true
RECOVERY_SDCARD_ON_DATA := true
TW_INCLUDE_CRYPTO := true
TW_EXCLUDE_SUPERSU := true
TW_NO_USB_STORAGE := true
BOARD_HAS_NO_REAL_SDCARD := true
#TW_INCLUDE_NTFS_3G := true
BOARD_SUPPRESS_EMMC_WIPE := true
RECOVERY_VARIANT := twrp
