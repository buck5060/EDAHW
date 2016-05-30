#include <iostream>
#include <fstream>
#include <string>

line* input;
line* output;
line* trans;
line* null;
gate* gates;

int input_num = 0;
int output_num = 0;
int dff_num = 0;
int gate_num = 0;
int trans_num = 0;

//void fileReading(int *input_num, int *output_num, int *dff_num, int* gate_num)
int fileReading()
{
	int temp = 0;
	string::size_type sz;
	string str_temp;

	int input_idx = 0;
	int input_idx2 = 0;
	int output_idx = 0;
	int trans_i = 0;
	int gate_idx = 0;
	int gate_i = 0; //index for object array "gate"
	
	
	ifstream netlist ("crc.isc");
	if(!netlist)
	{
		cout << "load fail!";
		return 1;
	}
	

	//input num
	netlist.ignore(256,'#');
	netlist >> input_num; 
	//output num
	netlist.ignore(256,'#');
	netlist >> output_num;
	//dff num
	netlist.ignore(256,'#');	
	netlist >> dff_num;
	//gate num
	netlist.ignore(256,'#');
	netlist >> gate_num;

	trans_num = gate_num * 3 - input_num - output_num;

	cout << "input_num:" << input_num << endl; 
	cout << "output_num:" << output_num << endl;
	cout << "dff_num:" << dff_num << endl;
	cout << "gate_num:" << gate_num << endl;
	cout << "trans_num: " << (gate_num * 3 - input_num - output_num);
	cout << endl;

	input = new line[input_num];
	output = new line[output_num];
	trans = new line[(gate_num * 3 - input_num - output_num)];
	null = new line;
	gates = new gate[gate_num];

	
	getline(netlist,str_temp);
	getline(netlist,str_temp);
	

	for(input_idx = 0; input_idx < input_num;)
	{
		getline(netlist,str_temp,'(');
		cout << str_temp << endl;
		if(str_temp ==  "INPUT")
		{
			getline(netlist,str_temp,')');
			temp = stoi (str_temp,&sz);
			input[input_idx].id = temp; 
			cout << input[input_idx].id << endl;
			input_idx++; 
		}
		getline(netlist,str_temp);
	}
	
	cout << "input_idx:" << input_idx << " / " << "input_num:" << input_num << endl;


	getline(netlist,str_temp);
	for(output_idx = 0; output_idx < output_num;)
	{
		getline(netlist,str_temp,'(');
		cout << str_temp << endl;
		if(str_temp ==  "OUTPUT")
		{
			getline(netlist,str_temp,')');
			temp = stoi (str_temp,&sz);
			output[output_idx].id = temp; 
			cout << output[output_idx].id << endl;
			output_idx++;
		
		}
		getline(netlist,str_temp);
	}
	
	cout << "output_idx:" << output_idx << " / " << "output_num:" << output_num << endl;

	getline(netlist,str_temp);

	
	while( getline(netlist,str_temp, ' ') )
	{
	
		cout << "//-------------gate recognize start----------------" << endl;

		cout << endl << "Found output : " << str_temp << endl; 
		output_idx = stoi (str_temp,&sz);

		getline(netlist,str_temp, ' ');
		getline(netlist,str_temp, '(');
		cout << "Found Gate type : " << str_temp << endl;
		gates[gate_i].type = gate_type(str_temp);
		cout << "Gate type:" << gates[gate_i].type << endl;

		getline(netlist,str_temp, ')');

		if(str_temp[3] != ',')
		{
			cout << "Found input : " << str_temp << endl << endl;
			input_idx = stoi (str_temp,&sz);
			input_idx2 = 0;
		}
		else
		{
			cout << "Found input : " << str_temp << endl << endl;
			input_idx = stoi (str_temp.substr (0,3),&sz);
			input_idx2 = stoi (str_temp.substr (4,6),&sz);
		}
		
		cout << "gate_i : " << gate_i  << endl << "gate id : " << gates[gate_i].type << endl  << "in1 id : " << input_idx << endl << "in2 id : " << input_idx2 << endl << endl;
		
		//--------------------- in1 -------------------------
		for(int i = 0; i < input_num; i++) //check if input_idx is input
		{
			cout << ".";
			if(input[i].id == input_idx)
			{
				gates[gate_i].in1 = &input[i];
				input[i].to = &gates[gate_i]; 
				cout << "input found" << endl;
				cout << "input as in1 of this gate:" << gates[gate_i].in1 -> id << endl ;
				input_idx = 0;
				break;
			}
		}
		
		if(input_idx != 0) //new, using middle line
		{
			cout << "tans_i : " << trans_i << " / input_idx : " << input_idx << endl;
			for(int i = 0; i < trans_i; i++)
			{	
				cout << "." ;
				if(trans[i].id == output_idx)
				{
					cout << "trans for in1 found" << endl;
					gates[gate_i].in1 = &trans[i];
					trans[i].to = &gates[gate_i];
					break;
				}
			}
				
			if (gates[gate_i].out == 0)
			{
				gates[gate_i].in1 = &trans[trans_i];
				trans[trans_i].to = &gates[gate_i];
				trans_i++;
			}


			gates[gate_i].in1 -> id = input_idx;


			cout << endl << ">>> middle line as input1 of this gate(on mem):" << trans[trans_i].to ->type << endl ;
			cout << "input as in1 of this gate:" << gates[gate_i].in1 -> id << endl ;
		}

		cout << "in1 process complete //" << endl << endl;

		// ----------------------- in2 --------------------------------
		if(input_idx2 != 0) //check if input_idx2 is a input 
		{
			for(int i = 0; i < input_num; i++)
			{
				if(input[i].id == input_idx2)
				{
					gates[gate_i].in2 = &input[i];
					input[i].to = &gates[gate_i];
					cout << "input found" << endl;
					cout << "input as in2 of this gate:" << gates[gate_i].in2 -> id << endl ;
					input_idx2 = 0;
					break;
				}
			}
		

			if(input_idx2 != 0) //new, using middle line
			{
				temp = 0;
				cout << "tans_i : " << trans_i << " / input_idx2 : " << input_idx2 << endl;
				for(temp = 0; temp < trans_i; temp++)
				{
					cout << "." ;
					if(trans[temp].id == input_idx2)
					{
						cout << "trans for in2 found" << endl;
						gates[gate_i].in2 = &trans[temp];
						trans[temp].to = &gates[gate_i];
						break;
					}
				}

				cout << temp << endl;
					
				if(-1 != input_idx2)
				{
					cout << "|" ;
					gates[gate_i].in2 = &trans[trans_i];
					cout << "|" ;
					trans[trans_i].to = &gates[gate_i];
					cout << "|" ;
					trans_i++;
				}
				
				gates[gate_i].in2 -> id = input_idx2;
				
				cout << endl << ">>> middle line as input2 of this gate(on mem):" << trans[trans_i].to ->type << endl ;
				cout << "middle line as in2 of this gate:" << gates[gate_i].in2 -> id << endl ;
			}

			cout << "in2 process complete //" << endl << endl;
		}
		else
		{
			gates[gate_i].in2 = null;
		}
		

		// ---------------------- out -----------------------
		cout << "output_idx = " << output_idx << endl;
		for(int i = 0; i < output_num; i++)
		{

			if(output[i].id == output_idx)
			{
				gates[gate_i].out = &output[i];
				output[i].from = &gates[gate_i];
				cout << "output found" << endl;
				output_idx = 0;
				break;
			}
		}


		if(output_idx != 0) //new, using middle line
		{
			cout << "tans_i : " << trans_i << " / output_idx : " << output_idx << endl;

			for(int i = 0; i < trans_i; i++)
			{
				if(trans[i].id == output_idx)
				{
					gates[gate_i].out = &trans[i];
					trans[i].from = &gates[gate_i];
					break;
				}
			}
				
			if (gates[gate_i].out == 0)
			{
				gates[gate_i].out = &trans[trans_i];
				trans[trans_i].from = &gates[gate_i];
				trans[trans_i].id = output_idx;
				trans_i++;
			}

			gates[gate_i].out -> id = output_idx;

			cout << endl << ">>> middle line as output of this gate(on mem):" << gates[gate_i].out->id <<endl ;
		
		}

		cout << "Checking for gate para correctness : " << gates[gate_i].out->id << endl ;

		gate_i++;


		cout << "//-------------gate recognize end----------------" << endl << endl;

	}

}
