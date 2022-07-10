// cam test program, should add more 
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <tuple>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Mat frame;
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return 0;
    for(;;)
    {
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow("Camera", frame);
          if( (waitKey(10)%256) == 27 ) break; // waitKeypatch: check for 10ms: then stop capturing by pressing ESC=27
    }
    // the camera will be closed automatically upon exit
    //cap.close();
    return 0;
}
