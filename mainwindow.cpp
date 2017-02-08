#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	recing = false;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::GetDepthFrame(int width, int height, uchar *data)
{
	ui->labelDepth->setPixmap(
				QPixmap::fromImage(
					QImage(data, width, height,
								 QImage::Format_RGB888)));
}

void MainWindow::on_buttonRec_clicked()
{
	emit Rec();
	recing = !recing;
	if(recing)
	{
		ui->buttonRec->setText(("Stop"));
	}
	else
	{
		ui->buttonRec->setText(QString("Record"));
	}
}
