#include "stdafx.h"
#include "common.h"
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>
using namespace std;
using namespace cv;


void testOpenImage()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		imshow("image", src);
		waitKey();
	}
}

void testOpenImagesFld()
{
	char folderName[MAX_PATH];
	if (openFolderDlg(folderName) == 0)
		return;
	char fname[MAX_PATH];
	FileGetter fg(folderName, "bmp");
	while (fg.getNextAbsFile(fname))
	{
		Mat src;
		src = imread(fname);
		imshow(fg.getFoundFileName(), src);
		if (waitKey() == 27) //ESC pressed
			break;
	}
}

void testImageOpenAndSave()
{
	Mat src, dst;

	src = imread("Images/Lena_24bits.bmp", CV_LOAD_IMAGE_COLOR);	// Read the image

	if (!src.data)	// Check for invalid input
	{
		printf("Could not open or find the image\n");
		return;
	}

	// Get the image resolution
	Size src_size = Size(src.cols, src.rows);

	// Display window
	const char* WIN_SRC = "Src"; //window for the source image
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Dst"; //window for the destination (processed) image
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, src_size.width + 10, 0);

	cvtColor(src, dst, CV_BGR2GRAY); //converts the source image to a grayscale one

	imwrite("Images/Lena_24bits_gray.bmp", dst); //writes the destination to file

	imshow(WIN_SRC, src);
	imshow(WIN_DST, dst);

	printf("Press any key to continue ...\n");
	waitKey(0);
}

void testNegativeImage()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		double t = (double)getTickCount(); // Get the current time [s]

		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = Mat(height, width, CV_8UC1);
		// Asa se acceseaaza pixelii individuali pt. o imagine cu 8 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				uchar val = src.at<uchar>(i, j);
				uchar neg = 255 - val;
				dst.at<uchar>(i, j) = neg;
			}
		}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image", src);
		imshow("negative image", dst);
		waitKey();
	}
}

void testParcurgereSimplaDiblookStyle()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = src.clone();

		double t = (double)getTickCount(); // Get the current time [s]

		// the fastest approach using the “diblook style”
		uchar *lpSrc = src.data;
		uchar *lpDst = dst.data;
		int w = (int)src.step; // no dword alignment is done !!!
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				uchar val = lpSrc[i*w + j];
				lpDst[i*w + j] = 255 - val;
			}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image", src);
		imshow("negative image", dst);
		waitKey();
	}
}

void testColor2Gray()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname);

		int height = src.rows;
		int width = src.cols;

		Mat dst = Mat(height, width, CV_8UC1);

		// Asa se acceseaaza pixelii individuali pt. o imagine RGB 24 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Vec3b v3 = src.at<Vec3b>(i, j);
				uchar b = v3[0];
				uchar g = v3[1];
				uchar r = v3[2];
				dst.at<uchar>(i, j) = (r + g + b) / 3;
			}
		}

		imshow("input image", src);
		imshow("gray image", dst);
		waitKey();
	}
}

void testBGR2HSV()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname);
		int height = src.rows;
		int width = src.cols;

		// Componentele d eculoare ale modelului HSV
		Mat H = Mat(height, width, CV_8UC1);
		Mat S = Mat(height, width, CV_8UC1);
		Mat V = Mat(height, width, CV_8UC1);

		// definire pointeri la matricele (8 biti/pixeli) folosite la afisarea componentelor individuale H,S,V
		uchar* lpH = H.data;
		uchar* lpS = S.data;
		uchar* lpV = V.data;

		Mat hsvImg;
		cvtColor(src, hsvImg, CV_BGR2HSV);

		// definire pointer la matricea (24 biti/pixeli) a imaginii HSV
		uchar* hsvDataPtr = hsvImg.data;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int hi = i * width * 3 + j * 3;
				int gi = i * width + j;

				lpH[gi] = hsvDataPtr[hi] * 510 / 360;		// lpH = 0 .. 255
				lpS[gi] = hsvDataPtr[hi + 1];			// lpS = 0 .. 255
				lpV[gi] = hsvDataPtr[hi + 2];			// lpV = 0 .. 255
			}
		}

		imshow("input image", src);
		imshow("H", H);
		imshow("S", S);
		imshow("V", V);

		waitKey();
	}
}

void testResize()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		Mat dst1, dst2;
		//without interpolation
		resizeImg(src, dst1, 320, false);
		//with interpolation
		resizeImg(src, dst2, 320, true);
		imshow("input image", src);
		imshow("resized image (without interpolation)", dst1);
		imshow("resized image (with interpolation)", dst2);
		waitKey();
	}
}

void testCanny()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src, dst, gauss;
		src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		double k = 0.4;
		int pH = 50;
		int pL = (int)k*pH;
		GaussianBlur(src, gauss, Size(5, 5), 0.8, 0.8);
		Canny(gauss, dst, pL, pH, 3);
		imshow("input image", src);
		imshow("canny", dst);
		waitKey();
	}
}

void testVideoSequence()
{
	VideoCapture cap("Videos/rubic.avi"); // off-line video from file
	//VideoCapture cap(0);	// live video from web cam
	if (!cap.isOpened()) {
		printf("Cannot open video capture device.\n");
		waitKey(0);
		return;
	}

	Mat edges;
	Mat frame;
	char c;

	while (cap.read(frame))
	{
		Mat grayFrame;
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		Canny(grayFrame, edges, 40, 100, 3);
		imshow("source", frame);
		imshow("gray", grayFrame);
		imshow("edges", edges);
		c = cvWaitKey(0);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished\n");
			break;  //ESC pressed
		};
	}
}


void testSnap()
{
	VideoCapture cap(0); // open the deafult camera (i.e. the built in web cam)
	if (!cap.isOpened()) // openenig the video device failed
	{
		printf("Cannot open video capture device.\n");
		return;
	}

	Mat frame;
	char numberStr[256];
	char fileName[256];

	// video resolution
	Size capS = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	// Display window
	const char* WIN_SRC = "Src"; //window for the source frame
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Snapped"; //window for showing the snapped frame
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, capS.width + 10, 0);

	char c;
	int frameNum = -1;
	int frameCount = 0;

	for (;;)
	{
		cap >> frame; // get a new frame from camera
		if (frame.empty())
		{
			printf("End of the video file\n");
			break;
		}

		++frameNum;

		imshow(WIN_SRC, frame);

		c = cvWaitKey(10);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished");
			break;  //ESC pressed
		}
		if (c == 115) { //'s' pressed - snapp the image to a file
			frameCount++;
			fileName[0] = NULL;
			sprintf(numberStr, "%d", frameCount);
			strcat(fileName, "Images/A");
			strcat(fileName, numberStr);
			strcat(fileName, ".bmp");
			bool bSuccess = imwrite(fileName, frame);
			if (!bSuccess)
			{
				printf("Error writing the snapped image\n");
			}
			else
				imshow(WIN_DST, frame);
		}
	}

}

