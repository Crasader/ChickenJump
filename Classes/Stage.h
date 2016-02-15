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
          const unsigned int difficulty,
          const unsigned int score,
          const unsigned int highScore,
          const unsigned int star,
          const bool         isUnlocked,
          const bool         isPlayed) :
    _name(name),
    _imageFile(imageFile),
    _clickedImageFile(clickedImageFile),
    _lockedImageFile(lockedImageFile),
    _difficulty(difficulty),
    _score(score),
    _highScore(highScore),
    _star(star),
    _isUnlocked(isUnlocked),
    _isPlayed(isPlayed) {}

    std::string  getName()               const { return _name; }
    std::string  getImageFile()          const { return _imageFile; }
    std::string  getClickedImageFile()   const { return _clickedImageFile; }
    std::string  getLockedImageFile()    const { return _lockedImageFile; }
    unsigned int getDifficulty()         const { return _difficulty; }
    unsigned int getScore()              const { return _isPlayed ? _score : 0; }
    unsigned int getHighScore()          const { return _highScore; }
    unsigned int getStar()               const { return _isPlayed ? _star : 0; }
    bool         isUnlocked()            const { return _isUnlocked; }
    bool         isPlayed()              const { return _isPlayed; }
    void         unlock()                      { _isUnlocked = true; }

    void setScore(unsigned int score) {
        _score = score;
        setAsPlayed();
        if(_score > getHighScore()) {
            setHighScore(score);
        }
    }

    void setStar (unsigned int star) {
        _star = star;
        if (star > 3) {
            _star = 3;
        }
    }
    
private:
    void setAsPlayed()                        { _isPlayed = true; }
    void setHighScore(unsigned int highScore) { _highScore = highScore; }

    std::string  _name;
    std::string  _imageFile;
    std::string  _clickedImageFile;
    std::string  _lockedImageFile;
    unsigned int _difficulty;
    unsigned int _score;
    unsigned int _highScore;
    unsigned int _star;
    bool         _isUnlocked;
    bool         _isPlayed;
};

#endif /* defined(__STAGE__) */
