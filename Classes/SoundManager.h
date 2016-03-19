#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include <cocos2d.h>

class SoundManager {
public:
    SoundManager();
    
    static float IsSoundActive();
    static float IsMusicActive();
    static void Play(std::string const& sound);
    static void PlayBackgroundMusic(std::string const& music);
    static void StopBackgroundMusic();
    static void ToggleMusic(std::string const& music);
    static void ToggleSound();

    static std::string soundStart;
    static std::string soundJump;
    static std::string soundPickupCoin;
    static std::string soundPickupFood;
    static std::string soundLifeup;
    static std::string soundExplosion;
    static std::string soundDead;
    static std::string soundWin;
    static std::string soundStageClear;
    
    static std::string menuMusic;
    static std::string gameplayMusic;
    
private:
    static std::string _currentMusic; // currently running background music
};

#endif // __SOUNDMANAGER__
