#include "viewmodel.h"

ViewModel::ViewModel()
{
	sensor = new KinectSensor();
	running = true;
	recing = false;
}

HRESULT ViewModel::Init()
{
	HRESULT hr = sensor->init(FrameSourceTypes_Depth);
	if(FAILED(hr))
	{
		qDebug("Failed to init kinect sensor");
		return hr;
	}
	return hr;
}

void ViewModel::stop()
{
	if(recing)
	{
		Rec();
	}
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
		if(recing) torec.push_back(depthFrame);
		depthFrame.convertTo(depthFrame, CV_8U, 1.0/10);
		cv::cvtColor(depthFrame, depthFrame, CV_GRAY2RGB);
		emit SetDepthFrame(512, 424, depthFrame.data);
	}
}

void ViewModel::Rec()
{
	if(recing)
	{
		MatStreamHeader header;
		header.bytesPerPixel = 2;
		header.channels = 1;
		header.height = 424;
		header.width = 512;
		header.type = CV_16U;
		MatStream stream;
		stream.SetHead(header);
		QString fileName =
				QFileDialog::getSaveFileName(
					nullptr,
					QString(),
					QString(),
					QString("All files(*.*)"));
		stream.Open(string(fileName.toLocal8Bit()),
								MatStream::Op::out);
		for(int i =0;i<torec.size();i++)
		{
			stream.Write(torec[i]);
		}
		stream.Close();
	}
	recing = !recing;
}
