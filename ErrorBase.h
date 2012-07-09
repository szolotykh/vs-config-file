#ifndef ERROR_BASE_H
#define ERROR_BASE_H

#include "Error.h"
#include <string>

class ErrorBase{
	Error lastError;
protected:
	void setLastError(int ecode, std::string emsg);
	void setLastError(Error err);
public:
	Error getLastErr();
	int getLastErrCode();
	std::string getLastErrMsg();
};

#endif