void MyCallBackFunc(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n",
			x, y,
			(int)(*src).at<Vec3b>(y, x)[2],
			(int)(*src).at<Vec3b>(y, x)[1],
			(int)(*src).at<Vec3b>(y, x)[0]);
	}
}

void testMouseClick()
{
	Mat src;
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname);
		//Create a window
		namedWindow("My Window", 1);

		//set the callback function for any mouse event
		setMouseCallback("My Window", MyCallBackFunc, &src);

		//show the image
		imshow("My Window", src);

		// Wait until user press some key
		waitKey(0);
	}
}

/* Histogram display function - display a histogram using bars (simlilar to L3 / PI)
Input:
name - destination (output) window name
hist - pointer to the vector containing the histogram values
hist_cols - no. of bins (elements) in the histogram = histogram image width
hist_height - height of the histogram image
Call example:
showHistogram ("MyHist", hist_dir, 255, 200);
*/
void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height)
{
	Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

	//computes histogram maximum
	int max_hist = 0;
	for (int i = 0; i < hist_cols; i++)
		if (hist[i] > max_hist)
			max_hist = hist[i];
	double scale = 1.0;
	scale = (double)hist_height / max_hist;
	int baseline = hist_height - 1;

	for (int x = 0; x < hist_cols; x++) {
		Point p1 = Point(x, baseline);
		Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
		line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins colored in magenta
	}

	imshow(name, imgHist);
}

void LeastMeanSquare()
{
	for (int ds = 0; ds < 6; ds++)
	{
		char filename[100] = "PointsLeastSquares/points";
		filename[strlen(filename)] = ds + 48;
		strcat(filename, ".txt");
		cout << filename << endl;
		ifstream f(filename);
		int n;
		Point2f points[1000];
		float minx = 10000000, miny = 10000000, maxx = 0, maxy = 0;
		f >> n;
		for (int i = 0; i < n; i++)
		{
			f >> points[i].x >> points[i].y;
			if (points[i].x < minx)
				minx = points[i].x;
			if (points[i].y < miny)
				miny = points[i].y;
			if (points[i].x > maxx)
				maxx = points[i].x;
			if (points[i].y > maxy)
				maxy = points[i].y;
		}
		if (minx < 0 || miny < 0)
			for (int i = 0; i < n; i++)
			{
				if (minx < 0)
					points[i].x -= minx;
				if (miny < 0)
					points[i].x -= miny;
				if (points[i].x > maxx)
					maxx = points[i].x;
				if (points[i].y > maxy)
					maxy = points[i].y;
			}
		Mat img(max((int)maxx + 1, (int)maxy + 1), max((int)maxx + 1, (int)maxy + 1), CV_8UC3, CV_RGB(255, 255, 255));
		for (int i = 0; i < n; i++)
			drawMarker(img, cv::Point(points[i].x, points[i].y), CV_RGB(0, 0, 0), MARKER_CROSS, 4, 1, 8);

		float t0 = 0, t1 = 0, s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;
		for (int i = 0; i < n; i++)
		{
			s1 += points[i].x*points[i].y;
			s2 += points[i].x;
			s3 += points[i].y;
			s4 += points[i].x*points[i].x;
			s5 += points[i].y*points[i].y - points[i].x*points[i].x;
		}
		t1 = (n*s1 - s2 * s3) / (n*s4 - s2 * s2);
		t0 = (s3 - t1 * s2) / n;
		cout << t0 << ' ' << t1 << '\n';

		float val1 = t0;
		float val2 = t0 + t1 * img.cols;
		line(img, Point(0, val1), Point(img.cols, val2), CV_RGB(255, 0, 0), 3, 8, 0);

		float beta = -1 * (atan2(2 * s1 - (2 * (s2*s3) / n), s5 + s2 * s2 / n - s3 * s3 / n)) / 2;
		float p = (cos(beta)*s2 + sin(beta)*s3) / n;

		cout << beta << ' ' << p;
		Point one(0, p / sin(beta));
		Point two(img.cols, ((p - img.cols * cos(beta)) / sin(beta)));
		line(img, one, two, CV_RGB(0, 0, 255), 1, 8, 0);


		imshow(filename, img);
		waitKey(0);
		f.close();
	}
}

void RANSACLineFitting()
{
	vector<Point> pointsInImage;
	float t = 10, p = 0.99, q = 0.8, s = 2, N;
	Mat src;

	char fname[MAX_PATH];
	openFileDlg(fname);
	src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			if (src.at<uchar>(i, j) == 0)
				pointsInImage.push_back(Point(j, i));

	N = log(1 - p) / log(1 - pow(q, s));
	for (int tr = 0; tr <= 5; tr++)
	{
		int bestScore = 0;
		Point bestp1, bestp2;
		for (int i = 0; i < ceil(N); i++)
		{
			int first = rand() % pointsInImage.size();
			int second = rand() % pointsInImage.size();
			while (first == second)
				second = rand() % pointsInImage.size();
			Point point1 = pointsInImage.at(first);
			Point point2 = pointsInImage.at(second);
			float a = point1.y - point2.y;
			float b = point2.x - point1.x;
			float c = point1.x*point2.y - point2.x * point1.y;

			int score = 0;
			for (int j = 0; j < pointsInImage.size(); j++)
			{
				Point current = pointsInImage.at(j);
				float dist = fabs(a*current.x + b * current.y + c) / sqrt(a*a + b * b);
				if (dist < t)
					score++;
			}
			if (score > bestScore)
			{
				bestScore = score;
				bestp1 = point1;
				bestp2 = point2;
			}

			if (bestScore > q * pointsInImage.size())
				break;
		}

		line(src, bestp1, bestp2, 1, 1, 8, 0);
		imshow("Points and line", src);
		waitKey(0);
	}
}

