

#include "Logger.h"
#include "Integral.h"
#include "ProcessorRpn.h"

int main(int argc, char *argv[])
{
	Logger logger;

	TCHAR function[512];
	TCHAR arr1[512], arr2[512], arr3[512], arr4[512], arr5[512], arr6[512];

	tifstream fin;
	fin.open("input.txt");
	fin >> function >> arr1 >> arr2 >> arr3 >> arr4 >> arr5 >> arr6;
	fin.close();

	double x1 = _ttof(arr1), x2 = _ttof(arr2),
		y1 = _ttof(arr3), y2 = _ttof(arr4),
		z1 = _ttof(arr5), z2 = _ttof(arr6);

	logger.logI(
		tstring(arr1).append(_T("  "))
		.append(arr2).append(_T("  "))
		.append(arr3).append(_T("  "))
		.append(arr4).append(_T("  "))
		.append(arr5).append(_T("  "))
		.append(arr6)
	); //log

	Integral integral(function);
	double result = integral.solve(x1, x2, y1, y2, z1, z2);

	ofstream fout;
	fout.open("output.txt", ofstream::out);
	fout << result;
	fout.close();
}

