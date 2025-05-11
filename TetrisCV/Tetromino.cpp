#include "Tetromino.h"

Tetromino::Tetromino(int t, cv::Scalar c) : type(t), color(c), position(0, 0) {
    initializeShape();
}

void Tetromino::initializeShape() {
    shape = std::vector<std::vector<bool>>(4, std::vector<bool>(4, false));
    switch (type) {
    case 0: shape[1][0] = shape[1][1] = shape[1][2] = shape[1][3] = true; break;
    case 1: shape[1][1] = shape[1][2] = shape[2][1] = shape[2][2] = true; break;
    case 2: shape[1][1] = shape[2][0] = shape[2][1] = shape[2][2] = true; break;
    case 3: shape[1][0] = shape[1][1] = shape[1][2] = shape[2][2] = true; break;
    case 4: shape[1][0] = shape[1][1] = shape[1][2] = shape[2][0] = true; break;
    case 5: shape[1][1] = shape[1][2] = shape[2][0] = shape[2][1] = true; break;
    case 6: shape[1][0] = shape[1][1] = shape[2][1] = shape[2][2] = true; break;
    }
}

void Tetromino::rotate() {
    std::vector<std::vector<bool>> rotated(4, std::vector<bool>(4, false));

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rotated[i][j] = shape[3 - j][i];

    shape = rotated;
}


cv::Point Tetromino::getPosition() const { return position; }

std::vector<std::vector<bool>> Tetromino::getShape() const { return shape; }

cv::Scalar Tetromino::getColor() const { return color; }

void Tetromino::setPosition(cv::Point pos) { position = pos; }
