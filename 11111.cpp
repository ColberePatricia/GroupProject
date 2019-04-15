medianBlur(imagegray, imagegray, 3); // removing the noise salt&pepper

	Mat element = getStructuringElement(0, Size(7,7), Point(3, 3)); // The kernel used

	morphologyEx(imagegray, imagegray, 3, element); // Morphlogy Operation (Closing)



	vector<Vec3f> circles;
	HoughCircles(imagegray, // Input image 
							circles, HOUGH_GRADIENT, // Define the detection method.
							1,  // The inverse ratio of resolution.
							imagegray.rows / 32, // Minimum distance between detected centers.
							200, // canny high threshold
							20, // minimum number of votes
							10, // min_radiusto detect circles
							30 // max_radiusto detect circles
							);