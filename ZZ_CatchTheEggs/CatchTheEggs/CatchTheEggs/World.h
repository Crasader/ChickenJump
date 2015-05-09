//
//  World.h
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Box2D.h"
#import "CCNode.h"
#import "Chicken.h"
#import "FingerLine.h"
#import "Egg.h"
#import "SimpleAudioEngine.h"


@class Chicken;
@class FingerLine;

@interface World : CCLayer{

}

@property (nonatomic, strong) FingerLine *fingerLine;
@property (nonatomic, strong) Chicken *chicken;
@property (nonatomic, readonly) b2World *world;
@property (nonatomic, assign) int score;
@end
