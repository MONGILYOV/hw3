

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
                // -1 - стена
                // -2 - пустое поле, начало и конец
                // -3 - конечный путь
                case '|':
                    matrix[i][k] = -1;
                    break;
                case '-':
                    matrix[i][k] = -1;
                    break;
                case ' ':
                    matrix[i][k] = -2;
                    break;
                case '*':
                    matrix[i][k] = -2;
                    sx = k; // sx и sy - координаты начала
                    sy = i;
                    break;
                case '!':
                    matrix[i][k] = -2;
                    ex = k; // ex и ey - координаты конца
                    ey = i;
                    break;
            }
        }
    }
    fint.close();
}

void saveInFile(std::vector<std::vector<int>>& matrix, size_t height, size_t length,
                   size_t sx, size_t sy, size_t ex, size_t ey, const std::string& filename) {
    std::ofstream file(filename, std::ios::app);
    for (size_t i = 0; i < length; ++i) {
        if (sy == 0 && sx == i) {
            file << '*';
            continue;
        }
        if (ey == 0 && ex == i) {
            file << '!';
            continue;
        }
        file << '-';
    }
    file << std::endl;

    for (size_t y = 1; y < height - 1; ++y) {
        for (size_t x = 0; x < length; ++x) {
            if (y == sy && x == sx) {
                file << '*';
                continue;
            }
            if (y == ey && x == ex) {
                file << '!';
                continue;
            }
            switch (matrix[y][x]) {
                case -1:
                    file << '|';
                    break;
                case -3:
                    file << '*';
                    break;
                default:
                    file << ' ';
                    break;
            }
        }
        file << std::endl;
    }

    for (size_t i = 0; i < length; ++i) {
        if (sy == height - 1 && sx == i) {
            file << '*';
            continue;
        }
        if (ey == height - 1 && ex == i) {
            file << '!';
            continue;
        }
        file << '-';
    }
    file << std::endl;
    file.close();
}

void waveAlgorithm(std::vector<std::vector<int>>& matrix, size_t height, size_t length,
                   size_t sx, size_t sy, size_t ex, size_t ey, const std::string& filename) {
    int dx[4] = {-1, 0, 0, 1}; // слева, снизу, сверху, справа
    int dy[4] = {0, -1, 1, 0};
    int i = 0; // волна
    matrix[sy][sx] = 0;
    while (matrix[ey][ex] == -2 && i < height * length) { // костыль, чтобы выйти из цикла если пути нет
        for (size_t y = 0; y < height; ++y) {
            for (size_t x = 0; x < length; ++x) {
                if (matrix[y][x] == i) {
                    for (size_t j = 0; j < 4; ++j) {
                        int tempY = y + dy[j];
                        int tempX = x + dx[j];
                        if ((tempY >= 0 && tempY < height) && (tempX >= 0 && tempX < length) &&
                        matrix[tempY][tempX] == -2) {
                            matrix[tempY][tempX] = i + 1; // сдвигаем волну
                        }
                    }
                }
            }
        }
        ++i;
    }

    if (matrix[ey][ex] == -2) {
        std::cout << "There is no way" << std::endl;
    }

    // восстановление пути
    i = matrix[ey][ex];
    int x = ex;
    int y = ey;
    matrix[ey][ex] = -3; // путь
    while (i > 0) {
        --i;
        for (size_t j = 0; j < 4; ++j) {
            int tempY = y + dy[j];
            int tempX = x + dx[j];
            if ((tempY >= 0 && tempY < height) && (tempX >= 0 && tempX < length) &&
                matrix[tempY][tempX] == i) {
                x = tempX;
                y = tempY;
                matrix[tempY][tempX] = -3;
            }
        }
    }

    saveInFile(matrix, height, length, sx, sy, ex, ey, filename);
}
