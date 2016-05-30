#include <iostream>
#include <fstream>
#include <string>
#include "var.h"
#include "read_file.h"

#include <sstream>
using namespace std;


void foo(line &bar)
{
	cout << bar.id;
	return ;
}


string int2str(int &);
//void foo(line &)
string find_booleanfunction(line &);
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
	/*
	line* lineptr;
	int fin = 0;
	lineptr = &output[0];
	while(fin != 1)
	{
		lineptr = lineptr -> from -> in1;
		for(int i = 0; i < input_num; i++)
		{
			cout << ".";
			if(lineptr -> id == input[i].id)			{
				fin = 1;
				break;
			}
		}
	}
	
	cout << endl << "The output " << output[0].id << " came from the input " << lineptr -> id << endl;
  */
 
 
 
	cout << find_booleanfunction( output[0] ) << endl;
  
  
  
	return 0;
}



string find_booleanfunction(line &output)
{ 
 string sin1,sin2;
   string sout;
   cout << "--------------" << endl;
   cout << "now id: " << output.id << endl;
   cout << "gate type: " << output.from << endl;
   cout << "gate type: " << output.to << endl;
   cout << "in1 id: " << output.from->in1->id << endl; 
   cout << "in2 id: " << output.from->in2->id << endl; 
   cout << "--------------" << endl << endl;



   if(output.from->in1->id/100!=1 && output.from->in1->id/100!=2 && output.from->in1!=nullptr)
   {	
   	cout << "next level of in1" << endl;
   	sin1 = find_booleanfunction(*(output.from->in1));
	cout << "sin1: " << sin1 << endl;
   }
   else
   {
   	cout << "End of in1 " << output.id << endl;
   }

   if(output.from->in2->id/100!=1 && output.from->in2->id/100!=2 && output.from->in2!=nullptr)
   {
   	cout << "next level of in2" << endl;
   	sin2 = find_booleanfunction(*output.from->in2);
	cout << "sin2: " << sin2 << endl;
   }
   else
   {
   	cout << "End of in2 " << output.id << endl;
   }

   sin1 = int2str(output.from->in1->id);
   sin2 = int2str(output.from->in2->id);
   
   switch(output.from->type)
   {
      case 1:
      sout = "(input["+sin1+"]&input["+sin2+"])";
      return sout;
      break;
      case 2:
      sout = "(input["+sin1+"]||input["+sin2+"])";
      return sout;
      break;
      case 3:
      sout = "(!input["+sin1+"])";
      return sout;
      break;
      case 4:
      sout = "(input["+sin1+"]^input["+sin2+"])";
      return sout;
      break;
      case 5:
      sout = "(input["+sin1+"])";
      return sout;
      break;
   }
	
}


string int2str(int& i)
{
  string s;
  stringstream ss;
  ss << i ;
  ss >> s ;
   
   return s;
}
