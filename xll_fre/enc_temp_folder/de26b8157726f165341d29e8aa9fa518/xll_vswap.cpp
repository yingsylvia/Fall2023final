#include "fre_vswap.h"
#include "xll_fre.h"

using namespace xll;
using namespace fre::vswap;

// Implement xll_vswap
AddIn xai_vswap(
    Function(XLL_DOUBLE, "xll_vswap", "XLL.VSWAP")
    .Arguments({
        Arg(XLL_DOUBLE, "f", "is the forward price."),
        Arg(XLL_FP, "k", "is an array of strike prices."),
        Arg(XLL_FP, "p", "is an array of put prices corresponding to strikes."),
        Arg(XLL_FP, "c", "is an array of call prices corresponding to strikes."),
        })
        .Category("VSWAP")
    .FunctionHelp("Calculate variance for variance swap.")
);

double WINAPI xll_vswap(double f, const _FP12* k, const _FP12* p, const _FP12* c) {
#pragma XLLEXPORT
   
    ensure(k->rows == p->rows && p->rows == c->rows);

   
    std::vector<double> x_values(k->rows, 1.0); 
    std::vector<double> y_values(k->rows, 1.0); 

 
    pwlinear pl(k->rows, x_values.data(), y_values.data());


    return pl.variance(f, k->rows, k->array, p->array, c->array);
}
