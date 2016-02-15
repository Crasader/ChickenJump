#ifndef __SPECIAL_COLLECTABLE_SPRITE__
#define __SPECIAL_COLLECTABLE_SPRITE__

#include <cocos2d.h>

class Stage;

class SpecialCollectable {
public:
    SpecialCollectable(Stage const& st);
    void spawn(cocos2d::Layer* layer, std::vector<cocos2d::Sprite*>& specialCollectables);
    
private:
    void populatePatterns(int difficultyLevel, int life, int floatingBomb, int invisibility, int magnetEffect);
    void initPatterns(int difficultyLevel);
    
    std::vector<int> _specialCollectableTypes;
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
    
    std::string const _imageFile = "egg3.png";
};


#endif /* __SPECIAL_COLLECTABLE_SPRITE__ */
