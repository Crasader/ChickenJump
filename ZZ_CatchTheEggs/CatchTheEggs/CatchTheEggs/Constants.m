//
//  Constants.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Constants.h"


//The constants of the chicken
NSString* const kChickenSpriteImage=@"chicken_head_fly_1.png";
float const kInitialPositionOfChicken_x= 350; // ipad retina 350
float const kInitialPositionOfChicken_y= 740; // ipad retina 740
float const kChickenImage_width=120;          //For ipad retina 120!
float const kChickenImage_height=120;         //For ipad retina 120!
//animated chicken
NSString* const kChickenAnimationSpriteImage = @"chicken_head_fly_%i.png";

// Menu
NSString* const kMenuBackground=@"menu.png";
NSString* const kPauseImage = @"pause.png";

// World Settings//

// Force settings
float const kWorldGravity_x=0;
float const kWorldGravity_y=9.8;            //For ipad

// World image
NSString* const kBackgroundImage=@"background.png";
NSString* const kCloudImage=@"cloud.png";
NSString* const kBuildingsImage=@"buildings.png";

//Environment//
int const kEnvironmentVisibility_z= -1;

//Arrow
NSString* const kArrowImage= @"arrow.png";

// Constants for Egg

NSString* const kGoodEggSprteImage = @"egg.png";
NSString* const kBadEggSprteImage = @"egg-black.png";

float const kEggSprteImage_width = 28;  //ipad retina width 28
float const kEggSprteImage_height = 34; //ipad retina width 34
float const kEggNumber = 20;

//good and bad eggs percentage
int const kGoodEggPercentage = 7;// 70 percent of the eggs will be good

//Audio
NSString* const kAudioJump=@"jump.wav";
NSString* const kAudioEggCollected=@"egg.wav";
NSString* const kAudioBadEggHit=@"blackegg.wav";
NSString* const kAudioGameOver=@"gameover.wav";
NSString* const kAudioMelody=@"melody.aiff";
NSString* const kAudioStart=@"play-yes.png";
NSString* const kAudioStop =@"play-no.png";

NSString* const kFinger=@"finger.png";
