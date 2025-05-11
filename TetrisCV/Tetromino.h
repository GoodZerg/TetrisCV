#pragma once

#include <opencv2/opencv.hpp>
#include <vector>


class Tetromino {
private:
    std::vector<std::vector<bool>> shape;
    cv::Scalar color;
    cv::Point position;
    int type;

public:
    Tetromino(int t, cv::Scalar c);

    void initializeShape();
    void rotate();

    cv::Point getPosition() const;
    std::vector<std::vector<bool>> getShape() const;
    cv::Scalar getColor() const;
    
    void setPosition(cv::Point pos);
};
