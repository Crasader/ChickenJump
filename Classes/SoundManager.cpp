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
std::string SoundManager::soundWin = "win.wav";
std::string SoundManager::soundStageClear = "stageclear.wav";

std::string SoundManager::menuMusic = "menu.mp3";
std::string SoundManager::gameplayMusic = "gameplay.mp3";

std::string SoundManager::_currentMusic = "";

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
    
    audioEngine->preloadEffect(menuMusic.c_str());
    audioEngine->preloadEffect(gameplayMusic.c_str());

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

void SoundManager::PlayBackgroundMusic(const std::string &music) {
    if (music == _currentMusic) { return; } // already running this music
    
    if (UserDefault::getInstance()->getFloatForKey(MUSIC, 1.0)) {
        auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
        audioEngine->stopBackgroundMusic();
        audioEngine->playBackgroundMusic(music.c_str(), true);

        _currentMusic = music;
    }
}

void SoundManager::StopBackgroundMusic() {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    _currentMusic = "";
}

void SoundManager::ToggleMusic(std::string const& music) {
    UserDefault* ud = UserDefault::getInstance();
    float currentStatus = ud->getFloatForKey(MUSIC, 1.0);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(not currentStatus);

    ud->setFloatForKey(MUSIC, not currentStatus);
    ud->flush();
    
    if (currentStatus) {
        _currentMusic = "";
    }
    
    PlayBackgroundMusic(music);
}

void SoundManager::ToggleSound() {
    UserDefault* ud = UserDefault::getInstance();
    float currentStatus = ud->getFloatForKey(SOUND, 1.0);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(not currentStatus);
    
    ud->setFloatForKey(SOUND, not currentStatus);
    ud->flush();
}

