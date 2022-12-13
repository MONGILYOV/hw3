// Copyright Mongilyov Andrey & Novikov Igor 2022

#ifndef WAYFIND_MYFUNCTIONS_HPP_
#define WAYFIND_MYFUNCTIONS_HPP_

#include <iostream>
#include <vector>

std::string isCorrect(const std::string& file_name, int& c, int& len);
void enterData(const std::string& file_name, int& c, int& len, std::vector<std::vector<int>>& matrix, int& sx, int& sy, int& ex, int& ey);


#endif //WAYFIND_MYFUNCTIONS_HPP_
