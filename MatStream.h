#pragma once

#ifndef _MATSTREAM_H
#define _MATSTREAM_H

#include <opencv2\opencv.hpp>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct MatStreamHeader
{
	int frameNum;
	int height;
	int width;
	int channels;
	int bytesPerPixel;
	int type;
	int time;
};


class MatStream
{
public:
	enum Op
	{
		in,
		out,
		unknown
	};

private:
	int frameNum;
	MatStreamHeader header;
	fstream file;
	Op mode;

private:
	void ReadHead();
	void WriteHead();

public:
	MatStream();
	void SetHead(MatStreamHeader _header);
	MatStreamHeader GetHead();
	void Open(string filename, Op op);
	bool Fail();
	bool Write(cv::Mat content);
	cv::Mat Read();
	void Close();
	int FrameNum();
	void SeekMat(int pos);
	};

#endif
