#include "Integral_MPI.h"


Integral_MPI::Integral_MPI(TCHAR* function, int processId, int processCount) {
	processorRpn = new ProcessorRpn(function);
	this->processId = processId;
	this->processCount = processCount;
	this->func = function;
}

Integral_MPI::~Integral_MPI() { }

double Integral_MPI::solve(const double x1, const double x2,
	const double y1, const double y2,
	const double z1, const double z2) {


	const double h_i = (x2 - x1) / N,
		h_j = (y2 - y1) / N,
		h_k = (z2 - z1) / N;

	logger.logI(
		to_tstring(h_i)
		.append(_T("  -h_i   "))
		.append(to_tstring(h_j))
		.append(_T("  -h_j   "))
		.append(to_tstring(h_k))
		.append(_T("  -h_k   "))
		.append(func)
		.append(_T("  -func   "))
		.append(_T("   process   "))
		.append(to_tstring(processId))
		.append(_T("   processCount   "))
		.append(to_tstring(processCount))
	);  // log

	double result_part = 0;

	for (int i = processId; i < N; i = i + processCount) {
		double x_i = x1 + h_i * i,
			C_i = countC(i);

		for (int j = 0; j < N; j++) {
			double y_j = y1 + h_j * j,
				C_j = countC(j);

			for (int k = 0; k < N; k++) {
				double z_k = z1 + h_k * k,
					C_k = countC(k);

				double C_ijk = C_i * C_j * C_k;

				result_part += C_ijk * function(x_i, y_j, z_k);
			}
		}
	}

	logger.logI(
		tstring(_T("result_part   "))
			.append(to_tstring(result_part))
			.append(_T("   process   "))
			.append(to_tstring(processId))
	); // log

	result_part *= 343 * h_i * h_j * h_k;

	return result_part;
}

double Integral_MPI::countC(int n) {
	return (n == 0 || n == N) ? 90241897.0 / 2501928000 : C[n % 14];
}

double Integral_MPI::function(double x, double y, double z) {
	return processorRpn->function(x, y, z);
}