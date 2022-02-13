#include "filter.h"

int Filter::greyscale(cv::Mat& src, cv::Mat& dst) {

    for (int x = 0; x < src.rows; x++) {
        for (int y = 0; y < src.cols; y++) {

            Vec3b intensity = src.at<Vec3b>(x, y);
            int gray_intensity;
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];
            gray_intensity = (int)(blue * 0.0722 + green * 0.7152 + red * 0.2126);
            dst.at<uchar>(x, y) = gray_intensity;
        }
    }
	return 0;
}

int Filter::blur5x5(cv::Mat& src, cv::Mat& dst) {

    Mat temp(src.size(), CV_8UC3);
    //cout << "depth: " << src.depth() <<endl;
    
    int blur[] = {1, 2, 4, 2, 1};
    int sumB = 0, sumG = 0, sumR = 0;


    for (int x = 2; x < src.rows-2; x++) {
        for (int y = 2; y < src.cols-2; y++) {
            
            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int j = y-2; j <= y+2; j++) {

                Vec3b intensity = src.at<Vec3b>(x, j);
                int filter_point = blur[j - (y-2)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            temp.at<Vec3b>(x, y)[0] = (int) sumB / 10;
            temp.at<Vec3b>(x, y)[1] = (int) sumG / 10;
            temp.at<Vec3b>(x, y)[2] = (int) sumR / 10;

        }
    }

    for (int x = 2; x < temp.rows-2; x++) {
        for (int y = 2; y < temp.cols-2; y++) {

            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int i = x - 2; i <= x + 2; i++) {

                Vec3b intensity = temp.at<Vec3b>(i, y);
                int filter_point = blur[i - (x - 2)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            dst.at<Vec3b>(x, y)[0] = (int) sumB / 10;
            dst.at<Vec3b>(x, y)[1] = (int) sumG / 10;
            dst.at<Vec3b>(x, y)[2] = (int) sumR / 10;

        }
    }

    return 0;
}

int Filter::sobelX3x3(cv::Mat& src, cv::Mat& dst) {

    int sobelX_hor[] = { -1, 0, 1 }; // 1x3
    int sobelX_ver[] = { 1,
                         2,
                         1 }; // 3x1

    int sumB = 0, sumG = 0, sumR = 0;

    Mat temp(src.size(), CV_16SC3);

    for (int x = 1; x < src.rows - 1; x++) {
        for (int y = 1; y < src.cols - 1; y++) {

            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int i = x - 1; i <= x + 1; i++) {

                Vec3b intensity = src.at<Vec3b>(i, y);
                int filter_point = sobelX_hor[i - (x - 1)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            temp.at<Vec3s>(x, y)[0] = sumB;
            temp.at<Vec3s>(x, y)[1] = sumG;
            temp.at<Vec3s>(x, y)[2] = sumR;

        }
    }

    for (int x = 1; x < temp.rows - 1; x++) {
        for (int y = 1; y < temp.cols - 1; y++) {

            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int j = y - 1; j <= y + 1; j++) {

                Vec3s intensity = temp.at<Vec3s>(x, j);
                int filter_point = sobelX_ver[j - (y - 1)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            dst.at<Vec3s>(x, y)[0] = abs(sumB / 4);
            dst.at<Vec3s>(x, y)[1] = abs(sumG / 4);
            dst.at<Vec3s>(x, y)[2] = abs(sumR / 4);

        }
    }

    return 0;
}

int Filter::sobelY3x3(cv::Mat& src, cv::Mat& dst) {

    int sobelY_hor[] = { 1, 2, 1 }; // 1x3
    int sobelY_ver[] = { -1, 
                          0, 
                          1 }; // 3x1

    int sumB = 0, sumG = 0, sumR = 0;
    
    Mat temp(src.size(), CV_16SC3);
    for (int x = 1; x < src.rows - 1; x++) {
        for (int y = 1; y < src.cols - 1; y++) {

            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int i = x - 1; i <= x + 1; i++) {

                Vec3b intensity = src.at<Vec3b>(i, y);
                int filter_point = sobelY_hor[i - (x - 1)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            temp.at<Vec3s>(x, y)[0] = sumB/4;
            temp.at<Vec3s>(x, y)[1] = sumG/4;
            temp.at<Vec3s>(x, y)[2] = sumR/4;

        }
    }

    for (int x = 1; x < temp.rows-1; x++) {
        for (int y = 1; y < temp.cols - 1; y++) {

            sumB = 0;
            sumG = 0;
            sumR = 0;

            for (int j = y - 1; j <= y + 1; j++) {

                Vec3s intensity = temp.at<Vec3s>(x, j);
                int filter_point = sobelY_ver[j - (y - 1)];
                sumB += intensity[0] * filter_point;
                sumG += intensity[1] * filter_point;
                sumR += intensity[2] * filter_point;
            }

            dst.at<Vec3s>(x, y)[0] = abs(sumB);
            dst.at<Vec3s>(x, y)[1] = abs(sumG);
            dst.at<Vec3s>(x, y)[2] = abs(sumR);

        }
    }
 
    return 0;
}

int Filter::magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst) {

    //dst.convertTo(dst, CV_16UC3);

    for (int i = 0; i < sx.rows; i++) {
        for (int j = 0; j < sx.cols; j++) {

            Vec3s x = sx.at<Vec3s>(i, j);
            Vec3s y = sy.at<Vec3s>(i, j);

            for (int c = 0; c < sx.channels(); c++) {
                dst.at<Vec3s>(i, j)[c] = sqrtf((x[c] * x[c]) + (y[c] * y[c]));
            }
        }
    }
    return 0;
}

int Filter::blurQuantize(cv::Mat& src, cv::Mat& dst, int levels) {

    Mat blur(src.size(), CV_8UC3);
    blur5x5(src, blur);
    int b = 255 / levels;
    int xt = 0, xf = 0;

    for (int i = 0; i < blur.rows; i++) {
        for (int j = 0; j < blur.cols; j++) {

            Vec3b intensity = blur.at<Vec3b>(i, j);

            for (int c = 0; c < blur.channels(); c++) {

                xt = intensity[c] / b;
                xf = xt * b;
                dst.at<Vec3b>(i, j)[c] = xf;
            }
        }
    }

    return 0;

}

int Filter::cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold) {

    Mat mag(src.size(), CV_16UC3);
    Mat sx(src.size(), CV_16UC3);
    Mat sy(src.size(), CV_16UC3);
    sobelX3x3(src, sx);
    sobelY3x3(src, sy);
    magnitude(sx, sy, mag);
    blurQuantize(src, dst, levels);

    for (int i = 0; i < mag.rows; i++) {
        for (int j = 0; j < mag.cols; j++) {

            Vec3b intensity = dst.at<Vec3b>(i, j);
            Vec3s magnitude = mag.at<Vec3s>(i, j);

            for (int c = 0; c < dst.channels(); c++) {

                if (magnitude[c] > magThreshold) {
                    dst.at<Vec3b>(i, j)[c] = 0;
                }
            }
        }
    }
    return 0;

}

int Filter::negative(cv::Mat& src, cv::Mat& dst) {

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {

            Vec3b intensity = src.at<Vec3b>(i, j);

            for (int c = 0; c < src.channels(); c++) {
                
                dst.at<Vec3b>(i, j)[c] = 255 - intensity[c];
              
            }
        }
    }
    return 0;
}

//int Filter::sobelX3x3(cv::Mat& src, cv::Mat& dst) {
//
//    int sobelx[3][3] = {-1, 0, 1,
//                        -2, 0, 2,
//                        -1, 0, 1 };
//    int sumB = 0, sumG = 0, sumR = 0;
//    //dst = src.clone();
//    //dst(src.rows, src.cols, CV_16SC3);
//    for (int x = 1; x < src.rows - 1; x++) {
//        for (int y = 1; y < src.cols - 1; y++) {
//
//            sumB = 0;
//            sumG = 0;
//            sumR = 0;
//
//            for (int i = x - 1; i <= x + 1; i++) {
//
//                for (int j = y - 1; j <= y + 1; j++) {
//
//                    Vec3b intensity = src.at<Vec3b>(i, j);
//                    int filter_point = sobelx[i - (x-1)][j - (y-1)];
//                    sumB += intensity[0] * filter_point;
//                    sumG += intensity[1] * filter_point;
//                    sumR += intensity[2] * filter_point;
//                }
//            }
//            //cout << dst << endl;
//            //cout << dst.elemSize1();
//            dst.at<Vec3s>(x, y)[0] = sumB / 4;
//            dst.at<Vec3s>(x, y)[1] = sumG / 4;
//            dst.at<Vec3s>(x, y)[2] = sumR / 4;
//            //cout << dst << endl;
//            
//
//        }
//    }
//    Mat temp = dst.clone();
//    convertScaleAbs(temp, dst, 1, 0);
//    return 0;
//
//}