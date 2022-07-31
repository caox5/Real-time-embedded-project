#pragma once 

#include "FallChecker.h"
    void FallChecker::checker(){
    VideoCapture cap(0);

    Ptr<BackgroundSubtractorMOG2> pMOG2 = createBackgroundSubtractorMOG2();
    
    bool toBeChecked = false; //Determine if the object requires further testing for falls.
    bool isFall = false; //Determining whether an object has fallen

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Mask", WINDOW_AUTOSIZE);

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

        // Pre-processing of images. Transforms a color frame into a black and white frame showing only the foreground and background.
        // Steps: 1. Convert to grayscale map. 
        // 2. Difference adjacent frames to obtain the difference map. 
        // 3. Substitute the difference map into the grayscale threshold model to distinguish between foreground and background. 
        // 4. Do dilate and erode on the image.
        pMOG2->setHistory(20);
        pMOG2->setNMixtures(10);
        pMOG2->setDetectShadows(false);
        pMOG2->apply(frame, fgMaskMOG2);
        pMOG2->getBackgroundImage(backgroundImg);
        
        
        findContours(fgMaskMOG2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0)); // Fits and creates the contour points of the object.

        if(!toBeChecked) {
            largestContour.clear();
        }

        double maxArea = 0.0;

        //Select the object with the largest contour area 
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

        movementCoefficientValue = fallDetector.getMovementCoefficient(&fgMaskMOG2, &history); //Calculating the coefficient of motion of an object
        thetaRatioValue = fallDetector.getStddev(&thetaRatio);
        aRatioValue = fallDetector.getStddev(&aRatio);
        bRatioValue = fallDetector.getStddev(&bRatio); //Calculate the standard deviation of θ, a, b of the ellipse

        //cout << "Coeff: " << movementCoefficientValue << ",  Theta: " << thetaRatioValue << ", A: " << aRatioValue << ", B: " << bRatioValue << endl;

        //Steps 'a' and 'b' for determining falls
        if(!toBeChecked) {
            if(movementCoefficientValue > 80 && thetaRatioValue > 20 && (aRatioValue / bRatioValue) > 0.9 ) {
                toBeChecked = true;
                start = time(0);
            }
        }

        //Step 'c' for determining falls
        if(toBeChecked) {
            fallDetector.checkIfStaysInPlace(start, &toBeChecked, &isFall, xPos, yPos);
        }

        //Reset the parameters
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

    }

    cap.release();
    frame.release();
    destroyAllWindows(); 
}
