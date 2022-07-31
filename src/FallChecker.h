#pragma once

#ifndef FALLCHECKER_H
#define FALLCHECKER_H

using namespace std;
using namespace cv;

class FallChecker{
public:
    Mat frame, eroded, dilated;
    Mat backgroundImg, foregroundImg; //"foregroundImg" is the moving object (the human body that will be tracked)
    Mat fgMaskMOG2; //A specific region in a frame
    Mat history; //The collection of information from multiple frames(fgMaskMOG2)
    Mat firstFrame;

    vector<vector<Point> > contours; //The collection of contour points of the human body
    vector<Vec4i> hierarchy; //The format of each element in contours
    vector<Point> largestContour; //The dataset of the largest contour. When multiple moving objects are detected, only the largest object will be tracked and determined if it falls


    vector<double> thetaRatio; //The angle of theta of the ellipse
    vector<double> aRatio; //The long axis of the ellipse
    vector<double> bRatio; //The short axis of the ellipse
    vector<double> xPos;  
    vector<double> yPos; //The coordinates of the center point of the ellipse

    double movementCoefficientValue; //Coefficient of motion of an object
    double aRatioValue;
    double bRatioValue;
    double thetaRatioValue;
  
    FallDetector fallDetector;
    void checker();

};

#endif