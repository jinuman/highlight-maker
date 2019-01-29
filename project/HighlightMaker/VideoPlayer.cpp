#include "VideoPlayer.h"

VideoPlayer::VideoPlayer() {
	src_path = "";
}

void VideoPlayer::setSourcePath(string m_src_path) {
	src_path = m_src_path;
}

void VideoPlayer::process()
{
	if (src_path.compare("") == 0) {
		cout << "src path not exist" << endl;
		exit(0);
	}

	//ffplay.exe로 소스파일 실행
	string ffplay_command = ".\\bin\\ffplay.exe " + src_path;
	system(ffplay_command.c_str());
	
	end();	// 종료하면 isEndParam = true;
}