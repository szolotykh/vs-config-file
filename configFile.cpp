/*
Last edition: 10/01/2011
*/
#include "configFile.h"


bool configFile::read(char *fileName){
	ifstream myfile;
	string sFile="";
	char ch1, ch2;
	bool fComment1=false;//  Type //
	bool fComment2=false;//  Type /* */

	try{
		//Open config file
		myfile.open(fileName);
		if(!myfile.is_open())
			throw Error(CF_OPEN_FILE_ERR,"Error opening config file.");
		myfile.unsetf(ios::skipws);

		//Read file to sFile and delete comments
		if(!myfile.eof())
			myfile >> ch1;

		while(!myfile.eof()){
			myfile >> ch2;
			if(!myfile.eof()){
				if(!fComment1 && !fComment2){ //Begining of the comment
					if(ch1==47 && ch2==47){// '/'=47
						fComment1=true;
						sFile=sFile+" ";//Replacing comment with " "
						ch1=ch2;
						continue;
					}
					if(ch1==47 && ch2=='*'){// '/'=47
						fComment2=true;
						sFile=sFile+" ";//Replacing comment with " "
						ch1=ch2;
						continue;
					}
					sFile=sFile+ch1;
				}
				if(fComment1 && !fComment2){ //End of the comment
						if(ch2=='\n'){
						fComment1=false;
						ch1=ch2;
						continue;
					}

				}
				if(fComment2 && !fComment1){ //End of the comment
						if(ch1=='*' && ch2==47){
						fComment2=false;
						ch1=' ';
						continue;
					}
				}
				ch1=ch2;
			}
		}
		if(!fComment1 && !fComment2)
			sFile=sFile+ch1;
		//-------------------------
		
		//Delete every thing aftre last ';'
		int p=sFile.rfind(";");
		if(p==-1)
			throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
		
		//cout<<sFile<<endl<<sFile.length()<<" p= "<<p<<endl;
		
		if(p!=sFile.length()){
			string sEnd=sFile.substr(p+1);
			int j=0;
			while(j<sEnd.length()){
				if(sEnd[j]!=' ' && sEnd[j]!='\n')//check if ending of file
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error1.");
				j++;
			}
			sFile=sFile.substr(0,p+1);
		}
		//-------------------------
		int k=0;
		while(k<sFile.length()){
			string str="";
			
			while(k<sFile.length()){
				if(sFile[k]==';'){
					k++; break;
				}
				str=str+sFile[k];
				k++;
			}

			int i=0;
			string name="";
			string value="";
			bool fName=true;
	
			int pos = str.find("=");
			if(pos==-1)
				throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
			name=str.substr(0,pos);
			value=str.substr(pos+1);

			//----Check name on error and delete spaces and line ends----
			string buff="";
			i=0;
			fName=false;
			bool fNameEnd=false;
			while(i<name.length()){
				if(!fName && !fNameEnd){
					if(name[i]==' '||name[i]=='\n'){
						i++;
						continue;
					}
					if((name[i]>=97&&name[i]<=122)||(name[i]>=65&&name[i]<=90)||(name[i]>=48&&name[i]<=57)||(name[i]=='_')){
						buff=buff+name[i];
						fName=true;
						i++;
						continue;
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}
				if(fName && !fNameEnd){
					if(name[i]==' '){
						fName=false;
						fNameEnd=true;
						i++; continue;
					}
					if((name[i]>=97&&name[i]<=122)||(name[i]>=65&&name[i]<=90)||(name[i]>=48&&name[i]<=57)||(name[i]=='_')){
						buff=buff+name[i];
						i++; continue;
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}
				if(!fName && fNameEnd){
					if(name[i]==' '){
						i++; continue;
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}
				
			}
			name=buff;

			//----Check value on error and delete spaces and line ends----
			buff="";
			i=0;
			bool fValue=false;
			bool fValueEnd=false;
			bool fValueType=false; //false is number, true is string;
			bool fValueDot=false;

			while(i<value.length()){
				if(!fValue && !fValueEnd){
					if(value[i]==' '||value[i]=='\n'){
						i++; continue;
					}
					if((value[i]>=48&&value[i]<=57)){//Number started
						buff=buff+value[i];
						fValue=true;
						i++; continue;
					}
					if(value[i]=='"'){//String started
						fValueType = true;
						fValue=true;
						i++; continue;
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}
				// if value is numver(fValueType=false)
				if(fValue && !fValueEnd && !fValueType){
					if(value[i]==' '){
						fValue=false;
						fValueEnd=true;
						i++; continue;
					}
					if(value[i]>=48&&value[i]<=57){
						buff=buff+value[i];
						i++; continue;
					}
					if(value[i]=='.'){
						if(!fValueDot){
							if(i==value.length()-1){//check if user put '.' at the end of number
								throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
							}
							buff=buff+value[i];
							i++;
							fValueDot=true;
							continue;
						}else{
							throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
						}
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}

				// if value is string(fValueType=true)
				if(fValue && !fValueEnd && fValueType){
					if(value[i]=='"'){
						fValue=false;
						fValueEnd=true;
						i++; continue;
					}
					if(i==value.length()-1){//check if user forgot close quotes
						throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
					}
					buff=buff+value[i];
					i++; continue;	
				}

				if(!fValue && fValueEnd){
					if(value[i]==' '){
						i++; continue;
					}
					throw Error(CF_SINTAXIS_ERR,"File sintaxis error.");
				}
				
			}
			value=buff;
			//----------------------
			//cout<<"Command: "<<name<<", Value: "<<value<<endl;
			this->push_back(cFileNote(name,value));
		}
	}
	catch(Error err){
		setLastError(err);
		this->clear();
		myfile.close();
		return false;
	}
	return true;
};