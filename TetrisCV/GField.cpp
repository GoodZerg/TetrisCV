#include "GField.h"

GField::GField() : position(0, 0), color(cv::Scalar(0, 0, 0)), occupied(false) {}

GField::GField(cv::Point pos, cv::Scalar col, bool occ) : position(pos), color(col), occupied(occ) {}


cv::Point GField::getPosition() const { return position; }

cv::Scalar GField::getColor() const { return color; }

bool GField::isOccupied() const { return occupied; }


void GField::setPosition(cv::Point pos) { position = pos; }

void GField::setColor(cv::Scalar col) { color = col; }

void GField::setOccupied(bool occ) { occupied = occ; }
