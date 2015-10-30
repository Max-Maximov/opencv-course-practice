#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string imgname;
	if (argc != 2)
	{
		imgname = "test.jpg";
	}
	else
		imgname = argv[1];

	Mat image;
	image = imread(imgname, IMREAD_COLOR);

	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Original image", WINDOW_AUTOSIZE);
	imshow("Original image", image);

	waitKey(0);
	Mat blurImage;
	blur(image, blurImage, Size(3, 3));
	
	namedWindow("Blur", WINDOW_AUTOSIZE);
	imshow("Blur", blurImage);
	waitKey(0);
	
	Mat morphImage;
	Mat kernel = getStructuringElement(MORPH_CROSS, Size(5, 5));
	morphologyEx(image, morphImage, MORPH_OPEN, kernel);
	namedWindow("Morphology", WINDOW_AUTOSIZE);
	imshow("Morphology", morphImage);
	waitKey(0);
		
	vector<Mat> channels(3), eqChannels(3);
	split(image, channels);
	for (int c = 0; c < 3; c++)
	{
		equalizeHist(channels[c], eqChannels[c]);
	}
	
	Mat eqHistImage;
	merge(eqChannels, eqHistImage);
	
	namedWindow("Equalized Histograms", WINDOW_AUTOSIZE);
	imshow("Equalized Histograms", image);

	waitKey(0);
	return 0;
}