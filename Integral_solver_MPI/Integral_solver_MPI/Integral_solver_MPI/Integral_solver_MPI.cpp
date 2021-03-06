#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "Integral_solver_MPI.h"
#include <iostream>
#include <fstream>
#include <tchar.h>

using namespace std;

JNIEXPORT jdouble JNICALL Java_by_gstu_it_domain_IntegralSolver_solve(
								JNIEnv *env, jobject obj, jstring str, jintArray args) {

	const char* utfChars = env->GetStringUTFChars(str, 0);
	jint* arr = env->GetIntArrayElements(args, 0);

	ofstream fout;
	fout.open("input.txt", ofstream::out);
	fout << utfChars << " ";
	fout << arr[0] << " " << arr[1] << " " << arr[2] << " " << arr[3] << " " << arr[4] << " " << arr[5];
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

	return result;
}