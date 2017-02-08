#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;
		bool recing;

	signals:
		void Rec();

	public slots:
		void GetDepthFrame(int, int, uchar*);

	private slots:
		void on_buttonRec_clicked();
};

#endif // MAINWINDOW_H
