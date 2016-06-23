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

string* output_list_502;

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
	ofstream fout("identical_fault_pairs.txt");
	string netlist_filename;
	string fault_filename;

	if(argc != 3)
	{
		cout << "Usage: cada021 <crc.isc> <fault_description.txt>" << endl << endl;
		return 1;
	}
	else
	{
		cout << argv[1] << endl;
		netlist_filename = argv[1];
		cout << argv[2] << endl;
		fault_filename = argv[2];
	}

	fileReading(netlist_filename);
	cout << "-------- netlist reading complete -------" << endl; 
	faultReading(fault_filename);
	cout << "-------- fault reading complete -------" << endl;
	input_list_502 = new string[10];

	//for(int i=0;i<23;i++)
	//cout << fault[15].times << " " << fault[15].id << " " << fault[15].fault << endl;
	
	//cout << "ans: "<< find_booleanfunction( output[1] , fault[0] ) << endl << endl;

	//init input
	cout << "ans: "<< ("( " + find_booleanfunction( output[1] , fault[15], 1 ) + " )" + " ;") << endl << endl;
	input_list_502_idx = 0;
	output_list_502 = new string[10];

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

	
	for(int i = 15; i < 23; i++)
	{
		//cout << "now list the truth table of fault[" << i << "] : "; 
		for(int j = 0; j < 31; j++)
		{	
			input_list_502[1] = intval2str(j % 2);
			input_list_502[3] = intval2str( (j /2) % 2 );
			input_list_502[5] = intval2str( (j /2 /2) % 2 );
			input_list_502[7] = intval2str( (j /2 /2 /2) % 2);
			input_list_502[9] = intval2str( (j /2 /2 /2 /2) );
			//for(int k = 0; k < 5; k++)
			//	cout << input_list_502[k * 2 + 1] << " , ";
			//cout << endl;

			//cout << booleancalc( ("( " + find_booleanfunction( output[1] , fault[i], 0 ) +  " )" + " ;") );
			output_list_502[i -15] += booleancalc( ("( " + find_booleanfunction( output[1] , fault[i], 0 ) +  " )" + " ;") );
			input_list_502_idx = 0;
		}
		//cout << endl;
	}
	
	for(int i = 0; i < 7; i++ )
	{
		for(int j = i + 1; j < 8; j++)
		{
			if(output_list_502[i] == output_list_502[j])
			{
				cout << "when i = " << i << " and j = " << j << " : ";
				cout << i + 16 << " and " << j + 16 << " is the same " ;
				fout << i + 16 << " " << j + 16 << endl;
				cout << " (" << output_list_502[i] << " " << output_list_502[j] << ")" << endl;
			}
		}
	}

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

