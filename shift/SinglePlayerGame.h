//
//  SinglePlayerGame.h
//  shift
//
//  Created by Brad Misik on 2/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "GameScene.h"

@interface SinglePlayerGame : GameScene
{
    int currentLevel;
}

+(SinglePlayerGame *) gameWithLevel:(int)level;

-(id) initWithLevel:(int)level;

@end
