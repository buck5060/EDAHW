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
//#include "booleancalc_tree.h"

using namespace std;

int find_trans_output(line &);
int find_line_idx(line* ,int ,int);

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
	input_list_502 = new string[10];

	//for(int i=0;i<23;i++)
	//cout << fault[15].times << " " << fault[15].id << " " << fault[15].fault << endl;
	
	//cout << "ans: "<< find_booleanfunction( output[1] , fault[0] ) << endl << endl;
	cout << "ans: "<< ("( " + find_booleanfunction( output[1] , fault[15], 1 ) + " )" + " ;") << endl << endl;
	input_list_502_idx = 0;

	//cout << find_trans_list(502) << endl;
	//cout << output[ find_trans_output( trans[ find_trans_list(502) ] ) ].id << endl;
	
	//cout << find_booleanfunction( output[ find_trans_output( trans[ find_trans_list(502) ] ) ], fault[15]) << endl;
 


	input_list_502[1] = "1";
	input_list_502[3] = "0";
	input_list_502[5] = "0";
	input_list_502[7] = "1";
	input_list_502[9] = "1";
	

	for(int i = 0; i < 10; i++)
	{
		cout << i << "\t" << input_list_502[i] << endl;
	}

	cout << booleancalc( ("( " + find_booleanfunction( output[1] , fault[22], 0 ) +  " )" + " ;") ) << endl << endl;
	input_list_502_idx = 0;
	
	//cout << booleancalc( (find_booleanfunction( output[1] , fault[16] )+" ;") ) << endl;
	//cout << booleancalc(  ) << endl;

	//cout << find_line_idx(trans, trans_num, 301) << endl;
	




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

int find_line_idx(line *target, int target_num, int line_id)
{
	
	for(int i = 0; i < target_num; i++) //find if it exist in trans
	{
		//cout << "searching for trans id 502 @ trans[ " << i << " ], id = " << target[i].id << endl;
		if(target[i].id == line_id)
		{
			return i;
		}
	}
	return -1;
	
}

