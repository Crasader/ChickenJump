#ifndef __STAGE_STATUS__
#define __STAGE_STATUS__

#include "cocos2d.h"

class Stage;

class StageStatus
{
public:
    static void                 createFreshStages();
    static Stage                getStage(std::string const& name);
    static std::string          getStageFullname(std::string const& name);
    static std::vector<Stage> 	getStage(void);
    static void                 saveStage(Stage const& stage);
    static void                 saveStage(std::vector<Stage> const& stages);
    static void                 unlockStage(Stage& name);
    static void                 unlockNextStage(Stage const& currentStage);
    
    static int                  incrementFullscreenAdCounter();
    
    static const std::string france;
    static const std::string germany;
    static const std::string england;
    static const std::string spain;
    static const std::string italy;
    static const std::string netherlands;
    static const std::string infinite;
    
private:
    // Extra attribute to maintain fullscreen ad counter
    static unsigned int _fullscreenAdCounter;
};

#endif /* #define(__STAGE_STATUS__) */
