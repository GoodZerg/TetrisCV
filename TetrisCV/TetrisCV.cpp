#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int main()
{
    cv::Mat img = cv::imread("C:\\Insaid\\GAME_ALL\\Art\\pint\\b469677fa5c5fd9880cf4ca092b4392f.jpg");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);

    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}