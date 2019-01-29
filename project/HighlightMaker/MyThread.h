#pragma once
#include <thread>
using namespace std;

/*
������ ���� ó���ϱ� ���� class MyThread
run simultaneously..
C++11 ���̺귯�������� �ü���� �Լ��� ������� �ʰ� 
��ü������ ��Ƽ�����带 ���� ����
std::thread thread
�� ������� ������ �����Ҷ����� �����带 �����Ѵ�
�׷��Ƿ� ��ü������ ������������
*/
class MyThread 
{
public:
	MyThread();
	~MyThread();
	void start();	//�������� process ����
	void end();		//����
	bool isEnd();	//isEndParam return
	void join();	//�����尡 �����ؾ� main�� �����ϵ��� main�� ������Ŵ

protected:
	virtual void process() = 0;	//process �Լ��� �ڽ�Ŭ�������� ������

private:
	bool isEndParam;	
	std::thread thread; 
};