void Hough()
{
	struct peak {
		int theta, ro, hval;
		bool operator < (const peak& o) const {
			return hval > o.hval;
		}
	};

	vector<Point> pointsInImage;
	vector<peak> Peaks[8];
	Mat src, H;

	char fname[MAX_PATH];
	openFileDlg(fname);
	src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			if (src.at<uchar>(i, j) == 255)
				pointsInImage.push_back(Point(j, i));

	const float roMin = 0, roMax = sqrt(src.rows*src.rows + src.cols*src.cols), tethaMin = 0, tethaMax = 360;

	const int deltaRo = 1;
	const int deltaTetha = 1;

	H = Mat(360, (int)roMax + 1, CV_32SC1);

	for (int i = 0; i < H.rows; i++)
		for (int j = 0; j < H.cols; j++)
			H.at<int>(i, j) = 0;

	for (int i = 0; i < pointsInImage.size(); i++)
	{
		Point pct = pointsInImage.at(i);
		int tetha;
		for (tetha = 0; tetha < 360; tetha++)
		{
			int ro = pct.x*cos(tetha * CV_PI / 180) + pct.y*sin(tetha * CV_PI / 180);
			if (ro < roMax && ro > 0)
				H.at<int>(tetha, ro)++;
		}
	}

	int maxHough = 0;

	for (int i = 0; i < H.rows; i++)
		for (int j = 0; j < H.cols; j++)
			if (H.at<int>(i, j) > maxHough)
				maxHough = H.at<int>(i, j);

	Mat houghImg;
	H.convertTo(houghImg, CV_8UC1, 255.f / maxHough);
	imshow("Hough img", houghImg);
	cout << "decide size of search area: 3,5,7: ";
	int sizeOfArea;
	cin >> sizeOfArea;
	for (int i = 0; i < H.rows; i++)
		for (int j = 0; j < H.cols; j++)
		{
			Point pMax(-1, -1);
			int vMax = 0;
			for (int k = i - sizeOfArea / 2; k <= i + sizeOfArea / 2; k++)
				for (int l = max(j - sizeOfArea / 2, 0); l <= min(j + sizeOfArea / 2, H.cols - 1); l++)
				{
					if (H.at<int>((k + 360) % 360, l) > vMax)
					{
						pMax = Point((k + 360) % 360, l);
						vMax = H.at<int>((k + 360) % 360, l);
					}
				}
			if (pMax.x == i && pMax.y == j)
			{
				peak pk;
				pk.hval = vMax;
				pk.ro = j;
				pk.theta = i;
				Peaks[sizeOfArea].push_back(pk);
			}
		}
	Mat matr(src.rows, src.cols, CV_8UC3);
	matr = imread(fname, CV_LOAD_IMAGE_COLOR);
	sort(Peaks[sizeOfArea].begin(), Peaks[sizeOfArea].end());
	for (int i = 0; i < 10; i++)
	{
		Point pt1, pt2;
		cout << "ro:" << Peaks[sizeOfArea][i].ro << " theta: " << Peaks[sizeOfArea][i].theta << '\n';
		double a = cos(CV_PI / 180 * (Peaks[sizeOfArea][i].theta)), b = sin(CV_PI / 180 * (Peaks[sizeOfArea][i].theta));
		double x0 = a * Peaks[sizeOfArea][i].ro, y0 = b * Peaks[sizeOfArea][i].ro;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(matr, pt1, pt2, Scalar(255, 0, 0));
	}

	imshow("", matr);
	waitKey(0);
}

void DistanceTransformAndPatternMatching()
{
	Mat src1, src2, H, resDist;
	int distx = 0, disty = 0;
	char fname[MAX_PATH];
	openFileDlg(fname);
	src1 = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	imshow("source 1 initial", src1);
	openFileDlg(fname);
	src2 = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	imshow("source 2", src2);
	//distance transform
	for (int i = 1; i < src1.rows - 1; i++)
		for (int j = 1; j < src1.cols - 1; j++)
		{
			// p0 p1 p2
			// p3 px
			int p0 = src1.at<uchar>(i - 1, j - 1) + 3;
			int p1 = src1.at<uchar>(i - 1, j) + 2;
			int p2 = src1.at<uchar>(i - 1, j + 1) + 3;
			int p3 = src1.at<uchar>(i, j - 1) + 2;
			src1.at<uchar>(i, j) = min(min(min(p0, p1), min(p2, p3)), src1.at<uchar>(i, j));
		}
	imshow("source 1 distance transform top down", src1);
	for (int i = src1.rows - 2; i > 1; i--)
		for (int j = src1.cols - 2; j > 1; j--)
		{
			//    px p0
			// p3 p2 p1
			int p0 = src1.at<uchar>(i, j + 1) + 2;
			int p1 = src1.at<uchar>(i + 1, j + 1) + 3;
			int p2 = src1.at<uchar>(i - 1, j) + 2;
			int p3 = src1.at<uchar>(i + 1, j - 1) + 3;
			src1.at<uchar>(i, j) = min(min(min(p0, p1), min(p2, p3)), src1.at<uchar>(i, j));
		}
	imshow("source 1 distance transform top down + bottom up", src1);
	int sum = 0;
	int count = 0;
	for (int i = 0; i < src2.rows; i++)
		for (int j = 0; j < src2.cols; j++)
			if (src2.at<uchar>(i, j) == 0)
			{
				sum += src1.at<uchar>(i, j);
				count++;
			}
	cout << (int)((float)(sum / count));
	waitKey(0);
}

void StatisticalDataAnalysis()
{
	//read data
	int p = 400, N = 361;
	Mat Features(p + 1, N, CV_8UC1, float(0));
	Mat COV(N, N, CV_32FC1, float(0));
	Mat COR(N, N, CV_32FC1, float(0));
	Mat CORC(256, 256, CV_8UC1);
	float averages[370];
	for (int i = 0; i < N; i++)
		averages[i] = 0;
	char folder[256] = "Images/images_faces";
	char fname[256];
	for (int i = 1; i <= p; i++)
	{
		sprintf(fname, "%s/face%05d.bmp", folder, i);
		Mat img = imread(fname, 0);
		for (int l = 0; l < 19; l++)
			for (int c = 0; c < 19; c++)
			{
				Features.at<uchar>(i - 1, l * 19 + c) = img.at<uchar>(l, c);
				averages[l * 19 + c] += (float)img.at<uchar>(l, c);
			}
	}
	//calc mediile
	for (int i = 0; i < N; i++)
		averages[i] /= (float)p;

	//calc matrice de covarianta
	ofstream g("COV.csv");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			g << 0;
			int sum = 0;
			for (int k = 0; k < p; k++)
				sum += ((float)Features.at<uchar>(k, i) - averages[i])*((float)Features.at<uchar>(k, j) - averages[j]);
			COV.at<float>(j, i) = COV.at<float>(i, j) = sum / (float)p;
			g << ',' << COV.at<float>(i, j);
		}
		g << '\n';
	}
	g.close();
	//calc matrice de corelatie
	ofstream gg("COR.csv");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			COR.at<float>(j, i) = COR.at<float>(i, j) = COV.at<float>(j, i) / (sqrt(COV.at<float>(i, i))*sqrt(COV.at<float>(j, j)));
			gg << ',' << COR.at<float>(i, j);
		}
		gg << '\n';
	}
	gg.close();
	//corelation chart
	int corcx1 = 5, corcy1 = 4;
	int corcx2 = 5, corcy2 = 14;
	for (int i = 0; i < p; i++)
	{
		int val1 = Features.at<uchar>(i, corcx1 * 19 + corcy1);
		int val2 = Features.at<uchar>(i, corcx2 * 19 + corcy2);
		CORC.at<uchar>(val1, val2) = 0;
	}
	imshow("corelation graph", CORC);
	cout << COR.at<float>(corcx1 * 19 + corcy1, corcx2 * 19 + corcy2);
	waitKey(0);
}

