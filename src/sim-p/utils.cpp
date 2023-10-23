#include "utils.h"
#include <fstream>


bool readWholeFile(const std::string &filename, std::vector<char> &fileBuffer) {
	bool retVal = false;
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if(file.is_open()) {
		std::streamsize fileSize = static_cast<std::streamsize>(file.tellg());
		fileBuffer.reserve(static_cast<std::vector<char>::size_type>(fileSize));
		file.seekg(0);
		file.read(fileBuffer.data(), fileSize);
		file.close();
		retVal = true;
	}
	return retVal;
}
