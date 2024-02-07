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

using MatrixData = std::vector<std::vector<int>>;

class Matrix 
{
public:
    Matrix(uint32_t rows, uint32_t columns);

    Matrix(const Matrix& m) = delete;
    Matrix& operator=(const Matrix& m) = delete;

    Matrix(Matrix&& m);
    Matrix operator+(const Matrix& m);
    Matrix& operator=(Matrix&& m);

    void read_string(std::string_view input_line, uint32_t row_len, uint32_t max_row);
    void print_matrix(void);

    uint32_t get_rows(void);
    uint32_t get_columns(void);

    void operator+=(const Matrix& other);

private:
    std::unique_ptr<MatrixData> m_upData;
};

Matrix::Matrix(uint32_t rows, uint32_t columns)
:m_upData(std::make_unique<MatrixData>(rows, std::vector<int>(columns)))
{
    // std::cout << "consturctor operator\r\n";
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
            m_upData->at(row_number)[i] = std::stoi(str_num.data());
            cursor = non_digit;
        }
        row_number++;
    }
}

void Matrix::print_matrix(void)
{
    for (uint32_t i(0); i < m_upData->size(); i++) {
        for (uint32_t j(0); j < m_upData->front().size(); j++) {
            std::cout << std::to_string(m_upData->at(i)[j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::operator+=(const Matrix& other)
{
    for (uint32_t i(0); i < m_upData->size(); i++) {
        for (uint32_t j(0); j < m_upData->front().size(); j++) {
            m_upData->at(i)[j] += other.m_upData->at(i)[j];
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
        // Matrix mtxC(nRows, nColumns);

        while (sLine.size() == 0) std::getline(std::cin, sLine);
        mtxA.read_string(sLine, nColumns, nRows);
        std::getline(std::cin, sLine);
        mtxB.read_string(sLine, nColumns, nRows);

        Matrix mtxC = mtxA + mtxB;
        // mtxC = mtxA + mtxB;
        mtxC.print_matrix();
        sLine.clear();
    }
}

Matrix::Matrix(Matrix &&m)
: m_upData(std::move(m.m_upData))
{
    // std::cout << "move consturctor operator\r\n";
}

// !!!!!!!!!!!!
// CANNOT BE Matrix&& Matrix::operator+(const Matrix &other)
// Will cause problem from the local variable returned
Matrix Matrix::operator+(const Matrix &other)
{
    Matrix mtxRet(get_rows(), get_columns());

    for (uint32_t i(0); i < get_rows(); i++) {
        for (uint32_t j(0); j < get_columns(); j++) {
            mtxRet.m_upData->at(i)[j] = m_upData->at(i)[j] + other.m_upData->at(i)[j];
        }
    }
    return mtxRet;
}

Matrix &Matrix::operator=(Matrix &&m)
{
    if (&m == this) return *this;

    // std::cout << "move assignment operator\r\n";

    m_upData = std::move(m.m_upData);
    return *this;
}

uint32_t Matrix::get_rows(void)
{
    return m_upData->size();
}

uint32_t Matrix::get_columns(void)
{
    return m_upData->front().size();
}
