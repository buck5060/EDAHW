#include<iostream>
#include<string>
#include<fstream>

class bollean_grp;

class boolean_grp
{
	public:
		boolean_grp *next;
		string *booleanFunct;
		int length; //number of element
		boolean_grp();
		~boolean_grp();

};

boolean_grp::boolean_grp()
{
	//length = len;
	//next = new boolean_grp[length];
	//booleanFunct = new string[length];
}

boolean_grp::~boolean_grp()
{}


