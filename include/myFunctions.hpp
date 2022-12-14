// Copyright Mongilyov Andrey & Novikov Igor 2022

#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include <fstream>
#include <iostream>
#include <vector>

std::string isCorrect(const std::string &file_name, size_t &c, size_t &len);

void enterData(const std::string &file_name, size_t &c, size_t &len, std::vector<std::vector<int>> &matrix,
               size_t &sx, size_t &sy, size_t &ex, size_t &ey);

void saveInFile(std::vector<std::vector<int>>& matrix, size_t height, size_t length,
                size_t sx, size_t sy, size_t ex, size_t ey, const std::string& filename);

void waveAlgorithm(std::vector<std::vector<int>>& matrix, size_t height, size_t length,
                   size_t sx, size_t sy, size_t ex, size_t ey, const std::string& filename);

#endif // INCLUDE_MAP_HPP_
