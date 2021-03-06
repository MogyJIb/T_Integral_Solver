#define _CRT_SECURE_NO_WARNINGS


#include <mpi.h>
#include "Logger.h"
#include "Integral.h"
#include "Integral_MPI.h"
#include "ProcessorRpn.h"
#include "atlstr.h"



void checkArgs(int argc, char *argv[]);
void solve();
void solve_MPI(int argc, char *argv[]);




static bool USE_MPI = false;
static TCHAR inputFileName[256];
static TCHAR outputFileName[256];
static tstring PATH(_T(""));

int main(int argc, char *argv[])
{
	checkArgs(argc, argv);

	if (USE_MPI)
		solve_MPI(argc, argv);
	else
		solve();

	return 0;
}



void checkArgs(int argc, char *argv[]) {
	USES_CONVERSION;

	if (argc > 1) {
		PATH.append(A2T(argv[1]));
	}
	if (!PATH.empty()) {
		_tcscpy(inputFileName, tstring(PATH).append(_T("input.txt")).data());
		_tcscpy(outputFileName, tstring(PATH).append(_T("output.txt")).data());
	} else {
		_tcscpy(inputFileName, _T("input.txt"));
		_tcscpy(outputFileName, _T("output.txt"));
	}

	if (argc > 2) {
		if (strcmp(argv[2], "1") == 0) USE_MPI = true;
	}
}


void solve() {

	Logger logger(PATH);

	logger.logI(_T("\r\n\r\n\r\n\r\n"));
	logger.logI(PATH); //log
	logger.logI(inputFileName); //log
	logger.logI(outputFileName); //log

	TCHAR function[512];
	TCHAR arr1[512], arr2[512], arr3[512], arr4[512], arr5[512], arr6[512];


	logger.logI(_T("read input")); //log

	tifstream fin;
	fin.open(inputFileName);
	fin >> function >> arr1 >> arr2 >> arr3 >> arr4 >> arr5 >> arr6;
	fin.close();

	logger.logI(_T("input read successful")); //log

	logger.logI(
		tstring(arr1).append(_T("  "))
		.append(arr2).append(_T("  "))
		.append(arr3).append(_T("  "))
		.append(arr4).append(_T("  "))
		.append(arr5).append(_T("  "))
		.append(arr6)
	); //log

	double x1 = _ttof(arr1), x2 = _ttof(arr2),
		y1 = _ttof(arr3), y2 = _ttof(arr4),
		z1 = _ttof(arr5), z2 = _ttof(arr6);

	logger.logI(
		to_tstring(x1).append(_T("  "))
		.append(to_tstring(x2)).append(_T("  "))
		.append(to_tstring(y1)).append(_T("  "))
		.append(to_tstring(y2)).append(_T("  "))
		.append(to_tstring(z1)).append(_T("  "))
		.append(to_tstring(z2))
	); //log


	double result = 0.0;

	logger.logI(_T("solve integral")); //log

	try {
		Integral integral(function);
		result = integral.solve(x1, x2, y1, y2, z1, z2);
	}
	catch (...) {
		logger.logI(_T("exception in solving integral")); //log
	}

	logger.logI(tstring(_T("solved, result = ")).append(to_tstring(result))); //log


	logger.logI(_T("write output")); //log

	ofstream fout;
	fout.open(outputFileName, ofstream::out);
	fout << result;
	fout.close();

	logger.logI(_T("output write successful")); //log
}


void solve_MPI(int argc, char *argv[]) {
	int processId;
	int processCount;
	static int master = 0;
	int ierr;

	Logger logger(PATH);

	logger.logI(_T("\r\n\r\n\r\n\r\n"));
	logger.logI(PATH); //log
	logger.logI(inputFileName); //log
	logger.logI(outputFileName); //log

	ierr = MPI_Init(&argc, &argv);

	if (ierr != 0)
	{
		logger.logI(_T("can't init mpi, fatal error"));
		return;
	}

	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &processId);

	logger.logI(to_tstring(processId).append(_T("   processId "))); //log
	logger.logI(to_tstring(processCount).append(_T("   processCount "))); //log


	double result = 0, result_part = 0;
	TCHAR function[512];

	TCHAR arr1[512], arr2[512], arr3[512], arr4[512], arr5[512], arr6[512];


	logger.logI(_T("read input")); //log

	tifstream fin;
	fin.open(inputFileName);
	fin >> function >> arr1 >> arr2 >> arr3 >> arr4 >> arr5 >> arr6;
	fin.close();

	logger.logI(_T("input read successful")); //log

	logger.logI(
		tstring(arr1).append(_T("  "))
		.append(arr2).append(_T("  "))
		.append(arr3).append(_T("  "))
		.append(arr4).append(_T("  "))
		.append(arr5).append(_T("  "))
		.append(arr6)
	); //log

	logger.logI(tstring(_T("function   "))
		.append(function)
		.append(_T("   process   "))
		.append(to_tstring(processId))); //log

	double x1 = _ttof(arr1), x2 = _ttof(arr2),
		y1 = _ttof(arr3), y2 = _ttof(arr4),
		z1 = _ttof(arr5), z2 = _ttof(arr6);


	logger.logI(_T("solve integral")); //log
	try {

		Integral_MPI integral(function, processId, processCount);
		result_part = integral.solve(x1, x2, y1, y2, z1, z2);

		MPI_Reduce(&result_part, &result, 1, MPI_DOUBLE, MPI_SUM, master, MPI_COMM_WORLD);
	}
	catch (...) {
		logger.logI(_T("exception in solving integral")); //log
	}

	
	if (processId == 0) {
		logger.logI(tstring(_T("solved, result = ")).append(to_tstring(result))); //log

		logger.logI(_T("write output")); //log

		ofstream fout;
		fout.open(outputFileName, ofstream::out);
		fout << result;
		fout.close();

		logger.logI(_T("output write successful")); //log
	}


	MPI_Finalize();
}