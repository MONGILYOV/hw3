// Copyright Mongilyov Andrey & Novikov Igor 2022

#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include <fstream>
#include <iostream>
#include <vector>

std::string isCorrect(const std::string &file_name, size_t &c, size_t &len);
void enterData(const std::string &file_name, size_t &c, size_t &len, std::vector<std::vector<int>> &matrix,
               size_t &sx, size_t &sy, size_t &ex, size_t &ey);

#endif // INCLUDE_MAP_HPP_
