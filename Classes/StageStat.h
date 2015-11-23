#ifndef __STAGESTAT__
#define __STAGESTAT__

#include <cocos2d.h>

class StageStat {
public:
    StageStat() {}
    StageStat(std::string name, int score, int star, bool isLocked) :
    _name(name), _score(score), _star(star), _isLocked(isLocked) {}

    std::string getName() { return _name; }
    int getScore() { return _score; }
    int getStar() { return _star; }
    bool isLocked() { return _isLocked; }
    
private:
    std::string _name;
    int _score;
    int _star;
    bool _isLocked;
};

#endif /* defined(__STAGESTAT__) */
