#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "var.h"
#include "read_file.h"
#include "read_fault.h"
#include "booleangen.h"
#include "classify_and_verify.h"
#include "booleancalc.h"

using namespace std;

int find_trans_output(line &);
int find_trans_list(int );
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
 
	//for(int i=0;i<23;i++)
	//cout << fault[15].times << " " << fault[15].id << " " << fault[15].fault << endl;
	
	cout << "ans: "<< find_booleanfunction( output[1] , fault[17] ) << endl << endl;
	
	//cout << find_trans_list(502) << endl;
	//cout << output[ find_trans_output( trans[ find_trans_list(502) ] ) ].id << endl;
	
	//cout << find_booleanfunction( output[ find_trans_output( trans[ find_trans_list(502) ] ) ], fault[15]) << endl;
 	
	//cout << booleancalc( (find_booleanfunction( output[15] , fault[0] )+" ;") ) << endl;

	return 0;
}

int find_trans_output(line &trans)
{
	line *lineptr;
	lineptr = &trans;
	while(1) //down toward output
	{
		
		for(int i = 0; i < output_num; i++) //find if it exist in output
		{
			if(lineptr -> id == output[i].id)
			{
				return i;
			}
		}
		lineptr = lineptr -> to -> out; //replace to next
	}
}

int find_trans_list(int trans_id)
{
	
	for(int i = 0; i < trans_num; i++) //find if it exist in trans
	{
		//cout << "searching for trans id 502 @ trans[ " << i << " ], id = " << trans[i].id << endl;
		if(trans[i].id == trans_id)
		{
			return i;
		}
	}
	
}

