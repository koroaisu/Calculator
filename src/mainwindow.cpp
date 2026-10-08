#include "mainwindow.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("電卓");
    setGeometry(100, 100, 300, 450);
    createUI();
    connectButtons();
}

MainWindow::~MainWindow() {}

void MainWindow::createUI() {
    // 中央ウィジェット
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ディスプレイ
    display = new QLineEdit();
    display->setReadOnly(true);
    display->setText("0");
    display->setAlignment(Qt::AlignRight);
    QFont font = display->font();
    font.setPointSize(18);
    font.setBold(true);
    display->setFont(font);
    display->setMinimumHeight(60);
    mainLayout->addWidget(display);

    // ボタンレイアウト
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(5);

    // ボタンデータ
    QString buttonTexts[5][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"},
        {"C", "", "", ""}
    };

    // ボタン作成
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 4; ++col) {
            QString text = buttonTexts[row][col];
            
            if (text.isEmpty()) continue;

            QPushButton *btn = new QPushButton(text);
            btn->setFont(QFont("Arial", 14, QFont::Bold));
            btn->setMinimumHeight(50);
            btn->setMinimumWidth(50);

            // ボタンの色分け
            if (text == "=") {
                btn->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;");
            } else if (text == "C") {
                btn->setStyleSheet("background-color: #f44336; color: white; font-weight: bold;");
            } else if (text == "/" || text == "*" || text == "-" || text == "+") {
                btn->setStyleSheet("background-color: #FF9800; color: white; font-weight: bold;");
            } else {
                btn->setStyleSheet("background-color: #e0e0e0; color: black;");
            }

            btn->setObjectName(text);
            gridLayout->addWidget(btn, row, col);
        }
    }

    mainLayout->addLayout(gridLayout);
}

void MainWindow::connectButtons() {
    // ボタンの接続
    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(
        qobject_cast<QVBoxLayout*>(centralWidget()->layout())->itemAt(1)->layout()
    );

    if (!gridLayout) return;

    for (int i = 0; i < gridLayout->count(); ++i) {
        QPushButton *btn = qobject_cast<QPushButton*>(gridLayout->itemAt(i)->widget());
        if (!btn) continue;

        QString text = btn->objectName();

        if (text >= "0" && text <= "9") {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onNumberClicked);
        } else if (text == "." ) {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onNumberClicked);
        } else if (text == "C") {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onClearClicked);
        } else if (text == "=") {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
        } else if (text == "+" || text == "-" || text == "*" || text == "/") {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onOperationClicked);
        }
    }
}

void MainWindow::onNumberClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString text = display->text();
    QString btnText = btn->text();

    if (newNumberFlag) {
        text = btnText;
        newNumberFlag = false;
    } else {
        // 小数点は1つだけ
        if (btnText == "." && text.contains(".")) return;
        text += btnText;
    }

    display->setText(text);
}

void MainWindow::onOperationClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    currentValue = display->text().toDouble();
    currentOperation = btn->text();
    newNumberFlag = true;
}

void MainWindow::onEqualClicked() {
    double secondValue = display->text().toDouble();
    double result = 0;

    if (currentOperation == "+") {
        result = currentValue + secondValue;
    } else if (currentOperation == "-") {
        result = currentValue - secondValue;
    } else if (currentOperation == "*") {
        result = currentValue * secondValue;
    } else if (currentOperation == "/") {
        if (secondValue != 0) {
            result = currentValue / secondValue;
        } else {
            display->setText("Error: Division by zero");
            newNumberFlag = true;
            return;
        }
    }

    display->setText(QString::number(result));
    currentOperation = "";
    newNumberFlag = true;
}

void MainWindow::onClearClicked() {
    display->setText("0");
    currentValue = 0;
    currentOperation = "";
    newNumberFlag = true;
}