#include "LayerBackground.h"

#include "Constants.h"

LayerBackground::LayerBackground(Stage const& stage){
    _stage = stage;
    _imageFile = "background.png";
    _zOrder = BackgroundLayer::layerBackground;

    _imageFile1 = "background1.png";
    _imageFile2 = "background2.png";
    _imageFile3 = "background3.png";
    _imageFile4 = "background4.png";
    _imageFile5 = "background5.png";
    _imageFile6 = "background6.png";
    
    if (_stage.getName() == StageStatus::infinite) {
        // ADD SPRITES FOR THE INFINITE STAGE
        _scrollingImages.push_back(_imageFile1);
        _scrollingImages.push_back(_imageFile2);
        _scrollingImages.push_back(_imageFile3);
        _scrollingImages.push_back(_imageFile4);
        _scrollingImages.push_back(_imageFile5);
        _scrollingImages.push_back(_imageFile6);
    }
    else {
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
    }
}

LayerBackground::~LayerBackground() {
    
}