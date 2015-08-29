#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

typedef enum
{
    layerBackground,
    layerTwo,
    layerGround,
    layerFour,
    layerChicken
    
} BackgroundLayer;

#define DISPLAY_TIME_SPLASH_SCREEN      2
#define TRANSITION_TIME                 0.5

#define LAYER_ONE_SPEED                 0.0005
#define LAYER_TWO_SPEED                 0.001
#define LAYER_GROUND_SPEED              0.002

#define TREE_SPAWN_FREQUENCY            0.001
#define TREE_SPEED                      0.004

#define CLOUD_SPAWN_FREQUENCY           0.005   // how frequently spawn function will be called
#define CLOUD_SPEED                     0.020   // amount of time the cloud gets to cross the screen

#endif // __CONSTANTS_H__