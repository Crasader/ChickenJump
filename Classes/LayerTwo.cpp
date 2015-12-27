#include "LayerTwo.h"

#include "Constants.h"

LayerTwo::LayerTwo(Stage& stage){
    _stage = stage;
    _imageFile = "layertwo.png";
    _zOrder = BackgroundLayer::layerTwo;    
 
    _imageFile1 = "layertwo1.png";
    _imageFile2 = "layertwo2.png";
    _imageFile3 = "layertwo3.png";
    _imageFile4 = "layertwo4.png";
    _imageFile5 = "layertwo5.png";
    _imageFile6 = "layertwo6.png";
    
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

LayerTwo::~LayerTwo(void) {

}


