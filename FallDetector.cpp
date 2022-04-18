#pragma once

#include "FallDetector.h"

double FallDetector::getStddev(vector<double>* vec) {
    Scalar mean, stddev;
    if(!vec->empty()) {
        meanStdDev(*vec, mean, stddev);
    }
    return stddev[0];
}

double FallDetector::getMovementCoefficient(Mat* foreground,Mat* history) {
    double sumForeground = sum(*foreground)[0];
    double sumHistory = sum(*history)[0];
    return (sumHistory / sumForeground) * 100.0;
}

void FallDetector::checkIfStaysInPlace(time_t start, bool* isChecking, bool* isFall, vector<double> xPos, vector<double> yPos) {
    double secondsSinceStart = difftime( time(0), start);
    double xDevValue;
    double yDevValue;


    xDevValue = this->getStddev(&xPos);
    yDevValue = this->getStddev(&yPos);


    if(xDevValue < 2 && yDevValue < 2) {
        *isFall = true;
    }

    if (!isFall && secondsSinceStart > 2) {
        *isChecking = false;
    }
}

void FallDetector::analyzePosition(Mat* frame, vector<double>* thetaRatio, vector<double>* aRatio, vector<double>* bRatio, vector<double>* xPos, vector<double>* yPos, vector<Point> largestContour) {
    Rect boundingRectangle = boundingRect(largestContour);
    rectangle(*frame, boundingRectangle, Scalar(0, 255, 0), 2);

    if(largestContour.size() > 5) {

        RotatedRect e = fitEllipse(largestContour);
        ellipse( *frame, e, Scalar(255, 0, 0), 2 );

        thetaRatio->push_back(e.angle);

        double a = (double)e.size.width / 2.0;
        double b = (double)e.size.height / 2.0;
        aRatio->push_back(a);
        bRatio->push_back(b);

        double x = e.center.x;
        double y = e.center.y;
        xPos->push_back(x);
        yPos->push_back(y);

        if(thetaRatio->size() > 10) {
            thetaRatio->erase(thetaRatio->begin());
        }

        if(aRatio->size() > 10) {
            aRatio->erase(aRatio->begin());
        }
        if(bRatio->size() > 10) {
            bRatio->erase(bRatio->begin());
        }
        if(xPos->size() > 10) {
            xPos->erase(xPos->begin());
        }
        if(yPos->size() > 10) {
            yPos->erase(yPos->begin());
        }
    }
}

void FallDetector::checkMovementAfterFall(bool* toBeChecked, bool *isFall, vector<double> xPos, vector<double> yPos) {
    double xDevValue = this->getStddev(&xPos);
    double yDevValue = this->getStddev(&yPos);

    cout << "X pos: " << xDevValue;
    cout << ", Y pos: " << yDevValue << "\n";

    if(xDevValue > 2 && yDevValue > 2) {
        *isFall = false;
        *toBeChecked = false;
    }
}