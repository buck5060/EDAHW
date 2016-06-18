
#include <iostream>
#include <fstream>
#include <string>

int fault_num=0;
int pin;
int behavior;
int fault_type(string );
line* fault;


 int faultReading()
{
 int temp=0;
 
 string::size_type sz;
 string str_tmp;
 ifstream r_fault ("fault_description.txt");
 if(!r_fault)
 {
  
  cout << "load fail!"<<endl;
	return 1;
 }
  while(!r_fault.eof())
 {
 getline(r_fault,str_tmp);
 
 }
 temp = stoi(str_tmp,&sz);

 fault_num=temp; //找到最底的數字
 r_fault.seekg(0);       //回頭
 
 fault = new line[fault_num];//new一個動態陣列

int fault_idx=0;     
 while(fault_idx<fault_num)
 { cout<<fault_idx<<" ";
   getline(r_fault,str_tmp,'	');
   temp = stoi(str_tmp,&sz);
   fault[fault_idx].times = temp; 
   cout<<temp<<" ";
   r_fault.ignore(256,'	');
   
   getline(r_fault,str_tmp,'	');
   temp = stoi(str_tmp,&sz);
   fault[fault_idx].id = temp;
   cout<<temp<<" ";
   
   r_fault.ignore(256,'	');
  
   getline(r_fault,str_tmp);
   fault[fault_idx].fault = fault_type(str_tmp); 
   int i=fault_type(str_tmp);
   cout<<i<<endl;
   fault_idx++;
   
 
 }
// for(int i=0;i<23;i++)
// cout<<fault[fault_idx].times<<" "<<fault[fault_idx].id<<" "<<fault[fault_idx].fault<<endl;
 }

int fault_type(string type)
{
	if(type == "	SA0")
		return 1;
	
	if(type == "	SA1")
		return 2;
	
	if(type == "	NEG")
		return 3;
	
	if(type == "	RDOB_AND")
		return 4;
	
	if(type == "	RDOB_NAND")
		return 5;
  
  if(type == "	RDOB_OR")
    return 6;
  
  if(type == "	RDOB_NOR")
    return 7;
    
  if(type == "	RDOB_XOR")
    return 8;
    
  if(type == "	RDOB_NXOR")
    return 9;
    
  if(type == "	RDOB_NOT")
    return 10;      
    
  if(type == "	RDOB_BUFF")
    return 11;      
}
