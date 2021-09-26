#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

signals:
  void signalFromButton(int buttonID);    // The signal for transmission down the number of the button
private:
  Ui::MainWindow *ui;

private slots:
  void slotButton1();
  void slotButton2();
  void slotButton3();

  // Slot, which call a message with number by pressed button
  void slotMessage(int buttonID);
};

#endif // MAINWINDOW_H
