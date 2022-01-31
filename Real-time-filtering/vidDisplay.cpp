#include "vidDisplay.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include "filter.h"

using namespace cv;
using namespace std;

Filter filter;

int main(int argc, char* argv[]) {
    cv::VideoCapture* capdev;
    
    // open the video device
    capdev = new cv::VideoCapture(0);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;
    cv::Mat grayframe;
 
    int option = 0;

    for (;;) {

        *capdev >> frame; // get a new frame from the camera, treat as a stream

        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }
        switch (option) {

            case 1: {
                //GRAY

                cvtColor(frame, grayframe, COLOR_RGBA2GRAY, 0);
                frame = grayframe;
                break;
            }
            case 2: {
                //Custom GRAY

                Mat dst(frame.size(), CV_8UC1);
                filter.greyscale(frame, dst);
                frame = dst;
                break;
            }
            case 3: {
                //Gaus Filter

                Mat dst = frame;
                filter.blur5x5(frame, dst);
                frame = dst;
                break;
            }
            case 4: {

                //Xsobel

                Mat dst(frame.size(), CV_16SC3);
                filter.sobelX3x3(frame, dst);
                convertScaleAbs(dst, frame, 1, 0);
                //frame = dst;
                break;
            }
            case 5: {

                //Ysobel

                Mat dst(frame.size(), CV_16SC3);
                filter.sobelY3x3(frame, dst);
                convertScaleAbs(dst, frame, 1, 0);
                //frame = dst;
                break;
            }
            case 6: {

                //Magnitude
                Mat dst = frame.clone();
                Mat sx(frame.size(), CV_16SC3);
                Mat sy(frame.size(), CV_16SC3); 
                filter.sobelX3x3(frame, sx);
                filter.sobelY3x3(frame, sy);
                filter.magnitude(sx, sy, dst);
                convertScaleAbs(dst, frame, 1, 0);
                break;
            }
            case 7: {

                // BlurQuantize

                Mat dst = frame;
                filter.blurQuantize(frame, dst, 15);
                frame = dst;
                break;
            }

            case 8: {

                // Cartoon

                Mat dst = frame;
                filter.cartoon(frame, dst, 15, 20);
                frame = dst;
                break;
            }
        }

        cv::imshow("Video", frame);

        // see if there is a waiting keystroke
        char key = cv::waitKey(10);

        if (key == 'q') {
            break;
        }
        else if (key == 's') {

            imwrite("screenshot.jpg", frame);
            cout << "Image saved!" << endl;
        }
        else if (key == 'g') {
            option = 1;
        }
        else if (key == 'h') {
            option = 2;
        }
        else if (key == 'b') {
            option = 3;
        }
        else if (key == 'x') {
            option = 4;
        }
        else if (key == 'y') {
            option = 5;
        }
        else if (key == 'm') {
            option = 6;
        }
        else if (key == 'l') {
            option = 7;
        }
        else if (key == 'c') {
            option = 8;
        }

    }

    delete capdev;
    return(0);
}
