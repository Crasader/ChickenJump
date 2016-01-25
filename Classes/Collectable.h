#ifndef __COLLECTABLE_SPRITE__
#define __COLLECTABLE_SPRITE__

#include <cocos2d.h>

class Stage;

class Collectable {
public:
    Collectable(Stage const& st);
    void spawn(cocos2d::Layer* layer, std::vector<cocos2d::Sprite*>& collectables);
    
private:
    void initPatterns(int difficultyLevle);
    void populatePatterns(int difficultyLevel, int eggs, int pizzas, int bombs);
    
    // pair < collectable_type, display_pattern >
    typedef std::pair<int, int> Pattern;
    std::vector<Pattern> _patterns;
    
    std::string const _imageFile = "egg1.png";
    
    cocos2d::Vec2 _origin;
    cocos2d::Size _visibleSize;
};


#endif /* __COLLECTABLE_SPRITE__ */
