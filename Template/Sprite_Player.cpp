//
//  Sprite_Player.cpp
//  ChickenJump
//
//  Created by Asish Biswas on 16/05/15.
//
//

#include "Sprite_Player.h"

Player::Player(void){
}

Player::~Player(void){
}

Player* Player::playerWithFile(const char * fileName) {
    auto sprite = new Player();
    if (sprite && sprite->initWithFile(fileName)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return sprite = nullptr;
}

void Player::setPosition(const Point& pos) {
    Sprite::setPosition(pos);
}
