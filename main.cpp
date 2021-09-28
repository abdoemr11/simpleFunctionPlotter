#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include<QList>
#include"inputHandler.h"
#include "mainwindow.h"
using namespace std;
QT_CHARTS_USE_NAMESPACE


int main(int argc, char *argv[])
 {
	QApplication a(argc, argv);
	InputHandler *inputHandler = new InputHandler();
	//vector<pair<int,int>> points = inputHandler->getPoints();


	MainWindow *window = new MainWindow();
	//window.setCentralWidget(chartView);
	//window->resize(400, 300);
	window->show();

	return a.exec();

}
