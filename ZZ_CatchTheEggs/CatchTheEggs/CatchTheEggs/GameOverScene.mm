//
//  GameOverScene.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "GameOverScene.h"
#import "MainMenu.h"
#import "GameLayer.h"

@implementation GameOverScene

static int score;

+ (CCScene*) scene:(int)gamescore{
    score=gamescore;
	CCScene *scene = [CCScene node];
	[scene addChild:[GameOverScene node]];
	return scene;
}

- (id)init{
    self = [super init];
    if (self) {
        
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        
        //Add background
        CCSprite* background = [CCSprite spriteWithFile:kMenuBackground];
        [background setPosition:ccp(screenSize.width/2, screenSize.height/2)];
        [self addChild:background];
        
        //[[SimpleAudioEngine sharedEngine] playEffect:kGameOverSound];
        CGSize size = [[CCDirector sharedDirector] winSize];
        CCLabelTTF *label = [CCLabelTTF labelWithString:@"Game Over" fontName:@"Marker Felt" fontSize:50];
        label.position = CGPointMake(size.width/2, size.height*0.7);
        [self addChild:label];
        
        NSString* scoreText = [NSString stringWithFormat:@"Your score %i", score];
        CCLabelTTF *labelScore = [CCLabelTTF labelWithString:scoreText fontName:@"Marker Felt" fontSize:50];
        labelScore.position = CGPointMake(size.width/2, size.height*0.5);
        [self addChild:labelScore];

        [self schedule:@selector(backToMenu) interval:2];
    }
    return self;
}

-(void) backToMenu {
    [[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:1.0 scene:[MainMenu scene]]];
}

@end
