#ifndef __TREE_SPRITE__
#define __TREE_SPRITE__

#include <cocos2d.h>

using namespace cocos2d;

class Tree {
public:
    Tree(void);
    void spawn(cocos2d::Layer* layer);
    
private:
    Vec2 _origin;
    Size _visibleSize;
    Sprite* _tree;
    
//    std::string const _spriteImage = "tree_br.png";
};


#endif /* __TREE_SPRITE__ */
