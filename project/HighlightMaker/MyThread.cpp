#include "MyThread.h"

MyThread::MyThread()
{
	isEndParam = false;
}


MyThread::~MyThread()
{
}

void MyThread::start()
{
	thread = std::thread(&MyThread::process, this);
}

void MyThread::end() 
{
	isEndParam = true;
}

bool MyThread::isEnd()
{
	return isEndParam;
}

void MyThread::join()
{
	thread.join();
}