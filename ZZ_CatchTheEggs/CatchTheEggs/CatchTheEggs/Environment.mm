//
//  Environment.m
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Environment.h"

@implementation Environment

-(id)init{
    if((self=[super init])){
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        
        //Add background
        CCSprite* background = [CCSprite spriteWithFile:kBackgroundImage];
        [background setPosition:ccp(screenSize.width/(2), screenSize.height/(2))];
        [self addChild:background];
        
        //Add buildings and clouds
        _clouds = [CCSprite spriteWithFile:kCloudImage];
        _buildings=[CCSprite spriteWithFile:kBuildingsImage];
        _flipedBuildings = [CCSprite spriteWithFile:kBuildingsImage];
        _flipedBuildings.scaleX *= -1.f;
        
        //set anchor points
        _clouds.anchorPoint = CGPointMake(0, 1);
        _buildings.anchorPoint = CGPointMake(0, 1);
        _flipedBuildings.anchorPoint = CGPointMake(2, 1);
        
        CGPoint topOffset = CGPointMake(0, screenSize.height);
        CCParallaxNode* paraNode = [CCParallaxNode node];
        
        //add layers(cloud, building, fliped building)
        [paraNode addChild:_clouds
                         z:1
             parallaxRatio:CGPointMake(0.5f, 0)
            positionOffset:topOffset];
        
        [paraNode addChild:_buildings
                         z:1
             parallaxRatio:CGPointMake(0.5f, 0)
            positionOffset:topOffset];
        
        [paraNode addChild:_flipedBuildings
                         z:1
             parallaxRatio:CGPointMake(0.5f, 0)
            positionOffset:topOffset];
        [self addChild:paraNode z:0 tag:21];
        
    }
    return self;
}

-(void)scrollBackground:(float)velocity_x{
    
    //Move the clouds
    CGSize screenSize = [[CCDirector sharedDirector] winSize];
    CGPoint pos = _clouds.position;
    if(velocity_x >0)
        pos.x -=1.5f*velocity_x;
    if(pos.x < -screenSize.width){
        pos.x += (screenSize.width * 2) + (arc4random()%200);
    }
    _clouds.position=pos;
    
    //Move the buildings
    CGPoint pos2= _buildings.position;
    if(velocity_x >0)
        pos2.x -=0.5f*velocity_x;
    if(pos2.x <= -(screenSize.width)){
        pos2.x += (screenSize.width * 2);
    }
    _buildings.position=pos2;
    
    //Move 2nd building image
    CGPoint pos3= _flipedBuildings.position;
    if(velocity_x >0)
        pos3.x -=0.5f*velocity_x;
    if(pos3.x <= -(2*screenSize.width)){
        pos3.x += (screenSize.width * 2);
    }
    _flipedBuildings.position=pos3;
}

@end
