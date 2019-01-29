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
	//ffplay.exe�� ��ķ�� ���ÿ� ����
	videoplayer.start();
	detector.start();

	//wait until player is end
	videoplayer.join();
	//player�� ���� ��ķ�� ����
	detector.end();
	
	//wait until thread is end
	detector.join();

	//highlightMaker�� detector�� time_log�� parameter�� �Ѱ��ش�
	highlightmaker.makeHighlightVideo(src_path, dst_path, detector.getTimeLog(), time_length);
}

void Manager::initialize() {
	if (!detector.initializeCascade()) {
		cout << "load cascade fail" << endl;
		exit(0);
	}
	videoplayer.setSourcePath(src_path);
}