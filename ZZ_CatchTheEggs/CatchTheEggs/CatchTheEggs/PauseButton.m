//
//  PauseButton.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "PauseButton.h"

@implementation PauseButton
+(void)addTo:(CCNode*) parent  {
    CGSize screenSize = parent.contentSize;
    CCMenuItemImage* pauseButton = [CCMenuItemImage itemWithNormalImage:kPauseImage selectedImage:kPauseImage target:parent selector:@selector(pause:)];
    pauseButton.scale = 0.7f;
    CCMenu* pauseMenu = [CCMenu menuWithItems:pauseButton, nil];
    pauseMenu.position = CGPointMake(screenSize.width-pauseButton.contentSize.width/2, screenSize.height-pauseButton.contentSize.height/2);
    [parent addChild:pauseMenu z:-1];
}
@end
