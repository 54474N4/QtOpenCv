#include "opencvworker.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

OpenCvWorker::OpenCvWorker(QObject *parent) :
    QObject(parent),
    status(false),
    toggleStream(false),
    binaryTresholdEnable(false),
    binaryTreshold(127)
{
    cap = new cv::VideoCapture();

}

OpenCvWorker::~OpenCvWorker()
{
    if(cap->isOpened()) cap->release();
    delete cap;
}

void OpenCvWorker::process()
{
 cv::cvtColor(_frameOriginal, _frameProcessed, cv::COLOR_BGR2BGRA);

 if(binaryTresholdEnable){
    cv::threshold(_frameProcessed, _frameProcessed, binaryTreshold, 255, cv::THRESH_BINARY);
 }
}

void OpenCvWorker::receiveGrabFrame()
{
    if(!toggleStream) return;

    (*cap)>>_frameOriginal;
    if(_frameOriginal.empty()) return;

    process();

   //QImage output((const unsigned char*)_frameProcessed.data,_frameProcessed.cols,_frameProcessed.rows, QImage::Format_Indexed8);
    QImage output((const unsigned char*)_frameProcessed.data,_frameProcessed.cols,_frameProcessed.rows, QImage::Format_RGB32);
    output.scaled(600, 400);
    emit sendFrame(output);
}

void OpenCvWorker::chekIfDeviceAlreadyOpened(const int device)
{
    if(cap->isOpened()) cap->release();
    cap->open(device);
}

void OpenCvWorker::receiveSetup(const int device)
{
    chekIfDeviceAlreadyOpened(device);

    if(!cap->isOpened()){
        status = false;
        return;
    }
    status = true;
}

void OpenCvWorker::receiveToggleStream()
{
    toggleStream = !toggleStream;
}


void OpenCvWorker::receiveEnableBinaryTreshold()
{
    binaryTresholdEnable = !binaryTresholdEnable;
}

void OpenCvWorker::receiveBinaryTreshold(int treshold)
{
    binaryTreshold = treshold;
}
