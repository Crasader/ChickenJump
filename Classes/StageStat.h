#ifndef __STAGESTAT__
#define __STAGESTAT__

#include <cocos2d.h>

class StageStat {
public:
    StageStat() {}
    StageStat(std::string const& name, std::string const& imageFile, int const& score, int const& star, bool const& isLocked) :
    _name(name), _imageFile(imageFile), _score(score), _star(star), _isLocked(isLocked) {}

    std::string getName() const { return _name; }
    std::string getImageFile() const { return _imageFile; }
    int getScore() const { return _score; }
    int getStar() const { return _star; }
    bool isLocked() const { return _isLocked; }
    
private:
    std::string _name;
    std::string _imageFile;
    int _score;
    int _star;
    bool _isLocked;
};

#endif /* defined(__STAGESTAT__) */
