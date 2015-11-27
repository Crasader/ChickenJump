//#define COCOS2D_DEBUG 1     // to enable CCLOG()

#include "cocos2d.h"
#include "FileOperation.h"

using namespace cocos2d;

void FileOperation::saveFile(StageStat const& stage)
{
    try {
        std::vector<StageStat> stages = readFile();
        
        for (uint8_t i = 0; i < stages.size(); ++i) {
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
        FILE *fp = fopen(path.c_str(), "wb");
        
        if (not fp) {
            CCLOG("can not create file %s", path.c_str());
            return;
        }
        
        uint8_t size = stages.size();
        fwrite(&size, sizeof(uint8_t), 1, fp);
        for (uint8_t i = 0; i < size; ++i) {
            fwrite(&stages.at(i), sizeof(StageStat), 1, fp);
        }
        
        fclose(fp);
        
    } catch (...) {
        CCLOG("Exception::FileOperation: during %lu stages write", stages.size());
    }
}

std::vector<StageStat> FileOperation::readFile()
{
    std::vector<StageStat> stages;

    try {
        std::string path = getFilePath();
        FILE *fp = fopen(path.c_str(), "rb");
        
        if (not fp) {
            CCLOG("can not open file %s", path.c_str());
            return stages;
        }
        
        uint8_t count;
        fread(&count, sizeof(uint8_t), 1, fp);

        StageStat ss;
        for(uint8_t i = 0; i < count; i++) {
            fread(&ss, sizeof(StageStat), 1, fp);
            stages.push_back(ss);
        }
        
        fclose(fp);
        
    } catch (...) {
        CCLOG("Exception::FileOperation: during file read");
    }
    return stages;
}

std::string FileOperation::getFilePath()
{
    std::string path = FileUtils::getInstance()->getWritablePath() + "stagestatus.txt";
    return path;
}

