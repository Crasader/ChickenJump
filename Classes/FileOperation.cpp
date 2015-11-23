// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"
#include <stdio.h>

using namespace std;

void FileOperation::saveFile()
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "w");

	if (! fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return;
	}

	fputs("file example", fp);
	fclose(fp);
}

void FileOperation::readFile()
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "r");
	char buf[50] = {0};

	if (! fp)
	{
		CCLOG("can not open file %s", path.c_str());
		return;
	}

	fgets(buf, 50, fp);
	CCLOG("read content %s", buf);

	fclose(fp);
}

string FileOperation::getFilePath()
{
	string path("");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// In android, every programe has a director under /data/data.
	// The path is /data/data/ + start activity package name.
	// You can save application specific data here.
	path.append("/data/data/com.sixeyes.chickenjump/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // save to document folder
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentsDirectory = [paths objectAtIndex:0];
//    string path = [documentsDirectory UTF8String];
//    path.append( "/test.txt" );
#endif

	return path;
}