//
//  Environment.h
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "CCNode.h"
#import "ScoreBoard.h"


@interface Environment : CCNode

// 3 static layers
@property (nonatomic,retain)CCSprite *clouds;
@property (nonatomic,retain)CCSprite *buildings;
@property (nonatomic,retain)CCSprite *flipedBuildings;

-(void)scrollBackground:(float)velocity_x;

@end
