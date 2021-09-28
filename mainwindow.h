#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
using namespace QtCharts;
//forwarding class
/*class QLineSeries;
class QChart;
class QChartView;*/
class QLineEdit;
class QGridLayout;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class InputHandler;

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
   void plot();

private:
  void initLayout();
  void populatLayout();
  void initChart();
  //input handler
  InputHandler *inputHandler;
   //for chart
  QLineSeries *series;
  QChart *chart;
  QChartView *chartView;
	QValueAxis *xAxis;
	QValueAxis *yAxis;
  
  //widget
  QPushButton *plotButton;
  QLineEdit *exprLineEdit;
  QLineEdit *minLineEdit;
  QLineEdit *maxLineEdit;
  QWidget *mainWidget;
  //layout
  QGridLayout *mainLayout;
  QVBoxLayout *leftLayout;
  //QCustomPlot *myplot;
  //variable 
  
};

#endif // MAINWINDOW_H
