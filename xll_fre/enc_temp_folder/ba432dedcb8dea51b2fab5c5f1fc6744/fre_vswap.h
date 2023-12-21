#pragma once
#include <algorithm>
#include <vector>
#include <cmath> 
#include "../xll/xll/ensure.h"

namespace fre::vswap {

	// Piecewise linear curve determined by (x_i, y_i) for i = 0, ..., n-1
	class pwlinear {
		std::vector<double> x;
		std::vector<double> y;
		// x[i] <= x_ < x[i+1]
		size_t index(double x_) const
		{
			return std::lower_bound(x.begin(), x.end(), x_) - x.begin();
		}
	public:
		pwlinear(size_t n, const double* x_, const double* y_)
			: x(x_, x_ + n), y(y_, y_ + n)
		{
			ensure(n >= 2);
			ensure(std::is_sorted(x.begin(), x.end()));
		}
		// value at x
		double value(double x_) const
		{
			size_t i = index(x_);

			if (i == x.size() - 1) {
				ensure(x_ > x.back());
				--i; // use last two points
			}
			double m = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);

			return y[i] + m * (x_ - x[i]);
		}

		// first derivative at x
		double derivative(double x_) const {
			size_t i = index(x_);
			if (i == x.size() - 1) {
				--i;
			}

			double m = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
			return m;
		}

		// second derivative at x[1], ..., x[n-2]
		std::vector<double> delta() const {
			std::vector<double> deltas(x.size() - 1, 0.0);
			return deltas;
		}
		double variance(double f, size_t n, const double* k, const double* p, const double* c) const {
			double var = 0.0;
			for (size_t i = 0; i < n; ++i) {
				if (k[i] <= 0) {
					throw std::invalid_argument("Strike price cannot be zero or negative");
				}
				double term = -2 * std::log(k[i] / f) + 2 * (k[i] - f) / f;
				double value = (k[i] < f) ? p[i] : c[i];
				var += value * term;
			}
			return var / n;
		}
	};

} // namespace fre::vswap