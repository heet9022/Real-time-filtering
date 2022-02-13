#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

class Filter
{
public:
	int greyscale(cv::Mat& src, cv::Mat& dst);
	int blur5x5(cv::Mat& src, cv::Mat& dst);
	int sobelX3x3(cv::Mat& src, cv::Mat& dst);
	int sobelY3x3(cv::Mat& src, cv::Mat& dst);
	int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst);
	int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);
	int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold);
	int negative(cv::Mat& src, cv::Mat& dst);
};

