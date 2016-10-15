
# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_us_supl.mk)

# GPS
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/gps/slp_conf:system/etc/slp_conf \
    $(LOCAL_PATH)/configs/gps/agps_profiles_conf2.xml:system/etc/agps_profiles_conf2.xml
