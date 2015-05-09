//
//  MainMenu.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "MainMenu.h"
#import "GameLayer.h"
#import "Credit.h"

@interface MainMenu(){
    BOOL _isMusicPlaying;
}

@end

@implementation MainMenu

+(CCScene *) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	MainMenu *layer = [MainMenu node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}

-(id) init
{
    if( (self=[super init])) {
        
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        
        _isMusicPlaying = FALSE;
        
        //Add background
        CCSprite* background = [CCSprite spriteWithFile:kMenuBackground];
        [background setPosition:ccp(screenSize.width/2, screenSize.height/2)];
        [self addChild:background];
        
        //Add background Music
        [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:kAudioMelody];
        if(!_isMusicPlaying){
            [[SimpleAudioEngine sharedEngine] playBackgroundMusic:kAudioMelody];
            _isMusicPlaying = TRUE;
        }
        
        //Elements of the menu
		CCMenuItem *item1 = [CCMenuItemFont itemWithString:@"Start Game" target:self selector:@selector(menuCallBack:)];
        
        //credit layer
        CCMenuItem *item2 = [CCMenuItemFont itemWithString:@"Credits" target:self selector:@selector(creditCallBack:)];
        
        // Sound on/off toggle
        CCMenuItem *soundOnItem = [CCMenuItemImage itemWithNormalImage:kAudioStart
                                                         selectedImage:kAudioStart
                                                                target:nil
                                                              selector:nil];
        
        CCMenuItem *soundOffItem = [CCMenuItemImage itemWithNormalImage:kAudioStop
                                                          selectedImage:kAudioStop
                                                                 target:nil
                                                               selector:nil];
        CCMenuItemToggle *soundToggleItem = nil;
        if(_isMusicPlaying) {
            soundToggleItem = [CCMenuItemToggle itemWithTarget:self
                                                      selector:@selector(musicTurn:)
                                                         items:soundOnItem, soundOffItem, nil];
        } else {
            soundToggleItem = [CCMenuItemToggle itemWithTarget:self
                                                      selector:@selector(musicTurn:)
                                                         items:soundOffItem, soundOnItem, nil];
        }
        
        CCMenu *menu = [CCMenu menuWithItems: item1, item2, soundToggleItem, nil];
        [menu alignItemsVerticallyWithPadding:20];

        [self addChild: menu];
    }
    return self;
}

-(void) menuCallBack: (id) sender
{
    CCScene *scene = [CCScene node];
    [scene addChild:[GameLayer node]];
    [[CCDirector sharedDirector] replaceScene: scene];
}

-(void) creditCallBack: (id) sender
{
    CCScene *scene = [CCScene node];
    [scene addChild:[Credit node]];
    [[CCDirector sharedDirector] replaceScene: scene];
}

-(void)musicTurn:(id) sender{
    _isMusicPlaying=!_isMusicPlaying;
    if([[SimpleAudioEngine sharedEngine] isBackgroundMusicPlaying])
        [[SimpleAudioEngine sharedEngine] stopBackgroundMusic];
    else
        [[SimpleAudioEngine sharedEngine] playBackgroundMusic:kAudioMelody];
}
@end
