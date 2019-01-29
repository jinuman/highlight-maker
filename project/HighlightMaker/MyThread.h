#pragma once
#include <thread>
using namespace std;

/*
쓰레드 별로 처리하기 위한 class MyThread
run simultaneously..
C++11 라이브러리에서는 운영체제의 함수를 사용하지 않고 
자체적으로 멀티쓰레드를 구현 가능
std::thread thread
이 쓰레드는 스스로 종료할때까지 쓰레드를 유지한다
그러므로 자체적으로 종료시켜줘야함
*/
class MyThread 
{
public:
	MyThread();
	~MyThread();
	void start();	//쓰레드의 process 실행
	void end();		//종료
	bool isEnd();	//isEndParam return
	void join();	//쓰레드가 종료해야 main도 종료하도록 main을 보류시킴

protected:
	virtual void process() = 0;	//process 함수를 자식클래스에서 재정의

private:
	bool isEndParam;	
	std::thread thread; 
};