#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasetool.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setLineEditHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_resultSearch_clicked()
{
    if (ui->pushButton_addMoves->isHidden()) {
        if ((ui->comboBox_moves_1->currentIndex() == 0 && ui->lineEdit->text().isEmpty()) ||
            (ui->comboBox_moves_2->currentIndex() == 0 && ui->lineEdit_2->text().isEmpty()) ||
            (ui->comboBox_moves_3->currentIndex() == 0 && ui->lineEdit_3->text().isEmpty()) ||
            (ui->comboBox_moves_4->currentIndex() == 0 && ui->lineEdit_4->text().isEmpty()) ||
            (ui->comboBox_moves_5->currentIndex() == 0 && ui->lineEdit_5->text().isEmpty()) ||
            (ui->comboBox_moves_6->currentIndex() == 0 && ui->lineEdit_6->text().isEmpty()) ){
            ui->label_result->setText("招式没填完，给锤子结果");
            return;
        }

        int matchesID = ui->comboBox_match->currentIndex() + 1;
        QString Moves_1_1 = ui->comboBox_moves_1->currentIndex() == 0 ? ui->lineEdit->text()   : ui->comboBox_moves_1->currentText();
        QString Moves_1_2 = ui->comboBox_moves_2->currentIndex() == 0 ? ui->lineEdit_2->text() : ui->comboBox_moves_2->currentText();
        QString Moves_1_3 = ui->comboBox_moves_3->currentIndex() == 0 ? ui->lineEdit_3->text() : ui->comboBox_moves_3->currentText();
        QString Moves_2_1 = ui->comboBox_moves_4->currentIndex() == 0 ? ui->lineEdit_4->text() : ui->comboBox_moves_4->currentText();
        QString Moves_2_2 = ui->comboBox_moves_5->currentIndex() == 0 ? ui->lineEdit_5->text() : ui->comboBox_moves_5->currentText();
        QString Moves_2_3 = ui->comboBox_moves_6->currentIndex() == 0 ? ui->lineEdit_6->text() : ui->comboBox_moves_6->currentText();
        QString result = DatabaseTool::GetInstance().serachRecord(matchesID, ui->comboBox_2->currentText(), ui->comboBox_3->currentText(), Moves_1_1, Moves_1_2, Moves_1_3, Moves_2_1, Moves_2_2, Moves_2_3);
        ui->label_result->setText(result);
    } else {
        if (ui->comboBox_moves_1->currentIndex() == 0 ||
            ui->comboBox_moves_2->currentIndex() == 0 ||
            ui->comboBox_moves_3->currentIndex() == 0 ||
            ui->comboBox_moves_4->currentIndex() == 0 ||
            ui->comboBox_moves_5->currentIndex() == 0 ||
            ui->comboBox_moves_6->currentIndex() == 0) {
            ui->label_result->setText("招式没填完，给锤子结果");
        } else {
            int matchesID = ui->comboBox_match->currentIndex() + 1;
            QString Moves_1_1 = ui->comboBox_moves_1->currentText();
            QString Moves_1_2 = ui->comboBox_moves_2->currentText();
            QString Moves_1_3 = ui->comboBox_moves_3->currentText();
            QString Moves_2_1 = ui->comboBox_moves_4->currentText();
            QString Moves_2_2 = ui->comboBox_moves_5->currentText();
            QString Moves_2_3 = ui->comboBox_moves_6->currentText();
            QString result = DatabaseTool::GetInstance().serachRecord(matchesID, ui->comboBox_2->currentText(), ui->comboBox_3->currentText(), Moves_1_1, Moves_1_2, Moves_1_3, Moves_2_1, Moves_2_2, Moves_2_3);
            ui->label_result->setText(result);
        }
    }
}


void MainWindow::on_pushButton_addMoves_clicked()
{
    setLineEditHidden(ui->lineEdit->isVisible());
    ui->pushButton_addMoves->setHidden(true);
}

void MainWindow::setLineEditHidden(bool Hidden)
{
    ui->lineEdit->setHidden(Hidden);
    ui->lineEdit_2->setHidden(Hidden);
    ui->lineEdit_3->setHidden(Hidden);
    ui->lineEdit_4->setHidden(Hidden);
    ui->lineEdit_5->setHidden(Hidden);
    ui->lineEdit_6->setHidden(Hidden);
}


