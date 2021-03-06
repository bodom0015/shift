//
//  SinglePlayerGame.m
//  shift
//
//  Created by Brad Misik on 2/19/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SinglePlayerGame.h"
#import "MainMenu.h"
#import "GameCenterHub.h"

@implementation SinglePlayerGame

+(SinglePlayerGame *) gameWithLevel:(int)level
{
    return [[SinglePlayerGame alloc] initWithLevel:level];
}

-(id) initWithLevel:(int)level
{
    if ((self = [super init])) {
        currentLevel = level;
        CGSize screenSize = [[CCDirector sharedDirector] winSize];
        boardCenter = CGPointMake((screenSize.width / 2), (screenSize.height / 2));
        
        board = [BoardLayer boardWithFilename:[NSString stringWithFormat:@"%d.plist", currentLevel]
                                       center:boardCenter
                                     cellSize:cellSize];
        
        [self addChild:board];
    }
    return self;
}

-(void) onGameStart
{
  //Your stuff here
  
  [super onGameStart];
}

-(void) onGameEnd
{
  [super onGameEnd];
  
  GKAchievement* achievement = [[GameCenterHub sharedInstance] addOrFindIdentifier:@"beat_game"];
  if (![achievement isCompleted]) 
  {
    [[GameCenterHub sharedInstance] reportAchievementIdentifier:@"beat_game" percentComplete:100.0];
    [[GameCenterHub sharedInstance] achievementCompleted:@"Oh Shift! Conqueror" message:@"Successfully completed a level of Oh Shift!"];
  }
}

-(void) onNextGame
{
    [self removeChild:board cleanup:YES];
    currentLevel++;
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSInteger highestLevel = [defaults integerForKey:@"highestLevel"];
    
    //If user beat a new level, save the progress
    if(currentLevel > highestLevel)
    {
        [defaults setInteger:currentLevel forKey:@"highestLevel"];
        [defaults synchronize];
    }

    //If user completed all levels, return to Main Menu (for now). Maybe display some congratulatory message? Fireworks?
    if(currentLevel > NUM_LEVELS)
    {
        [[CCDirector sharedDirector] replaceScene:[CCTransitionSlideInL transitionWithDuration:kSceneTransitionTime scene:[MainMenu scene]]];
    }
    else
    {
        board = [BoardLayer boardWithFilename:[NSString stringWithFormat:@"%d.plist", currentLevel]
                                   center:boardCenter
                                 cellSize:cellSize];
        [self addChild:board];
    }
}
                             
@end
