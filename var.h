#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class line;
class gate;

class line
{
	public:
		gate *from;
		gate *to;
		int times;
		int data;
		int id;
		int fault; //for fault
		line *nextLine;
		line();
		~line();
};

line::line()
{
	from = nullptr;
	to = nullptr;
	times = 0; 	
	data = -1;
	id = -1;
	fault = -1;
}

line::~line()
{}


class gate
{
	public:
		line *in1,*in2,*out; //make gate linked with line
		int type;
		/*
		enum Type
		{
			AND,
			OR,
			NOT,
			XOR,
			BUFF
		};
		*/

		gate();
		~gate();
		
		/*
		bool calc(int type, line in1, line in2)
		{
			bool out;
			switch(type)
			{
				case AND:
					out = in1 & in2;
					break;
				case OR:
					out = in1 | in2;
					break;
				case NOT:
					out = !in1;
					break;
				case XOR:
					out = in1 ^ in2;
					break;
			}
				
			return out;
		}
		*/
};

gate::gate()
{
	in1 = nullptr;
	in2 = nullptr;
	out = nullptr;
	type = -1;
}

gate::~gate()
{
	
}

int gate_type(string type)
{
	if(type == "AND")
		return 1;
	
	if(type == "OR")
		return 2;
	
	if(type == "NOT")
		return 3;
	
	if(type == "XOR")
		return 4;
	
	if(type == "BUFF")
		return 5;
}


