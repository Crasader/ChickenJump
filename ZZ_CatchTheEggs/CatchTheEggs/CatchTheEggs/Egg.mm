//
//  Egg.m
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/9/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Egg.h"
#import "World.h"

@interface Egg(){
    CCParticleSystem* particleEffect;
}

@end

@implementation Egg

- (id) initGoodEggWithGameWorld:(World*)game{
    if ((self = [super init])) {
		self.game = game;

        _sprite = [CCSprite spriteWithFile:kGoodEggSprteImage];
        [game addChild:_sprite];
        
	}
	return self;
}

- (id) initBadEggWithGameWorld:(World*)game{
    if ((self = [super init])) {
		self.game = game;
        
        _sprite = [CCSprite spriteWithFile:kBadEggSprteImage];
        [game addChild:_sprite];
        
	}
	return self;
}

-(void) applyParticleEffect{
    particleEffect = [CCParticleExplosion node];
    particleEffect.duration = 0.1f;
    particleEffect.totalParticles = 50;
    particleEffect.life = 0.3f;
    particleEffect.lifeVar = 0.1f;
    ccColor4F startColor = ccc4FFromccc3B(ccYELLOW);
    particleEffect.startColor = startColor;
    particleEffect.endColor = startColor;
    
    particleEffect.autoRemoveOnFinish = YES;
    particleEffect.position = _sprite.position;
    [[_sprite parent] addChild:particleEffect];
}

-(CGRect)boundingBox
{
    CGRect temp;
    temp.size = _sprite.contentSize;
    temp.origin = ccpAdd(_sprite.position, ccpMult(ccpFromSize(temp.size), -0.5));
    return temp;
}

-(BOOL) isActive {
    return ([_sprite numberOfRunningActions] != 0 && _sprite.visible);
}

-(void) destroy {
    [self applyParticleEffect];
    _sprite.visible = NO;
}

// Check for collision Chicken-Egg
-(BOOL) collidesWithChicken:(CGRect) chickenBoundingBox {
    
    if ([self.sprite visible]) {
        
        float eggRadius = _sprite.contentSize.width / 2;
        float chickenCollisionRadius = chickenBoundingBox.size.width/2;
        float eggCollisionRadius = eggRadius * 0.90f;
        
        CGPoint eggPosition = _sprite.position;
        CGPoint chickenPosition = ccpAdd(chickenBoundingBox.origin, ccpMult(ccpFromSize(chickenBoundingBox.size), 0.5));
        
        float maxCollisionDistance = chickenCollisionRadius + eggCollisionRadius;
        float actualDistance = ccpDistance(eggPosition, chickenPosition);

        if(actualDistance < maxCollisionDistance){
            [self destroy];
            return YES;
        }
    }
    return NO;
}

@end
