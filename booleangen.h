#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string int2str(int &);
//void foo(line &)
string find_booleanfunction(line &, line &fault, int);
//line* input;
//line* output;
//line* trans; //intermediate line
//gate* gates;

//int input_num = 0;
//int output_num = 0;
//int dff_num = 0;
//int gate_num = 0;

string* input_list_502;
int input_list_502_idx = 0;


//Type of fault
//1.Stack At ?
//2.change gate type
//3.invert the output


string find_booleanfunction(line &output, line &fault, int nofault)
{
	string sin1,sin2;
   	string sout;
	int gate_type = -1;
 


	bool endIn1;
	bool endIn2;

   	cout << "--------------" << endl;
	cout << "now id: " << output.id << endl;
	cout << "gate type: " << output.from << endl;
	cout << "gate type: " << output.to << endl;
	cout << "fault id: " << fault.id << endl;
	cout << "in1 id: " << output.from->in1->id << endl; 
	cout << "in2 id: " << output.from->in2->id << endl; 
	cout << "--------------" << endl << endl;

	if(output.from->in1->id/100!=1 && output.from->in1->id/100!=2 && output.from->in1!=nullptr)
		endIn1 = 0;
	else
		endIn1 = 1;

	if(output.from->in2->id/100!=1 && output.from->in2->id/100!=2 && output.from->in2!=nullptr && output.from->in2->id != -1)
		endIn2 = 0;
	else
		endIn2 = 1;

   if(!endIn1)
   {	
   	cout << "next level of in1" << endl;
   	sin1 = find_booleanfunction(*(output.from->in1) , fault, nofault);
	cout << "sin1: " << sin1 << endl;
   }
   else
   {
	sin1 = int2str(output.from->in1->id);
	if(nofault)
	{
		input_list_502[ input_list_502_idx ] = sin1;
		if(input_list_502_idx < 10)
			input_list_502_idx += 2;
		cout << "the truth table no " << input_list_502_idx - 2 << " is " << input_list_502[ input_list_502_idx - 2] << endl;
	}
   	cout << "End of in1 " << output.id << endl;

   }

   if(!endIn2)
   {
   	cout << "next level of in2" << endl;
   	sin2 = find_booleanfunction(*output.from->in2 , fault, nofault);
	cout << "sin2: " << sin2 << endl;
   }
   else
   {
	sin2 = int2str(output.from->in2->id);
	if(nofault)
	{
		input_list_502[ input_list_502_idx ] = sin2;
		if(input_list_502_idx < 10)
			input_list_502_idx += 2;
		cout << "the truth table no " << input_list_502_idx - 2 << " is " << input_list_502[ input_list_502_idx - 2] << endl;
	}
   	cout << "End of in2 " << output.id << endl;

   }

if(output.id == fault.id)
{
  switch(fault.fault)
  {
  	case 4 : gate_type = 1;	break;
  	case 5 : gate_type = 1;	break;
  	case 6 : gate_type = 2;	break;
  	case 7 : gate_type = 2;	break;
  	case 8 : gate_type = 4;	break;
  	case 9 : gate_type = 4;	break;
  	case 10: gate_type = 3;	break;
  	case 11: gate_type = 5;	break;
	default: gate_type = output.from->type;
  }
 }
 else
 {
 	gate_type = output.from->type;
 }

//*** generate sout with string append ****



if (endIn1 == 0)
{
	if(fault.fault == 1 && fault.id == output.from -> in1 -> id) //SA0
		sout = "0";
	else if(fault.fault == 2 && fault.id == output.from -> in1 -> id) //SA1
		sout = "1";
	else
	{
		
		if( gate_type == 3 ^ ( ( fault.fault == 3 || fault.fault == 5 || fault.fault == 7 || fault.fault == 9) && fault.id == output.from -> in1 -> id) ) //only when one of them is right, the fault is 3,5,7,9
		{
			sout += "!";
		}
		sout = sout + "( " + sin1 + " )";  
	}
}
else
{
	sout = sout + "input[" + sin1 + "]";
}

switch(gate_type) // and, or, xor  NOT INCLUDE buff, not
{
	case 1:
		sout += " && ";
		break;
	case 2:
		sout += " || ";
		break;
	case 4:
		sout += " ^ ";
		break;
}

if(gate_type != 3 && gate_type != 5) //when using not gate or buff will not have input2
{
	if (endIn2 == 0)
	{
		
		if(fault.fault == 1 && fault.id == output.from -> in2 -> id) //SA0
			sout = "0";
		else if(fault.fault == 2 && fault.id == output.from -> in2 -> id) //SA1
			sout = "1";
		else
		{
			
			if( gate_type == 3 ^ ( ( fault.fault == 3 || fault.fault == 5 || fault.fault == 7 || fault.fault == 9) && fault.id == output.from -> in2 -> id) ) //only when one of them is right
			{
				sout += "!";
			}
			sout = sout + "( " + sin2 + " )";  
		}
	}
	else
	{
		sout = sout + "input[" + sin2 + "]";
	}
}


return sout;


/*** generate sout with table ****
  if(endIn1==0&&endIn2==0)
  {
	   switch(gate_type)
	   {
	      case 1:
	      sout =" ("+sin1+") && ( "+sin2+" ) ";
	      return sout;
	      break;
	      case 2:
	      sout = " ("+sin1+" ) || ( "+sin2+" ) " ;
	      return sout;
	      break;
	      case 3:
	      sout = " (!"+sin1+") ";
	      return sout;
	      break;
	      case 4:
	      sout = " ("+sin1+") ^ ( "+sin2+" ) ";
	      return sout;
	      break;
	      case 5:
	      sout = " ("+sin1+") ";
	      return sout;
	      break;
	   }
  }
  else if(endIn1==0&&endIn2==1)
  {
	   switch(gate_type)
	   {
	      case 1:
	      sout = " ("+sin1+") && input["+sin2+"]";
	      return sout;
	      break;
	      case 2:
	      sout = " ("+sin1+") || input["+sin2+"]";
	      return sout;
	      break;
	      case 3:
	      sout = " (!"+sin1+")";
	      return sout;
	      break;
	      case 4:
	      sout = " ("+sin1+") ^ input["+sin2+"]";
	      return sout;
	      break;
	      case 5:
	      sout =" ("+sin1+") ";
	      return sout;
	      break;
	   }
  }
  else if(endIn1==1&&endIn2==0)
  {
	   switch(gate_type)
	   {
	      case 1:
	      sout = " input["+sin1+"] && ("+sin2+") ";
	      return sout;
	      break;
	      case 2:
	      sout = " input["+sin1+"] || ("+sin2+") ";
	      return sout;
	      break;
	      case 3:
	      sout = "! input["+sin1+"]";
	      return sout;
	      break;
	      case 4:
	      sout = " input["+sin1+"] ^ (" +sin2+") ";
	      return sout;
	      break;
	      case 5:
	      sout = " input["+sin1+"] ";
	      return sout;
	      break;
	   }
  }
  else
  {
  switch(gate_type)
	   {
	      case 1:
	      sout = " input["+sin1+"] && input["+sin2+"]";
	      return sout;
	      break;
	      case 2:
	      sout = " input["+sin1+"] || input["+sin2+"]";
	      return sout;
	      break;
	      case 3:
	      sout = " !input["+sin1+"]";
	      return sout;
	      break;
	      case 4:
	      sout = " input["+sin1+"] ^ input["+sin2+"] ";
	      return sout;
	      break;
	      case 5:
	      sout = " input["+sin1+"] ";
	      return sout;
	      break;
	   }
  }*/
}

string int2str(int& i)
{
  string s;
  stringstream ss;
  ss << i ;
  ss >> s ;
   
   return s;
}
