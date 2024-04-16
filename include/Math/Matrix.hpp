/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-raytracer-thomas.pommier
** File description:
** Matrix.hpp
*/

#pragma once

#include <array>
#include <iostream>
#include <cstdint>

#include "Error.hpp"

template <size_t Rows, size_t Columns>
class Matrix {
public:
    Matrix() {};
    ~Matrix() = default;

    Matrix(const Matrix<Rows, Columns> &m)
    {
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                _list[i][j] = m(i, j);
    }

    Matrix &operator=(const Matrix<Rows, Columns> &m)
    {
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                _list[i][j] = m(i, j);
        return *this;
    }

    double operator()(size_t row, size_t col) const
    {
        if (row >= Rows)
            throw Error("Row out of range", "Math::Matrix");
        if (col >= Cols)
            throw Error("Columns out of range", "Math::Matrix");
        return _list[row][col];
    }

    double &operator()(size_t row, size_t col)
    {
        if (row >= Rows)
            throw Error("Row out of range", "Math::Matrix");
        if (col >= Cols)
            throw Error("Columns out of range", "Math::Matrix");
        return _list[row][col];
    }

    template <size_t M_Rows, size_t M_Cols>
    Matrix operator*(const Matrix<M_Rows, M_Cols> &right)
    {
        Matrix<M_Rows, Columns> newM;

        for (size_t i = 0; i < Rows; i++)
            for (size_t j = 0; j < M_Cols; j++)
                for (size_t k = 0; k < Columns; k++)
                    newM(i, j) += _list[i][k] * right(k, j);
        return newM;
    }

    template <size_t M_Rows, size_t M_Cols>
    Matrix &operator*=(const Matrix<M_Rows, M_Cols> &m)
    {
        const Matrix<M_Rows, Columns> newM = *this * m;
        const size_t rows = std::min(Rows, M_Rows);
        const size_t cols = std::min(Columns, M_Cols);

        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                _list[i][j] = newM(i, j);
        return *this;
    }

    std::ostream &display(std::ostream &stream) const
    {
        return stream << _list;
    }

private:
    std::array<std::array<double, Columns>, Rows> _list;
};

template <size_t Rows, size_t Columns>
std::ostream &operator<<(std::ostream &stream, const Matrix<Rows, Columns> &mat)
{
    return mat.display(stream);
}