double dist(std::vector<int> a, std::vector<int> b)
{
	double sum = 0;
	for (int i = 0; i < a.size(); i++)
		sum += (a[i] - b[i])*(a[i] - b[i]);
	return sum; //could be sqrt but it is faster like this
}

typedef struct PointCluster {
	int x, y, cluster;
};

double distPoints(PointCluster a, PointCluster b)
{
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);//could be sqrt but it is faster like this
}

void KmeansClustering()
{
	int k;
	cout << "give k:";
	cin >> k;
	char fname1[MAX_PATH];
	openFileDlg(fname1);
	Mat src = imread(fname1, CV_LOAD_IMAGE_GRAYSCALE);

	vector<PointCluster> x;
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			if (src.at<uchar>(i, j) == 0)
				x.push_back(PointCluster{ i, j, -1 });

	int n = x.size();

	//initialize clusters
	default_random_engine gen;
	gen.seed(time(NULL));
	uniform_int_distribution<int> distribution(0, n - 1);
	vector<PointCluster> centers;
	for (int i = 0; i < k; i++)
	{
		int randint = distribution(gen);
		x[randint].cluster = i;
		centers.push_back(x[randint]);
	}

	bool stop = false;
	while (stop == false)
	{
		//assignment
		for (int i = 0; i < n; i++)
		{
			int minDist = INT_MAX;
			//find closest cluster center
			for (int j = 0; j < k; j++)
			{
				int dist = distPoints(x[i], centers[j]);
				if (dist < minDist)
				{
					minDist = dist;
					x[i].cluster = centers[j].cluster;
				}
			}
		}

		//update centers
		for (int i = 0; i < k; i++)
		{
			int x1Sum = 0;
			int x2Sum = 0;
			int noPointsInCluster = 0;
			for (int j = 0; j < n; j++)
				if (x[j].cluster == i)
				{
					x1Sum += x[j].x;
					x2Sum += x[j].y;
					noPointsInCluster++;
				}

			if (centers[i].x == (x1Sum / noPointsInCluster) &&
				centers[i].y == (x2Sum / noPointsInCluster))
				stop = true;
			else
				centers[i].x = x1Sum / noPointsInCluster,
				centers[i].y = x2Sum / noPointsInCluster;

		}
	}

	Mat img(src.rows, src.cols, CV_8UC3, Scalar(255, 255, 255));
	Vec3b* colors = new Vec3b[k];
	srand(time(NULL));
	for (int i = 0; i < k; i++)
	{
		unsigned char r = rand() % 256;
		unsigned char g = rand() % 256;
		unsigned char b = rand() % 256;
		colors[i] = { r, g, b };
	}


	for (int i = 0; i < n; i++)
	{
		PointCluster point = x[i];
		img.at<Vec3b>(point.x, point.y) = colors[point.cluster];
	}

	//voronoi
	Mat voronoi(src.rows, src.cols, CV_8UC3);
	for (int i = 0; i < voronoi.rows; i++)
		for (int j = 0; j < voronoi.cols; j++)
		{
			int min = INT_MAX;
			int label;
			for (int t = 0; t < k; t++)
			{
				int dist = distPoints(PointCluster{ i, j, 0 }, centers[t]);
				if (dist < min)
				{
					min = dist;
					label = t;
				}
			}
			voronoi.at<Vec3b>(i, j) = colors[label];
		}

	imshow("original", src);
	imshow("clusters", img);
	imshow("voronoi", voronoi);
	waitKey(0);
}


void componentAnalysis()
{
	ifstream file;
	char fname[MAX_PATH];
	openFileDlg(fname);
	file.open(fname);
	int nr;
	int features;
	file >> nr >> features;
	Mat X(nr, features, CV_64F);
	Mat Xprim;
	for (int i = 0; i < nr; i++)
	{
		vector<double> pct;
		double feat;
		for (int j = 0; j < features; j++)
		{
			file >> feat;
			X.at<double>(i, j) = feat;
		}
	}

	X.copyTo(Xprim);

	for (int i = 0; i < features; i++)
	{
		double sum = 0;
		for (int j = 0; j < nr; j++)
			sum += Xprim.at<double>(j, i);

		sum /= nr;
		for (int j = 0; j < nr; j++)
			Xprim.at<double>(j, i) -= sum;

	}

	Mat C = Xprim.t() * Xprim / (nr - 1);
	Mat Lambda, Q;
	eigen(C, Lambda, Q);
	Q = Q.t();

	for (int i = 0; i < features; i++)
		cout << Lambda.at<double>(i, 0) << ", ";
	cout << endl;
	int k;
	cout << "Nr. of relevant features: ";
	cin >> k;
	Rect roi(0, 0, k, Q.rows);
	Mat cropped(Q, roi);
	Mat Xcoeff = Xprim * cropped;
	Mat Xapprox = Xcoeff * cropped.t();

	double minC0 = 99999, minC1 = 99999, maxC0 = -99999, maxC1 = -99999, delta = 0;
	for (int i = 0; i < Xapprox.rows; i++)
	{
		for (int j = 0; j < Xapprox.cols; j++)
			delta += fabs(Xprim.at<double>(i, j) - Xapprox.at<double>(i, j));

		if (Xcoeff.at<double>(i, 0) > maxC0) maxC0 = Xcoeff.at<double>(i, 0);
		if (Xcoeff.at<double>(i, 1) > maxC1) maxC1 = Xcoeff.at<double>(i, 1);
		if (Xcoeff.at<double>(i, 0) < minC0) minC0 = Xcoeff.at<double>(i, 0);
		if (Xcoeff.at<double>(i, 1) < minC1) minC1 = Xcoeff.at<double>(i, 1);
	}
	delta /= (X.rows * X.cols);

	Mat showMat((int)(maxC1 - minC1 + 1), (int)(maxC0 - minC0 + 1), CV_8UC1);

	for (int i = 0; i < Xapprox.rows; i++)
		showMat.at<uchar>(Xcoeff.at<double>(i, 1) - minC1, Xcoeff.at<double>(i, 0) - minC0) = 0;


	imshow("img", showMat);
	cout << "Difference between matrices: " << delta << endl;
	waitKey(0);
}



