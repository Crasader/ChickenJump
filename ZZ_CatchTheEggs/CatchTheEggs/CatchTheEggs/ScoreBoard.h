//
//  ScoreBoard.h
//  CatchTheEggs
//
//  Created by Endri Koci on 10/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ScoreBoard : NSObject

@property (nonatomic) int score;

-(id) initWithCCNode:(CCNode*) parent;
-(void) updateScore:(int) newScore;

@end
