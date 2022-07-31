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
#include "FallChecker.cpp"

using namespace std;
using namespace cv;





int main(){
    FallChecker start;
    start.checker();
    return 0;
}


