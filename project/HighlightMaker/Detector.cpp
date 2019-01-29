#include "Detector.h"

void Detector::process()
{
	//내장 웹캠으로 영상을 캡처한다
	cap.open(0);

	//영상은 960*640으로 세팅
	cap.set(CAP_PROP_FRAME_WIDTH, 960);
	cap.set(CAP_PROP_FRAME_HEIGHT, 640);

	int smile_cnt = 0;

	//시간을 측정하기 위한 변수 선언
	//start : 촬영 시작시간
	//end : 각 frame에서 미소 검출이 된 시간
	//end - start : 현재 frame에서 미소 검출이 될 때까지 소요된 시간
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end;

	//5초의 연속된 시간을 기록하는 vector
	vector<int> five_seconds;
	//int타입(초)의 시간로그를 string타입(00:00:00)을 기록하는 vector
	vector<string> str_time_log;//?

	while (!isEnd())
	{

		//웹캠에서 받은 이미지를 Mat타입으로 받음
		cap >> img;

		cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

		//원본 크기로 검출을 할 경우 처리속도가 느려, 사실상 실시간 감지가 불가능
		//이를 해결하기위해 원본이미지의 크기를 변경한다
		resize(img, img, Size(480, 320));

		//원본이미지를 흑백이미지로 변경하여 gray가 받는다
		cvtColor(img, gray, CV_BGR2GRAY);

		//1. faces : 얼굴의 구역(직사각형)을 저장할 vector
		//2. mouths : 입의 구역(직사각형)을 저장할 vector
		//3. smiles : 미소의 구역(직사각형)을 저장할 vector
		vector<Rect> faces;
		vector<Rect> mouths;
		vector<Rect> smiles;


		// 얼굴 검출
		// parameters
		// detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3,
		//                    int flags=0, Size minSize=Size(), Size maxSize=Size())
		// 1. image  : 검출할 대상 이미지
		// 2. objects: 검출된 영역을 저장하는 컨테이너
		// 3. scaleFactor : 대상 이미지가 감소되는 정도(ex. 1.05 : 크기가 5% 줄어듬)
		// 4. minNeighbors :  
		// 5. minSize : 검출될 물체의 최소 크기
		// 6. maxSize : 검출될 물체의 최대 크기

		face_cascade.detectMultiScale(gray, faces, 1.1, 10, 0 | CV_HAAR_SCALE_IMAGE, Size(80, 40));


		//미소는 얼굴의 하관에서 검출되므로
		//검출된 얼굴의 영역을 하단부로 제한한다

		for (int i = 0; i < faces.size(); i++) {
			faces[i].y = faces[i].y + (faces[i].height) * 2 / 3;
			faces[i].height /= 3;
		}


		//검출된 얼굴의 영역을 그리고
		//검출된 얼굴의 영역안에서 미소를 검출한다

		for (int i = 0; i < faces.size(); i++)
		{
			//검출된 얼굴의 영역을 직사각형으로 그린다
			rectangle(img, faces[i], Scalar(255, 0, 0), 1, 8, 0);
			//검출된 영역안에서 미소를 검출한다
			Mat faceROI = img(faces[i]);
			smile_cascade.detectMultiScale(faceROI, smiles, 1.6, 15, 0 | CASCADE_SCALE_IMAGE, Size(10, 5));
			//미소가 검출되면(smiles.size()>0)
			for (size_t k = 0; k < smiles.size(); k++) {
				//미소가 검출된 시간 
				end = system_clock::now();
				//미소가 검출되기까지 걸린시간
				duration<double> Sec = end - start;
				//미소가 검출되기까지 걸린시간을 int타입으로 변환
				int total_seconds = Sec.count();
				int time = Sec.count();
				//시,분,초 계산
				int hour = total_seconds / 3600;
				total_seconds %= 3600;
				int minutes = total_seconds / 60;
				int seconds = total_seconds % 60;

				bool flag = true;


				//로그를 기록하는 알고리즘
				//5초동안 웃어야 로그를 기록
				if (five_seconds.size() != 0)
				{
					auto r_it = five_seconds.rbegin();
					if (time == *(r_it))
						;
					else if (time == *(r_it)+1)
					{
						five_seconds.push_back(time);
					}
					else
					{
						flag = false;
					}

					if (five_seconds.size() == 6)
					{
						time_log.push_back(five_seconds[0]);
						auto it = time_log.rbegin();
						cout << "log 기록됨!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-------->" << five_seconds[0] << endl;
						//last_log_time = five_seconds[5];
						flag = false;
					}
				}
				else
				{
					five_seconds.push_back(time);
				}

				if (!flag)
				{
					five_seconds.clear();
				}

				//미소 검출 시간 출력
				cout << "smile detected! -> " << hour << ":" << minutes << ":" << seconds << endl;

				//검출된 미소의 영역을 직사각형으로 그린다
				rectangle(faceROI, smiles[k], Scalar(0, 0, 255), 1, 8, 0);
				smile_cnt++;
			}
		}



		//줄였던 원본 이미지의 크기를 다시 키운다
		resize(img, img, Size(640, 420));
		// 이미지 출력
		imshow("webcam", img);
		char ch = waitKey(1);

		//ecs를 키면 webcam 종료
		if (ch == 27) break;       // 27 == ESC key

	}
	cap.release();
}

bool Detector::initializeCascade()
{
	if (!face_cascade.load(".\\xml\\haarcascade_frontalface_alt.xml"))
		return false;
	//if (!eye_cascade.load(".\\xml\\haarcascade_eye_tree_eyeglasses.xml"))
	//	return false;
	if (!smile_cascade.load(".\\xml\\haarcascade_smile.xml"))
		return false;
	if (!mouth_cascade.load(".\\xml\\Mouth.xml"))
		return false;
	return true;
}

vector<int> Detector::getTimeLog()
{
	return time_log;
}