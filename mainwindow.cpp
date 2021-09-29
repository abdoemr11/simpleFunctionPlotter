#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
//QT_CHARTS_USE_NAMESPACE
#include"inputHandler.h"
//#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  //initialize layout
  initLayout();
  populatLayout();
  initChart();
  inputHandler = new InputHandler();
  //plot();
  connect(plotButton, SIGNAL(clicked()), this, SLOT(plot()));


}

void MainWindow::initLayout()
{
  mainLayout = new QGridLayout();
  leftLayout = new QVBoxLayout();
  
}
void MainWindow::populatLayout()
{
    //initialize widgets
  mainWidget = new QWidget();
  exprLineEdit  = new QLineEdit();
  minLineEdit = new QLineEdit();
  maxLineEdit = new QLineEdit();
  plotButton = new QPushButton(tr("Plot"));
	/******************************************************/
  QLineSeries *test = new QLineSeries();
  series = new QLineSeries();
  chart = new QChart();
  chartView = new QChartView();
  xAxis = new QValueAxis;
  yAxis = new QValueAxis;
  //label
  QLabel *exprLabel = new QLabel("Enter F(x)");
  QLabel *minMaxLabel = new QLabel("Enter min and max value");
  ///////////////////////////////////////////////////
  setCentralWidget(mainWidget);
  mainWidget->setLayout(mainLayout);
  ///////////////////////////////////////////////
  minLineEdit->setPlaceholderText("min value");
  maxLineEdit->setPlaceholderText("max value");

  ////////////////////////////////////
  mainLayout->setColumnStretch(0,10);
  mainLayout->setColumnStretch(1,10);
  mainLayout->setColumnStretch(2,50);
  mainLayout->addWidget(exprLabel,0,0,1,2);
  mainLayout->addWidget(exprLineEdit, 1,0);
  mainLayout->addWidget(minMaxLabel, 2,0,1,2);
  mainLayout->addWidget(minLineEdit, 3,0);
  mainLayout->addWidget(maxLineEdit, 3,1);
  mainLayout->addWidget(plotButton,4, 1);
  mainLayout->addWidget(chartView, 0,2,6,1);





}
void MainWindow::initChart()
{
  chart->legend()->hide(); 
	chart->addSeries(series);
	chart->addAxis(xAxis, Qt::AlignBottom);
	chart->addAxis(yAxis, Qt::AlignLeft);
	series->attachAxis(xAxis);
	series->attachAxis(yAxis);
	xAxis->setRange(-10,10);
	yAxis->setRange(-10,10);
	//xAxis->setTickCount(10);
	//yAxis->setTickCount(10);
	
	chart->setTitle("Function Plotter");
	chartView->setChart(chart);
	//chartView->setRenderHint(QPainter::Antialiasing);
}
/**************************************************************
 *plot(): 
 *called when pressed plotButton
 *it use  getPoints from InputHandler class to get value
 *then pass it to the series
 *
 *
 *************************************************************/
void MainWindow::plot() 
{
	QString exprStr = exprLineEdit->text();
	int min = minLineEdit->text().toInt();
	int max = maxLineEdit->text().toInt();
	if(!validateInput(exprStr, min, max))
		return;
  std::vector<std::pair<int,int>> points = inputHandler->getPoints(exprStr.toStdString(), min, max);
	series->clear();
	QVector<QPointF> pointVec;
	qDebug() << "std::vector length  "<<points.size();
  for(auto point: points)
	{
		QPointF qpoint(point.first, point.second);
		//pointsList->append(qpoint);
		//series->replace(qpoint);
		series->append(qpoint);
	}
	foreach(QPointF p, series->pointsVector())
		qDebug() << p;
		QPointF minqpoint(points.back().first, points.back().second);
	qDebug()<< minqpoint << " " << series->pointsVector().length();
	/*******Set range of axis************/
	int xrange = ((max + 99)/100) * 100;
	int yrange = ((points.back().second+99)/100) * 100;
	xAxis->setRange(-xrange, xrange);
	yAxis->setRange(-yrange, yrange);
}
/**********************************************************************
 * validateInput: 
 * - first validate that max > min
 * - validate that expression is not empty;
 * -				 expression is valid
**********************************************************************/
bool MainWindow::validateInput(QString exprString, int min, int max)
{
	if(!(max > min))			
	{
		qDebug() << "Maximum value must be greater than minimum value.";
		QMessageBox msgBox;
		msgBox.setText("Maximum value must be greater than minimum value.");
		msgBox.exec();
		return false;
	}
	if(exprString.isEmpty())
	{
		qDebug() << "You must Enter a function to plot";
		QMessageBox msgBox;
		msgBox.setText("You must Enter a function to plot.");
		msgBox.exec();
		return false;
	}
	/******************************************************************/
	QRegularExpression r1("(?:[0-9-+*/^()x])+");
	if(!r1.match(exprString).hasMatch())
	{
		qDebug() << "Can't plot this function Please use numbers,+,-,*,^,/ only"	;
		QMessageBox msgBox;
		msgBox.setText("Can't plot this function Please use (x) numbers,+,-,*,^,/ only.");
		msgBox.exec();
		return false;
	}
	return true;
}
