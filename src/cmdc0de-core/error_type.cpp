
#include <sstream>

#include "error_type.h"
#include <string.h>

using namespace cmdc0decore;

std::map<uint32_t, ErrStrHandler *> ErrorType::mESHandlerMap;

std::string ErrorType::getOSErrorString() const {
	return getOSErrorString(getOSError());
}

//static version
std::string ErrorType::getOSErrorString(uint32_t nError) {
#ifdef WIN32 
	char lpSource[1024];
	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		0, nError,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		lpSource, 1024, 0);
	return lpSource;

#else
	return ::strerror(static_cast<int>(nError));
#endif
}

void ErrorType::getApplicationErrorString(std::string &errStr) const {
	uint32_t fac = getErrorFacility();
	if( mESHandlerMap[fac] ) {
		// facility registered an ErrStrHandler
		errStr.assign(mESHandlerMap[fac]->getErrorString(getClientError()));
	}
	else {
		std::ostringstream os;
		os << "Not Completely implemented yet, Error Number is: "
			<< getError()
			<< " Facility is: " << getErrorFacility()
			<< std::ends;
		errStr.assign(os.str().c_str());
	}
}

void ErrorType::addHandler(uint32_t facility, ErrStrHandler *facErrStrHandler) {
	mESHandlerMap[facility] = facErrStrHandler;
}

void ErrorType::removeHandler(uint32_t facility) {
	delete mESHandlerMap[facility];
	mESHandlerMap[facility] = 0;
	mESHandlerMap.erase(facility);
}

