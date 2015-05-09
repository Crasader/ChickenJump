//
//  AnimationComponent.h
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/11/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"

@protocol AnimationComponent <NSObject>

-(void) animate:(CCSprite*) sprite withBaseImage:(NSString*) baseImageName;

@end
