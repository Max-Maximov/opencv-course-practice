#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
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

	int heigth = image.rows;
	int width = image.cols;

	if (image.empty())
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);

	waitKey(0);
	Mat grayImage;
	cvtColor(image, grayImage, COLOR_BGR2GRAY);
	
	Mat edges;
	Canny(grayImage, edges, 50, 150);

	
	Mat invEdges;
	bitwise_not(edges, invEdges);
	
	Mat dMap;
	distanceTransform(invEdges, dMap, CV_DIST_L2, 0);
	
	vector<Mat> channels(3);
	split(image, channels);
	for (int c = 0; c < 3; c++)
	{
		Mat intImage;
		integral(channels[c], intImage);
		for (int j = 0; j < heigth; j++)
			for (int i = 0; i < width; i++)
			{
				int masksize = static_cast <int> (dMap.at <float>(j, i) / 5);
				if (!masksize) masksize = 1;
				if (masksize > 5) masksize = 5;
				if (j > masksize && i > masksize && j < heigth - masksize && i < width - masksize)
				{
					channels[c].at<uchar>(j, i) =
						(intImage.at<int>(j + masksize, i + masksize) -
							intImage.at<int>(j - masksize, i + masksize) -
							intImage.at<int>(j + masksize, i - masksize) +
							intImage.at<int>(j - masksize, i - masksize)) / ((masksize * 2) * (masksize * 2));

				}
			}
	}

	Mat res;
	merge(channels, res);
	imshow("Display window", res);

	waitKey(0);
	return 0;
}
