// CVaribleScanHacker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>
#pragma comment(lib, "user32.lib")
using namespace std;

int main()
{
	
	string windowName;
	cout << "Please enter window name of program you wish to access." << endl;
	cin >> windowName;
	
	HWND hwnd = FindWindowA(0, windowName.c_str());
	
	if (hwnd == 0) {
		cout << "Error could not find program" << endl;
	}
	else {
		cout << "Program found" << endl;

		
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		cout << pid << endl;
		//Opens handle with full access
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (!hProc) {
			cout << "Error could not open process" << endl;
		}
		else {
			cout << "Process opened" << endl;
			//Memory location of pointer 
			DWORD pointer = 0x0109F848;
			cin >> pointer;
			cout << pointer << endl;
			DWORD Pointed;
			//Memory Offset
			WORD offset = 0x0018;
			//Change Varible type when applicable
			int currentValue = 0;
			int newValue;
			ReadProcessMemory(hProc, (LPCVOID)(pointer), &Pointed , 4 , NULL);
			//The operator for the offset may need to be changed depending on program being accessed			
			ReadProcessMemory(hProc, (LPCVOID)(Pointed - offset), &currentValue , 4, NULL);
			cout << "Current Value- " + currentValue << endl;
			cout << "Please enter a new value" << endl;
			cin >> newValue;

			int Success = WriteProcessMemory(hProc, (LPVOID)(Pointed - offset), &newValue, (DWORD)sizeof(newValue), NULL);
			
			if (Success > 0) {
				cout << "Write was successful" << endl;
				cout << "Current Value- " + currentValue << endl;
			}
			else {cout << "Could not write to memory" << endl;}
		}
	}
	cin.get();
	return 0;
}


