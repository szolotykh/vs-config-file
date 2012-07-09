#ifndef ERROR_H
#define ERROR_H

#include <string>
// Basic error class:
//	construct and set upon receiving an error.
class Error{
	int code; // Error code
	std::string msg; // Error message
public:
	Error();
	Error(int ecode, std::string emsg);
	int getCode();
	std::string getMessage();
	void set(int ecode, std::string emsg);
};

#endif