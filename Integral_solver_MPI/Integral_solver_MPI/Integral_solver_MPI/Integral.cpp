#include "Integral.h"


Integral::Integral(TCHAR* function) {
	processorRpn = new ProcessorRpn(function);
}

Integral::~Integral() { }

double Integral::solve(const double x1, const double x2,
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
	);  // log

	double result = 0;

	for (int i = 0; i < N; i++) {
		double x_i = x1 + h_i * i,
			C_i = countC(i);

		for (int j = 0; j < N; j++) {
			double y_j = y1 + h_j * j,
				C_j = countC(j);

			for (int k = 0; k < N; k++) {
				double z_k = z1 + h_k * k,
					C_k = countC(k);

				double C_ijk = C_i * C_j * C_k;

				result += C_ijk * function(x_i, y_j, z_k);
			}
		}
	}

	logger.logI(
		to_tstring(result)
		.append(_T("  -result   "))
	); // log

	result *= 343 * h_i * h_j * h_k;

	return result;
}

double Integral::countC(int n) {
	return (n == 0 || n == N) ? 90241897.0 / 2501928000 : C[n % 14];
}

double Integral::function(double x, double y, double z) {
	double result = processorRpn->function(x, y, z);

	logger.logI(
		to_tstring(result)
		.append(_T("  -result from rpn   x: "))
		.append(to_tstring(x))
		.append(_T("   y: "))
		.append(to_tstring(y))
		.append(_T("   z: "))
		.append(to_tstring(z))
	);  // log
	return result;
}