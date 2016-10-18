#ifndef QCVWIDGET_H
#define QCVWIDGET_H

#include <QWidget>
#include <QThread>

namespace Ui {
class QCVWidget;
}

class QCVWidget : public QWidget
{
    Q_OBJECT


private:
    Ui::QCVWidget *ui;
    QThread *thread;

    void setup();

public:
    explicit QCVWidget(QWidget *parent = 0);
    ~QCVWidget();

signals:
    void sendSetup(int device);
    void sendToggleStream();

private slots:
    void receiveFrame(QImage frame);
    void receiveToggleStream();



};

#endif // QCVWIDGET_H
