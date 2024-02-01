#include "utils.h"
#include <cstdio>
#include <iostream>
#include <fstream>

#if 0
bool readWholeFile(const std::string &filename, std::vector<char> &fileBuffer) {
	bool retVal = false;
	int64_t totalSize = 0;
	FILE *file = fopen(filename.c_str(),"ab");
	if(file) {
		int64_t fileSize = ftell(file);
		fseek(file,0, SEEK_SET);
		std::cout << "file position " << ftell(file) << std::endl;
		while(!feof(file)) {
			char buf[2048] = {'\0'};
			int64_t readBytes = static_cast<int64_t>(fread(&buf[0],1,1, file));
			fileBuffer.insert(fileBuffer.end(),&buf[0], &buf[0]+readBytes);
			totalSize += readBytes;
		}
		fclose(file);
		if(totalSize == fileSize) retVal = true;
	}
	return retVal;
}

#else
bool readWholeFile(const std::string &filename, std::vector<char> &fileBuffer) {
	bool retVal = false;
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if(file.is_open()) {
		std::streamsize fileSize = static_cast<std::streamsize>(file.tellg());
		std::cout << "File size is: " << fileSize << std::endl;
		fileBuffer.reserve(static_cast<std::vector<char>::size_type>(fileSize));
		file.seekg(0);
		std::cout << "file position: " << file.tellg() << std::endl;
		char buf[2048] = {'\0'};
		file.read(&buf[0], fileSize);
		std::cout << "file position: " << file.tellg() << std::endl;
		fileBuffer.insert(fileBuffer.end(),&buf[0], &buf[0]+fileSize);
		file.close();
		retVal = true;
	}
	return retVal;
}
#endif
