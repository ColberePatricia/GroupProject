#include <opencv2\opencv.hpp>   // opencv  library is included
#include <iostream> // standard C++ I/O
#include <cmath>

using namespace cv;  // OpenCV API is in the C++ "cv" namespace
using namespace std; // OpenCV API is in the C++ "std" namespace


Mat images, image, imagegray, threshold_output, backgroud;
int Total = 0, ave;



int Hough(int argc, char** argv) {

	medianBlur(imagegray, imagegray, 3);



	Mat eroded, dialated;
	Mat element = getStructuringElement(0, Size(7,7), Point(3, 3));


	erode(imagegray, eroded, element);
	dilate(imagegray, dialated, element);
	morphologyEx(imagegray, imagegray, 3, element);



	vector<Vec3f> circles;
	HoughCircles(imagegray, circles, HOUGH_GRADIENT, 1, imagegray.rows / 16, 100,20, 10, 60 );

	
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		stringstream ss;
		ss << i + 1;
		putText(imagegray, ss.str(), center, 1, 1, Scalar(0, 0, 255), 2, 0);
		int radius = cvRound(circles[i][2]);
		// draw the circle center
		circle(imagegray, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// draw the circle outline
		circle(imagegray, center, radius, Scalar(0, 0, 255), 3, 8, 0);

	}
	imshow("Hough Circles", imagegray);





	return 0;
}

int main(int argc, char** argv)
{


	for (int i = 1; i < argc; i++)
	{
		imagegray = imread(argv[i], 0);

		Hough(argc, argv);

		waitKey(0);

	}
	return(0);
}