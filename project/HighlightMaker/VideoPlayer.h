/*
�ҽ� �������� Play�� ����ϴ� class VideoPlayer
ffmpeg ���̺귯���� �׽�Ʈ�� �� �ַ� ���Ǵ� ffplay.exe ���
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