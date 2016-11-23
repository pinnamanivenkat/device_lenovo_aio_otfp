#
# Copyright (C) 2015-2016 The CyanogenMod Project
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


#Device make file for aio_otfp(K3 Note)


$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)
#Short cut to call device tree path
LOCAL_PATH := device/lenovo/aio_otfp

#To make vendor folder visible
$(call inherit-product, device/lenovo/aio_otfp/vendor/copyfiles.mk)
$(call inherit-product, vendor/lenovo/aio_otfp/aio_otfp-vendor-blobs.mk)

#To call overlay folder
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay


# Device uses high-density artwork where available
PRODUCT_AAPT_CONFIG := normal xhdpi xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

#Tells ota package to flash only on these devices
TARGET_OTA_ASSERT_DEVICE := aio_otfp,5m,5M,k50-T5,K50-T5,k50-a40,k50-t5,K50-A40

#To use prebuilt kernel

ifeq ($(TARGET_PREBUILT_KERNEL),)
	LOCAL_KERNEL := $(LOCAL_PATH)/root/kernel
else
	LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

#To copy the kernel
PRODUCT_COPY_FILES += \
$(LOCAL_KERNEL):kernel

PRODUCT_PACKAGES += \
libxlog

PRODUCT_PACKAGES += \
libgui_shim

include $(LOCAL_PATH)/dev_extd/*.mk

# Dalvik heap configurations
$(call inherit-product-if-exists, frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

# Call hwui memory config
$(call inherit-product-if-exists, frameworks/native/build/phone-xxhdpi-2048-hwui-memory.mk)
