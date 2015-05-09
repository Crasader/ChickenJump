//
//  Egg.h
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/9/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "CCNode.h"
#import "Box2D.h"

@class World;

@interface Egg : NSObject 

@property (nonatomic, strong) CCSprite* sprite;
@property (nonatomic, strong) World *game;
@property (nonatomic, assign) BOOL active;
@property (nonatomic, assign, readonly) CGRect boundingBox;
@property (nonatomic, assign) BOOL goodOrBad;// True = good | False = bad

- (id) initGoodEggWithGameWorld:(World*)game;
- (id) initBadEggWithGameWorld:(World*)game;

-(BOOL) isActive;
-(void) destroy;
-(BOOL) collidesWithChicken:(CGRect) chickenBoundingBox;
@end
