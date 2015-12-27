#include "LayerBackground.h"

#include "Constants.h"

LayerBackground::LayerBackground(void){
    _imageFile = "background.png";
    _zOrder = BackgroundLayer::layerBackground;
    
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

LayerBackground::~LayerBackground() {
    
}