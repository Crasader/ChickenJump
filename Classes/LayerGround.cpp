#include "LayerGround.h"

#include "Constants.h"

LayerGround::LayerGround(void) {
    _imageFile = "layerground.png";
    _zOrder = BackgroundLayer::layerGround;
    
    if (_stage.getName() == StageStatus::infinite) {
        // ADD MORE SPRITES FOR THE INFINITE STAGE
        _scrollingImages.push_back(cocos2d::StringUtils::format("DE/%s", _imageFile.c_str()));
        _scrollingImages.push_back(cocos2d::StringUtils::format("DE/%s", _imageFile.c_str()));
        _scrollingImages.push_back(cocos2d::StringUtils::format("DE/%s", _imageFile.c_str()));
        _scrollingImages.push_back(cocos2d::StringUtils::format("DE/%s", _imageFile.c_str()));
        _scrollingImages.push_back(cocos2d::StringUtils::format("DE/%s", _imageFile.c_str()));
    }
    else {
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
    }
}

LayerGround::~LayerGround() {
    
}