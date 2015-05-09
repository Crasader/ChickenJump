//
//  FingerLine.h
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "CCNode.h"
#import "cocos2d.h"
#import "Box2D.h"

@class World;

@interface FingerLine : CCNode

@property (nonatomic, strong) World* game;
@property (readwrite) b2Vec2 vectorStart;
@property (readwrite) b2Vec2 vectorEnd;
@property (readwrite) b2EdgeShape shape;

- (id) initWithGame:(World*)game;
-(void)setNewPosition:(CGPoint)startNew withEnd:(CGPoint)endNew;

@end
