#pragma once
#include <Windows.h>
#include <string>
#include "VideoPlayer.h"
#include "Detector.h"
#include "HighlightMaker.h"

/*
���α׷��� ���� class Manager
Manager Ŭ������ 
Video�� Play���ִ� VideoPlayer Ŭ������
Webcam���� Smile�� �ν��ϴ� Detector Ŭ������
Video�� �����ϰ� ��ġ�� HighlightMaker Ŭ������ �����Ѵ�
*/

class Manager {
public:
	Manager(string m_src_path, string m_dst_path, string m_time_length);
	void make();
	void initialize();		//opencv cascade load Ȯ��

private:
	string src_path;		//�ҽ������� ���
	string dst_path;		//��������� ���
	string time_length;		//split ���� �ð� ����
	VideoPlayer videoplayer;		
	Detector detector;		
	HighlightMaker highlightmaker;
};