#pragma once

#ifndef PROJECT_FALLDETECTOR_H
#define PROJECT_FALLDETECTOR_H

using namespace std;
using namespace cv;

class FallDetector {
public:
    double getStddev(vector<double>* vec);
    double getMovementCoefficient(Mat* foreground,Mat* history);
    void analyzePosition(Mat* frame, vector<double>* thetaRatio, vector<double>* aRatio, vector<double>* bRatio, vector<double>* xPos, vector<double>* yPos, vector<Point> largestContour);
    void checkIfStaysInPlace(time_t start, bool* isChecking, bool* isFall, vector<double> xPos, vector<double> yPos);
    void checkMovementAfterFall(bool* toBeChecked,  bool *isFall, vector<double> xPos, vector<double> yPos);
};


#endif
