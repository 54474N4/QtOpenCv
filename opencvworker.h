#ifndef OPENCVWORKER_H
#define OPENCVWORKER_H

#include <QObject>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class OpenCvWorker : public QObject
{
    Q_OBJECT
private:
    cv::Mat _frameOriginal;
    cv::Mat _frameProcessed;
    cv::VideoCapture *cap;


    bool status;
    bool toggleStream;

    bool binaryTresholdEnable;
    int binaryTreshold;

    void process();

    void chekIfDeviceAlreadyOpened(const int device);

public:
    explicit OpenCvWorker(QObject *parent = 0);
    ~OpenCvWorker();

signals:
    void sendFrame(QImage frameProcessed);



public slots:
    void receiveGrabFrame();
    void receiveSetup(const int device);
    void receiveToggleStream();

    void receiveEnableBinaryTreshold();
    void receiveBinaryTreshold(int treshold);

};

#endif // OPENCVWORKER_H
