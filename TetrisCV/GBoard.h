#pragma once

#include "GField.h"
#include "Tetromino.h"

class GBoard {
private:
    int width, height, blockSize;
    std::vector<std::vector<GField>> grid;
    cv::Scalar backgroundColor;

public:
    GBoard(int w, int h, int bs, cv::Scalar bg);

    bool checkCollision(const Tetromino& tetromino);
    void placeTetromino(const Tetromino& tetromino);

    int clearLines();
    void draw(cv::Mat& image);

    int getWidth() const;
    int getHeight() const;
    int getBlockSize() const;
};