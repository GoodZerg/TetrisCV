#include "GBoard.h"

GBoard::GBoard(int w, int h, int bs, cv::Scalar bg) :
    width(w), height(h), blockSize(bs), backgroundColor(bg) {
    grid.resize(height, std::vector<GField>(width));
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            grid[y][x] = GField(cv::Point(x, y), backgroundColor, false);
}

bool GBoard::checkCollision(const Tetromino& tetromino) {
    cv::Point pos = tetromino.getPosition();
    auto shape = tetromino.getShape();

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                int boardX = pos.x + x;
                int boardY = pos.y + y;

                if (boardX < 0 || boardX >= width || boardY >= height)
                    return true;

                if (boardY >= 0 && grid[boardY][boardX].isOccupied())
                    return true;
            }
        }
    }
    return false;
}

void GBoard::placeTetromino(const Tetromino& tetromino) {
    cv::Point pos = tetromino.getPosition();
    auto shape = tetromino.getShape();
    cv::Scalar color = tetromino.getColor();

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                int boardX = pos.x + x;
                int boardY = pos.y + y;
                if (boardY >= 0) {
                    grid[boardY][boardX].setOccupied(true);
                    grid[boardY][boardX].setColor(color);
                }
            }
        }
    }
}

int GBoard::clearLines() {
    int linesCleared = 0;

    for (int y = height - 1; y >= 0; --y) {
        bool lineComplete = true;
        for (int x = 0; x < width; ++x) {
            if (!grid[y][x].isOccupied()) {
                lineComplete = false;
                break;
            }
        }

        if (lineComplete) {
            // move
            for (int ny = y; ny > 0; --ny) {
                for (int x = 0; x < width; ++x) {
                    grid[ny][x] = grid[ny - 1][x];
                }
            }

            // clear top
            for (int x = 0; x < width; ++x) {
                grid[0][x].setOccupied(false);
                grid[0][x].setColor(backgroundColor);
            }

            linesCleared++;
            y++; //check after move
        }
    }

    return linesCleared;
}

void GBoard::draw(cv::Mat& image) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            cv::Point topLeft(x * blockSize, y * blockSize);
            cv::Point bottomRight((x + 1) * blockSize, (y + 1) * blockSize);

            if (grid[y][x].isOccupied()) {
                rectangle(image, topLeft, bottomRight, grid[y][x].getColor(), cv::FILLED);
            }
            else {
                rectangle(image, topLeft, bottomRight, backgroundColor, cv::FILLED);
            }
            rectangle(image, topLeft, bottomRight, cv::Scalar(50, 50, 50), 1);
        }
    }
}

int GBoard::getWidth() const { return width; }

int GBoard::getHeight() const { return height; }

int GBoard::getBlockSize() const { return blockSize; }
