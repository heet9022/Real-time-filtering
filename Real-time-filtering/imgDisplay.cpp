
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

#include "filter.h"

using namespace cv;
using namespace std;

Filter filter;
Mat output;

int imgDisplay()
{
	
		std::string image_path = samples::findFile("taj mahal.jpg");
		Mat img = imread(image_path, IMREAD_COLOR);
		cout << "Width : " << img.size().width << endl;
		cout << "Height: " << img.size().height << endl;
		imshow("Display window", img);
		int key = 0;
        int option = 0;
        string name;
		while (key != 'q')
		{
			key = waitKey(0);
            if (key == 's') {

                cout << "Name the image: "; 
                getline(cin, name);
                imwrite(name+".jpg", output);
                cout << name << " saved!" << endl;
            }
            else if (key == 'g') {

                Mat grayframe;
                cvtColor(img, grayframe, COLOR_RGBA2GRAY, 0);
                output = grayframe;
            }
            else if (key == 'h') {
                Mat dst(img.size(), CV_8UC1);
                filter.greyscale(img, dst);
                output = dst;
                
            }
            else if (key == 'b') {
                Mat dst(img.size(), CV_8UC3);
                filter.blur5x5(img, dst);
                output = dst;
            }
            else if (key == 'x') {
                Mat dst(img.size(), CV_16SC3);
                filter.sobelX3x3(img, dst);
                convertScaleAbs(dst, output, 1, 0);
            }
            else if (key == 'y') {
                Mat dst(img.size(), CV_16SC3);
                filter.sobelY3x3(img, dst);
                convertScaleAbs(dst, output, 1, 0);

            }
            else if (key == 'm') {
                Mat dst(img.size(), CV_16UC3);
                Mat sx(img.size(), CV_16UC3);
                Mat sy(img.size(), CV_16UC3);
                filter.sobelX3x3(img, sx);
                filter.sobelY3x3(img, sy);
                filter.magnitude(sx, sy, dst);
                convertScaleAbs(dst, output, 1, 0);

            }
            else if (key == 'l') {
                Mat dst(img.size(), CV_8UC3);
                filter.blurQuantize(img, dst, 15);
                output = dst;
            }
            else if (key == 'c') {
                Mat dst(img.size(), CV_8UC3);
                filter.cartoon(img, dst, 18, 25);
                output = dst;
            }

            imshow("Display window", output);

            }
	
	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
