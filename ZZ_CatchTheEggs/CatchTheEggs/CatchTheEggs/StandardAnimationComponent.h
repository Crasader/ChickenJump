//
//  StandardAnimationComponent.h
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/11/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AnimationComponent.h"

@interface StandardAnimationComponent : NSObject<AnimationComponent>{
    CCAction* animationAction;
}

@end
