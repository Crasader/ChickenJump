#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define PI                              3.1416
#define radian2degree(a)                (a * 57.295779513082)
#define degree2radian(a)                (a * 0.017453292519)

// LAYER
typedef enum
{
    layerBackground,
    layerTwo,
    layerGround,
    layerFour,
    layerChicken
    
} BackgroundLayer;

// SPLASH SCREEN
#define DISPLAY_TIME_SPLASH_SCREEN      2
#define TRANSITION_TIME                 0.5

// LAYERS
#define LAYER_ONE_SPEED                 0.0005  // (Bigger = Faster)
#define LAYER_TWO_SPEED                 0.001   // (Bigger = Faster)
#define LAYER_GROUND_SPEED              0.002   // (Bigger = Faster)

// CLOUD
#define CLOUD_SPAWN_FREQUENCY           0.005   // How frequently spawn function will be called (Bigger = Less Frequently)
#define CLOUD_SPEED                     0.020   // Amount of time the cloud gets to cross the screen (Bigger = Slow)

// CHICKEN
#define ACCELERATION                    0.5
#define INITIAL_SPEED                   8
#define FORCE_GRAVITY                   1.5
#define TERMINAL_VELOCITY               70

// CHICKEN JUMP
#define VELOCITY_Y_MAX                  0.008    // ScreenHeight x 0.07 = 80 (Bigger = Higher)
#define VELOCITY_Y_DECREASE_RATE        0.0001   // ScreenHeight x 0.0045 = 5 (Bigger = More)

// TREE
#define TREE_SPAWN_FREQUENCY            0.001
#define TREE_SPEED                      0.004

#endif // __CONSTANTS_H__