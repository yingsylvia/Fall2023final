#include "fre_vswap.h"
#include "xll_fre.h"

using namespace xll;
using namespace fre::vswap;

//!!! implement xll_vswap
AddIn xai_vswap(
	Function(XLL_DOUBLE, "xll_vswap", "XLL.VSWAP")
	.Arguments({
		Arg(XLL_DOUBLE, "f", "is the forward price."),
		Arg(XLL_LPOPER, "k", "is an array of strike prices."),
		Arg(XLL_LPOPER, "p", "is an array of put prices corresponding to strikes."),
		Arg(XLL_LPOPER, "c", "is an array of call prices corresponding to strikes."),
		})
		.Category("VSWAP")
	.FunctionHelp("Calculate variance for variance swap.")
);

double WINAPI xll_vswap(double f, const _FP12* k, const _FP12* p, const _FP12* c) {
#pragma XLLEXPORT
	
	std::vector<double> x(k->rows, 0.0);
	std::vector<double> y(k->rows, 0.0); 

	
	pwlinear pl(k->rows, x.data(), y.data());

	
	return pl.variance(f, k->rows, k->array, p->array, c->array);
}
