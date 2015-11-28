//#define COCOS2D_DEBUG 1     // to enable CCLOG()

#include "cocos2d.h"
#include "FileOperation.h"
#include "StageStat.h"

using namespace cocos2d;

void FileOperation::saveFile(StageStat const& stage)
{
    try {
        std::vector<StageStat> stages = readFile();
        
        for (int i = 0; i < stages.size(); ++i) {
            if (stages.at(i).getName() == stage.getName()) {
                stages[i] = stage;
            }
        }
        
        saveFile(stages);
        
    } catch (...) {
        CCLOG("Exception::FileOperation: during single stage write");
    }
    
}
void FileOperation::saveFile(std::vector<StageStat> stages)
{
    try {
        std::string path = getFilePath();
        FILE* fw = fopen(path.c_str(), "wb");
        
        if (not fw) {
            CCLOG("can not create file %s", path.c_str());
            return;
        }
        
        int count = stages.size();
        fwrite(&count, sizeof(int), 1, fw);

        for (int i = 0; i < count; ++i) {
            fwrite(&stages.at(i), sizeof(StageStat), 1, fw);
        }
        
        fclose(fw);
        
    } catch (...) {
        CCLOG("Exception::FileOperation: during %lu stages write", stages.size());
    }
}

std::vector<StageStat> FileOperation::readFile()
{
    std::vector<StageStat> stages;

    try {
        std::string filePath = getFilePath();
        FILE* fr = fopen(filePath.c_str(), "rb");
        
        if (not fr) {
            CCLOG("can not open file %s", filePath.c_str());
            return stages;
        }
        
        int count;
        fread(&count, sizeof(int), 1, fr);
        
        StageStat ss;
        for(int i = 0; i < count; i++) {
            fread(&ss, sizeof(StageStat), 1, fr);
            stages.push_back(ss);
        }
        
        fclose(fr);
        
    } catch (...) {
        CCLOG("Exception::FileOperation: during file read");
    }
    return stages;
}

std::string FileOperation::getFilePath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string path = "/storage/sdcard0/Android/data/com.sixeyes.chickenjump";
    FileUtils::getInstance()->createDirectory(path);
    return path + "/stagestat.txt";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return FileUtils::getInstance()->getWritablePath() + "stagestat.txt";
#endif
    return "";
}

