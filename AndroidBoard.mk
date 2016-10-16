LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ALL_PREBUILT += $(INSTALLED_KERNEL_TARGET)

#Work areound for the failure of making KERNEL_OBJ/usr directory 
$(shell mkdir -p $(OUT)/obj/KERNEL_OBJ/usr)
