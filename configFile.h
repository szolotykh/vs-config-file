/*
ConfigFile.h
Last edition: 07/09/2012
*/
#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "ErrorBase.h"

using namespace std;

#define CF_OPEN_FILE_ERR 1
#define CF_SINTAXIS_ERR 5
#define CF_NAME_IS_NOT_PRESENT 10
#define CF_VALUE_CONVERT_ERR 15

//------Class cFileNote----------
class cFileNote{
	string name; // Name of variable
	string value; // Value of variable
public:
	cFileNote(string n, string v){ name=n; value=v; };
	string getStrValue(){ return value; };
	string getName(){ return name; };
	bool operator==(cFileNote el){ return name==el.name; };
	bool operator==(string varName){ return name==varName; };
	template <class data_t> bool getValue(data_t &var);
};

template <class data_t> bool cFileNote::getValue(data_t &var){
	// Convert note value type from string to type of var
	// (char, string, int, float, double)
	std::stringstream st;
	st << this->getStrValue();
	return !(st >> var).fail();
};

//-----class configFile-------------
class configFile: public  vector<cFileNote>, public ErrorBase{
public:
	bool read(char *fileName);
	template <class data_t> bool getValue(string varName, data_t &var);
};

template <class data_t> bool configFile::getValue(string varName, data_t &var){
	for(int i=0;i<this->size();i++){
		if(this->at(i)==varName){
			if(!this->at(i).getValue(var)){
				setLastError(
					CF_VALUE_CONVERT_ERR,
					"Value can not be converted.");
				return false;
			}
			return true;
		}
	}
	setLastError(
		CF_NAME_IS_NOT_PRESENT,
		"Name isn't in a config file.");
	return false;
};
#endif