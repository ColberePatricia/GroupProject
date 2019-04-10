#include <opencv2\opencv.hpp>   // opencv  library is included
#include <iostream> // standard C++ I/O
#include <cmath>

void display_img(cv::Mat& img, std::string winname);
void wait_delete();

using namespace cv;  // OpenCV API is in the C++ "cv" namespace
using namespace std; // OpenCV API is in the C++ "std" namespace



int main(int argc, char* argv[])
{


	cv::Ptr<cv::BackgroundSubtractorMOG2> bg = cv::createBackgroundSubtractorMOG2();
	bg->setHistory(46);
	bg->setNMixtures(3);
	bg->setBackgroundRatio(0.7);
	bg->setDetectShadows(false);

	Mat images, imagegray;
	images = imread(argv[1], 0);
	//cout << argv[1] << endl;
	Mat mask ,back;

	for (int i = 0; i < argc; i++)
	{
		imagegray = imread(argv[i], 0);
		
		bg->apply(imagegray, mask);
		

		
	}

	bg->getBackgroundImage(back);

	display_img(back, "back");
	wait_delete();

	return(0);
}

void display_img(cv::Mat& img, std::string winname) {
	cv::namedWindow(winname);
	cv::imshow(winname, img);
}

void wait_delete() {
	cv::waitKey(0);
	cv::destroyAllWindows();
}