void MainWindow::on_comboBox_match_currentIndexChanged(int index)
{
    int matches = index + 1;
    QStringList moves_1 = DatabaseTool::GetInstance().serachMoves(matches, ui->comboBox_2->currentText());
    QStringList moves_2 = DatabaseTool::GetInstance().serachMoves(matches, ui->comboBox_3->currentText());
    moves_1.prepend("没合适的");
    moves_2.prepend("没合适的");
    ui->comboBox_moves_1->clear();
    ui->comboBox_moves_1->addItems(moves_1);
    ui->comboBox_moves_1->setCurrentIndex(0);

    ui->comboBox_moves_2->clear();
    ui->comboBox_moves_2->addItems(moves_1);
    ui->comboBox_moves_2->setCurrentIndex(0);

    ui->comboBox_moves_3->clear();
    ui->comboBox_moves_3->addItems(moves_1);
    ui->comboBox_moves_3->setCurrentIndex(0);

    ui->comboBox_moves_4->clear();
    ui->comboBox_moves_4->addItems(moves_2);
    ui->comboBox_moves_4->setCurrentIndex(0);

    ui->comboBox_moves_5->clear();
    ui->comboBox_moves_5->addItems(moves_2);
    ui->comboBox_moves_5->setCurrentIndex(0);

    ui->comboBox_moves_6->clear();
    ui->comboBox_moves_6->addItems(moves_2);
    ui->comboBox_moves_6->setCurrentIndex(0);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    int matches = ui->comboBox_match->currentIndex() + 1;
    QStringList moves_1 = DatabaseTool::GetInstance().serachMoves(matches, arg1);
    moves_1.prepend("没合适的");
    ui->comboBox_moves_1->clear();
    ui->comboBox_moves_1->addItems(moves_1);
    ui->comboBox_moves_1->setCurrentIndex(0);

    ui->comboBox_moves_2->clear();
    ui->comboBox_moves_2->addItems(moves_1);
    ui->comboBox_moves_2->setCurrentIndex(0);

    ui->comboBox_moves_3->clear();
    ui->comboBox_moves_3->addItems(moves_1);
    ui->comboBox_moves_3->setCurrentIndex(0);

}

void MainWindow::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    int matches = ui->comboBox_match->currentIndex() + 1;
    QStringList moves_2 = DatabaseTool::GetInstance().serachMoves(matches, arg1);
    moves_2.prepend("没合适的");
    ui->comboBox_moves_4->clear();
    ui->comboBox_moves_4->addItems(moves_2);
    ui->comboBox_moves_4->setCurrentIndex(0);

    ui->comboBox_moves_5->clear();
    ui->comboBox_moves_5->addItems(moves_2);
    ui->comboBox_moves_5->setCurrentIndex(0);

    ui->comboBox_moves_6->clear();
    ui->comboBox_moves_6->addItems(moves_2);
    ui->comboBox_moves_6->setCurrentIndex(0);
}


void MainWindow::on_pushButton_2_clicked()
{
    QPushButton *okbtn = new QPushButton(QString("胜利"));
    QPushButton *cancelbtn = new QPushButton(QString("失败"));
    QMessageBox *mymsgbox = new QMessageBox;

    mymsgbox->setIcon(QMessageBox::Warning);
    mymsgbox->setWindowTitle(QString("比赛结果"));
    mymsgbox->setText(QString("前者获胜了么？"));
    mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);
    mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);
    mymsgbox->show();

    mymsgbox->exec();//阻塞等待用户输入
    int result = 0;
    if (mymsgbox->clickedButton()== okbtn)//点击了OK按钮
    {
        result = 1;
    }
    // this->close();

    int matchesID = ui->comboBox_match->currentIndex() + 1;
    QString occupation_1 = ui->comboBox_2->currentText();
    QString occupation_2 = ui->comboBox_3->currentText();
    QString Moves_1_1 = ui->comboBox_moves_1->currentIndex() == 0 ? ui->lineEdit->text()   : ui->comboBox_moves_1->currentText();
    QString Moves_1_2 = ui->comboBox_moves_2->currentIndex() == 0 ? ui->lineEdit_2->text() : ui->comboBox_moves_2->currentText();
    QString Moves_1_3 = ui->comboBox_moves_3->currentIndex() == 0 ? ui->lineEdit_3->text() : ui->comboBox_moves_3->currentText();
    QString Moves_2_1 = ui->comboBox_moves_4->currentIndex() == 0 ? ui->lineEdit_4->text() : ui->comboBox_moves_4->currentText();
    QString Moves_2_2 = ui->comboBox_moves_5->currentIndex() == 0 ? ui->lineEdit_5->text() : ui->comboBox_moves_5->currentText();
    QString Moves_2_3 = ui->comboBox_moves_6->currentIndex() == 0 ? ui->lineEdit_6->text() : ui->comboBox_moves_6->currentText();
    DatabaseTool::GetInstance().addInfo(matchesID, occupation_1, occupation_2, Moves_1_1, Moves_1_2, Moves_1_3, Moves_2_1, Moves_2_2, Moves_2_3, result);
}

