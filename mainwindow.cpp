#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
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
  QLabel *exprLabel = new QLabel("Enter the function you want to plot");
  QLabel *minMaxLabel = new QLabel("choose the min and max value");
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
  mainLayout->addWidget(exprLabel,0,0);
  mainLayout->addWidget(exprLineEdit, 1,0);
  mainLayout->addWidget(minMaxLabel, 2,0);
  mainLayout->addWidget(minLineEdit, 3,0);
  mainLayout->addWidget(maxLineEdit, 3,1);
  mainLayout->addWidget(plotButton,4, 1);
  mainLayout->addWidget(chartView, 0,2,4,1);





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
	chart->setTitle("Simple line chart example");
	chartView->setChart(chart);
	//chartView->setRenderHint(QPainter::Antialiasing);
}
void MainWindow::plot() 
{
	QString exprStr = exprLineEdit->text();
  std::vector<std::pair<int,int>> points = inputHandler->getPoints(exprStr.toStdString());
	series->clear();
	QVector<QPointF> pointVec;
  for(auto point: points)
	{
		QPointF qpoint(point.first, point.second);
		//pointsList->append(qpoint);
		//series->replace(qpoint);
		series->append(qpoint);
	} 
	//
	QVector<QPointF> test = series->pointsVector();
	//test.removeFirst();
	qDebug() << "Before adding";
	Q_FOREACH( QPointF p, series->pointsVector() ) {
    qDebug() << p;
	}

	test.append(QPointF(1,1));
	//series->replace(test);
	series->append(QPointF(1,1));
	qDebug() << "After adding";
	Q_FOREACH( QPointF p, series->pointsVector() ) {
    qDebug() << p;
}
	xAxis->setRange(-20,20);
	yAxis->setRange(-20,20);
	qDebug() << "finish\n";
}
