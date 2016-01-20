#include "SoundManager.h"

#include "Constants.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

std::string SoundManager::soundStart = "start.wav";
std::string SoundManager::soundJump = "jump.wav";
std::string SoundManager::soundPickupCoin = "pickup_coin.wav";
std::string SoundManager::soundPickupFood = "pickup_coin.wav";
std::string SoundManager::soundLifeup = "lifeup.wav";
std::string SoundManager::soundExplosion = "explosion.wav";
std::string SoundManager::soundDead = "dead.wav";

SoundManager::SoundManager() {
    // Cache
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    audioEngine->preloadEffect(soundJump.c_str());
    audioEngine->preloadEffect(soundPickupCoin.c_str());
    audioEngine->preloadEffect(soundPickupFood.c_str());
    audioEngine->preloadEffect(soundExplosion.c_str());
    audioEngine->preloadEffect(soundLifeup.c_str());
    audioEngine->preloadEffect(soundDead.c_str());
    audioEngine->preloadEffect(soundStart.c_str());
    audioEngine->setEffectsVolume(0.5f);
}

float SoundManager::IsSoundActive() {
    return UserDefault::getInstance()->getFloatForKey(SOUND, 1.0);
}

float SoundManager::IsMusicActive() {
    return UserDefault::getInstance()->getFloatForKey(MUSIC, 1.0);
}

void SoundManager::Play(std::string  const& sound) {
    if (UserDefault::getInstance()->getFloatForKey(SOUND, 1.0)) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sound.c_str());
    }
}

void SoundManager::ToggleMusic() {
    UserDefault* ud = UserDefault::getInstance();
    float currentStatus = ud->getFloatForKey(MUSIC, 1.0);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(not currentStatus);

    ud->setFloatForKey(MUSIC, not currentStatus);
    ud->flush();
}

void SoundManager::ToggleSound() {
    UserDefault* ud = UserDefault::getInstance();
    float currentStatus = ud->getFloatForKey(SOUND, 1.0);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(not currentStatus);
    
    ud->setFloatForKey(SOUND, not currentStatus);
    ud->flush();
}

