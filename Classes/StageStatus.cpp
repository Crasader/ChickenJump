//#define COCOS2D_DEBUG 1     // to enable CCLOG()

#include "Stage.h"
#include "StageStatus.h"

using namespace cocos2d;

const std::string StageStatus::france = "FR";
const std::string StageStatus::germany = "DE";
const std::string StageStatus::england = "UK";
const std::string StageStatus::spain = "SP";
const std::string StageStatus::italy = "IT";
const std::string StageStatus::netherlands = "NL";
const std::string StageStatus::infinite = "INFINITE";

void StageStatus::createFreshStages() {
    // name, imagefile, clicked_image, locked_image, difficulty, score, star, isunlocked, isPlayed
    saveStage(Stage(france, "FR.png", "FR_clicked.png", "FR_locked.png", 1, 0, 0, true, false));
    saveStage(Stage(italy, "IT.png", "IT_clicked.png", "IT_locked.png", 2, 0, 0, true, false));
    saveStage(Stage(england, "UK.png", "UK_clicked.png", "UK_locked.png", 3, 0, 0, true, false));
    saveStage(Stage(germany, "DE.png", "DE_clicked.png", "DE_locked.png", 4, 0, 0, true, false));
    saveStage(Stage(spain, "SP.png", "SP_clicked.png", "SP_locked.png", 5, 0, 0, true, false));
    saveStage(Stage(netherlands, "NL.png", "NL_clicked.png", "NL_locked.png", 6, 0, 0, true, false));
    saveStage(Stage(infinite, "INFINITE.png", "INFINITE_clicked.png", "INFINITE_locked.png", 7, 0, 0, true, false));
}

std::vector<Stage> StageStatus::getStage(void) {
    std::vector<Stage> stages;
    stages.push_back(getStage(france));
    stages.push_back(getStage(italy));
    stages.push_back(getStage(germany));
    stages.push_back(getStage(england));
    stages.push_back(getStage(spain));
    stages.push_back(getStage(netherlands));
    stages.push_back(getStage(infinite));
    
    return stages;
}

Stage StageStatus::getStage(std::string const& name) {
    std::string stage = UserDefault::getInstance()->getStringForKey(name.c_str());
    std::stringstream ss(stage);
    if (ss.rdbuf()->in_avail() == 0) return Stage();
    
    std::string stageName, imageFile, clickedImageFile, lockedImageFile;
    int difficulty, score, star;
    bool isUnlocked, isPlayed;
    ss >> stageName >> imageFile >> clickedImageFile >> lockedImageFile >> difficulty >> score >> star >> isUnlocked >> isPlayed;
    
    return Stage(stageName, imageFile, clickedImageFile, lockedImageFile, difficulty, score, star, isUnlocked, isPlayed);
}

void StageStatus::saveStage(Stage const& stage) {
    std::string status = StringUtils::format("%s %s %s %s %d %d %d %d %d",
                                             stage.getName().c_str(),
                                             stage.getImageFile().c_str(),
                                             stage.getClickedImageFile().c_str(),
                                             stage.getLockedImageFile().c_str(),
                                             stage.getDifficulty(),
                                             stage.getScore(),
                                             stage.getStar(),
                                             stage.isUnlocked(),
                                             stage.isPlayed());
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

void StageStatus::unlockNextStage(Stage const& currentStage) {
    std::vector<Stage> stages = getStage();
    for (int i = 0; i < stages.size() - 1; ++i) {
        if (stages.at(i).getName() == currentStage.getName()) {
            unlockStage(stages.at(i + 1));
        }
    }
}





