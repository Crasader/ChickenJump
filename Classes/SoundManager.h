#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include <cocos2d.h>

class SoundManager {
public:
    SoundManager();
    
    static void Play(const std::string& sound);
    static void ToggleMusic();
    static void ToggleSound();

    static std::string soundStart;
    static std::string soundJump;
    static std::string soundPickupCoin;
    static std::string soundPickupFood;
    static std::string soundLifeup;
    static std::string soundExplosion;
    static std::string soundDead;
    
private:
    static bool _isSoundActive;
    static bool _isMusicActive;
};

#endif // __SOUNDMANAGER__
