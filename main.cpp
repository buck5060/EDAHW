#include <iostream>
#include <fstream>
#include <string>
#include "var.h"
#include "read_file.h"

using namespace std;


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


	/* List for all gate infomation
	cout << endl << "/Gate read---------" << endl;
	for(int i = 0; i < gate_num; i++)
	{
		cout << "i = " << i << endl;
		cout << "Gate Type : " << gates[i].type << endl;
		cout << "in1 id : " << gates[i].in1 -> id << endl;
		if(gates[i].in2 != nullptr)
		{
			cout << "in2 id : " << gates[i].in2 -> id << endl;
		}
		cout << "out id : " << gates[i].out -> id << endl;
		cout << endl;
	}
	*/
	
	/*check for muti output drive
	int printed = 0;
	for(int i = 0; i < gate_num; i++)
	{
		for(int j = 0; j < gate_num; j++)
		{
			if(gates[i].out -> id == gates[j].in1 -> id)
			{
				cout << "output gate_i / output id : " << i << " / " << gates[i].out -> id << " drives" << endl;
				cout << "input1 gate_j / input1 id : " << j << " / " << gates[j].in1 -> id << endl;
				printed = 1;
			}

			if(gates[i].out -> id == gates[j].in2 -> id)
			{
				cout << "output gate_i / output id : " << i << " / " << gates[i].out -> id << " drives" << endl;
				cout << "input2 gate_j / input2 id : " << j << " / " << gates[j].in2 -> id << endl;
				printed = 1;
			}
		}
		
		if(printed == 1)
			cout << endl << "-------------------------------------------------" << endl << endl;

		printed = 0;
	}
	*/
	
	line *lineptr;
	int fin = 0;
	lineptr = &output[0];
	while(fin != 1)
	{
		lineptr = lineptr -> from -> in1;
		for(int i = 0; i < input_num; i++)
		{
			cout << ".";
			if(lineptr -> id == input[i].id)
			{
				fin = 1;
				break;
			}
		}
	}
	
	cout << endl << "The output " << output[0].id << " came from the input " << lineptr -> id << endl;
	
	
	return 0;
}

