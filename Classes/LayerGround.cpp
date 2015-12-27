#include "LayerGround.h"

#include "Constants.h"

LayerGround::LayerGround(Stage& stage) {
    _stage = stage;
    _imageFile = "layerground.png";
    _zOrder = BackgroundLayer::layerGround;
    
    _imageFile1 = "layerground1.png";
    _imageFile2 = "layerground2.png";
    _imageFile3 = "layerground3.png";
    _imageFile4 = "layerground4.png";
    _imageFile5 = "layerground5.png";
    _imageFile6 = "layerground6.png";
    
    if (_stage.getName() == StageStatus::infinite) {
        // ADD MORE SPRITES FOR THE INFINITE STAGE
        _scrollingImages.push_back(_imageFile1);
        _scrollingImages.push_back(_imageFile1);
        _scrollingImages.push_back(_imageFile1);
        _scrollingImages.push_back(_imageFile2);
        _scrollingImages.push_back(_imageFile2);
        _scrollingImages.push_back(_imageFile2);
        _scrollingImages.push_back(_imageFile3);
        _scrollingImages.push_back(_imageFile3);
        _scrollingImages.push_back(_imageFile3);
        _scrollingImages.push_back(_imageFile4);
        _scrollingImages.push_back(_imageFile4);
        _scrollingImages.push_back(_imageFile4);
        _scrollingImages.push_back(_imageFile5);
        _scrollingImages.push_back(_imageFile5);
        _scrollingImages.push_back(_imageFile5);
        _scrollingImages.push_back(_imageFile6);
        _scrollingImages.push_back(_imageFile6);
        _scrollingImages.push_back(_imageFile6);
    }
    else {
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
        _scrollingImages.push_back(_imageFile);
    }
}

LayerGround::~LayerGround() {
    
}