Mat X(60001, 28 * 28 + 1, CV_8UC1);
Mat priors(11, 1, CV_64FC1);
Mat likelihood(10, 28 * 28, CV_64FC1);


void loadImages()
{
	char fname[256];
	int counter = 0;
	for (int c = 0; c < 10; c++)
	{
		std::cout << "doing " << c << " .......";
		int index = 0;
		while (index < 7000)
		{
			sprintf(fname, "./Images/images_Bayes/train/%d/%06d.png", c, index);
			Mat img = imread(fname, 0);
			if (img.cols == 0) break;
			X.at<uchar>(counter, 0) = c;
			counter++;
			for (int i = 0; i < img.rows; i++)
				for (int j = 0; j < img.rows; j++)
					if (img.at<uchar>(i, j) > 128)
						X.at<uchar>(counter, 1 + i * 28 + j) = 255;
					else
						X.at<uchar>(counter, 1 + i * 28 + j) = 0;

			index++;
		}
		cout << " done!\n";
	}

	for (int i = 0; i < 10; i++)
		priors.at<double>(i, 0) /= counter;

	imwrite("./Images/images_Bayes/trainimage.bmp", X);

	cout << endl;
}

void loadTrainingSet()
{
	Mat img = imread("./Images/images_Bayes/trainimage.bmp", 0);
	//priors
	for (int i = 0; i < 10; i++)
		priors.at<double>(i, 0) = 0.0;

	for (int i = 0; i < img.rows - 1; i++)
		priors.at<double>((int)img.at<uchar>(i, 0), 0) += 1.0;

	//likelihood
	for (int i = 0; i < likelihood.rows; i++)
		for (int j = 0; j < likelihood.cols; j++)
			likelihood.at<double>(i, j) = 0.0;

	for (int i = 0; i < img.rows - 1; i++)
	{
		int nr = img.at<uchar>(i, 0);
		for (int j = 1; j < img.cols; j++)
			if (img.at<uchar>(i, j) > 128)
				likelihood.at<double>(nr, j - 1) += 1.0;
	}

	for (int i = 0; i < 10; i++)
	{
		//likelihood
		for (int j = 0; j < 28 * 28; j++)
		{
			likelihood.at<double>(i, j) += 1.0;
			likelihood.at<double>(i, j) /= (priors.at<double>(i, 0) + 10);
		}
		//prioris
		priors.at<double>(i, 0) /= img.rows;
	}
}

void classify()
{
	char fname[MAX_PATH];
	openFileDlg(fname);
	Mat unknown = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
	Mat probability(10, 1, CV_64FC1);
	for (int i = 0; i < 10; i++)
		probability.at<double>(i, 0) = 0.0;

	for (int i = 0; i < unknown.rows; i++)
		for (int j = 0; j < unknown.cols; j++)
		{
			int pixel = unknown.at<uchar>(i, j);
			for (int cls = 0; cls < 10; cls++)
			{
				double lh;
				if (pixel > 128)
					lh = likelihood.at<double>(cls, i*unknown.rows + j);
				else
					lh = 1.0 - likelihood.at<double>(cls, i*unknown.rows + j);

				probability.at<double>(cls, 0) += log(lh);
			}
		}
	double max = -999999;
	int classMax = 0;
	for (int i = 0; i < 10; i++)
		if (probability.at<double>(i, 0) > max)
		{
			max = probability.at<double>(i, 0);
			classMax = i;
		}
	cout << "Loaded image is probably a " << classMax << endl;
}

void naiveBayesianClassifier()
{
	//loadImages();
	int c = 1;
	loadTrainingSet();
	while (c != 0)
	{
		classify();
		cin >> c;
	}
}

Mat calcHist(Mat img, int nr_bins) {
	Mat hist_vec(1, nr_bins * 3, CV_32S, Scalar(0));
	int el_per_bin = 256 / nr_bins;

	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++) {
			Vec3b value = img.at<Vec3b>(i, j);
			hist_vec.at<int>(value[0] / el_per_bin)++;
			hist_vec.at<int>(nr_bins + (value[1] / el_per_bin))++;
			hist_vec.at<int>(2 * nr_bins + (value[2] / el_per_bin))++;
		}
	return hist_vec;
}

float calcDist(Mat x, Mat y) {
	float dist = 0.0;
	for (int i = 0; i < x.cols; i++)
		dist += pow(x.at<int>(0, i) - y.at<int>(0, i), 2);
	return sqrt(dist);
}

struct Neighbour {
	int index;
	float distance;

	bool operator < (const Neighbour& n) const
	{
		return (distance < n.distance);
	}
};

bool compareNeighbours(const Neighbour& n1, const Neighbour& n2) {
	return n1.distance < n2.distance;
}

void kNearestClassifier(int no_of_bins, int k) {
	const int nrclasses = 6;
	char classes[nrclasses][10] = { "beach", "city", "desert", "forest", "landscape", "snow" };

	int feature_dim = no_of_bins * 3;
	Mat X(0, feature_dim, CV_32S);
	vector<int> Y;

	char* fname = (char*)malloc(256 * sizeof(char));
	for (int c = 0; c < nrclasses; c++) {
		int fileNr = 0;
		while (1) {
			sprintf(fname, "images/images_KNN/train/%s/%06d.jpeg", classes[c], fileNr++);
			Mat img = imread(fname, CV_LOAD_IMAGE_COLOR);
			if (img.cols == 0)
				break;

			//add the histogram vec to global hist matrix
			X.push_back(calcHist(img, no_of_bins));
			Y.push_back(c);
		}
		//cout << "class " << c<< ": " << X.rows << " " << Y.size();
	}
	cout << "Finished computing feature vectors";

	//load test image
	Mat confusionMat(nrclasses, nrclasses, CV_32S, Scalar(0));
	for (int c = 0; c < nrclasses; c++) {
		int fileNr = 0;
		while (1) {
			sprintf(fname, "images_KNN/test/%s/%06d.jpeg", classes[c], fileNr++);
			Mat img = imread(fname, CV_LOAD_IMAGE_COLOR);
			if (img.cols == 0)
				break;

			Mat hist_vec = calcHist(img, no_of_bins);
			vector<Neighbour> neighbours;
			// compute distances
			for (int i = 0; i < X.rows; i++)
				neighbours.push_back(Neighbour{ i,  calcDist(hist_vec, X.row(i)) });

			// sort neighbour vector
			sort(neighbours.begin(), neighbours.end());
			int classVotes[6] = { 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < k; i++)
				classVotes[Y.at(neighbours.at(i).index)]++;
			// predict class
			int max = classVotes[0], predictedClass = 0;
			for (int i = 1; i< nrclasses; i++)
				if (classVotes[i] > max) {
					max = classVotes[i];
					predictedClass = i;
				}

			confusionMat.at<int>(c, predictedClass)++;
			//free(classVotes);
		}
	}

	// compute confusion matrix
	float accuracy;
	int mainDiagCount = 0;
	int nr_el = 0;
	cout << "Confusion matrix:\n";
	for (int i = 0; i < nrclasses; i++) {
		for (int j = 0; j < nrclasses; j++) {
			if (i == j)
				mainDiagCount += confusionMat.at<int>(i, i);
			nr_el += confusionMat.at<int>(i, j);
			cout << confusionMat.at<int>(i, j) << " ";
		}
		cout << endl;
	}
	cout << "\nAccuracy: " << (float)(mainDiagCount) / nr_el;

	free(fname);
	char a;
	scanf("%c", &a);
	scanf("%c", &a);
}

