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

bool SoundManager::_isSoundActive = true;
bool SoundManager::_isMusicActive = true;

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

void SoundManager::Play(const std::string &sound) {
    if (_isSoundActive) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sound.c_str());
    }
}

void SoundManager::ToggleMusic() {
    _isMusicActive = not _isMusicActive;
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(_isMusicActive);

    UserDefault::getInstance()->setFloatForKey(MUSIC, _isMusicActive);
    UserDefault::getInstance()->flush();
}

void SoundManager::ToggleSound() {
    _isSoundActive = not _isSoundActive;
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(_isSoundActive);

    UserDefault::getInstance()->setFloatForKey(SOUND, _isSoundActive);
    UserDefault::getInstance()->flush();
}

