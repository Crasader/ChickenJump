#include "LayerTwo.h"

#include "Constants.h"

LayerTwo::LayerTwo(Stage& stage){
    _stage = stage;
    _imageFile = "layertwo.png";
    _zOrder = BackgroundLayer::layerTwo;    
 
    _imageFile1 = "foreground1.png";
    _imageFile2 = "foreground2.png";
    _imageFile3 = "foreground3.png";
    _imageFile4 = "foreground4.png";
    _imageFile5 = "foreground5.png";
    _imageFile6 = "foreground6.png";
    
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

LayerTwo::~LayerTwo(void) {

}


