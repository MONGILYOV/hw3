// Copyright Mongilyov Andrey & Novikov Igor 2022

#include <myFunctions.hpp>
#include <fstream>
#include <iostream>

std::string isCorrect(const std::string& file_name, int& c, int& len) { //проверка корректноси файла
    std::ifstream fint(file_name);
    std::string temp;
    int countOfStar = 0;
    int countOfExclMark = 0;
    if (!fint) { // существование
        return "Error: file not found";
    } else if (fint.peek() == EOF) { // пустота
        return "Error: file is empty";
    } else {
        c = 0;
        while (std::getline(fint, temp)) ++c;
        fint.clear();
        fint.seekg(0, std::ios::beg);
        std::vector<char> symbols({'|', '-', '*', '!', ' '});
        std::getline(fint, temp);
        len = int(temp.length()); // получение длины первой строки
        for (size_t i = 0; i < len; ++i) { // проверка первой строки на допустимость символов
            if (temp[i] != '-') return "Error: file contains invalid characters";
        }
        for (size_t k = 0; k < (c - 1); ++k) { //проверка остальных строк
            std::getline(fint, temp);
            if (temp.length() != len) // проверка на соответствие длины
                return "Error: wrong length of the line";
            if (k == c - 1) {
                for (size_t i = 0; i < len; ++i) { // проверка первой строки на допустимость символов
                    if (temp[i] != '-') return "Error: file contains invalid characters";

                }
            }
            for (size_t i = 0; i < len; ++i) { // проверка на допустимость символов
                bool flag = false;
                for (auto sym: symbols) {
                    if (i == 0 or i == len) {
                        if (temp[i] == '|') {
                            flag = true;
                            break;
                        }
                    }
                    if (sym == temp[i]) {
                        if (sym == '*')
                            countOfStar += 1;
                        if (sym == '!')
                            countOfExclMark += 1;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    return "Error: file contains invalid characters";
                }
            }
        }
    }
    if (countOfExclMark == 1 and countOfStar == 1) {  // проверка количества начал и концов (должно быть по 1)
        return "ok";
    } else return "Error: Count of stars or exclamation mark is not 1";
}

void enterData(const std::string& file_name, int& c, int& len, std::vector<std::vector<int>>& matrix, int& sx, int& sy, int& ex, int& ey){
    std::string check = isCorrect(file_name,c, len); // проверка
    if (check != "ok"){
        std::cerr << check;
        exit(1);
    }
    std::ifstream fint(file_name);
    std::string temp;
    matrix.assign(c, std::vector<int>(len));
    for (size_t i = 0; i < c; ++i){
        std::getline(fint, temp);
        for (size_t k = 0; k < len; ++k){
            switch (temp[k]) {
                case '|': case '-': {
                    matrix[i][k] = -1; // здесь: -1 стена, -2 свободная клетка
                    break;
                }
                case ' ': {
                    matrix[i][k] = -2;
                    break;
                }
                case '*': {
                    matrix[i][k] = -2;
                    sx = int (k); // sx и sy - координаты начала
                    sy =int (i);
                    break;
                }
                case '!': {
                    matrix[i][k] = -2;
                    ex = int (k); // ex и ey - координаты конца
                    ey = int(i);
                    break;
                }
            }
        }
    }
    fint.close();
}
// todo: Волновой алгоритм и вывод