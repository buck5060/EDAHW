#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string int2str(int &);
//void foo(line &)
string find_booleanfunction(line &, line &fault);
//line* input;
//line* output;
//line* trans; //intermediate line
//gate* gates;

//int input_num = 0;
//int output_num = 0;
//int dff_num = 0;
//int gate_num = 0;

//Type of fault
//1.Stack At ?
//2.change gate type
//3.invert the output

string find_booleanfunction(line &output, line &fault)
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
	if(fault.fault == 1 && fault.id == output.from -> in1 -> id) //type 1 of fault (SA0)
		sin1 = "0";
	else if(fault.fault == 2 && fault.id == output.from -> in1 -> id) //type 1 of fault (SA1)
		sin1 = "1";
	else if(fault.fault == 3 && fault.id == output.from -> in1 -> id)
		sin1 = "!" + find_booleanfunction(*(output.from->in1) , fault);
	else
   		sin1 = find_booleanfunction(*(output.from->in1) , fault);
	cout << "sin1: " << sin1 << endl;
   }
   else
   {
	sin1 = int2str(output.from->in1->id);
   	cout << "End of in1 " << output.id << endl;
   }

   if(!endIn2)
   {
   	cout << "next level of in2" << endl;
	if(fault.fault == 1 && fault.id == output.from -> in2 -> id) //type 1 of fault (SA0)
		sin2 = "0";
	else if(fault.fault == 2 && fault.id == output.from -> in2 -> id) //type 1 of fault (SA1)
		sin2 = "1";
	else if(fault.fault == 3 && fault.id == output.from -> in2 -> id)
		sin2 = "!" + find_booleanfunction(*(output.from->in2) , fault);
	else
   		sin2 = find_booleanfunction(*output.from->in2 , fault);
	cout << "sin2: " << sin2 << endl;
   }
   else
   {
	sin2 = int2str(output.from->in2->id);
   	cout << "End of in2 " << output.id << endl;
   }

  switch(fault.fault)
  {
  	case 4 : gate_type = 1;	break;
  	//case 5 : gate_type = ;	break;
  	case 6 : gate_type = 2;	break;
  	//case 7 : gate_type = ;	break;
  	case 8 : gate_type = 4;	break;
  	//case 9 : gate_type = ;	break;
  	case 10: gate_type = 3;	break;
  	case 11: gate_type = 5;	break;
	default: gate_type = output.from->type;
  }

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
