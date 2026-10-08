#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNumberClicked();
    void onOperationClicked();
    void onEqualClicked();
    void onClearClicked();

private:
    QLineEdit *display;
    double currentValue = 0;
    QString currentOperation = "";
    bool newNumberFlag = true;

    void createUI();
    void connectButtons();
};

#endif // MAINWINDOW_H