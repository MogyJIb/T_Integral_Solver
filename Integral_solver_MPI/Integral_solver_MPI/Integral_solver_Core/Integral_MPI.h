#pragma once
#include "ProcessorRpn.h"
#include "Logger.h"
#include "mpi.h"

class Integral_MPI
{
private:
	Logger logger;
	ProcessorRpn* processorRpn;
	int processId;
	int processCount = 1;
	TCHAR* func;
	const int N = 14;
	const double C[14] = {
							90241897.0 / 1250964000,	// 0
							44436679.0 / 156370500,		// 1
							-770720657.0 / 2501928000,	// 2
							109420087.0 / 78185250,		// 3
							-6625093363.0 / 2501928000,	// 4
							789382601.0 / 156370500,	// 5
							-5600756791.0 / 833976000,	// 6
							101741867.0 / 13030875,		// 7
							-5600756791.0 / 833976000,	// 6
							789382601.0 / 156370500,	// 5
							-6625093363.0 / 2501928000,	// 4
							109420087.0 / 78185250,		// 3
							-770720657.0 / 2501928000,	// 2
							44436679.0 / 156370500		// 1
	};

	double countC(int n);
	double function(double x, double y, double z);

public:
	Integral_MPI(TCHAR* function, int processId, int processCount);
	~Integral_MPI();

	double solve(const double x1, const double x2,
		const double y1, const double y2,
		const double z1, const double z2);
};