void Perceptron()
{
	char fname[MAX_PATH];
	openFileDlg(fname);
	Mat X(0, 3, CV_32FC1);
	Mat Y(0, 1, CV_32FC1);
	Mat img = imread(fname, CV_LOAD_IMAGE_COLOR);
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			if (img.at<Vec3b>(i, j) != Vec3b(255, 255, 255))
			{
				float vec[3] = { 1,j,i };
				X.push_back(Mat(1, 3, CV_32FC1, vec));
				if (img.at<Vec3b>(i, j) == Vec3b(0, 0, 255))
					Y.push_back(Mat(1, 1, CV_32FC1, { 1 }));
				else
					Y.push_back(Mat(1, 1, CV_32FC1, { -1 }));

			}
	float Elim = 0.00001, etha = 0.0001;
	Mat w(1, 3, CV_32FC1, { 0.1,0.1,0.1 });
	Mat gradL(1, 3, CV_32FC1, { 0,0,0 });
	for (int iter = 0; iter < 100000; iter++)
	{
		float E = 0;
		for (int i = 0; i < X.rows; i++)
		{
			float zi = 0.0;
			for (int j = 0; j < 3; j++)
				zi += w.at<float>(j) * X.at<float>(i, j);
			if (zi*Y.at<float>(i, 0) <= 0)
			{
				gradL -= Y.at<float>(i, 0)*X.row(i);
				E++;
			}
		}
		E /= X.rows;
		gradL = gradL / X.rows;
		if (E < Elim)
			break;
		w -= etha * gradL;
	}
	line(img, Point(0, -1 * w.at<float>(0, 0) / w.at<float>(0, 2)),
		Point(img.cols, (-1)*(w.at<float>(0, 0) + w.at<float>(0, 1)*img.cols) / w.at<float>(0, 2)), Vec3b(0, 255, 0));
	imshow("img", img);
	waitKey();
}
//
//struct weaklearner
//{
//	int feature_i;
//	int threshold;
//	int class_label;
//	float error;
//	int classify(Mat X)
//	{
//		if (X.at<float>(feature_i) < threshold)
//			return class_label;
//		else
//			return -class_label;
//	}
//};
//
//struct classifier
//{
//	int T;
//	double alphas[100];
//	weaklearner hs[100];
//	int classify(Mat X)
//	{
//		double s = 0.0;
//		for (int i = 0; i < T; i++)
//			s += alphas[i] * (double)hs[i].classify(X);
//		return s > 0 ? 1 : -1;
//	}
//};
//
//weaklearner findWeakLearner(Mat img, Mat X, Mat y, Mat w)
//{
//	weaklearner best_h = { 0,0,0,0 };
//	double best_err = 100000;
//
//	for (int j = 0; j < X.cols; j++)
//	{
//		int size;
//		j == 0 ? size = img.rows : size = img.cols;
//		for (int th = 0; th < size; th++)
//		{
//			for (int class_label = -1; class_label <= 1; class_label += 2)
//			{
//				double e = 0;
//				for (int i = 0; i < X.rows; i++)
//				{
//					int z = X.at<int>(i, j) < th ? class_label : -1 * class_label;
//					if (z * y.at<int>(i) < 0)
//						e += w.at<double>(i);
//				}
//				if (e < best_err)
//				{
//					best_err = e;
//					best_h.feature_i = j;
//					best_h.class_label = class_label;
//					best_h.threshold = th;
//					best_h.error = e;
//				}
//			}
//		}
//	}
//	return best_h;
//}
//
//
//classifier AdaBoost(int T, Mat img)
//{
//	classifier c;
//	c.T = T;
//	Mat X(0, 2, CV_32S);
//	Mat Y(0, 1, CV_32S);
//	for (int i = 0; i < img.rows; i++)
//		for (int j = 0; j < img.cols; j++)
//			if (img.at<Vec3b>(i, j) != Vec3b(255, 255, 255))
//			{
//				int vec[2] = { j,i };
//				X.push_back(Mat(1, 2, CV_32S, vec));
//				if (img.at<Vec3b>(i, j) == Vec3b(0, 0, 255))
//					Y.push_back(Mat(1, 1, CV_32S, { 1 }));
//				else
//					Y.push_back(Mat(1, 1, CV_32S, { -1 }));
//			}
//
//	Mat w(X.rows, 1, CV_64FC1, (double)(1.0 / (double)X.rows));
//	for (int t = 0; t < T; t++)
//	{
//		c.hs[t] = findWeakLearner(img, X, Y, w);
//		c.alphas[t] = 0.5 * log((1.0 - c.hs[t].error) / c.hs[t].error);
//		double s = 0;
//		for (int i = 0; i < X.rows; i++)
//		{
//			w.at<double>(i) *= exp(-c.alphas[t] * Y.at<int>(i) * (double)(c.hs[t].classify(X.row(i))));
//			s += w.at<double>(i);
//		}
//		for (int i = 0; i < X.rows; i++)
//			w.at<double>(i) /= s;
//	}
//	return c;
//}
//
//void AdaBoostCaller()
//{
//
//	int a;
//	cout << "T=";
//	cin >> a;
//	char fname[MAX_PATH];
//	openFileDlg(fname);
//	Mat img = imread(fname, CV_LOAD_IMAGE_COLOR);
//	classifier c = AdaBoost(a, img);
//	Mat res;
//	img.copyTo(res);
//	for (int i = 0; i < img.rows; i++)
//		for (int j = 0; j < img.cols; j++)
//			if (res.at<Vec3b>(i, j) == Vec3b(255, 255, 255))
//			{
//				int vec[2] = { i,j };
//				if (c.classify(Mat(1, 2, CV_32S, vec)) > 0)
//					res.at<Vec3b>(i, j) = Vec3b(0, 255, 0);
//				else
//					res.at<Vec3b>(i, j) = Vec3b(123, 234, 15);
//			}
//	imshow("res", res);
//	waitKey();
//}

