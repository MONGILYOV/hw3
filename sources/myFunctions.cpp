

#include <myFunctions.hpp>

std::string isCorrect(const std::string &file_name, size_t &c, size_t &len) { // проверка корректности файла
    std::ifstream fint(file_name);
    std::string temp;
    int countOfStar = 0;
    int countOfExclMark = 0;
    if (!fint.is_open()) { // существование
        return "Error: file not found";
    }
    if (fint.peek() == EOF) { // пустота
        return "Error: file is empty";
    }
    c = 0;

    while (std::getline(fint, temp)) {
        ++c;
    }

    fint.clear();
    fint.seekg(0, std::ios::beg);
    std::vector<char> symbols = {'|', '-', '*', '!', ' '};
    std::getline(fint, temp);
    len = temp.length(); // получение длины первой строки

    for (size_t i = 0; i < len; ++i) { // проверка первой строки
        if (temp[i] != '-' && temp[i] != '!' && temp[i] != '*') {
            return "Error: wrong characters";
        }
        if (temp[i] == '*') {
            ++countOfStar;
        }
        if (temp[i] == '!') {
            ++countOfExclMark;
        }
    }

    for (size_t k = 1; k < c - 1; ++k) { // проверка всех строк, кроме первой и последней
        std::getline(fint, temp);
        if (temp.length() != len) {
            return "Error: wrong length of the line";
        }
        for (size_t i = 0; i < len; ++i) {
            if (temp[i] == '*') {
                ++countOfStar;
            }
            if (temp[i] == '!') {
                ++countOfExclMark;
            }
            if (i == 0 || i == len - 1) {
                if (temp[i] != '|' && !(temp[i] == '!' || temp[i] == '*')) {
                    return "Error: wrong characters";
                }
            } else {
                if (!(temp[i] == ' ' || temp[i] == '|')) {
                    return "Error: wrong characters";
                }
            }
        }
    }

    std::getline(fint, temp);
    for (size_t i = 0; i < len; ++i) { // проверка последней строки
        if (temp[i] != '-' && temp[i] != '!' && temp[i] != '*') {
            return "Error: wrong characters";
        }
        if (temp[i] == '*') {
            ++countOfStar;
        }
        if (temp[i] == '!') {
            ++countOfExclMark;
        }
    }

    if (countOfExclMark == 1 && countOfStar == 1) {
        return "ok";
    }
    return "Error: Count of stars or exclamation mark is not 1";
}

void enterData(const std::string &file_name, size_t &c, size_t &len, std::vector<std::vector<int>> &matrix,
               size_t &sx, size_t &sy, size_t &ex, size_t &ey) {
    std::string check = isCorrect(file_name, c, len); // проверка
    if (check != "ok") {
        std::cerr << check;
        exit(1);
    }
    std::ifstream fint(file_name);
    std::string temp;
    matrix.assign(c, std::vector<int>(len));
    for (size_t i = 0; i < c; ++i) {
        std::getline(fint, temp);
        for (size_t k = 0; k < len; ++k) {
            switch (temp[k]) {
                case '|':
                    matrix[i][k] = -1;
                    break;
                case '-':
                    matrix[i][k] = -1;
                    break;
                case ' ':
                    matrix[i][k] = 0;
                    break;
                case '*':
                    matrix[i][k] = 0; // пока так, если будет удобно, то оставим
                    sx = k; // sx и sy - координаты начала
                    sy = i;
                    break;
                case '!':
                    matrix[i][k] = 0; // пока так, если будет удобно, то оставим
                    ex = k; // ex и ey - координаты конца
                    ey = i;
                    break;
            }
        }
    }
    fint.close();
}
// todo: Волновой алгоритм и вывод
