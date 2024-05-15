/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Vetor3.h
*/

#pragma once

#include <cstdint>
#include <iostream>

#include "Error.hpp"
#include "Angle3D.hpp"

namespace Raytracer {
    namespace Math {
        class Vector3D {
        public:
            /**
            * @brief Constructor of the Vector3D class
            * @param valX The x value
            * @param valY The y value
            * @param valZ The z value
            * @return The new Vector3D
            **/
            Vector3D(double valX = 0, double valY = 0, double valZ = 0);

            /**
            * @brief Constructor of the Vector3D class
            * @param right The Vector3D to copy
            * @return The new Vector3D
            **/
            Vector3D(const Vector3D &right);

            /**
            * @brief Constructor of the Vector3D class
            * @param vals Float
            * @return The copy of the Vector3D
            **/
            Vector3D(float *vals);
            ~Vector3D() = default;

            /**
            * @brief Operator= of the Vector3D class
            * @param vec The Vector3D to copy
            * @return The new Vector3D
            **/
            Vector3D &operator=(const Vector3D &vec);
            operator float *();

            double operator[](uint8_t i) const
            {
                switch (i) {
                case 0:
                    return getX();
                case 1:
                    return getY();
                case 2:
                    return getZ();
                default:
                    throw Error("Invalid point index", "");
                }
            }
            double &operator[](uint8_t i)
            {
                switch (i) {
                case 0:
                    return x;
                case 1:
                    return y;
                case 2:
                    return z;
                default:
                    throw Error("Invalid point index", "");
                }
            }

            /**
            * @brief Getter of the X value in the Vector3D
            * @return The X value
            **/
            double getX(void) const { return x; }

            /**
             * @brief Getter of the Y value in the Vector3D
             * @return The Y value 
             */
            double getY(void) const { return y; }

            /**
             * @brief Getter of the Z value in the Vector3D
             * @return The Z value 
             */
            double getZ(void) const { return z; }

            /**
             * @brief Setter of the X value in the Vector3D
             * @param val The value to set
             */
            void setX(double val) { x = val; }

            /**
             * @brief Setter of the Y value in the Vector3D
             * @param val The value to set
             */
            void setY(double val) { y = val; }

            /**
             * @brief Setter of the Z value in the Vector3D
             * @param val The value to set
             */
            void setZ(double val) { z = val; }

            //////////////////////////

            /**
            * @brief Overload of the operato += for the Vector3D class
            * @param right The Vector3D to add
            * @return Replace the current Vector3D with the sum of the two vectors
            **/
            Vector3D &operator+=(const Vector3D &right);

            /**
             * @brief Overload of the operator -= for the Vector3D class
             * 
             * @param right The Vector3D to subtract
             * @return Replace the current Vector3D with the difference of the two vectors
             */
            Vector3D &operator-=(const Vector3D &right);

            /**
             * @brief Overload of the operator *= for the Vector3D class
             * 
             * @param scalar The scalar to multiply
             * @return Replace the current Vector3D with the product of the vector and the scalar
             */
            Vector3D &operator*=(double scalar);

            /**
             * @brief Overload of the operator *= for the Vector3D class
             * 
             * @param right The Vector3D to multiply
             * @return Replace the current Vector3D with the product of the two vectors
             * coordinates by coordinates
             */
            Vector3D &operator*=(const Vector3D &right);

            /**
             * @brief Overload of the operator /= for the Vector3D class
             * 
             * @param scalar The scalar to divide
             * @return Replace the current Vector3D with the division of the vector and the scalar
             */
            Vector3D &operator/=(double scalar);

            /**
             * @brief Overload of the operator /= for the Vector3D class
             * 
             * @param right The Vector3D to divide
             * @return Replace the current Vector3D with the division of the two vectors
             * coordinates by coordinates
             */
            Vector3D &operator/=(const Vector3D &right);

            //////////////////////////

            /**
             * @brief Overload of the operator + for the Vector3D class
             * 
             * @param right The Vector3D to add
             * @return A new Vector3D with the sum of the two vectors 
             */
            Vector3D operator+(const Vector3D &right) const;

            /**
             * @brief Overload of the operator + for the Vector3D class
             * 
             * @param num The scalar to add
             * @return A new Vector3D with the sum of the vector and the scalar
             */
            Vector3D operator+(double num) const;

            /**
             * @brief Overload of the operator - for the Vector3D class
             * 
             * @return A new Vector3D after making the current Vector3D negative
             */
            Vector3D operator-() const;

            /**
             * @brief Overload of the operator - for the Vector3D class
             * 
             * @param right The Vector3D to subtract
             * @return A new Vector3D with the difference of the two vectors
             */
            Vector3D operator-(const Vector3D &right) const;

