#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <windows.h>

using namespace std;

int main()
{
	ofstream fout;
	fout.open("input.txt", ofstream::out);
	fout << "x*x+y*y+z*z-9 0 2 0 2 0 2";
	fout.close();

	STARTUPINFO cif;
	ZeroMemory(&cif, sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	TCHAR cmdCommand[256];
	_tcscpy(cmdCommand, _T("Integral_solver_Core.exe"));
	if (CreateProcess(NULL, cmdCommand, NULL, NULL, FALSE, NULL, NULL, NULL, &cif, &pi)) {
		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	char content[512];

	ifstream fin;
	fin.open("output.txt");
	fin >> content;

	double result = atof(content);

	printf("%.f", result);
	getchar();
}
