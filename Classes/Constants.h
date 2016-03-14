#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define PI                              3.1416
#define radian2degree(a)                (a * 57.295779513082)
#define degree2radian(a)                (a * 0.017453292519)

// FONT
#define font                            "Marker Felt.ttf"

// LAYER
typedef enum
{
    layerBG,
    layerBackground,
    layerTwo,
    layerGround,
    layerChicken,
    layerTouch

} BackgroundLayer;

// Score factors
#define MAX_TIME_BONUS                  15   // points

// Number of lives
#define CHICKEN_LIVES_MAX               3
#define CHICKEN_LIVES                   3

#define STAGE_LENGTH                    40 // 35 // increased to 70 since designResolution decreased from 1024 to 512

// UserDefault Strings
#define FIRST_TIME                      "FIRST_TIME"
#define SOUND                           "SOUND"
#define MUSIC                           "MUSIC"
#define EFFECT_DURATION                 20 // TODO::make it resonable may be 15 sec

// SPLASH SCREEN
#define DISPLAY_TIME_SPLASH_SCREEN      2
#define TRANSITION_TIME                 0.5

// LAYERS
#define LAYER_BACKGROUND_SPEED          0.0006  // (Bigger = Faster)
#define LAYER_TWO_SPEED                 0.002   // (Bigger = Faster)
#define LAYER_GROUND_SPEED              0.002   // (Bigger = Faster)

// CLOUD
#define CLOUD_SPAWN_FREQUENCY           0.007   // How frequently spawn function will be called (Bigger = Less Frequently)
#define CLOUD_SPEED                     0.030   // Amount of time the cloud gets to cross the screen (Bigger = Slow)

// Special Collectable spawn frequency
#define SPECIAL_OBJ_SPAWN_DISTANCE      3       // after this value * screen width new special collectable will spawn

// CHICKEN
#define SPEED_CHANGE_FREQUENCY          0.01
#define MAX_SPEED_X                     12      // = starting speed times 10
#define MIN_SPEED_X                     1
#define ACCELERATION_DEFAULT            1.3
#define CUSTOM_ACCELERATION             0.05    // (Bigger = Faster)
#define MAX_WEIGHT                      2.0
#define MIN_WEIGHT                      1.0
#define MAX_SCALE                       2.0
#define MIN_SCALE                       1.0
#define SCALE_FACTOR                    0.25

// CHICKEN JUMP
#define VELOCITY_Y_MAX                  0.0130   // 0.008  // ScreenHeight x .008 | .031 = 2.16 | 3.51 (Bigger = Higher)
#define VELOCITY_Y_DECREASE_RATE        0.0003   // 0.0001 // ScreenHeight x .0001 | .0003 = 0.027 | .081 (Bigger = More)

#define FLYING_Y_MAX                    0.01000  // 0.008  // ScreenHeight x .008 | .031 = 2.16 | 3.51 (Bigger = Higher)
#define FLYING_Y_DECREASE_RATE          0.00015  // 0.0001 // ScreenHeight x .0001 | .0003 = 0.027 | .081 (Bigger = More)

// COLLISION BITMASKS // 1:chicken; 2:egg 4:pizza 8:bomb(static & floating) 16:life 32:invisibility 64:trampoline 128:magnet effect
#define CATEGORY_BITMASK_NOTHING        0x0000   // (0)   0000 0000
#define CATEGORY_BITMASK_CHICKEN        0x0001   // (1)   0000 0001
#define CATEGORY_BITMASK_COLLECT_EGG    0x0002   // (2)   0000 0010
#define CATEGORY_BITMASK_COLLECT_PIZZA  0x0004   // (4)   0000 0100
#define CATEGORY_BITMASK_COLLECT_BOMB   0x0008   // (8)   0000 1000
#define CATEGORY_BITMASK_COLLECT_LIFE   0x0010   // (16)  0001 0000
#define CATEGORY_BITMASK_INVISIBILITY   0x0020   // (32)  0010 0000
#define CATEGORY_BITMASK_TRAMPOLINE     0x0040   // (64)  0100 0000
#define CATEGORY_BITMASK_MAGNET         0x0080   // (128) 1000 0000

#define CONTACTTEST_BITMASK_CHICKEN_ALL 0x00FE   //       1111 1110
#define CONTACTTEST_BITMASK_CHICKEN_NO_BOMB 0x00F6   //   1111 0110
#define CONTACTTEST_BITMASK_CHICKEN_NON 0x0000   //       0000 0000


// COLLECTABLE
#define COLLECTABLE_SPAWN_FREQUENCY     0.001
#define COLLECTABLE_SPEED               LAYER_TWO_SPEED
#define COLLECTABLE_FALLING_SPEED       0.003
// SCORE LABEL
#define SCORE_FONT_SIZE_BIG             0.085
#define SCORE_FONT_SIZE_MID             0.075
#define SCORE_FONT_SIZE_SMALL           0.065
#define SCORE_FONT_SIZE_EXTRA_SMALL     0.045

#define CREDIT_FONT_SIZE_SMALL          0.06
#define CREDIT_FONT_SIZE_MID            0.085
#define CREDIT_FONT_SIZE_BIG            0.1
#define GO_FONT_SIZE                    0.1


#endif // __CONSTANTS_H__
