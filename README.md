<h1 align="center"><b>Fall Detection</b></h1><br><br>
<p align="center">
<img alt="Screenshot 2022-04-17 at 22 27 20" src="https://user-images.githubusercontent.com/50026800/163732671-387926f1-9513-4b1d-b710-4ed6c5dd5bbc.png" width="200px" height="200px"></p><br><br>

https://user-images.githubusercontent.com/97770910/164187842-7714061e-b3e5-4bea-a51c-2a16744592f4.mp4

<p align="center">
    <a href="https://github.com/caox5/Real-time-embedded-project/graphs/contributors" alt="Contributors">
        <img src="https://img.shields.io/github/contributors/SunitaAcharya/myYogaMate.svg?style=flat&amp;label=Contributors&amp;maxAge=86400" alt="Contributors" /></a>
    <a href="https://github.com/caox5/Real-time-embedded-project/issues" alt="Issues">
        <img src="https://img.shields.io/github/issues/LancerMar/Guitartuner.svg" /></a>
    <a href="https://github.com/caox5/Real-time-embedded-project/blob/main/LICENSE" alt="License">
        <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License" /></a>
</p>

## Contents
<ul>
    <li><a href="#Introduction">Introduction</a>
        <ul>
            <li><a href="#Software-and-programming-language">Software and programming language</a>
            <li><a href="#Hardware">Hardware</a>
            <li><a href="#Concept">Concept</a>
        </ul>
    <li><a href="#Quick start">Quick start</a>
        <ul>
            <li><a href="#Connect-hardware">Connect hardware</a>
            <li><a href="#Installation">Installation</a>
            <li><a href="#OpenCV-Test">OpenCV Test</a>
            <li><a href="#Run-Fall-Detection">Run Fall Detection</a>
        </ul>
    <li><a href="#Social-Media">Social Media</a>
    <li><a href="#Credits">Credits</a>
    <li><a href="#Reference">Reference</a>
</ul>
            
## Introduction

This program is mainly used for elder people to keep them in safe, that is because most of them are move slowly and once they falling down, they may hard to get up and even life-threatening. This project could do the falling detection and warning the guardian by sending the realtime message or calling them. Additionally, in order to make sure someone will help them after they falling down, developers will send the emails to their families after the fall detection (use Python to send email).

### Software and programming language

 - C++
 - Opencv
 - Debian 10
 
### Hardware
 - Raspberry Pi 4 Model B; Memory: 2GB 
    - <p align="center"><img alt="Screenshot 2022-04-18 at 10 45 01" src="https://user-images.githubusercontent.com/50026800/163790690-ccf2e6ba-62aa-4cad-a626-eb86eb2bd2a8.png"  width="200px" height="150px"></p>
   - purchase link: https://thepihut.com/collections/raspberry-pi/products/raspberry-pi-4-model-b?variant=20064052674622
 - Raspberry Pi Camera Module V2.1 
   - <p align="center"><img  alt="Screenshot 2022-04-18 at 10 45 17" src="https://user-images.githubusercontent.com/50026800/163790875-b79c394a-8754-49ad-b413-951cd316d8dd.png" width="200px" height="150px"></p>
   - purchase link: https://thepihut.com/collections/raspberry-pi-camera/products/raspberry-pi-camera-module
 - 64 GB Micro-SD card (16 GB/32 GB Micro-SD card also works)
 - monitor (necessary)
 - keyboard (not necessary)
 - mouse (not necessary)
 
 ### Concept
  - There are three steps[^1][^2]:
    - 1. <b>Movement coefficient analysis</b>: the camera should have the ability to distinguish whether the motion is falling or normal movement, when the value is larger than 0.8, it assumes as falling, additionally, Sudden movements or walk perpendicular also have the high movement coefficient.
    - 2. <b>Human shape analysis</b>: using an ellipse to represent a person, when a person falls, the sudden change of orientation and ratio of the major and minor axis of the ellipse would perfectly represent that person's movement. In this case, using standard deviation to calculate the value is the average amount of variability in the dataset. Therefore, when people are falling, the angle theta and axis ratio a/b will be higher than normal movement, based on tests and datasets online, if the angle theta is greater than 15 degrees and the axis ratio is larger than 0.9, it could be considered falling.
    - <p align="center"><img alt="Screenshot 2022-04-18 at 10 45 01" src="https://user-images.githubusercontent.com/50026800/163798022-d8dc20c8-7104-4151-a761-fc2b66bb44fa.jpeg"  width="650px" height="400px"></p>
    - 3. <b>Remain motionless</b>:Monitor whether the coordinates of the center point of the ellipse remain stable for several consecutive frames (calculate the mean value of the standard deviation of the x and y coordinates over a period of time), and judge whether the object moves according to this.
## Quick start
  - This part will tell you how to connect hardwares and install the packages to use
 
