LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/SplashScreenLayer.cpp \
                   ../../Classes/MainMenuLayer.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameOverHUD.cpp \
                   ../../Classes/Collectable.cpp \
                   ../../Classes/Chicken.cpp \
                   ../../Classes/Cloud.cpp \
                   ../../Classes/LayerBackground.cpp \
                   ../../Classes/LayerGround.cpp \
                   ../../Classes/LayerTwo.cpp \
                   ../../Classes/ScrollingLayerBase.cpp \
                   ../../Classes/Trampoline.cpp \
                   ../../Classes/PauseHUD.cpp \
                   ../../Classes/ScoreHUD.cpp \
                   ../../Classes/HomeLayer.cpp \
                   ../../Classes/Stage.cpp \
                   ../../Classes/StageStatus.cpp \
                   ../../Classes/FloatingChicken.cpp \
                   ../../Classes/SpecialCollectable.cpp \
                   ../../Classes/SettingsMenuHUD.cpp \
                   ../../Classes/BackButton.cpp \
                   ../../Classes/SoundManager.cpp \
                   ../../Classes/CreditLayer.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2d/cocos/ui

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
