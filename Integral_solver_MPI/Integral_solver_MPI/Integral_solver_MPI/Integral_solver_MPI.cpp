

#include "stdafx.h"
#include "Integral_solver_MPI.h"
#include "ProcessorRpn.h"
#include "atlstr.h"
#include "Logger.h"
#include "Integral.h"


JNIEXPORT jdouble JNICALL Java_by_gstu_it_domain_IntegralSolver_solve(
								JNIEnv *env, jobject obj, jstring str, jintArray args) {

	Logger logger;

	const char* utfChars = env->GetStringUTFChars(str, 0);
	USES_CONVERSION;
	TCHAR* function = A2T(utfChars);
	logger.logI(function); //log

	jint* arr = env->GetIntArrayElements(args, 0);
	logger.logI(
		to_tstring(arr[0])
		.append(_T("  "))
		.append(to_tstring(arr[1]))
		.append(_T("  "))
		.append(to_tstring(arr[2]))
		.append(_T("  "))
		.append(to_tstring(arr[3]))
		.append(_T("  "))
		.append(to_tstring(arr[4]))
		.append(_T("  "))
		.append(to_tstring(arr[5]))
	); //log

	Integral integral(function);
	double result = integral.solve(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
	logger.logI(to_tstring(result)); //log

	return result;
}