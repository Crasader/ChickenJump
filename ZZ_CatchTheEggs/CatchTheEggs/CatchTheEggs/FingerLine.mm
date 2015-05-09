//
//  FingerLine.m
//  CatchTheEggs
//
//  Created by Endri Koci on 07/04/13.
//  Copyright (c) 2013 TUM LS1. All rights reserved.
//

#import "FingerLine.h"
#import "Box2D.h"
#import "World.h"

@interface FingerLine(){
    b2Body *_body;
    b2Vec2 _vectorStart;
    b2Vec2 _vectorEnd;
    b2EdgeShape _shape;
    b2BodyDef _bd;
	float _radius;
}

@end

@implementation FingerLine

- (id) initWithGame:(World*)game {
	
	if ((self = [super init])) {
		self.game = game;
        
        self.vectorStart.SetZero();
        self.vectorEnd.SetZero();
        
        //Create the body of the line
        _bd.type = b2_staticBody;
        _bd.position.Set(0, 0);
        _body = _game.world->CreateBody(&_bd);
        
        _shape.Set(b2Vec2(_vectorStart.x, _vectorStart.y), b2Vec2(_vectorEnd.x, _vectorEnd.y));
        _body->CreateFixture(&_shape, 0.0f);
	}
	return self;
}

//Delete the line if exists and create a new body of the line with the new 'start' and 'end' position
-(void)setNewPosition:(CGPoint)startNew withEnd:(CGPoint)endNew{
    if(_body != nil){
        _body->GetWorld()->DestroyBody(_body);
    }
    _body = _game.world->CreateBody(&_bd);
    b2Vec2 s((startNew.x/PTM_RATIO),startNew.y/PTM_RATIO);
    b2Vec2 e((endNew.x/PTM_RATIO),endNew.y/PTM_RATIO);
    _shape.Set(b2Vec2(s.x, s.y), b2Vec2(e.x, e.y));
    _body->CreateFixture(&_shape, 0.0f);
}

@end
