#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QThread>
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
	signals:
		void SetDepthFrame(int width, int height, uchar* data);
};

#endif // VIEWMODEL_H
