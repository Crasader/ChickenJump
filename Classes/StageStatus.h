#ifndef __STAGE_STATUS__
#define __STAGE_STATUS__

#include "cocos2d.h"

class Stage;

class StageStatus
{
public:
    static void createFreshStages();
    static Stage getStage(std::string const& name);
    static std::vector<Stage> getStage(void);
    static void saveStage(Stage const& stage);
    static void saveStage(std::vector<Stage> const& stages);
    static void unlockStage(Stage& name);
    static void unlockNextStage(const Stage& currentStage);
};

#endif /* #define(__STAGE_STATUS__) */
