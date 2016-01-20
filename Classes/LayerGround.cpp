#include "LayerGround.h"

#include "Constants.h"

LayerGround::LayerGround(Stage const& stage) {
    _stage = stage;
    _imageFile = "layerground.png";
    _zOrder = BackgroundLayer::layerGround;
    
    if (_stage.getName() == StageStatus::infinite) {
        // ADD SPRITES FOR THE INFINITE STAGE
    }
    else {
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
    }
}

LayerGround::~LayerGround() {
    
}