#pragma once
#include <vector>

namespace oceandirect {
	namespace api {
        class OceanProcess {
        public:
            /**
             * Evaluate the polynomial with specified coefficients at the point x.
             * The coefficients must be in ascending order i.e. the intercept is the first
             * element and the highest order coefficient last.
            */
            static double EvaluatePolynomial(const double x, const std::vector<double>& polyCoeff);

            //ColorObject PerformColorCalculations(int *errorCode, std::vector<double> irradiance_data, std::vector<double> _waveln_data);

            /**
             * Find the nearest element to a specified value contained wholly within the specified array
             * of values (sorted in ascending order) i.e. xaxis[first] <= wl <= xaxis[last].
             * If the criterion is met, return the index of the found value, otherwise return -1.
            */
            static int FindNearest(const std::vector<double>& xaxis, double wl);
        };
	}
}
