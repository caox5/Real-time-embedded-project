<h1 align="center"><b>Fall Detection</b></h1><br><br>
<p align="center">
<img alt="Screenshot 2022-04-17 at 22 27 20" src="https://user-images.githubusercontent.com/50026800/163732671-387926f1-9513-4b1d-b710-4ed6c5dd5bbc.png" width="200px" height="200px"></p><br><br>

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
            <li><a href="#Software and programming language">Software and programming language</a>
            <li><a href="#Hardware">Hardware</a>
            <li><a href="#Concept">Concept</a>
        </ul>
    <li><a href="#Quick start">Quick start</a>
        <ul>
            <li><a href="#Connect hardware">Connect hardware</a>
            <li><a href="#Installation">Installation</a>
        </ul>
</ul>
            
## Introduction

This program is mainly used for elder people to keep them in safe, that is because most of them are move slowly and once they falling down, they may hard to get up and even life-threatening. This project could do the falling detection and warning the guardian by sending the realtime message or calling them. Additionally, in order to make sure someone will help them after they falling down, developers will send the emails to their families after the fall detection.

### Software and programming language
 - C++
 - Opencv
 
### Hardware
 - Raspberry Pi 4 Model B; Memory: 2GB 
    - <p align="center"><img alt="Screenshot 2022-04-18 at 10 45 01" src="https://user-images.githubusercontent.com/50026800/163790690-ccf2e6ba-62aa-4cad-a626-eb86eb2bd2a8.png"  width="200px" height="150px"></p>
   - purchase link: https://thepihut.com/collections/raspberry-pi/products/raspberry-pi-4-model-b?variant=20064052674622
 - Raspberry Pi Camera Module V2.1 
   - <p align="center"><img  alt="Screenshot 2022-04-18 at 10 45 17" src="https://user-images.githubusercontent.com/50026800/163790875-b79c394a-8754-49ad-b413-951cd316d8dd.png" width="200px" height="150px"></p>
   - purchase link: https://thepihut.com/collections/raspberry-pi-camera/products/raspberry-pi-camera-module
 - 32 GB Micro-SD card
 
 ### Concept
  - There are three steps:
    - 1. <b>Movement coefficient analysis</b>: the camera should have the ability to distinguish whether the motion is falling or normal movement, when the value is larger than 0.8, it assumes as falling, additionally, Sudden movements or walk perpendicular also have the high movement coefficient.
    - 2. <b>Human shape analysis</b>: using an ellipse to represent a person, when a person falls, the sudden change of orientation and ratio of the major and minor axis of the ellipse would perfectly represent that person's movement. In this case, using standard deviation to calculate the value is the average amount of variability in the dataset. Therefore, when people are falling, the angle theta and axis ratio a/b will be higher than normal movement, based on tests and datasets online, if the angle theta is greater than 15 degrees and the axis ratio is larger than 0.9, it could be considered falling.
    - <p align="center"><img alt="Screenshot 2022-04-18 at 10 45 01" src="https://user-images.githubusercontent.com/50026800/163798022-d8dc20c8-7104-4151-a761-fc2b66bb44fa.jpeg"  width="650px" height="400px"></p>
    - 3. <b>Remain motionless</b>: the last algorithm in judging whether it really falls or not, the coefficient motion should be less than 0.2 from the twentieth and the thirtieth frame of the video after falling is detected. which means that the time interval is from 0.83 to 1.25 seconds. 

## Quick start
  - This part will tell you how to connect hardwares and install the packages to use
 
### Connect hardware
<p align="center">
<img alt="Screenshot 2022-04-17 at 22 27 20" src="https://user-images.githubusercontent.com/50026800/163800636-5de2369b-844a-4926-9138-57d88edb5216.jpeg" width="500px" height="400px"></p>

### Installation


