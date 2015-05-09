//
//  Chicken.m
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "Chicken.h"
#import "Box2D.h"
#import "GameLayer.h"
#import "World.h"

#import "SimpleAudioEngine.h"
#import "StandardAnimationComponent.h"

@interface Chicken(){
    b2Body *_body;
    BOOL _isSoundActive;
    id<AnimationComponent> animationComponent;
}

@end

@implementation Chicken

// Init
- (id) initWithGame:(World*)game {
	
	if ((self = [super init])) {        
		self.game = game;
        
        //Add the chicken sprite
		self.sprite = [CCSprite spriteWithFile:kChickenSpriteImage ];
        [self addChild:_sprite];
        
        //Setting for Audio
        _isSoundActive = TRUE;
		_body = NULL;
        
        //Preload the sound
        [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:kAudioJump];
        
        //Animation component
        animationComponent = [[StandardAnimationComponent alloc] init];
        
        //Make sound playable after every sec. this is done to stop playing multiple times on one hit
        [self schedule:@selector(activateSound) interval:2];
        [self reset];
	}
	return self;
}

-(void) activateSound{
    _isSoundActive = TRUE;
}

-(void) animateChicken {
    _sprite.visible = YES;
    NSString* baseImageName = kChickenAnimationSpriteImage;
    [animationComponent animate:_sprite withBaseImage:baseImageName];
}

//Redefinition of boundigBox for better Collision detection
-(CGRect)boundingBox{
    
    CGRect temp;
    temp.size = _sprite.contentSize;
    temp.origin = ccpAdd(self.position, ccpMult(ccpFromSize(temp.size), -0.5));
    return temp;
}

// Create the Chicken with his physics properties
- (void) createBox2ChickenBody{
	
    CGPoint startPosition = ccp(kInitialPositionOfChicken_x, kInitialPositionOfChicken_y);
    
    //Create Body b2Body, using: b2BodyDef with properties: type, linearDamping, position, fixedRotation
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.userData = _sprite.userData;
    bd.linearDamping = 0.05f;
    bd.fixedRotation = true;
    bd.position.Set(startPosition.x/PTM_RATIO, startPosition.y/PTM_RATIO);
    _body = _game.world->CreateBody(&bd);
    
    //Create fixture with density, restitution, friction and shape
    b2CircleShape shape;
    shape.m_radius = 0.8 * _sprite.contentSize.width/2/PTM_RATIO;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = .5f;
    fd.restitution = .8f;
    fd.friction = 0.2f;
    _body->CreateFixture(&fd);
    
    
}

//Apply a force (wind effect) to the chicken when there is a collision between the chicken and the line
- (void)applyForce{
    b2Vec2 force = b2Vec2(0.4, 0.4);
    _body->ApplyLinearImpulse(force,_body->GetPosition());
}

//Apply a negative force to the chicken when there is a collision between a black egg and a chicken 
- (void)applyForceEggCollision{
    b2Vec2 force = b2Vec2(-10, 0);
    _body->ApplyLinearImpulse(force,_body->GetPosition());
}

- (void) updateNode{
    // Update the position of the Chicken considering the physic position of the Chicken
    float x = _body->GetPosition().x *PTM_RATIO;
    float y = _body->GetPosition().y *PTM_RATIO;
    self.position = ccp(x,y);
    
    if(_body->GetContactList()){
        if(_isSoundActive){
            [self playSound];
            _isSoundActive=FALSE;
        }
        [self applyForce];
    }
    
    //With the velocity we can change properly the velocity of the background scroll
    self.velocity = _body->GetLinearVelocity();
    
}

-(void)playSound{
    [[SimpleAudioEngine sharedEngine] playEffect:kAudioJump];    
    _isSoundActive = FALSE;
}

- (void) reset {    
    // Destroy body if it exists
    if(_body){
        _game.world->DestroyBody(_body);
    }
	[self createBox2ChickenBody];
	[self updateNode];
}

@end
