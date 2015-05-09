//
//  Credit.m
//  CatchTheEggs
//
//  Created by Asish Biswas on 4/12/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Credit.h"
#import "MainMenu.h"
#import "GameLayer.h"

@implementation Credit


+ (CCScene*) scene{
	CCScene *scene = [CCScene node];
	[scene addChild:[Credit node]];
	return scene;
}

- (id)init{
    self = [super init];
    if (self) {
        
        CGSize winSize = [[CCDirector sharedDirector] winSize];
        
        //Add background
        CCSprite* background = [CCSprite spriteWithFile:kMenuBackground];
        [background setPosition:ccp(winSize.width/2, winSize.height/2)];
        [self addChild:background];
        
        int fontSize = 15;
        
        CCLabelTTF *labelCopyright = [[CCLabelTTF alloc] initWithString: @"Endri Koci & Asish Biswas, April 2013" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelUniversity = [[CCLabelTTF alloc] initWithString: @"Technische Universität München" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelChair = [[CCLabelTTF alloc] initWithString: @"Chair for Applied Software Engineering, Professor Brügge" fontName:@"Arial" fontSize:fontSize];
        
        CCLabelTTF *labelSourceImages = [[CCLabelTTF alloc] initWithString: @"Special thanks to:" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelSourceSpecialThanks = [[CCLabelTTF alloc] initWithString: @"Nazmus Sakib" fontName:@"Arial" fontSize:fontSize];
        
        CCLabelTTF *labelSourceMusic= [[CCLabelTTF alloc] initWithString: @"Music:" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelSourceMusicLine1= [[CCLabelTTF alloc] initWithString: @"Free Sounds (http://www.freesound.org)" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelSourceMusicLine2= [[CCLabelTTF alloc] initWithString: @"Licensed under Creative Commons:" fontName:@"Arial" fontSize:fontSize];
        CCLabelTTF *labelSourceMusicLine3= [[CCLabelTTF alloc] initWithString: @"By Attribution 3.0 http://creativecommons.org/licenses/by/3.0/" fontName:@"Arial" fontSize:fontSize];
        
        CGPoint leftPositionLetters = CGPointMake(winSize.width * 0.5 , winSize.height * 0.3);
        
        labelCopyright.position = CGPointMake(leftPositionLetters.x + labelCopyright.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.02 * winSize.height);
        labelUniversity.position = CGPointMake(leftPositionLetters.x + labelUniversity.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.05 * winSize.height);
        labelChair.position = CGPointMake(leftPositionLetters.x + labelChair.boundingBox.size.width * 0.5, leftPositionLetters.y - 0.07 * winSize.height);
        
        labelSourceImages.position = CGPointMake(leftPositionLetters.x + labelSourceImages.boundingBox.size.width * 0.5, leftPositionLetters.y - 0.12 * winSize.height);
        labelSourceSpecialThanks.position = CGPointMake(leftPositionLetters.x + labelSourceSpecialThanks.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.145 * winSize.height);
        
        labelSourceMusic.position = CGPointMake(leftPositionLetters.x + labelSourceMusic.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.21 * winSize.height);
        labelSourceMusicLine1.position = CGPointMake(leftPositionLetters.x + labelSourceMusicLine1.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.235 * winSize.height);
        labelSourceMusicLine2.position = CGPointMake(leftPositionLetters.x + labelSourceMusicLine2.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.255 * winSize.height);
        labelSourceMusicLine3.position = CGPointMake(leftPositionLetters.x + labelSourceMusicLine3.boundingBox.size.width * 0.5 , leftPositionLetters.y - 0.275 * winSize.height);
        
        labelCopyright.color = ccBLACK;
        labelUniversity.color = ccBLACK;
        labelChair.color = ccBLACK;
        
        labelSourceImages.color = ccBLACK;
        labelSourceSpecialThanks.color = ccBLACK;
        
        labelSourceMusic.color = ccBLACK;
        labelSourceMusicLine1.color = ccBLACK;
        labelSourceMusicLine2.color = ccBLACK;
        labelSourceMusicLine3.color = ccBLACK;
        
        [self addChild:labelCopyright];
        [self addChild:labelUniversity];
        [self addChild:labelSourceImages];
        [self addChild:labelChair];
        [self addChild:labelSourceSpecialThanks];
        [self addChild:labelSourceMusic];
        [self addChild:labelSourceMusicLine1];
        [self addChild:labelSourceMusicLine2];
        [self addChild:labelSourceMusicLine3];
        
        CCMenuItem *item1 = [CCMenuItemFont itemWithString:@"Back" target:self selector:@selector(menuCallBack:)];

        CCMenu *menu = [CCMenu menuWithItems: item1, nil];
        [menu alignItemsVerticallyWithPadding:50];
        
        [self addChild: menu];

        
        //[self schedule:@selector(backToMenu)];
    }
    return self;
}

//-(void) backToMenu {
//    [[CCDirector sharedDirector] replaceScene:[CCTransitionFade transitionWithDuration:1.0 scene:[MainMenu scene]]];
//}

-(void) menuCallBack: (id) sender{
    CCScene *scene = [CCScene node];
    [scene addChild:[MainMenu node]];
    [[CCDirector sharedDirector] replaceScene: scene];
}

@end
