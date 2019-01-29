#pragma once
#include "MyThread.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <chrono>
using namespace std;
using namespace cv;
using namespace chrono;

class Detector : public MyThread {
public:
	virtual void process();
	vector<int> getTimeLog();
	bool initializeCascade();

private:
	//variable
	VideoCapture cap;
	//img : 원본이미지
	//gray : 원본이미지를 gray로 바꾼 이미지, detection에 사용
	Mat img;
	Mat gray;
	//얼굴의 각 부위를 검출할 cascade 선언

	//1. face_cascade : 얼굴을 검출할 cascade
	//미소와 입을 검출할 때, 얼굴 전체의 부위에서 검출하게 되면 인식의 정확도가 떨어진다(하관부위가 아닌 다른 부위에서 검출됨)
	//따라서 얼굴의 범위를 하관으로 변경해주고, 미소와 입을 검출한다
	//2. mouth_cascade : 입을 검출할 cascade
	//3. smile_cascade : 미소를 검출할 cascade
	//4. eye_cascade : 눈을 검출할 cascade

	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;
	CascadeClassifier smile_cascade;
	CascadeClassifier mouth_cascade;

	//int타입(초)의 시간로그를 기록하는 vector
	vector<int> time_log;
};