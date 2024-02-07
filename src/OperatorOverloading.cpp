#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>
#include <memory>
#include <unordered_set>

#include <deque>

class Matrix 
{
public:
    Matrix(uint32_t rows, uint32_t columns);

    Matrix(const Matrix& m) = delete;
    Matrix& operator=(const Matrix& m) = delete;

    Matrix(Matrix&& m);
    Matrix& operator+(const Matrix& m);
    Matrix& operator=(Matrix&& m);

    void read_string(std::string_view input_line, uint32_t row_len, uint32_t max_row);
    void print_matrix(void);

    void operator+=(const Matrix& other);

private:
    std::vector<std::vector<int>> m_data;
};

Matrix::Matrix(uint32_t rows, uint32_t columns)
:m_data(rows, std::vector<int>(columns))
{
}

void Matrix::read_string(std::string_view input_line, uint32_t row_len, uint32_t max_row)
{
    if (input_line.size() == 0) {
        return;
    }

    std::string_view digits = "0123456789";
    uint32_t cursor(0), non_digit(0);
    uint32_t row_number(0);
    // Last character of input_line is RETURN key
    while (row_number < max_row) {
        for (uint32_t i(0); i < row_len; i++) {
            cursor = input_line.find_first_of(digits, cursor);
            non_digit = input_line.find_first_not_of(digits, cursor);

            std::string_view str_num = input_line.substr(cursor, non_digit - cursor);
            m_data[row_number][i] = std::stoi(str_num.data());
            cursor = non_digit;
        }
        row_number++;
    }
}

void Matrix::print_matrix(void)
{
    for (uint32_t i(0); i < m_data.size(); i++) {
        for (uint32_t j(0); j < m_data.front().size(); j++) {
            std::cout << std::to_string(m_data[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::operator+=(const Matrix& other)
{
    for (uint32_t i(0); i < m_data.size(); i++) {
        for (uint32_t j(0); j < m_data.front().size(); j++) {
            m_data[i][j] += other.m_data[i][j];
        }
    }
}


int main()
{
    uint32_t test_cases;
    std::cin >> test_cases;

    uint32_t nRows, nColumns;
    std::string sLine;
    for (uint32_t i(0); i < test_cases; i++) {
        std::cin >> nRows >> nColumns;
        std::cin.ignore();

        Matrix mtxA(nRows, nColumns);
        Matrix mtxB(nRows, nColumns);

        while (sLine.size() == 0) std::getline(std::cin, sLine);
        mtxA.read_string(sLine, nColumns, nRows);
        std::getline(std::cin, sLine);
        mtxB.read_string(sLine, nColumns, nRows);

        mtxA += mtxB;
        mtxA.print_matrix();
        sLine.clear();
    }
}