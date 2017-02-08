#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QThread>
#include <vector>
#include <QFileDialog>
using namespace std;
#define _USE_OPENCV
#include "EasyKinect.h"
#include "MatStream.h"

class ViewModel : public QThread
{
	Q_OBJECT
	public:
		ViewModel();
		void stop();
		HRESULT Init();
	protected:
		void run();
	private:
		KinectSensor* sensor;
		bool running;
		bool recing;
		vector<cv::Mat> torec;
	signals:
		void SetDepthFrame(int width, int height, uchar* data);
	public slots:
		void Rec();
};

#endif // VIEWMODEL_H
