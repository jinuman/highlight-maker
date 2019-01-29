#pragma once
#include <Windows.h>
#include <string>
#include "VideoPlayer.h"
#include "Detector.h"
#include "HighlightMaker.h"

/*
프로그램의 동작 class Manager
Manager 클래스는 
Video를 Play해주는 VideoPlayer 클래스와
Webcam으로 Smile을 인식하는 Detector 클래스와
Video를 편집하고 합치는 HighlightMaker 클래스를 포함한다
*/

class Manager {
public:
	Manager(string m_src_path, string m_dst_path, string m_time_length);
	void make();
	void initialize();		//opencv cascade load 확인

private:
	string src_path;		//소스파일의 경로
	string dst_path;		//결과파일의 경로
	string time_length;		//split 파일 시간 정보
	VideoPlayer videoplayer;		
	Detector detector;		
	HighlightMaker highlightmaker;
};