struct WEAK_LEARNER
{
	int feature; //can be 0 or 1 (indicates the column number in feature vector X
	double threshold;
	int class_label;
	double error;

	int classifiy(Mat X)//X is a row vector having all the features
	{
		if (X.at<double>(feature) < threshold)
			return class_label;
		else
			return -class_label;
	}
};

struct CLASSIFIER
{
	int T;
	double alphas[1000];

	WEAK_LEARNER hs[1000];

	int classify(Mat X) {//X is a row vector having all the features
		double s = 0.;

		for (int t = 0; t < T; t++)
		{
			s += alphas[t] * (double)(hs[t].classifiy(X));
		}

		if (s > 0)
			return 1;
		else
			return -1;
	}
};

void drawBoundary(Mat *img, CLASSIFIER classifier)
{
	const int nr_of_features = 2;
	for (int i = 0; i < (*img).rows; i++)
		for (int j = 0; j < (*img).cols; j++)
		{
			//pixel is white => color it depending on its class
			if ((*img).at<Vec3b>(i, j) == Vec3b{ 255, 255, 255 })
			{
				Mat row_X(1, nr_of_features, CV_64FC1);
				row_X.at<double>(0, 0) = i; //y coordinate
				row_X.at<double>(0, 1) = j; //x coordinate

				//blue = -1, red = 1
				if (classifier.classify(row_X) < 0)
				{
					//blue class
					(*img).at<Vec3b>(i, j) = Vec3b{ 255, 255, 0 };
				}
				else
				{
					//red class
					(*img).at<Vec3b>(i, j) = Vec3b{ 0, 255, 255 };
				}
			}
		}
}

WEAK_LEARNER findWeakLearner(Mat X, Mat Y, Mat W, int width, int height)
{
	WEAK_LEARNER best_h;
	double best_err = 1;

	for (int j = 0; j < X.cols; j++)
	{
		// X  n x {y, x} - first column = y coordinate, second column = x coordinate
		int size = j == 0 ? height : width;

		for (int threshold = 0; threshold < size; threshold++)
		{
			for (int class_label = -1; class_label <= 1; class_label += 2) // class_label can be {-1, +1}
			{
				double e = 0;

				for (int i = 0; i < X.rows; i++)
				{
					double z;
					if (X.at<double>(i, j) < (double)(threshold))
					{
						z = class_label;
					}
					else
					{
						z = -class_label;
					}

					if (z * Y.at<double>(i, 0) < 0)
					{
						e += W.at<double>(i, 0);
					}
				}

				if (e < best_err)
				{
					best_err = e;
					best_h = WEAK_LEARNER{ j, (double)(threshold), class_label, best_err };
				}
			}
		}
	}
	return best_h;
}

CLASSIFIER adaBoost(Mat X, Mat Y, const int T, const int width, const int height)
{

	//initialise the weight vector with 1/n, where n is the number of examples
	Mat W(X.rows, 1, CV_64FC1, double(1. / X.rows)); // weight vector

	CLASSIFIER classifier;
	classifier.T = T;

	for (int t = 0; t < T; t++)
	{
		WEAK_LEARNER weakLearner = findWeakLearner(X, Y, W, width, height);

		double alpha_t = 0.5 * log((1 - weakLearner.error) / weakLearner.error);

		double s = 0.;

		for (int i = 0; i < W.rows; i++)
		{
			W.at<double>(i, 0) *= exp(-alpha_t * Y.at<double>(i, 0) * (double)(weakLearner.classifiy(X.row(i))));

			s += W.at<double>(i, 0);
		}

		//normalize the weights
		for (int i = 0; i < W.rows; i++)
			W.at<double>(i, 0) /= s;

		classifier.alphas[t] = alpha_t;
		classifier.hs[t] = weakLearner;
	}
	return classifier;
}

void AdaBoostCaller()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

		const int nr_elements_feature_vector = 2;

		Mat X(0, nr_elements_feature_vector, CV_64FC1);
		Mat Y(0, 1, CV_64FC1);

		// read the coordinates: x = [1 x_coordinate y_coordinate]
		for (int i = 0; i < src.rows; i++)
			for (int j = 0; j < src.cols; j++)
			{
				//blue: green == 0 && red == 0
				if (src.at<Vec3b>(i, j)[1] == 0 && src.at<Vec3b>(i, j)[2] == 0)
				{
					Mat row_X(1, nr_elements_feature_vector, CV_64FC1);
					row_X.at<double>(0, 0) = i; //y coordinate
					row_X.at<double>(0, 1) = j; //x coordinate

					Mat row_Y(1, 1, CV_64FC1);
					row_Y.at<double>(0, 0) = -1;

					X.push_back(row_X);
					Y.push_back(row_Y);
				}
				//red: blue == 0 && green == 0
				else if (src.at<Vec3b>(i, j)[0] == 0 && src.at<Vec3b>(i, j)[1] == 0)
				{
					Mat row_X(1, nr_elements_feature_vector, CV_64FC1);
					row_X.at<double>(0, 0) = i; //y coordinate
					row_X.at<double>(0, 1) = j; //x coordinate

					Mat row_Y(1, 1, CV_64FC1);
					row_Y.at<double>(0, 0) = 1;

					X.push_back(row_X);
					Y.push_back(row_Y);
				}
			}

		CLASSIFIER classifier = adaBoost(X, Y, 200, src.cols, src.rows);

		drawBoundary(&src, classifier);
		cv::imshow("src", src);
		cv::waitKey(0);
	}
}

void FinalProjectWithLibrary()
{

}


Mat erosionOnce(Mat img)
{
	Mat copy(img.rows, img.cols, CV_8UC1);
	img.copyTo(copy);
	for (int i = 1; i < img.rows - 1; i++)
		for (int j = 1; j < img.cols - 1; j++)
		{
			if (img.at<uchar>(i, j) == 0)
				if (img.at<uchar>(i - 1, j) == 255 ||
					img.at<uchar>(i - 1, j - 1) == 255 ||
					img.at<uchar>(i, j - 1) == 255 ||
					img.at<uchar>(i + 1, j - 1) == 255 ||
					img.at<uchar>(i + 1, j) == 255 ||
					img.at<uchar>(i + 1, j + 1) == 255 ||
					img.at<uchar>(i, j + 1) == 255 ||
					img.at<uchar>(i - 1, j + 1) == 255)

					copy.at<uchar>(i, j) = 255;

		}
	return copy;
}

