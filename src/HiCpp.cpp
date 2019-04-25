//============================================================================
// Name        : HiCpp.cpp
// Author      : D. Miers
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#if 0
#include <iostream>
#include <mutex>
#include "mingw.mutex.h"
#include <thread>
#include "mingw.thread.h"


void thread_function()
{
	for( int i=0; i<10000; i++ );

	std::cout << "thread function executing\n";
}

int main()
{
	std::thread threadObj( thread_function );

	for( int i=0; i<10000; i++ );

	threadObj.join();

	std::cout << "Exit of main function\n"; // prints Crunch My Data
	return 0;
}
#endif

#if 1
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}
int main(int argc, char** argv)
{
    cv::CommandLineParser parser(argc, argv,
        "{help h ||}{@image|../data/board.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    string filename = parser.get<string>("@image");
    if (filename.empty())
    {
        help();
        cout << "no image_name provided" << endl;
        return -1;
    }
    Mat img = imread(filename, 0);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }
    Mat cimg;
    medianBlur(img, img, 5);
    cvtColor(img, cimg, COLOR_GRAY2BGR);
    vector<Vec3f> circles;
    HoughCircles(img, circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( cimg, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( cimg, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }
    imshow("detected circles", cimg);
    waitKey();
    return 0;
}
#endif
