//
//  World.m
//  CatchTheEggs
//
//  Created by Endri Koci on 09/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//


#import "World.h"

@interface World(){
    CGPoint _startPointTouch;
    CGPoint _endPointTouch;
    CGSize screenSize;
    CCArray *_eggArray;
    int _eggCollected;
    Egg *lastEggOfTheArray;
    CCSprite* arrow;
    CCSprite* finger;
    BOOL gameStarted;        //flag for handling the how to play animation at the begening
}

@end

@implementation World

- (id)init{
    if ((self = [super init])) {
        
        [self setTouchEnabled:YES];
        screenSize = [[CCDirector sharedDirector] winSize];
        
        //Create the physic 'world'
        [self createBox2DWorld];
        
        //Score
        _score = 0;
        _eggCollected = 0;
        
        gameStarted = FALSE;
        
        // Initialize the draw line
        self.fingerLine =[[FingerLine  alloc]initWithGame:self];
        
        // Set the left edge
        [self drawLeftEdge];
        
        self.chicken = [[Chicken alloc]initWithGame:self];
        [self addChild:_chicken z:1 tag:1];
        
        //initialize egg array with good and bad eggs
        [self initEggs];
        
        //preload audio
        [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:kAudioEggCollected];
        [[SimpleAudioEngine sharedEngine] preloadBackgroundMusic:kAudioBadEggHit];        
        
        //Create the arrow to indicate out of screen chicken
        arrow=[CCSprite spriteWithFile:kArrowImage];
        arrow.visible = TRUE;
        [arrow setPosition:ccp(self.chicken.position.x, screenSize.height - arrow.boundingBox.size.height/2)];
        [self addChild:arrow];
        
        //Create the finger sprite
        finger=[CCSprite spriteWithFile:kFinger];
        CCMoveBy *fingerMovementStart =[CCMoveTo actionWithDuration:1 position:ccp(-kInitialPositionOfChicken_x/PTM_RATIO,finger.position.y + finger.boundingBox.size.height)];
        CCMoveTo *fingerMovementEnd =[CCMoveTo actionWithDuration:1 position:ccp(screenSize.width/2,finger.position.y + finger.boundingBox.size.height)];
        CCSequence *sequence =[CCSequence actions:fingerMovementStart,fingerMovementEnd, nil];
        CCRepeatForever* repeat = [CCRepeatForever actionWithAction:sequence];
        [finger runAction:repeat];
        
        [self addChild:finger z:1 tag:11];

        //schedule chicken animation
        [self schedule:@selector(initChickenAnimation) interval:1.0f];
        
		[self scheduleUpdate];
    }
    return self;
}

//called every second for chicken flying animation
-(void) initChickenAnimation{
    [self.chicken animateChicken];
}

//freeing memory
-(void) dealloc
{
    delete _world;
}

//creating world with gravity
-(void)createBox2DWorld{
    b2Vec2 gravity = b2Vec2(kWorldGravity_x,-kWorldGravity_y);
    _world = new b2World(gravity);
}

//draw the left boundary. so that the chicken doesnt go beyond the left bar
-(void) drawLeftEdge
{
    // Size of the window
    CGSize winSize= [[CCDirector sharedDirector]winSize];
    
	float height = winSize.height;
    
    // Create the body of the left edge
    b2BodyDef leftEdge;
    leftEdge.type = b2_staticBody;
    leftEdge.position.Set(0, 0);
    
    b2EdgeShape shape;
    shape.Set(b2Vec2(0,0), b2Vec2(0,height/PTM_RATIO));
    b2Body *staticBody = _world->CreateBody(&leftEdge);
    
    // Creating fixture for body
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &shape;
    staticBody->CreateFixture(&myFixtureDef);
    
}

//user draws a line on the screen
-(void)draw{    
    glLineWidth(4.0f);
    
    ccDrawLine( _startPointTouch, _endPointTouch);

    [super draw];
}

