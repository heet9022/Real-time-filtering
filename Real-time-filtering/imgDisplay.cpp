
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int imgDisplay()
{
	
		std::string image_path = samples::findFile("taj mahal.jpg");
		Mat img = imread(image_path, IMREAD_COLOR);
		cout << "Width : " << img.size().width << endl;
		cout << "Height: " << img.size().height << endl;
		imshow("Display window", img);
		int a = 0;
		while (a != 'q')
		{
			a = waitKey(0);
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
