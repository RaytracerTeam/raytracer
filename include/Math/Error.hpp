/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Error.h
*/

#pragma once

#include <exception>

namespace Raytracer {
    namespace Math {
        class Error : public std::exception {
        public:
            Error(const char *message, const char *where)
                : m_message(message)
                , m_where(where)
            {
            }
            ~Error() = default;

            const char *what() const noexcept
            {
                return m_message;
            }
            const char *where() const noexcept
            {
                return m_where;
            }

        private:
            const char *m_message;
            const char *m_where;
        };
    }
}
