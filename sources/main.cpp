// Copyright Mongilyov Andrey & Novikov Igor 2022

#include <myFunctions.hpp>

int main() {
    size_t c = 0, len = 0, sx = 0, sy = 0, ex = 0, ey = 0;
    std::vector<std::vector<int>> matrix;
    // TODO: file_name из командной строки
    enterData("labirint5.txt", c, len, matrix, sx, sy, ex, ey);
    for (const auto& row : matrix) {
        for (const auto& column : row) {
            std::cout << column << '\t';
        }
        std::cout << std::endl;
    }
}
