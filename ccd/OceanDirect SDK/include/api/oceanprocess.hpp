#pragma once
#include <iterator>
namespace oceandirect {
    namespace api {

        /* Quick and dirty version to evaluate a polynomial that will work for
         * a std::vector iterator and pointer to types.
         * IMPORTANT NOTE: This version assumes the coefficients
         * are in descending order i.e. the highest power first. Polynomials in
         * Ocean are usually in ascending order so wrap the iterators with std::reverse_iterator
         * before you use them with this.
        */
        template<typename IterType>
        typename std::iterator_traits<IterType>::value_type EvalPolynomial(typename std::iterator_traits<IterType>::value_type x,
                IterType coeffBegin, IterType coeffEnd) {

            typename std::iterator_traits<IterType>::value_type result = 0.0;
            for (IterType currentCoeff = coeffBegin; currentCoeff != coeffEnd; ++currentCoeff) {
                result = result * x + *currentCoeff;
            }
            return result;
        }
    }
}
