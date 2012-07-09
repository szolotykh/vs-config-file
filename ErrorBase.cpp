#include "ErrorBase.h"

//SET_LAST_ERROR
void ErrorBase::setLastError(int ecode, std::string emsg){
	lastError.set(ecode, emsg);
};
void ErrorBase::setLastError(Error err){
	lastError=err;
}
//GET_LAST_ERROR
Error ErrorBase::getLastErr(){
	return lastError;
};
//GET_LAST_ERROR_CODE
int ErrorBase::getLastErrCode(){
	return lastError.getCode();
};
//GET_LAST_ERROR_MSG
std::string ErrorBase::getLastErrMsg(){
	return lastError.getMessage();
};