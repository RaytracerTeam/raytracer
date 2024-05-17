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
    /**
    * @brief Math namespace
    * Contains all math functions and classes 
    **/
    namespace Math {
        typedef std::complex<double> complex;

        /**
        * @brief Algorithm class
        * Contains all functions related to the math of the raytracer
        **/
        class Algorithm {
        public:
            /**
            * @brief Clamps a value between a min and a max
            * @param value The value to clamp
            * @param min The minimum value
            * @param max The maximum value
            * @return The clamped value
            **/
            static double clampD(double value, double min, double max);

            /**
            * @brief Clamps a color from a color object
            * @param color The color to clamp
            * @return The clamped color
            **/
            static Color clampColor(const Color &color);

            static double minOfThree(double a, double b, double c);
            static double maxOfThree(double a, double b, double c);

            static Vector3D minOfVector3D(const Vector3D &v1, const Vector3D &v2);
            static Vector3D maxOfVector3D(const Vector3D &v1, const Vector3D &v2);

            /**
            * @brief Checks if a complex number is zero
            * @param x The complex number to check
            * @return True if the complex number is zero, false otherwise
            **/
            static inline bool isZero(complex x)
            {
                return (fabs(x.real()) < TOLERANCE)
                    && (fabs(x.imag()) < TOLERANCE);
            }

            /**
            * @brief sorts the roots of a polynomial
            * @param roots The roots of the polynomial
            * @param n The number of roots
            **/
            static void sortRoots(double *roots, int n);

            /**
            * @brief Filters the real numbers from a complex array
            * @param numComplexValues The number of complex values
            * @param inArray The input array
            * @param outArray The output array
            * @return The number of real values
            **/
            static int filterRealNumbers(int numComplexValues,
                const complex inArray[], double outArray[]);

            /**
             * @brief Cubic root of a complex number
             * 
             * @param a 
             * @param n 
             * @return The cubic root of the complex number 
             */
            static complex cbrt(complex a, int n);

            /**
             * @brief Solves a cubic equation on complex numbers
             * 
             * @param a 
             * @param b 
             * @param c 
             * @param d 
             * @param roots 
             * @return The sum of all real numbers
             */
            static int solveCubicEquation(
                complex a, complex b, complex c, complex d, complex roots[3]);


            /**
             * @brief Solves a cubic equation on double numbers
             * 
             * @param a 
             * @param b 
             * @param c 
             * @param d 
             * @param roots 
             * @return The sum of all real numbers
             */
            static inline int solveCubicEquation(
                double a, double b, double c, double d, double roots[3])
            {
                complex croots[3];

                const int numComplexRoots = solveCubicEquation(
                    complex(a), complex(b), complex(c), complex(d), croots);

                return filterRealNumbers(numComplexRoots, croots, roots);
            }

            /**
             * @brief Solves a quartic equation on complex numbers
             * 
             * @param a 
             * @param b 
             * @param c 
             * @param d 
             * @param e 
             * @param roots 
             * @return The sum of all real numbers
             */
            static int solveQuarticEquation(complex a, complex b, complex c,
                complex d, complex e, complex roots[4]);

            /**
             * @brief Solves a quartic equation on double numbers
             * 
             * @param a 
             * @param b 
             * @param c 
             * @param d 
             * @param e 
             * @param roots 
             * @return int 
             */
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
