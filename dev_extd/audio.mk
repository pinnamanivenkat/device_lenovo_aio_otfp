# Audio
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio.usb.default \
    audio.r_submix.default \
    audio_policy.default \
    libaudio-resampler \
    libtinycompress \
	libtinyxml

#permissions
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/configs/audio/audio_device.xml:system/etc/audio_device.xml \
	$(LOCAL_PATH)/configs/audio/audio_effects.conf:system/etc/audio_effects.conf \
	$(LOCAL_PATH)/configs/audio/audio_em.xml:system/etc/audio_em.xml \
	$(LOCAL_PATH)/configs/audio/audio_policy.conf:system/etc/audio_policy.conf \
	$(LOCAL_PATH)/configs/audio_param/AudioParamOptions.xml:system/etc/audio_param/AudioParamOptions.xml




