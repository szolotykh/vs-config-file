#include "Error.h"
// Basic error class:
//	construct and set upon receiving an error.
Error::Error(){
	this->code = 0; msg = "Error not occurred.";
};

Error::Error(int ecode, std::string emsg){
	this->code = ecode; msg = emsg;
};

int Error::getCode(){
	return code;
};
	
std::string Error::getMessage(){
	return msg;
};

void Error::set(int ecode, std::string emsg) {
		code = ecode; msg = emsg;
};
