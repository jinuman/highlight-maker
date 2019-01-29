/*
Video Edit 부분
video를 split하고 concatenate하는 class HighlightMaker
생성된 highlight#.avi를 이어서
최종적으로 result.avi 생성
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class HighlightMaker {
public:
	//time_length만큼 hightlight#.avi 생성
	void makeHighlightVideo(string src_path, string dst_path, vector<int> time_log, string time_length);
};