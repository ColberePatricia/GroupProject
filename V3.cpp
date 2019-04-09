#include <opencv2\opencv.hpp>   // opencv  library is included
#include <iostream> // standard C++ I/O
#include <cmath>

#pragma warning (disable : 4996)
using namespace cv;  // OpenCV API is in the C++ "cv" namespace
using namespace std; // OpenCV API is in the C++ "std" namespace


Mat images, image, imagegray, threshold_output, backgroud;



int Hough(cv::String path, std::string save_file_name) {

	medianBlur(imagegray, imagegray, 3);

	Mat element = getStructuringElement(0, Size(7,7), Point(3, 3));

	morphologyEx(imagegray, imagegray, 3, element);



	vector<Vec3f> circles;
	HoughCircles(imagegray, circles, HOUGH_GRADIENT, 1, imagegray.rows / 32, 200,20, 10, 30 );

	
	ofstream outfile;
	outfile.open(save_file_name);


	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		
		putText(imagegray, to_string(i+1), center, 1, 1, Scalar(0, 0, 255), 2, 0);

		int radius = cvRound(circles[i][2]);
		
		

		

		
		outfile << path << ":" << " X : " <<  circles[i][0] <<   " Y : " << circles[i][1]   <<  " Diameter " << to_string(radius*2) << endl;
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
	
	vector<cv::String> filepaths;
	glob("Sample2\\*.jpg", filepaths);

	cout << filepaths.size() << std::endl;

	for (int i = 0; i < filepaths.size(); i++)
	{
		imagegray = imread(filepaths[i], 0);
		
		std:string data_text = "text_results\\data" + to_string(i) + ".txt";
		Hough(filepaths[i], data_text);

		waitKey(0);

	}
	return(0);
}