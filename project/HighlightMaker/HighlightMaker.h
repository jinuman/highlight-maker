/*
Video Edit �κ�
video�� split�ϰ� concatenate�ϴ� class HighlightMaker
������ highlight#.avi�� �̾
���������� result.avi ����
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class HighlightMaker {
public:
	//time_length��ŭ hightlight#.avi ����
	void makeHighlightVideo(string src_path, string dst_path, vector<int> time_log, string time_length);
};