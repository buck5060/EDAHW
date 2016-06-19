#include <iostream>
#include <fstream>
#include <string>
#include "var.h"
#include "read_file.h"
#include "read_fault.h"
#include "booleangen.h"
#include <sstream>
using namespace std;


//void foo(line &)
//line* input;
//line* output;
//line* trans; //intermediate line
//gate* gates;

//int input_num = 0;
//int output_num = 0;
//int dff_num = 0;
//int gate_num = 0;

int main(int argc, char *argv[])
{
	fileReading();
 
	faultReading();
 
	 for(int i=0;i<23;i++)
	 cout << fault[i].times << " " << fault[i].id << " " << fault[i].fault << endl;
 
 
  
	return 0;
}



