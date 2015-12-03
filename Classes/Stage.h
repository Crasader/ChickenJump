#ifndef __STAGE__
#define __STAGE__

#include <cocos2d.h>

class Stage {
public:
    Stage() {}
    Stage(const std::string& name,
          const std::string& imageFile,
          const std::string& clickedImageFile,
          const std::string& lockedImageFile,
          const int score,
          const int star,
          const bool isUnlocked,
          const bool isPlayed) :
    _name(name),
    _imageFile(imageFile),
    _clickedImageFile(clickedImageFile),
    _lockedImageFile(lockedImageFile),
    _score(score),
    _star(star),
    _isUnlocked(isUnlocked),
    _isPlayed(isPlayed) {}

    std::string getName() const { return _name; }
    std::string getImageFile() const { return _imageFile; }
    std::string getClickedImageFile() const { return _clickedImageFile; }
    std::string getLockedImageFile() const { return _lockedImageFile; }
    int getScore() const { return _isPlayed ? _score : 0; }
    int getStar() const { return _isPlayed ? _star : 0; }
    bool isUnlocked() const { return _isUnlocked; }
    bool isPlayed() const { return _isPlayed; }
    void setAsPlayed() { _isPlayed = true; }
    void unlock() { _isUnlocked = true; }
    
private:
    std::string _name;
    std::string _imageFile;
    std::string _clickedImageFile;
    std::string _lockedImageFile;
    int _score;
    int _star;
    bool _isUnlocked;
    bool _isPlayed;
};

#endif /* defined(__STAGE__) */
