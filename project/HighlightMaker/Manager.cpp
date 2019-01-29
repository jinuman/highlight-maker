#include "Manager.h"

Manager::Manager(string m_src_path, string m_dst_path, string m_time_length) {
	src_path = m_src_path;
	dst_path = m_dst_path;
	time_length = m_time_length;
}

void Manager::make() {
	//initialize part
	initialize();

	//start
	//ffplay.exe와 웹캠을 동시에 구동
	videoplayer.start();
	detector.start();

	//wait until player is end
	videoplayer.join();
	//player를 끄면 웹캠을 종료
	detector.end();
	
	//wait until thread is end
	detector.join();

	//highlightMaker로 detector의 time_log를 parameter로 넘겨준다
	highlightmaker.makeHighlightVideo(src_path, dst_path, detector.getTimeLog(), time_length);
}

void Manager::initialize() {
	if (!detector.initializeCascade()) {
		cout << "load cascade fail" << endl;
		exit(0);
	}
	videoplayer.setSourcePath(src_path);
}