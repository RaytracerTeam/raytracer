/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Angle.hpp
*/

#pragma once

namespace Raytracer {
    namespace Math {
        /**
        * @brief Angle3D class
        * Contains all functions related to the angles of the raytracer
        **/
        class Angle3D {
        public:
            /**
            * @brief Constructor of the Angle3D class
            * @param x The x value of the angle
            * @param y The y value of the angle
            * @param z The z value of the angle
            **/
            Angle3D(double x = 0, double y = 0, double z = 0);
            ~Angle3D() = default;
            // Angle3D &operator=(const Angle3D &angle);
            operator float *();

            /**
            * @brief Get the yaw of the angle (x axis)
            * @return The yaw of the angle
            **/
            double getYaw(void) const { return m_yaw; }

            /**
             * @brief Get the Pitch object
             * @return The pitch of the angle 
             */
            double getPitch(void) const { return m_pitch; }

            /**
             * @brief Get the Roll object
             * @return The roll of the angle 
             */
            double getRoll(void) const { return m_roll; }

            /**
             * @brief Set the Yaw object
             * @param a The new yaw value
             */
            void setYaw(double a) { m_yaw = a; }

            /**
             * @brief Set the Pitch object
             * @param a The new pitch value
             */
            void setPitch(double a) { m_pitch = a; }

            /**
             * @brief Set the Roll object
             * @param a The new roll value
             */
            void setRoll(double a) { m_roll = a; }
        private:
            double m_yaw = 0; ///< rotation around the x axis (yaw)
            double m_pitch = 0; ///< rotation around the y axis (pitch)
            double m_roll = 0; ///< rotation around the z axis (roll)
            float m_vals[3]; ///< The values of the angles
        };
    } // namespace Math

} // namespace Raytracer