-(void) initEggs{
    // good or bad eggs !!! 0 to 8->good 9 to 10->bad
    BOOL goodOrBad = 0;
    // Initialize the eggs array using alloc init
    _eggArray = [[CCArray alloc] initWithCapacity:kEggNumber];
    for (int i = 0; i < kEggNumber ; i++) {
        goodOrBad = arc4random() % 10;
        
        Egg* egg;
        if(goodOrBad > kGoodEggPercentage){
            egg = [[Egg alloc] initBadEggWithGameWorld:self];
            egg.goodOrBad = false;
        }
        else{
            egg = [[Egg alloc] initGoodEggWithGameWorld:self];
            egg.goodOrBad = true;
        }
        
        [_eggArray addObject:egg];
    }
    
    [self setEggsPosition];

}

//set random position for eggs
-(void) setEggsPosition{
    int x = self.chicken.position.x;
    x = x + screenSize.width +arc4random() % 100;
    for (int i =0 ; i < kEggNumber; i++) {
        float egg_x = x + (i+1)*(screenSize.width/7);
        float egg_y = arc4random() % (int)screenSize.height;
        Egg *egg = [_eggArray objectAtIndex:i];
        [egg.sprite setPosition:ccp(egg_x, egg_y)];
        [egg.sprite setVisible:YES];
    }
}

//get the first point of the line user drawing
-(void)ccTouchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:[touch view]];
    location = [[CCDirector sharedDirector] convertToGL:location];
    location.x += -kInitialPositionOfChicken_x +self.chicken.position.x;
    _startPointTouch = location;
    _endPointTouch = location;
    
}

- (void)ccTouchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    int maxLineLength = screenSize.width / 3;
    
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView:[touch view]];
    location = [[CCDirector sharedDirector] convertToGL:location];
    location.x += -kInitialPositionOfChicken_x +self.chicken.position.x;
    
    if(ccpDistance(_startPointTouch, location) < maxLineLength){
        _endPointTouch = location;
    }
    
}

- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInView: [touch view]];
    location = [[CCDirector sharedDirector] convertToGL: location];
    
    float distance = ccpDistance(_startPointTouch, _endPointTouch);
    if (distance > 1)
    {
        [_fingerLine setNewPosition:_startPointTouch withEnd:_endPointTouch];
    }
    
    //after the first line been drawn, start the game. and make invisible the instruction animation
    if(!gameStarted){
        [finger stopAllActions];
        finger.visible = FALSE;
        gameStarted = TRUE;
    }
    
}

- (void) update:(ccTime)dt {
    
    //Call step method on world which will update all bodies, using: world->Step()
    int32 velocityIterations= 8;
    int32 positionIterations = 3;
    if(gameStarted)
        _world->Step(dt, velocityIterations, positionIterations);
    
    
    //Update the position of the chicken
	[_chicken updateNode];
    //Update the position of the World considering the position of the chicken
    [self setPosition:ccp(kInitialPositionOfChicken_x - self.chicken.position.x,self.position.y)];
        
    //Reset all eggs when array of eggs has passed the chicken
    lastEggOfTheArray = [_eggArray lastObject];
    if(self.chicken.position.x - kInitialPositionOfChicken_x > lastEggOfTheArray.sprite.position.x){
       [self setEggsPosition];        
    }
    
    //Set the position of the arrow that is following the chicken
    [arrow setPosition:ccp(self.chicken.position.x, arrow.position.y)];
    if(screenSize.height<self.chicken.position.y)
        arrow.visible = TRUE;
    else
        arrow.visible = FALSE;
    
    [self checkForCollision];
}

-(void) checkForCollision {
    // Detect collision of Chicken with Egg
    CGRect chickenBoundingBox = [self.chicken boundingBox];
    for (Egg* egg in _eggArray) {
        if ([egg collidesWithChicken:chickenBoundingBox]) {
            //_score++ if chicken hits good egg
            if (egg.goodOrBad) {
                _eggCollected++;
                [self playSound:kAudioEggCollected];
            } else{
                [self.chicken applyForceEggCollision];
                [self playSound:kAudioBadEggHit];
            }
            
            [self updateScore];
        }
    }
}

-(void) playSound:(NSString*) sound{
    [[SimpleAudioEngine sharedEngine] playEffect:sound];
}

-(void) updateScore{
    _score = _eggCollected;
}

@end
