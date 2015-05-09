//
//  GameLayer.m
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "GameLayer.h"
#import "Environment.h"
#import "World.h"
#import "Chicken.h"
#import "PauseButton.h"
#import "Pause.h"
#import "GameOverScene.h"

@interface GameLayer(){
    ScoreBoard* _score;
    BOOL _isSoundActive;
}

@end

@implementation GameLayer

//Create scene
+ (CCScene*) scene {
	CCScene *scene = [CCScene node];
	[scene addChild:[GameLayer node]];
	return scene;
}

- (id)init{
    if ((self = [super init])) {
        
        // Create Environment
        _environment = [[Environment alloc]init];
        [self addChild:_environment z:kEnvironmentVisibility_z];
        
        //Score
        _score = [[ScoreBoard alloc] initWithCCNode:self];
        
        //make sound active at first
        _isSoundActive = TRUE;
        
        // Create the World with Physics
        [self addChild:[[World alloc]init] z:1 tag:1];
        
        //Add Pause
        [PauseButton addTo:self];
        [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:kAudioGameOver];
               
		[self scheduleUpdate];
    }
    return self;
}

-(void) pause:(id) sender {
    [[CCDirector sharedDirector] pause];
    [[CCDirector sharedDirector] pushScene:[Pause node]];
}

- (void) update:(ccTime)dt {
    
    Chicken* chicken = (Chicken*)[[self getChildByTag:1] getChildByTag:1];
    [self.environment scrollBackground:chicken.velocity.x];
    
    World* world=(World*)[self getChildByTag:1];
    
    [_score updateScore: world.score];
    
    //Game over if the chicken position y is under 0 
    if(chicken.position.y < 0){
        [[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:1.0 scene:[GameOverScene scene:_score.score]]];
        if(_isSoundActive){
            [[SimpleAudioEngine sharedEngine] playEffect:kAudioGameOver];            
            _isSoundActive = FALSE;
        }
    }
    
}

@end
