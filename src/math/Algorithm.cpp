/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Algorithm
*/

#include "Math/Algorithm.hpp"

namespace Raytracer {
    namespace Math {
        double Algorithm::clampD(double value, double min, double max)
        {
            if (value < min)
                return min;
            if (value > max)
                return max;
            return value;
        }

        Color Algorithm::clampColor(const Color &color)
        {
            return Color(color.getR(), color.getG(), color.getB());
        }

        double Algorithm::minOfThree(double a, double b, double c)
        {
            return std::min(std::min(a, b), c);
        }

        double Algorithm::maxOfThree(double a, double b, double c)
        {
            return std::max(std::max(a, b), c);
        }

        Vector3D Algorithm::minOfVector3D(const Vector3D &v1, const Vector3D &v2)
        {
            return Vector3D(std::min(v1.getX(), v2.getX()), std::min(v1.getY(), v2.getY()),
                std::min(v1.getZ(), v2.getZ()));
        }

        Vector3D Algorithm::maxOfVector3D(const Vector3D &v1, const Vector3D &v2)
        {
            return Vector3D(std::max(v1.getX(), v2.getX()), std::max(v1.getY(), v2.getY()),
                std::max(v1.getZ(), v2.getZ()));
        }

        void Algorithm::sortRoots(double *roots, int n)
        {
            for (int i = 0; i < n; i++)
                if (std::isnan(roots[i]))
                    roots[i] = -1e-8;

            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (roots[j] > roots[j + 1]) {
                        double tmp = roots[j];
                        roots[j] = roots[j + 1];
                        roots[j + 1] = tmp;
                    }
                }
            }
        }

        int Algorithm::filterRealNumbers(
            int numComplexValues, const complex inArray[], double outArray[])
        {
            int numRealValues = 0;
            for (int i = 0; i < numComplexValues; ++i)
                if (fabs(inArray[i].imag()) < TOLERANCE)
                    outArray[numRealValues++] = inArray[i].real();
            return numRealValues;
        }

        complex Algorithm::cbrt(complex a, int n)
        {
            const double TWOPI = 2.0 * M_PI;

            double rho = pow(abs(a), 1.0 / 3.0);
            double theta = ((TWOPI * n) + arg(a)) / 3.0;
            return complex(rho * cos(theta), rho * sin(theta));
        }

        int Algorithm::solveCubicEquation(
            complex a, complex b, complex c, complex d, complex roots[3])
        {
            if (isZero(a))
                a = TOLERANCE;

            b /= a;
            c /= a;
            d /= a;

            complex S = b / 3.0;
            complex D = c / 3.0 - S * S;
            complex E = S * S * S + (d - S * c) / 2.0;
            complex Froot = std::sqrt(E * E + D * D * D);
            complex F = -Froot - E;

            if (isZero(F))
                F = Froot - E;

            for (int i = 0; i < 3; ++i) {
                const complex G = cbrt(F, i);
                roots[i] = G - D / G - S;
            }

            return 3;
        }

        int Algorithm::solveQuarticEquation(complex a, complex b, complex c, complex d,
            complex e, complex roots[4])
        {
            if (isZero(a))
                return solveCubicEquation(b, c, d, e, roots);

            b /= a;
            c /= a;
            d /= a;
            e /= a;

            complex b2 = b * b;
            complex b3 = b * b2;
            complex b4 = b2 * b2;

            complex alpha = (-3.0 / 8.0) * b2 + c;
            complex beta = b3 / 8.0 - b * c / 2.0 + d;
            complex gamma
                = (-3.0 / 256.0) * b4 + b2 * c / 16.0 - b * d / 4.0 + e;

            complex alpha2 = alpha * alpha;
            complex t = -b / 4.0;

            if (isZero(beta)) {
                complex rad = std::sqrt(alpha2 - 4.0 * gamma);
                complex r1 = std::sqrt((-alpha + rad) / 2.0);
                complex r2 = std::sqrt((-alpha - rad) / 2.0);

                roots[0] = t + r1;
                roots[1] = t - r1;
                roots[2] = t + r2;
                roots[3] = t - r2;
            } else {
                complex alpha3 = alpha * alpha2;
                complex P = -(alpha2 / 12.0 + gamma);
                complex Q
                    = -alpha3 / 108.0 + alpha * gamma / 3.0 - beta * beta / 8.0;
                complex R = -Q / 2.0 + sqrt(Q * Q / 4.0 + P * P * P / 27.0);
                complex U = cbrt(R, 0);
                complex y = (-5.0 / 6.0) * alpha + U;
                if (isZero(U))
                    y -= cbrt(Q, 0);
                else
                    y -= P / (3.0 * U);
                complex W = std::sqrt(alpha + 2.0 * y);

                complex r1 = std::sqrt(-(3.0 * alpha + 2.0 * y + 2.0 * beta / W));
                complex r2 = std::sqrt(-(3.0 * alpha + 2.0 * y - 2.0 * beta / W));

                roots[0] = t + (W - r1) / 2.0;
                roots[1] = t + (W + r1) / 2.0;
                roots[2] = t + (-W - r2) / 2.0;
                roots[3] = t + (-W + r2) / 2.0;
            }

            return 4;
        }
    }
} // namespace Raytracer
