//
//  GameConfig.h
//  shift
//
//  Created by Brad Misik on 8/17/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

//
// Supported Autorotations:
//		None,
//		UIViewController,
//		CCDirector
//
#define kGameAutorotationNone 0
#define kGameAutorotationCCDirector 1
#define kGameAutorotationUIViewController 2

//
// Define here the type of autorotation that you want for your game
//

// 3rd generation and newer devices: Rotate using UIViewController. Rotation should be supported on iPad apps.
// TIP:
// To improve the performance, you should set this value to "kGameAutorotationNone" or "kGameAutorotationCCDirector"
#if defined(__ARM_NEON__) || TARGET_IPHONE_SIMULATOR
#define GAME_AUTOROTATION kGameAutorotationUIViewController

// ARMv6 (1st and 2nd generation devices): Don't rotate. It is very expensive
#elif __arm__
#define GAME_AUTOROTATION kGameAutorotationNone


// Ignore this value on Mac
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)

#else
#error(unknown architecture)
#endif


//Describes the current movement occurring on a block train
typedef enum Movement {
    kMovementColumn,
    kMovementRow,
    kMovementNone
} Movement;

typedef enum Difficulty {
    kDifficultyEasy = 3,
    kDifficultyMedium = 5,
    kDifficultyHard = 7
} Difficulty;

typedef enum gamemode {
    QUICKPLAY,
    SINGLE,
    RANDOMMULTI,
    FRIENDMULTI,
    LEADERBOARD,
    HARDTIMELB,
    HARDMOVELB
} gamemode;

//NOTE: if you change this value, you must change the way the levels are displayed in SinglePlayerMenu.m to correspond with
//the number of levels. Look for the line [menu alignItemsInColumns ....
#define NUM_LEVELS 20

#define len(array) (sizeof((array))/sizeof(typeof((array[0]))))

//Scene transition time
#define kSceneTransitionTime 0.3f

#define kMinCollisionForce 30.0

//id lastQuickPlayGame = nil;
//id lastSinglePlayerGame = nil;

static NSMutableDictionary *colors;
__attribute__((constructor))
static void initialize_colors() {
    @autoreleasepool {
        colors = [[NSMutableDictionary alloc] initWithCapacity:20];
        NSString *path = [[NSBundle mainBundle] pathForResource:@"colors" ofType:@"plist"];
        NSDictionary *plist = [NSDictionary dictionaryWithContentsOfFile:path];
        NSDictionary *defaults = [plist objectForKey:@"default"];
        NSArray *colorNames = [defaults allKeys];
        for (NSArray *colorName in colorNames) {
            NSArray *colorValues = [defaults objectForKey:colorName];
            ccColor3B color = ccc3([[colorValues objectAtIndex:0] intValue],
                                   [[colorValues objectAtIndex:1] intValue],
                                   [[colorValues objectAtIndex:2] intValue]);
            [colors setObject:[NSData dataWithBytes:&color length:sizeof(color)] forKey:colorName];
        }
    }
}

#endif // __GAME_CONFIG_H