### Connect hardware
(Important!!!) Follow the [link](https://projects.raspberrypi.org/en/projects/getting-started-with-picamera/1) to set up the camera module on Raspberry Pi.
<p align="center">
<img alt="Screenshot 2022-04-17 at 22 27 20" src="https://user-images.githubusercontent.com/50026800/163800636-5de2369b-844a-4926-9138-57d88edb5216.jpeg" width="500px" height="400px"></p>


### Installation
Prerequisites: Have the latest Raspbian installed on your Raspberry Pi
 
Follow the steps to install [OpenCV 4](https://opencv.org/) with Python and C++ support on Raspberry Pi.
- 1 . Download the already built OpenCV 4 from [article](https://github.com/sol-prog/raspberry-pi-opencv/releases/), there are four versions, choose the proper version for your Pi. <b>I use full GUI version on a RPi 2 and up</b>. If you are using other versions, make sure you change the file name properly.
- 2 . Open terminal and download it:

        wget https://github.com/sol-prog/raspberry-pi-opencv/releases/download/opencv4rpi2.1/opencv-4.1.0-armhf.tar.bz2        
- 3 . extract the archive:

        tar xvf opencv-4.1.0-armhf.tar.bz2 
- 4 . move the resulting opencv-4.1.0 folder to /opt and then remove the archive:

        sudo mv opencv-4.1.0 /opt
        rm opencv-4.1.0-armhf.tar.bz2
- 5 . Install couple of necessary libraries on OpenCV:
        
        sudo apt install cmake
        sudo apt install libtiff-dev zlib1g-dev
        sudo apt install libjpeg-dev libpng-dev
        sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
        sudo apt-get install libxvidcore-dev libx264-dev
        sudo apt install python-numpy python3-numpy
- 6 . If you are using GUI version, install these two libraries, else ignore it:
          
        sudo apt install libgtk-3-dev libcanberra-gtk3-dev
- 7 . Add OpenCV to the system library path and run it on root:
        
        cd ~
        echo 'export LD_LIBRARY_PATH=/opt/opencv-4.1.0/lib:$LD_LIBRARY_PATH' >> .bashrc
        . .bashrc
- 8 . Restart the terminal and then create symbolic links that will allow Python to load the newly created libraries:
        
        sudo ln -s /opt/opencv-4.1.0/lib/python2.7/dist-packages/cv2 /usr/lib/python2.7/dist-packages/cv2
        sudo ln -s /opt/opencv-4.1.0/lib/python3.7/dist-packages/cv2 /usr/lib/python3/dist-packages/cv2
- 9 . Install git
        
        sudo apt install git
- 10 . Clone a simple config file useful if you want to be able to use OpenCV from C++:
        
        git clone https://gist.github.com/sol-prog/ed383474872958081985de733eaf352d opencv_cpp_compile_settings
        cd opencv_cpp_compile_settings/
        sudo cp opencv.pc /usr/lib/arm-linux-gnueabihf/pkgconfig
        cd ~
        rm -rf opencv_cpp_compile_settings/
 <b>When you done these steps, you should be able to use the OpenCV library from C++ or Python. You could use following test case on next part.</b>
 
 ### OpenCV Test
 - (Optional)You can download the code on your Pi to test:
 
        git clone https://github.com/caox5/Real-time-embedded-project.git
        cd Real-time-embedded-project/test/
 - Build and Run C++ test: 
 
       g++ video.cpp -o video `pkg-config --cflags --libs opencv`
        ./video

### Run Fall Detection[^3]
Install the Fall Detection:
Make sure you finish the [Installation Guide](https://github.com/caox5/Real-time-embedded-project/wiki/Installation-Guide), if everything works properly, then back to this step!

- Download the Fall detection from the Github 

        git clone https://github.com/caox5/Real-time-embedded-project
        cd Real-time-embedded-project
- You can compile the our project by using following command on RaspberryPi
        
        mkdir build
        cd build
        cmake ..
        make
- The 'project' is the executable file, run it

        ./FallDetectionRpi
- You should see the following pictures: 
<p align="center"><img alt="Screenshot 2022-04-18 at 21 02 59" src="https://user-images.githubusercontent.com/50026800/163869484-7a83954a-4e22-440d-bf1b-c2e009268b84.png" width="500px" height="400px"></p>

## Social Media
 Follow us on:
 - Bilibili
 - YouTube

## Credits
 The fall detection progect is maintained by the PTEP_Progect_Team 13, from University of Glasgow. The members of the group are:
 - Xin Cao https://github.com/caox5
 - Ying Li https://github.com/807river
 - Dingrui Chen https://github.com/2646944C
 - Jingben Xu https://github.com/Xubenbenn
 
## Reference
[^1]: https://www.researchgate.net/publication/221910572_Video_Surveillance_for_Fall_Detection
[^2]: https://ieeexplore.ieee.org/abstract/document/6240925
[^3]: https://github.com/ashwani227/humanBodyFallDetection

        
        
