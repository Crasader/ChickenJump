//
//  GameOverScene.h
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CCLayer.h"

@interface GameOverScene : CCLayer

+(CCScene*)scene:(int)highscore;
-(void) backToMenu;

@end
