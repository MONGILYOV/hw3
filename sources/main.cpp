// Copyright Mongilyov Andrey & Novikov Igor 2022

#include <myFunctions.hpp>

int main(int argc, char* args[]) {
    // c - количество строк
    // len - количество столбцов
    // sx, sy - координаты начала
    // ex, ey - координаты конца
    if (argc == 1) {
        std::cout << "Error: no filename" << std::endl;
        return -1;
    }
    size_t c = 0, len = 0, sx = 0, sy = 0, ex = 0, ey = 0;
    std::vector<std::vector<int>> matrix;
    enterData(args[1], c, len, matrix, sx, sy, ex, ey);
    waveAlgorithm(matrix, c, len, sx, sy, ex, ey, args[1]);
}
