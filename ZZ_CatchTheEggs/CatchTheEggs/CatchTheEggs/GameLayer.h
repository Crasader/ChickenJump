//
//  GameLayer.h
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "CCLayer.h"
#import "GLES-Render.h"
#import "ScoreBoard.h"
#import "SimpleAudioEngine.h"

@class Environment;

@interface GameLayer : CCLayer

@property (nonatomic, strong) Environment *environment;
@property (nonatomic, strong) CCSprite *pauseButton;
@property (nonatomic, strong) ScoreBoard* score;

+(CCScene*)scene;
@end
