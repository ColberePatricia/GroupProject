#include <sstream>
#include <string>
#include <iostream>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

//Function to convert an integer number to a string.
String intToString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}

int main(int argc, const char **argv)
{
	//Variables to write the radius and center position on the screen.
	string radiusStr;
	string radiusmmStr;
	string xcenterStr;
	string ycenterStr;
	int Rvalue;
	int Rmmvalue;
	int Xvalue;
	int Yvalue;

	// Open the original colored image and convert to a grayscaled image
	Mat coloredimage;
	Mat grayimage;

	//vector to store the center value ( x and y coordinates ) and the radius of each detected circle
	vector<Vec3f> circles;

	//Open and resize the colored image.
	coloredimage = imread(argv[1], 1);
	resize(coloredimage, coloredimage, Size(640, 480));
	imshow("Original Image", coloredimage);

	//convert colored image to gray scale
	cvtColor(coloredimage, grayimage, CV_BGR2GRAY);

	// Apply blur to Reduce the noise to avoid false detections.
	GaussianBlur(grayimage, grayimage, Size(9, 9), 2, 2);

	// Apply the Hough Transform to find the circles (use the gray scale image as input)
	//Arguments: 1: input image( grayscaled ) . 2: vector to tore the circle parameters .3: detection method,
	// 4: inverse ratio of resolution . 5 minimum distance between detected centers. 6: upper threshold for the internal canny edge detector
	//7: threshold for center detection . 8: Minimum radius to be detected (0=unknown) . 9: maximum radius to be detected

	HoughCircles(grayimage, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0);

	// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		//Get the informations from the circles vector generated by the function HoughCircles. 
		//X center coordinate is circles[i][0]  , Y center coordinate is circles[i][1] , radius is circles[i][2] 
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		//Store these values into variables to be converted into string and displayed on the image
		Rvalue = radius;
		Rmmvalue = Rvalue * 0.2; // Scale factor is 0.2 for mikrometer
		Xvalue = cvRound(circles[i][0]);
		Yvalue = cvRound(circles[i][1]);

		//DRAWING THE CENTER OF THE CIRCLE
		//Use the circle function to draw the center of the detected circle
		//Use the center coordinate and a radius of 3 to just draw a point on the center.
		circle(coloredimage, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		//DRAWING THE CIRCLE CONTOUR.
		//Use the circle function to draw the detected circle on the image
		//Use the center coordinate and the radius coordinate detected by the HoughCircles function
		circle(coloredimage, center, radius, Scalar(0, 0, 255), 3, 8, 0);

		//Convert the integer Center point and radius values to string
		radiusStr = intToString(Rvalue);
		radiusmmStr = intToString(Rmmvalue);
		xcenterStr = intToString(Xvalue);
		ycenterStr = intToString(Yvalue);

		//Display on the colored image the center and radius values.
		putText(coloredimage, "(" + xcenterStr + "," + ycenterStr + ")", Point(Xvalue, Yvalue - 20), 1, 1, Scalar(0, 255, 0), 2);

		cout << "radius in mikrometer:" << radiusmmStr << "    radius in pixel:" << radiusStr << "    Column:" << xcenterStr << "    Row:" << ycenterStr << endl;
	}

	// Show your results
	namedWindow("Circle Detector", CV_WINDOW_AUTOSIZE);
	imshow("Circle Detector", coloredimage);

	waitKey(0);
	return 0;
}