Mat viz;
Point cTL, cBR;
int ci, cj;
void fill()
{
	//cout << ci << ' ' << cj << '\n';
	viz.at<uchar>(ci, cj) = 128;
	if (ci < cTL.x)
		cTL.x = ci;
	if (cj < cTL.y)
		cTL.y = cj;
	if (ci > cBR.x)
		cBR.x = ci;
	if (cj > cBR.y)
		cBR.y = cj;
	if (ci > 0 && viz.at<uchar>(ci - 1, cj) == 255) { ci--; fill(); ci++; }
	if (cj > 0 && viz.at<uchar>(ci, cj - 1) == 255) { cj--; fill(); cj++; }
	if (ci < viz.rows - 1 && viz.at<uchar>(ci + 1, cj) == 255) { ci++; fill(); ci--; }
	if (cj < viz.cols - 1 && viz.at<uchar>(ci, cj + 1) == 255) { cj++; fill(); cj--; }

}
Point TL, BR;
void GetContourOfBiggestShape(Mat src)
{
	TL = Point(0, 0);
	BR = Point(0, 0);
	int currentArea, maxArea = 0;
	
	src.copyTo(viz);
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
		{
			if (src.at<uchar>(i, j) == 255 && viz.at<uchar>(i, j) == 255)
			{
				currentArea = 0;
				cTL = Point(i, j);
				cBR = Point(i, j);
				ci = i; cj = j;
				fill();
				if ((cBR.x - cTL.x)*(cBR.y - cTL.y) > maxArea)
				{
					maxArea = (cBR.x - cTL.x)*(cBR.y - cTL.y);
					TL.x = cTL.x;
					TL.y = cTL.y;
					BR.x = cBR.x;
					BR.y = cBR.y;
				}
			}
		}
}

void FinalProjectWithoutLibrary()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

		//# compute the Scharr gradient magnitude representation of the images
				// in both the x and y direction using OpenCV 2.4
		int ddepth = CV_32F;
		Mat gradX, gradY;
		Sobel(src, gradX, ddepth, 1, 0, -1);
		Sobel(src, gradY, ddepth, 0, 1, -1);

		// subtract the y - gradient from the x - gradient
		Mat gradient;
		subtract(gradX, gradY, gradient);
		convertScaleAbs(gradient, gradient);
		imshow("gradient", gradient);

		// blur and threshold the image
		Mat blurred;
		blur(gradient, blurred, Size(9, 9));
		Mat thresh;
		threshold(blurred, thresh, 225, 255, THRESH_BINARY);
		imshow("threshold", thresh);

		// construct a closing kernel and apply it to the thresholded image
		Mat kernel, closed;
		kernel = getStructuringElement(MORPH_RECT, Size(21, 7));
		morphologyEx(thresh, closed, MORPH_CLOSE, kernel);

		imshow("closed", closed);


		// perform a series of erosions and dilations
		kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		erode(closed, closed, kernel, Point(-1, -1), 4);
		dilate(closed, closed, kernel, Point(-1, -1), 4);
		imshow("closed refactored", closed);
		//find the contours in the thresholded image, then sort the contours
		// by their area, keeping only the largest one
		//Mat contours;
		//findContours(closed, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//cnts = imutils.grab_contours(cnts)
		//	c = sorted(cnts, key = cv2.contourArea, reverse = True)[0]

		//	// compute the rotated bounding box of the largest contour
		//	rect = cv2.minAreaRect(c)
		//	box = boxPoints(rect);
		//	box = np.int0(box)

		//	// draw a bounding box arounded the detected barcode and display the image
		//	cv2.drawContours(image, [box], -1, (0, 255, 0), 3)
		GetContourOfBiggestShape(closed);
		cvtColor(src, src, COLOR_GRAY2BGR);
		cout << BR.x << ' ' << BR.y << '\n';
		rectangle(src, Rect(TL.y, TL.x, BR.y- TL.y, BR.x- TL.x), CV_RGB(255, 0, 0));
		imshow("Image", src);
		waitKey();
	}
}

void FinalProject()
{
	cout << "mode: \n1. Library\n2. No library";
	int m;
	cin >> m;
	if (m == 1)
		FinalProjectWithLibrary();
	else
		FinalProjectWithoutLibrary();
}

int main()
{
	int op;
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Open image\n");
		printf(" 2 - Open BMP images from folder\n");
		printf(" 3 - Image negative - diblook style\n");
		printf(" 4 - BGR->HSV\n");
		printf(" 5 - Resize image\n");
		printf(" 6 - Canny edge detection\n");
		printf(" 7 - Edges in a video sequence\n");
		printf(" 8 - Snap frame from live video\n");
		printf(" 9 - Mouse callback demo\n");
		printf(" 10 - Lab 1 - Least Mean Square\n");
		printf(" 11 - Lab 2 - RANSAC Line Fitting\n");
		printf(" 12 - Lab 3 - Hough\n");
		printf(" 13 - Lab 4 - Distance transform and pattern matching\n");
		printf(" 14 - Lab 5 - Statistical Data Analysis\n");
		printf(" 15 - Lab 6 - K means clustering\n");
		printf(" 16 - Lab 7 - Component Analysis\n");
		printf(" 17 - Lab 8 - KNN Classifier\n");
		printf(" 18 - Lab 9 - Naive Bayes Component\n");
		printf(" 19 - Lab 10 - Linear Classifiers and the Perceptron Algorithm\n");
		printf(" 20 - Lab 11 - Adaboost\n");
		printf(" 100 - Final Project - Barcode detection\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			testOpenImage();
			break;
		case 2:
			testOpenImagesFld();
			break;
		case 3:
			testParcurgereSimplaDiblookStyle();
			break;
		case 4:
			testBGR2HSV();
			break;
		case 5:
			testResize();
			break;
		case 6:
			testCanny();
			break;
		case 7:
			testVideoSequence();
			break;
		case 8:
			testSnap();
			break;
		case 9:
			testMouseClick();
			break;
		case 10:
			LeastMeanSquare();
			break;
		case 11:
			RANSACLineFitting();
			break;
		case 12:
			Hough();
			break;
		case 13:
			DistanceTransformAndPatternMatching();
			break;
		case 14:
			StatisticalDataAnalysis();
			break;
		case 15:
			KmeansClustering();
			break;
		case 16:
			componentAnalysis();
			break;
		case 17:
			naiveBayesianClassifier();
			break;
		case 18:
			int m, kk;
			cout << "m = ";
			cin >> m;
			cout << "k = ";
			cin >> kk;
			kNearestClassifier(m, kk);
			
			break;
		case 19:
			Perceptron();
			int a;
			cin >> a;
			break;
		case 20:
			AdaBoostCaller();
			break;
		case 100:
			FinalProject();
			break;
		}
	} while (op != 0);
	return 0;
}