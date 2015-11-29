#ifndef __STAGE__
#define __STAGE__

#include <cocos2d.h>

class Stage {
public:
    Stage() {}
    Stage(const std::string& name, const std::string& imageFile, const int score, const int star, const bool isUnlocked, const bool isPlayed) :
    _name(name), _imageFile(imageFile), _score(score), _star(star), _isUnlocked(isUnlocked), _isPlayed(isPlayed) {}

    std::string getName() const { return _name; }
    std::string getImageFile() const { return _imageFile; }
    int getScore() const { return _isPlayed ? _score : 0; }
    int getStar() const { return _isPlayed ? _star : 0; }
    bool isUnlocked() const { return _isUnlocked; }
    bool isPlayed() const { return _isPlayed; }
    void setAsPlayed() { _isPlayed = true; }
    void unlock() { _isUnlocked = true; }
    
private:
    std::string _name;
    std::string _imageFile;
    int _score;
    int _star;
    bool _isUnlocked;
    bool _isPlayed;
};

#endif /* defined(__STAGE__) */
