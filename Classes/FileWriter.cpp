#include "FileWriter.h"
void FileWriter::writeFirstTime(std::string fileName){

	std::string wpath = FileUtils::sharedFileUtils()->getWritablePath() + fileName;
	std::string directory;
	const size_t last_slash_idx = wpath.rfind('/');
	if (std::string::npos != last_slash_idx)
	{
		directory = wpath.substr(0, last_slash_idx);
	}

	if (FileUtils::getInstance()->isFileExist(wpath))
		return;

	if (!FileUtils::getInstance()->isDirectoryExist(directory))
	{
		FileUtils::getInstance()->createDirectory(directory);
	}
	FILE *fp = fopen(wpath.c_str(), "w+");
	//for (std::string line : lines){
	//	const char* conv_my_str = line.c_str();
	//	fputs(conv_my_str, fp);
	//}

	fclose(fp);
}

//void write(std::string path, std::string content)
//{
//	/*string wpath = FileUtils::sharedFileUtils()->getWritablePath() + path;
//	string directory;
//	const size_t last_slash_idx = wpath.rfind('/');
//	if (std::string::npos != last_slash_idx)
//	{
//	directory = wpath.substr(0, last_slash_idx);
//	}
//	if (!FileUtils::getInstance()->isDirectoryExist(directory))
//	{
//	FileUtils::getInstance()->createDirectory(directory);
//	}
//	FILE *fp = fopen(wpath.c_str(), "w+");
//	fputs(content.c_str(), fp);
//
//	fclose(fp);*/
//}