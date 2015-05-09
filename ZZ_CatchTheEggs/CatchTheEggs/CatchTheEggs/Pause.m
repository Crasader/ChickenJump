//
//  Pause.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Pause.h"

@implementation Pause

- (id)init {
    self = [super init];
    if (self) {
        CGSize size = [[CCDirector sharedDirector] winSize];
        self.touchEnabled = YES;
        CCLabelTTF *label = [CCLabelTTF labelWithString:@"Paused" fontName:@"Marker Felt" fontSize:64];
        label.position = CGPointMake(size.width/2, size.height/2);
        CCLabelTTF *label2 = [CCLabelTTF labelWithString:@"Tap to continue" fontName:@"Marker Felt" fontSize:24];
        label2.position = CGPointMake(size.width/2, label.position.y - 50);
        
        [self addChild:label];
        [self addChild:label2];
    }
    return self;
}

-(void) ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [[CCDirector sharedDirector] popScene];
    [[CCDirector sharedDirector] resume];
}

@end
