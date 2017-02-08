#include "MatStream.h"

MatStream::MatStream() :
	mode(Op::unknown),
	frameNum(0)
{

}

void MatStream::ReadHead()
{
	if (file.fail()) return;
	if (mode == Op::out) return;
	file.seekg(ios::beg, 0);
	file.read((char*)(&header), sizeof(header));
	frameNum = header.frameNum;
}

void MatStream::WriteHead()
{
	if (file.fail()) return;
	if (mode == Op::in) return;
	file.seekp(ios::beg, 0);
	file.write((char*)(&header), sizeof(header));
}

void MatStream::SetHead(MatStreamHeader _header)
{
	header = _header;
	return;
}

MatStreamHeader MatStream::GetHead()
{
	return header;
}

void MatStream::Open(string filename, Op op)
{
	mode = op;
	if (op == Op::in)
	{
		file.open(filename, ios::in | ios::binary);
		ReadHead();
	}
	if (op == Op::out)
	{
		file.open(filename, ios::out | ios::binary);
		WriteHead();
	}
}

bool MatStream::Fail()
{
	return file.fail();
}

bool MatStream::Write(cv::Mat content)
{
	if (content.rows != header.height || content.cols != header.width)
		return false;
	if (file.fail()) return false;
	if (mode == Op::in) return false;
	file.write((char*)content.data, header.height*header.width*header.bytesPerPixel*header.channels);
	frameNum++;
	return true;
}

cv::Mat MatStream::Read()
{
	cv::Mat content(header.height, header.width, header.type, cv::Scalar::all(0));
	if (file.fail()) return cv::Mat();
	if (mode == Op::out) return cv::Mat();
	file.read((char*)(content.data), header.height*header.width*header.bytesPerPixel*header.channels);
	return content;
}

void MatStream::Close()
{
	if (file.fail()) return;
	if (mode == Op::out)
	{
		file.seekp(ios::beg, 0);
		file.write((char*)(&frameNum), sizeof(frameNum));
	}
	file.close();
}

int MatStream::FrameNum()
{
	return frameNum;
}

void MatStream::SeekMat(int pos)
{
	if(mode == Op::in)
	{
		int frameSize = header.height * header.width * header.bytesPerPixel * header.channels;
		file.seekg(sizeof(MatStreamHeader)+pos*frameSize, ios::beg);
	}
}
