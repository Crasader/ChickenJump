#ifndef __FILE_OPERATION__
#define __FILE_OPERATION__

class StageStat;

class FileOperation 
{
public:
    static void saveFile(std::vector<StageStat> stages);
    static void saveFile(StageStat const& stage);
	static std::vector<StageStat> readFile(void);
	static std::string getFilePath();
};

#endif
