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
	//img : �����̹���
	//gray : �����̹����� gray�� �ٲ� �̹���, detection�� ���
	Mat img;
	Mat gray;
	//���� �� ������ ������ cascade ����

	//1. face_cascade : ���� ������ cascade
	//�̼ҿ� ���� ������ ��, �� ��ü�� �������� �����ϰ� �Ǹ� �ν��� ��Ȯ���� ��������(�ϰ������� �ƴ� �ٸ� �������� �����)
	//���� ���� ������ �ϰ����� �������ְ�, �̼ҿ� ���� �����Ѵ�
	//2. mouth_cascade : ���� ������ cascade
	//3. smile_cascade : �̼Ҹ� ������ cascade
	//4. eye_cascade : ���� ������ cascade

	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;
	CascadeClassifier smile_cascade;
	CascadeClassifier mouth_cascade;

	//intŸ��(��)�� �ð��α׸� ����ϴ� vector
	vector<int> time_log;
};