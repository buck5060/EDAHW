/*
給鍾旺偉：
	input：
		int inputNum //輸入變數的數量
		string truthtable //輸入變數的真值表
		string notCutString //未切割的布林函式 
	output：
		string inputString[0] //輸入布林函式的答案，"0"或"1" 
*/ 

#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>

using namespace std; 

//fstream outputfile; 
int iforLoop, tempforLoop; 
int inputNum = 4; //input：有幾個變數 

string assign; 
string inputString[100]; //可改為動態陣列 
//string notCutString = "( ( ( input[105] ) && ( input[103] ^ input[231] ) ) ^ input[211] ) ;"; //input：未切割的布林函式字串
string truthtable[100] = { "0", "0", "0", "1" }; //input：變數的真值表，可改為動態陣列 

string booleancalc ( string notCutString )
{ 
	
	//以下為字串分割 
	stringstream ss( notCutString ); 
	//getline( ss, assign, ' ' ); //將assign存入字串assign  
	for( iforLoop = 0; ; iforLoop++ ){
		getline( ss, inputString[iforLoop], ' ' ); //將布林函式分割存入字串陣列inputString 
		if( inputString[iforLoop] == ";" ) break;  
	}
	
	//以下為帶入input值
	tempforLoop = 0; 
	for( iforLoop = 0; ; iforLoop++ ){
		if( ( inputString[iforLoop] != "(" ) && ( inputString[iforLoop] != ")" ) && ( inputString[iforLoop] != "&&" ) && ( inputString[iforLoop] != "^" ) && ( inputString[iforLoop] != "||" ) && ( inputString[iforLoop] != ";" ) ){
			inputString[iforLoop] = truthtable[tempforLoop]; 
			tempforLoop++; 
			if( tempforLoop == inputNum ) break; 
		}
		else continue; 
	}
	
	//以下為算出布林函式的答案 
	for( iforLoop = 0; ; iforLoop++ ){ //找"(" 
		if( inputString[iforLoop] == "(" ){ //找到"("
			if( inputString[iforLoop+2] == ")" ){ //此( )為buffer 
				//將buffer( )拿掉，陣列前移
				inputString[iforLoop] = inputString[iforLoop+1]; 
				for( tempforLoop = iforLoop+1; ; tempforLoop++ ){
					inputString[tempforLoop] = inputString[tempforLoop+2]; 
					if( inputString[tempforLoop] == ";" ) break; 
				} 
				
				iforLoop = -1; 
			}
			else if( ( inputString[iforLoop+1] == "(" ) || ( inputString[iforLoop+2] == "(" ) || ( inputString[iforLoop+3] == "(" ) ) continue; //表示不是最裡面的( ) 
			else{ //找到最裡面的( ) 
				if( inputString[iforLoop+2] == "^" ){ //XOR gate 
					if( inputString[iforLoop+1] == inputString[iforLoop+3] ) inputString[iforLoop] = "0"; 
					else inputString[iforLoop] = "1"; 
				}
				else if( inputString[iforLoop+2] == "&&" ){ //AND gate 
					if( ( inputString[iforLoop+1] == "0" ) || ( inputString[iforLoop+3] == "0" ) ) inputString[iforLoop] = "0"; 
					else inputString[iforLoop] = "1"; 
				}
				else if( inputString[iforLoop+2] == "||" ){ //OR gate 
					if( ( inputString[iforLoop+1] == "1" ) || ( inputString[iforLoop+3] == "1" ) ) inputString[iforLoop] = "1"; 
					else inputString[iforLoop] = "0"; 
				}
				//else if
				//else 
				
				//將字串陣列前移
				for( tempforLoop = iforLoop+1; ; tempforLoop++ ){
					inputString[tempforLoop] = inputString[tempforLoop+4]; 
					if( inputString[tempforLoop] == ";" ) break; 
				}
				
				iforLoop = -1; //因為陣列已被修改，重頭開始找"(" 
			}
		}
		else if( inputString[iforLoop] == ";" ) break; //字串陣列內已經沒有( ) 
	}
	//cout << inputString[0] << endl; 
	//outputfile << inputString[0] << endl; 

	
	//輸出的答案存在字串inputString[0]中 
	
	//system("pause"); 
	return inputString[0]; 
}


