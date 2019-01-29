#include "Detector.h"

void Detector::process()
{
	//���� ��ķ���� ������ ĸó�Ѵ�
	cap.open(0);

	//������ 960*640���� ����
	cap.set(CAP_PROP_FRAME_WIDTH, 960);
	cap.set(CAP_PROP_FRAME_HEIGHT, 640);

	int smile_cnt = 0;

	//�ð��� �����ϱ� ���� ���� ����
	//start : �Կ� ���۽ð�
	//end : �� frame���� �̼� ������ �� �ð�
	//end - start : ���� frame���� �̼� ������ �� ������ �ҿ�� �ð�
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end;

	//5���� ���ӵ� �ð��� ����ϴ� vector
	vector<int> five_seconds;
	//intŸ��(��)�� �ð��α׸� stringŸ��(00:00:00)�� ����ϴ� vector
	vector<string> str_time_log;//?

	while (!isEnd())
	{

		//��ķ���� ���� �̹����� MatŸ������ ����
		cap >> img;

		cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

		//���� ũ��� ������ �� ��� ó���ӵ��� ����, ��ǻ� �ǽð� ������ �Ұ���
		//�̸� �ذ��ϱ����� �����̹����� ũ�⸦ �����Ѵ�
		resize(img, img, Size(480, 320));

		//�����̹����� ����̹����� �����Ͽ� gray�� �޴´�
		cvtColor(img, gray, CV_BGR2GRAY);

		//1. faces : ���� ����(���簢��)�� ������ vector
		//2. mouths : ���� ����(���簢��)�� ������ vector
		//3. smiles : �̼��� ����(���簢��)�� ������ vector
		vector<Rect> faces;
		vector<Rect> mouths;
		vector<Rect> smiles;


		// �� ����
		// parameters
		// detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3,
		//                    int flags=0, Size minSize=Size(), Size maxSize=Size())
		// 1. image  : ������ ��� �̹���
		// 2. objects: ����� ������ �����ϴ� �����̳�
		// 3. scaleFactor : ��� �̹����� ���ҵǴ� ����(ex. 1.05 : ũ�Ⱑ 5% �پ��)
		// 4. minNeighbors :  
		// 5. minSize : ����� ��ü�� �ּ� ũ��
		// 6. maxSize : ����� ��ü�� �ִ� ũ��

		face_cascade.detectMultiScale(gray, faces, 1.1, 10, 0 | CV_HAAR_SCALE_IMAGE, Size(80, 40));


		//�̼Ҵ� ���� �ϰ����� ����ǹǷ�
		//����� ���� ������ �ϴܺη� �����Ѵ�

		for (int i = 0; i < faces.size(); i++) {
			faces[i].y = faces[i].y + (faces[i].height) * 2 / 3;
			faces[i].height /= 3;
		}


		//����� ���� ������ �׸���
		//����� ���� �����ȿ��� �̼Ҹ� �����Ѵ�

		for (int i = 0; i < faces.size(); i++)
		{
			//����� ���� ������ ���簢������ �׸���
			rectangle(img, faces[i], Scalar(255, 0, 0), 1, 8, 0);
			//����� �����ȿ��� �̼Ҹ� �����Ѵ�
			Mat faceROI = img(faces[i]);
			smile_cascade.detectMultiScale(faceROI, smiles, 1.6, 15, 0 | CASCADE_SCALE_IMAGE, Size(10, 5));
			//�̼Ұ� ����Ǹ�(smiles.size()>0)
			for (size_t k = 0; k < smiles.size(); k++) {
				//�̼Ұ� ����� �ð� 
				end = system_clock::now();
				//�̼Ұ� ����Ǳ���� �ɸ��ð�
				duration<double> Sec = end - start;
				//�̼Ұ� ����Ǳ���� �ɸ��ð��� intŸ������ ��ȯ
				int total_seconds = Sec.count();
				int time = Sec.count();
				//��,��,�� ���
				int hour = total_seconds / 3600;
				total_seconds %= 3600;
				int minutes = total_seconds / 60;
				int seconds = total_seconds % 60;

				bool flag = true;


				//�α׸� ����ϴ� �˰���
				//5�ʵ��� ����� �α׸� ���
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
						cout << "log ��ϵ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-------->" << five_seconds[0] << endl;
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

				//�̼� ���� �ð� ���
				cout << "smile detected! -> " << hour << ":" << minutes << ":" << seconds << endl;

				//����� �̼��� ������ ���簢������ �׸���
				rectangle(faceROI, smiles[k], Scalar(0, 0, 255), 1, 8, 0);
				smile_cnt++;
			}
		}



		//�ٿ��� ���� �̹����� ũ�⸦ �ٽ� Ű���
		resize(img, img, Size(640, 420));
		// �̹��� ���
		imshow("webcam", img);
		char ch = waitKey(1);

		//ecs�� Ű�� webcam ����
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