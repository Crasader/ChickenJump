//
//  AppDelegate.h
//  CatchTheEggs
//
//  Created by Stephan Krusche on 4/5/13.
//  Copyright TUM LS1 2013. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "cocos2d.h"

// Added only for iOS 6 support
@interface MyNavigationController : UINavigationController <CCDirectorDelegate>
@end

@interface AppController : NSObject <UIApplicationDelegate>

@property (nonatomic, strong) UIWindow *window;
@property (readonly) MyNavigationController *navController;
@property (weak, readonly) CCDirectorIOS *director;

@end
