#include <opencv2\opencv.hpp>   // opencv  library is included
#include <iostream> // standard C++ I/O
#include <cmath>

using namespace cv;  // OpenCV API is in the C++ "cv" namespace
using namespace std; // OpenCV API is in the C++ "std" namespace


Mat images, image, imagegray, threshold_output, backgroud;
int Total = 0, ave;



int getBackground(int argc, char** argv)
{

	vector<vector<int>> myVector(images.rows, vector<int>(images.cols)); //an empty matrix with the size of the images

	int i;
	for (i = 1; i < argc; i++)
	{
		images = imread(argv[i], 0);

		for (int x = 0; x < images.rows; x++) {

			for (int y = 0; y < images.cols; y++) {

				myVector[x][y] += images.at<uchar>(x, y); // filling the matrix with values from all the images

			}
		}
	}


	images.copyTo(backgroud);
	for (int x = 0; x < images.rows; x++) {

		for (int y = 0; y < images.cols; y++)
		{
			
			backgroud.at<uchar>(x, y) = myVector[x][y] / i; // calculating the mean and creating a mean image(background)
		}
	}


	for (int x = 0; x < images.rows; x++) {
		{
			for (int y = 0; y < images.cols; y++)
			{
				Total += backgroud.at<uchar>(x, y); // calculating the total 
			} 
			ave = Total / (images.rows * images.cols); // getting the ave by dividing the total over the size of the images
		}
	}

	return 0;
}



int noiseremovel(int argc, char** argv, int i)
{

	for (int x = 0; x < imagegray.rows; x++) {

		for (int y = 0; y < imagegray.cols; y++)
		{
			imagegray.at<uchar>(x, y) = imagegray.at<uchar>(x, y) - backgroud.at<uchar>(x, y) + ave; 
		}
	}

	return 0;
}


int countour(int argc, char** argv) {




	threshold(imagegray, threshold_output, 105, 255, THRESH_BINARY);
	Canny(threshold_output, threshold_output, 50, 240, 7);


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		//boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle((Mat)contours_poly[i], center[i], radius[i]);
	}


	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(0, 0, 255);
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);

	return 0;
}


int Hough(int argc, char** argv) {

	GaussianBlur(imagegray, imagegray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	HoughCircles(imagegray, circles, HOUGH_GRADIENT, // detection method..
		1, // The inverse ratio .
		imagegray.rows / 4, // Minimum distance between detected centers. 
		100, // canny high threshold
		20, // minimum number of votes
		10, 200 // (min_radius & max_radius) to detect circles
	);
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


	imshow("circles", imagegray);
	//waitKey(0);

	return 0;
}

int main(int argc, char** argv)
{

	
	images = imread(argv[1], 0);  // loading all the images in grayscale
	getBackground(argc,argv);     // calculating the mean and ave of the images

	for (int i = 1; i < argc; i++)
	{
		imagegray = imread(argv[i], 0); //loading the image one by one in grayscale
		noiseremovel(argc, argv, i);    // using the extracted information from getBackground to enhance the image

		Hough(argc, argv);              // detecting droplet using hough transform
		countour(argc, argv);           // detecting droplet using findContours


		waitKey(0);

	}
	return(0);
}