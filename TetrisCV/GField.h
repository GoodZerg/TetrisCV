#pragma once

#include <opencv2/opencv.hpp>

class GField {
private:
    cv::Point position;
    cv::Scalar color;
    bool occupied;

public:
    GField();
    GField(cv::Point pos, cv::Scalar col, bool occ);

    cv::Point getPosition() const;
    cv::Scalar getColor() const;
    bool isOccupied() const;

    void setPosition(cv::Point pos);
    void setColor(cv::Scalar col);
    void setOccupied(bool occ);
};