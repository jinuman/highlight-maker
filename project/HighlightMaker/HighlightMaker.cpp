#include "HighlightMaker.h"

void HighlightMaker::makeHighlightVideo(string src_path, string dst_path, vector<int> time_log, string time_length)
{
	//시,분,초 계산에 필요한 변수 선언
	int s_hour = 0;
	int s_minute = 0;
	int s_second = 0;
	int s_temp = 0;
	//시,분,초를 string으로 표현
	string str_temp;

	ofstream outf("list.txt");
	outf.clear();
	int count = 0;
	for (auto it = time_log.begin(); it != time_log.end(); it++)
	{
		count++;
		//시,분,초 계산
		s_temp = *it;
		s_hour = s_temp / 3600;
		s_temp %= 3600;
		s_minute = s_temp / 60;
		s_temp %= 60;
		s_second = s_temp;
		str_temp = to_string(s_hour) + ":" + to_string(s_minute) + ":" + to_string(s_second);

		string filename = ".\\video\\highlight" + to_string(count) + ".avi";
		string command = ".\\bin\\ffmpeg.exe -y -i troublemaker.avi -c copy -ss " + str_temp + " -t " + time_length  + " " + filename;
		system(command.c_str());

		//split video들을 합치기 위한 작업
		//split file들을 list.txt에 저장
		string fileCommand = "file '" + filename + "'\n";
		outf << fileCommand;
	}
	outf.close();
	//list.txt에 저장된 file들을 concatenate 해서 result.avi 생성
	if (time_log.size() != 0) {
		string resultCommand = ".\\bin\\ffmpeg.exe -y -f concat -safe 0 -i list.txt -c copy .\\video\\result.avi";
		system(resultCommand.c_str());
	}
}