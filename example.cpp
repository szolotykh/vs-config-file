#include <stdio.h>
#include <conio.h>
#include "configFile.h"

using namespace std;

// Default values for variables
int port=7777;
string address="127.0.0.1";
float max_num=30.1;


int main(){
	cout<<"=== Test of config file class ==="<<endl;

	// Create config file object
	configFile f1;
	// Read config file
	if(!f1.read("example.conf")){
		cout<<f1.getLastErrMsg()<<endl;
		getch();
		return 0;
	}
	// Get value from file
	f1.getValue("address", address);
	f1.getValue("port", port);
	f1.getValue("max_num", max_num);

	// Display variables
	cout<<"Address: "<<address<<endl
		<<"Port: "<<port<<endl
		<<"max_num: "<<max_num<<endl;

	// Wait
	getch();
	return 0;
}

