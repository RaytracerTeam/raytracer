/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Algorithm
*/

#pragma once

#define _USE_MATH_DEFINES
#include <array>
#include <cmath>
#include <complex>

#include "Color.hpp"

#define TOLERANCE 1.0e-8

namespace Raytracer {
    namespace Math {
        typedef std::complex<double> complex;

        class Algorithm {
        public:
            static double clampD(double value, double min, double max);

            static Color clampColor(const Color &color);

            static inline bool isZero(complex x)
            {
                return (fabs(x.real()) < TOLERANCE)
                    && (fabs(x.imag()) < TOLERANCE);
            }

            static void sortRoots(double *roots, int n);

            static int filterRealNumbers(int numComplexValues,
                const complex inArray[], double outArray[]);

            static complex cbrt(complex a, int n);

            static int solveCubicEquation(
                complex a, complex b, complex c, complex d, complex roots[3]);

            static inline int solveCubicEquation(
                double a, double b, double c, double d, double roots[3])
            {
                complex croots[3];

                const int numComplexRoots = solveCubicEquation(
                    complex(a), complex(b), complex(c), complex(d), croots);

                return filterRealNumbers(numComplexRoots, croots, roots);
            }

            static int solveQuarticEquation(complex a, complex b, complex c,
                complex d, complex e, complex roots[4]);

            static inline int solveQuarticEquation(double a, double b, double c,
                double d, double e, double roots[4])
            {
                complex croots[4];

                const int numComplexRoots = solveQuarticEquation(complex(a),
                    complex(b), complex(c), complex(d), complex(e), croots);

                return filterRealNumbers(numComplexRoots, croots, roots);
            }
        };
    }
} // namespace Raytracer
