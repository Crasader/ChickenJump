//#define COCOS2D_DEBUG 1     // to enable CCLOG()

#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;

static const std::string france = "FRANCE";
static const std::string germany = "GERMANY";
static const std::string england = "ENGLAND";
static const std::string spain = "SPAIN";
static const std::string italy = "ITALY";
static const std::string netherlands = "NETHERLANDS";

void StageStatus::createFreshStages() {
    // name, imagefile, score, star, isunlocked, isPlayed
    saveStage(Stage(france, "france.png", 0, 0, true, false));
    saveStage(Stage(germany, "germany.png", 0, 0, false, false));
    saveStage(Stage(england, "england.png", 0, 0, false, false));
    saveStage(Stage(spain, "spain.png", 0, 0, false, false));
    saveStage(Stage(italy, "italy.png", 0, 0, false, false));
    saveStage(Stage(netherlands, "netherlands.png", 0, 0, false, false));
}

Stage StageStatus::getStage(std::string const& name) {
    std::string stage = UserDefault::getInstance()->getStringForKey(name.c_str());
    std::stringstream ss(stage);
    if (ss.rdbuf()->in_avail() == 0) return Stage();
    
    std::string stageName, imageFile;
    int score, star;
    bool isUnlocked, isPlayed;
    ss >> stageName >> imageFile >> score >> star >> isUnlocked >> isPlayed;
    
    return Stage(stageName, imageFile, score, star, isUnlocked, isPlayed);
}

std::vector<Stage> StageStatus::getStage(void) {
    std::vector<Stage> stages;
    stages.push_back(getStage(france));
    stages.push_back(getStage(germany));
    stages.push_back(getStage(england));
    stages.push_back(getStage(spain));
    stages.push_back(getStage(italy));
    stages.push_back(getStage(netherlands));
    
    return stages;
}

void StageStatus::saveStage(Stage const& stage) {
    std::string status = StringUtils::format("%s %s %d %d %d %d",
                                             stage.getName().c_str(), stage.getImageFile().c_str(), stage.getScore(), stage.getStar(), stage.isUnlocked(), stage.isPlayed());
    UserDefault::getInstance()->setStringForKey(stage.getName().c_str(), status);

    UserDefault::getInstance()->flush();
}

void StageStatus::saveStage(std::vector<Stage> const& stages) {
    for (auto i = stages.begin(); i != stages.end(); ++i) {
        saveStage(*i);
    }
}

void StageStatus::unlockStage(Stage& stage) {
    stage.unlock();
    saveStage(stage);
}

void StageStatus::unlockNextStage(const Stage& currentStage) {
    std::vector<Stage> stages = getStage();
    for (int i = 0; i < stages.size() - 1; ++i) {
        if (stages.at(i).getName() == currentStage.getName()) {
            unlockStage(stages.at(i + 1));
        }
    }
}





