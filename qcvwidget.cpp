#include "qcvwidget.h"
#include "ui_qcvwidget.h"
#include "opencvworker.h"
#include <QTimer>


QCVWidget::QCVWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCVWidget)
{
    ui->setupUi(this);
    ui->labelView->setScaledContents(true);
    setup();
}

QCVWidget::~QCVWidget()
{
    thread->quit();
    while(!thread->isFinished());

    delete thread;
    delete ui;
}

void QCVWidget::setup()
{
    thread = new QThread();
    OpenCvWorker *worker =  new OpenCvWorker();
    QTimer *workerTrigger = new QTimer();
    workerTrigger->setInterval(1);

    connect(workerTrigger, SIGNAL(timeout()), worker, SLOT(receiveGrabFrame()));
    connect(this, SIGNAL(sendSetup(int)), worker, SLOT(receiveSetup(int)));
    connect(this, SIGNAL(sendToggleStream()), worker, SLOT(receiveToggleStream()));
    connect(ui->pushButtonPlay, SIGNAL(clicked(bool)), this, SLOT(receiveToggleStream()));
    connect(ui->checkBoxEnable, SIGNAL(toggled(bool)), worker, SLOT(receiveEnableBinaryTreshold()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), worker, SLOT(receiveBinaryTreshold(int)));
    //connect(thread, SIGNAL(started()), workerTrigger, SLOT(start()));
    connect(worker, SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrame(QImage)));

    workerTrigger->start();
    worker->moveToThread(thread);
    workerTrigger->moveToThread(thread);

    thread->start();

    emit sendSetup(0);

}

void QCVWidget::receiveFrame(QImage frame)
{
    ui->labelView->setPixmap(QPixmap::fromImage(frame));
}

void QCVWidget::receiveToggleStream()
{
    if(!ui->pushButtonPlay->text().compare(">")) ui->pushButtonPlay->setText("||");
    else ui->pushButtonPlay->setText(">");

    emit sendToggleStream();
}
