//
//  StandardAnimationComponent.m
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/11/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "StandardAnimationComponent.h"

@implementation StandardAnimationComponent

//initialize animation with multiple image files renamed as "chicken_head_fly_%i.png"
-(void) initAnimationAction:(NSString*) baseImageName {
    NSMutableArray* spriteArray = [NSMutableArray arrayWithCapacity:2];
    for (int animationNumber = 1; ; animationNumber++) {
        NSString* filename = [NSString stringWithFormat: baseImageName, animationNumber];
        CCTexture2D* texture = [[CCTextureCache sharedTextureCache] addImage:filename];
        if (texture) {
            CGRect textureRect = CGRectMake(0, 0, texture.contentSize.width, texture.contentSize.height);
            [spriteArray addObject: [CCSpriteFrame frameWithTexture: texture rect: textureRect]];
        } else {
            break;
        }
    }
    CCAnimation* animation = [CCAnimation animationWithSpriteFrames:spriteArray delay:0.5f];
    CCAnimate* animate = [CCAnimate actionWithAnimation:animation];
    animationAction = [CCRepeatForever actionWithAction:animate];
}

//animate images
-(void) animate:(CCSprite*) sprite withBaseImage:(NSString*) baseImageName {
    [self initAnimationAction: baseImageName];
    [sprite runAction: animationAction];
}


@end
