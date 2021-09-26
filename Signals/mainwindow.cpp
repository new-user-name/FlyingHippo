#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QPushButton *but_1 = new QPushButton(this);
  QPushButton *but_2 = new QPushButton(this);
  QPushButton *but_3 = new QPushButton(this);

  /* Устанавливаем номера кнопок
   * */
  but_1->setText("1");
  but_2->setText("2");
  but_3->setText("3");

  ui->verticalLayout->addWidget(but_1);
  ui->verticalLayout->addWidget(but_2);
  ui->verticalLayout->addWidget(but_3);

  connect(but_1, SIGNAL(clicked()), this, SLOT(slotButton1()));
  connect(but_2, SIGNAL(clicked()), this, SLOT(slotButton2()));
  connect(but_3, SIGNAL(clicked()), this, SLOT(slotButton3()));

  connect(this, &MainWindow::signalFromButton, this, &MainWindow::slotMessage);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotButton1()
{
  emit signalFromButton(1);
}

void MainWindow::slotButton2()
{
  emit signalFromButton(2);
}

void MainWindow::slotButton3()
{
  emit signalFromButton(3);
}

void MainWindow::slotMessage(int buttonID)
{
  QMessageBox::information(this,
                           "Уведомление о нажатой кнопке",
                           "Нажата кнопка под номером " + QString::number(buttonID));
}
