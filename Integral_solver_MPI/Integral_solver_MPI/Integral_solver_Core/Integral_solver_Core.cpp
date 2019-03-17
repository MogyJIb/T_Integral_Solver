#define _CRT_SECURE_NO_WARNINGS


#include <mpi.h>
#include "Logger.h"
#include "Integral.h"
#include "Integral_MPI.h"
#include "ProcessorRpn.h"
#include "atlstr.h"



void checkArgs(int argc, char *argv[]);




static bool USE_MPI = false;
static TCHAR inputFileName[256];
static TCHAR outputFileName[256];
static tstring PATH(_T(""));

int main(int argc, char *argv[])
{
	checkArgs(argc, argv);

	Logger logger(PATH);

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
		if (USE_MPI && MPI_Init(&argc, &argv)) {
			Integral_MPI integral(function);
			result = integral.solve(x1, x2, y1, y2, z1, z2);
		}
		else {
			Integral integral(function);
			result = integral.solve(x1, x2, y1, y2, z1, z2);
		}
	} catch(...) {
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
		if (strcmp(argv[2], "1")) USE_MPI = true;
	}
}