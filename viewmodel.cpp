#include "viewmodel.h"

ViewModel::ViewModel()
{
	sensor = new KinectSensor();
	running = true;
}

HRESULT ViewModel::Init()
{
	HRESULT hr = sensor->init(FrameSourceTypes_Depth);
	if(FAILED(hr))
	{
		qDebug("Failed to init kinect sensor");
		return hr;
	}
}

void ViewModel::stop()
{
	running = false;
	if(sensor)
	{
		sensor->close();
	}
}

void ViewModel::run()
{
	if(!sensor) return;
	while(running)
	{
		HRESULT hr = sensor->update();
		if(FAILED(hr))
		{
			continue;
		}
		cv::Mat depthFrame = sensor->getDepthMat();
		if(depthFrame.empty())
		{
			qDebug("Warning: missed frame from Kinect.");
			continue;
		}
	}
}
