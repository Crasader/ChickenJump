//
//  Chicken.h
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "CCNode.h"
#import "Box2D.h"

@class World;

@interface Chicken : CCNode

@property (nonatomic, strong) CCSprite *sprite;
@property (nonatomic, strong) World *game;
@property (nonatomic) b2Vec2 velocity;

- (id) initWithGame:(World*)game;
- (void) applyForce; 
- (void)applyForceEggCollision;
- (void) updateNode;
- (void) animateChicken;

@end
