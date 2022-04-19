#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/optflow.hpp>
#include <opencv2/optflow/motempl.hpp>

#include <iostream>
#include <vector>
#include <sys/time.h>
#include <time.h>

#include "FallDetector.cpp"

#define ESC 27

using namespace std;
using namespace cv;

int main() {
    VideoCapture cap(0);

    FallDetector fallDetector;

    Mat frame, eroded, dilated;
    Mat backgroundImg, foregroundImg; //"foregroundImg" is the moving object (the human body that will be tracked)
    Mat fgMaskMOG2; //A specific region in a frame
    Mat history; //The collection of information from multiple frames(fgMaskMOG2)

    Ptr<BackgroundSubtractorMOG2> pMOG2 = createBackgroundSubtractorMOG2();

    vector<vector<Point> > contours; //The collection of contour points of the human body
    vector<Vec4i> hierarchy; //The format of each element in contours
    vector<Point> largestContour; //The dataset of the largest contour. When multiple moving objects are detected, only the largest object will be tracked and determined if it falls
    vector<Moments> center(1);

    vector<double> thetaRatio; //The angle of theta of the ellipse
    vector<double> aRatio; //The long axis of the ellipse
    vector<double> bRatio; //The short axis of the ellipse
    vector<double> xPos;  
    vector<double> yPos; //The coordinates of the center point of the ellipse

    double movementCoefficientValue;
    double aRatioValue;
    double bRatioValue;
    double thetaRatioValue;

    bool toBeChecked = false;
    bool isFall = false;

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Mask", WINDOW_AUTOSIZE);

    Mat firstFrame;

    if(cap.isOpened()) {
        cap >> firstFrame;
        history = Mat::zeros(firstFrame.size().height, firstFrame.size().width, CV_32FC1);
    }

    time_t start;

    while(true) {

        cap >> frame;

        if(frame.empty()) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap >> frame;
        }

        pMOG2->setHistory(20);
        pMOG2->setNMixtures(10);
        pMOG2->setDetectShadows(false);
        pMOG2->apply(frame, fgMaskMOG2);
        pMOG2->getBackgroundImage(backgroundImg);

        findContours(fgMaskMOG2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

        if(!toBeChecked) {
            largestContour.clear();
        }

        double maxArea = 0.0;

        for(size_t i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i], false);
            if(area > maxArea && area > 500) {
                maxArea = area;
                largestContour = contours[i];
            }
        }


        if(!largestContour.empty()) {
            fallDetector.analyzePosition(&frame, &thetaRatio, &aRatio, &bRatio, &xPos, &yPos, largestContour);
        }

        double timestamp = (double)clock() / CLOCKS_PER_SEC;
        motempl::updateMotionHistory(fgMaskMOG2, history, timestamp, 0.5);

        movementCoefficientValue = fallDetector.getMovementCoefficient(&fgMaskMOG2, &history);
        thetaRatioValue = fallDetector.getStddev(&thetaRatio);
        aRatioValue = fallDetector.getStddev(&aRatio);
        bRatioValue = fallDetector.getStddev(&bRatio);

        //cout << "Coeff: " << movementCoefficientValue << ",  Theta: " << thetaRatioValue << ", A: " << aRatioValue << ", B: " << bRatioValue << endl;

        if(!toBeChecked) {
            if(movementCoefficientValue > 80 && thetaRatioValue > 20 && (aRatioValue / bRatioValue) > 0.9 ) {
                toBeChecked = true;
                start = time(0);
            }
        }

        if(toBeChecked) {
            fallDetector.checkIfStaysInPlace(start, &toBeChecked, &isFall, xPos, yPos);
        }

        if(isFall) {
            fallDetector.checkMovementAfterFall(&toBeChecked, &isFall, xPos, yPos);
        }


        Point textOrg(10, cap.get(CAP_PROP_FRAME_HEIGHT) - 15);

        string text;
        if(isFall && toBeChecked) {
            text = "Fall";
        } else if(!isFall && toBeChecked) {
            text = "Warning";
        }
        putText(frame, text, textOrg, FONT_ITALIC, 1, Scalar::all(255), 2, 8);


        imshow("Original", frame);
        imshow("Mask", fgMaskMOG2);
        //imshow("History", history);

        if(waitKey(30) == ESC) break;
    }

    cap.release();
    frame.release();
    destroyAllWindows();

    return 0;
}
