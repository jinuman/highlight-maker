/*
소스 동영상의 Play를 담당하는 class VideoPlayer
ffmpeg 라이브러리를 테스트할 때 주로 사용되는 ffplay.exe 사용
*/
#pragma once
#include "MyThread.h"
#include <iostream>
using namespace std;

class VideoPlayer : public MyThread {
public:
	VideoPlayer();
	void setSourcePath(string m_src_path);
	virtual void process();
private:
	string src_path;
};