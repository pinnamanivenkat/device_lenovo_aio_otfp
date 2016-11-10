# Ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/root/enableswap.sh:root/enableswap.sh \
    $(LOCAL_PATH)/root/factory_init.rc:root/factory_init.rc \
    $(LOCAL_PATH)/root/fstab.mt6752:root/fstab.mt6752 \
    $(LOCAL_PATH)/root/init.modem.rc:root/init.modem.rc \
    $(LOCAL_PATH)/root/init.mt6752.rc:root/init.mt6752.rc \
    $(LOCAL_PATH)/root/init.mt6752.usb.rc:root/init.mt6752.usb.rc \
    $(LOCAL_PATH)/root/init.project.rc:root/init.project.rc \
    $(LOCAL_PATH)/root/ueventd.mt6752.rc:root/ueventd.mt6752.rc
