#pragma once

#include <random>
#include "GBoard.h"

class Game {
private:
    GBoard board;
    Tetromino* currentTetromino, * nextTetromino;
    int score;
    int _infoSize;
    bool gameOver;
    std::vector<cv::Scalar> colors;
    std::default_random_engine randomEngine;

    void drawTetromino(cv::Mat& image, const Tetromino& tetromino);

public:
    Game(int width, int height, int blockSize, int infoSize);

    Tetromino* createRandomTetromino();
    void update();
    void handleInput(int key);
    void draw(cv::Mat& image);

    bool isGameOver() const;
};

