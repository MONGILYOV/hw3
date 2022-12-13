// Copyright Mongilyov Andrey & Novikov Igor 2022

#include <myFunctions.hpp>

int main() {
    std::string  file_name = "test.txt"; // todo: ввод file_name как аргумента консоли
    int c = 0, len = 0;
    int sx = 0, sy = 0, ex = 0, ey = 0;
    std::vector<std::vector<int>> matrix;
    std::vector<int> wx;
    std::vector<int> wy;
    enterData(file_name, c, len, matrix, sx, sy, ex, ey);

}
