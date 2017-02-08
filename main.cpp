#include "mainwindow.h"
#include "viewmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	ViewModel viewModel;

	QObject::connect(
				&viewModel, &ViewModel::SetDepthFrame,
				&w, &MainWindow::GetDepthFrame,
				Qt::QueuedConnection);
	QObject::connect(
				&w, &MainWindow::Rec,
				&viewModel, &ViewModel::Rec);

	w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint);
	w.show();

	viewModel.Init();
	viewModel.start();

	return a.exec();
}
