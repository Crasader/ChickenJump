//
//  ScoreBoard.m
//  CatchTheEggs
//
//  Created by Endri Koci on 10/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "ScoreBoard.h"

@interface ScoreBoard(){
    CCLabelTTF *label;
}

@end


@implementation ScoreBoard

@synthesize score;

-(id) initWithCCNode:(CCNode*) parent {
    self = [super init];
    if (self) {
        score = 0;
        NSString* scoreText = [NSString stringWithFormat:@"%i", score];
        label = [CCLabelTTF labelWithString:scoreText fontName:@"Marker Felt" fontSize:32];
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        label.position = CGPointMake(screenSize.width/2, screenSize.height-label.contentSize.height/2);
        [parent addChild:label];
    }
    return self;
}

-(void) updateScore:(int) newScore {
    if (score != newScore) {
        score = newScore;
        NSString* scoreText = [NSString stringWithFormat:@"%i", score];
        [label setString:scoreText];
    }
}

@end
