#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define PI                              3.1416
#define radian2degree(a)                (a * 57.295779513082)
#define degree2radian(a)                (a * 0.017453292519)

// LAYER
typedef enum
{
    layerBG,
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
#define LAYER_ONE_SPEED                 0.0006  // (Bigger = Faster)
#define LAYER_TWO_SPEED                 0.002   // (Bigger = Faster)
#define LAYER_GROUND_SPEED              0.002   // (Bigger = Faster)

// CLOUD
#define CLOUD_SPAWN_FREQUENCY           0.005   // How frequently spawn function will be called (Bigger = Less Frequently)
#define CLOUD_SPEED                     0.030   // Amount of time the cloud gets to cross the screen (Bigger = Slow)

// CHICKEN
#define SPEED_CHANGE_FREQUENCY          0.01
#define MAX_SPEED_X                     10      // = starting speed times 10
#define ACCELERATION_DEFAULT            1.3
#define CUSTOM_ACCELERATION             0.05    // (Bigger = Faster)

//#define INITIAL_SPEED                   8
//#define FORCE_GRAVITY                   1.5
//#define TERMINAL_VELOCITY               70

// CHICKEN JUMP
#define VELOCITY_Y_MAX                  0.013    // 0.008  // ScreenHeight x .008 | .031 = 2.16 | 3.51 (Bigger = Higher)
#define VELOCITY_Y_DECREASE_RATE        0.0003   // 0.0001 // ScreenHeight x .0001 | .0003 = 0.027 | .081 (Bigger = More)

// COLLISION BITMASKS
#define CATEGORY_BITMASK_CHICKEN        0x0001
#define CATEGORY_BITMASK_TRAMPOLINE     0x0002
#define CATEGORY_BITMASK_EGG            0x0004
#define CONTACTTEST_BITMASK_CHICKEN_EGG 0x0004
#define CONTACTTEST_BITMASK_CHICKEN_ALL 0x0006


// EGG
#define EGG_SPAWN_FREQUENCY             0.001
#define EGG_SPEED                       LAYER_TWO_SPEED

// SCORE LABEL
#define SCORE_FONT_SIZE                 0.085


#endif // __CONSTANTS_H__

