            /**
             * @brief Overload of the operator - for the Vector3D class
             * 
             * @param num The scalar to subtract
             * @return A new Vector3D with the difference of the vector and the scalar
             */
            Vector3D operator-(double num) const;

            /**
             * @brief Overload of the operator * for the Vector3D class
             * 
             * @param scalar The scalar to multiply
             * @return A new Vector3D with the product of the vector and the scalar
             */
            Vector3D operator*(double scalar) const;

            /**
             * @brief Overload of the operator * for the Vector3D class
             * 
             * @param right The Vector3D to multiply
             * @return A new Vector3D with the product of the two vectors
             * coordinates by coordinates
             */
            Vector3D operator*(const Vector3D &right) const;

            /**
             * @brief Overload of the operator / for the Vector3D class
             * 
             * @param scalar The scalar to divide
             * @return A new Vector3D with the division of the vector and the scalar
             */
            Vector3D operator/(double scalar) const;

            /**
             * @brief Overload of the operator / for the Vector3D class
             * 
             * @param right The Vector3D to divide
             * @return A new Vector3D with the division of the two vectors
             * coordinates by coordinates
             */
            Vector3D operator/(const Vector3D &right) const;

            //////////////////////////

            /**
             * @brief Overload of the operator == for the Vector3D class
             * 
             * @param right The Vector3D to compare
             * @return True if the two vectors are equals, false otherwise
             */
            bool operator==(const Vector3D &right);

            /**
             * @brief Overload of the operator != for the Vector3D class
             * 
             * @param right The Vector3D to compare
             * @return True if the two vectors are different, false otherwise
             */
            bool operator!=(const Vector3D &right);

            //////////////////////////

            /**
            * @brief returns the sum of the product each component of the two vectors 
            * @param v The Vector3D to use
            * @return The result of the function
            **/
            double dot(const Vector3D &v) const;

            /**
            * @brief returns the length of the vector
            * @return The length of the vector
            **/
            double length(void) const;

            /**
            * @brief returns the cross product of the two vectors
            * @param v The Vector3D to use
            * @return The result of the function
            **/
            Vector3D cross(const Vector3D &v) const;

            /**
            * @brief returns the normalized vector
            * @return The normalized vector
            **/
            Vector3D normalize(void) const;

            /**
            * @brief returns the rotated vector
            * @param angle The angle to rotate
            * @return The rotated vector
            **/
            Vector3D rotate(const Angle3D &angle);

            /**
            * @brief returns the angle between two vectors
            * @param right The Vector3D to use
            * @return The angle between the two vectors
            **/
            double angle(const Vector3D &right);

            //////////////////////////

            /**
            * @brief returns the distance between two vectors
            * @param left The first Vector3D
            * @param right The second Vector3D
            * @return The distance between the two vectors
            **/
            static double gDist(const Vector3D &left, const Vector3D &right);

            /**
            * @brief returns the dot product of two vectors
            * @param left The first Vector3D
            * @param right The second Vector3D
            * @return The dot product of the two vectors
            **/
            static double gDot(const Vector3D &left, const Vector3D &right);

            /**
            * @brief returns the Rotation product of two vectors
            * @param left The first Vector3D
            * @param right The angle to rotate
            * @return The rotation of the left vector by the right value
            **/
            static Vector3D gRotate(const Vector3D &left, const Angle3D &right);

            /**
            * @brief returns the angle between two vectors
            * @param left The first Vector3D
            * @param right The second Vector3D
            * @return The angle between the two vectors
            **/
            static double gAngle(const Vector3D &left, const Vector3D &right);

            /**
            * @brief returns the reflection of a vector
            * @param v The Vector3D to reflect
            * @param n The normal vector
            * @return The reflected vector
            **/
            static Vector3D gReflect(const Vector3D &v, const Vector3D &n);

            /**
            * @brief function for linear interpolation
            * @param left The first Vector3D
            * @param right The second Vector3D
            * @param t The value to interpolate
            * @return The interpolated vector
            **/
            static Vector3D gLerp(const Vector3D &left, const Vector3D &right, double t);

        private:
            double x; ///< x value
            double y; ///< y value
            double z; ///< z value
            float m_vals[3]; ///< The values of the vector
        };

    } // namespace Math
} // namespace Raytracer

/**
 * @brief Overload of the operator << for the Vector3D class
 * 
 * @param os output stream
 * @param v vector to print
 * @return The output stream with the vector printed
 */
std::ostream &operator<<(std::ostream &os, const Raytracer::Math::Vector3D &v);
