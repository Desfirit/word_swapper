#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "string"
#include "sstream"
#include <vector>
#include <iterator>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_transformButton_clicked()
{
    size_t a = ui->a->value()-1;
    size_t b = ui->b->value()-1;
    std::string s {ui->input->toPlainText().toStdString()};
    std::istringstream ss{s};

    std::vector<std::string> words(std::istream_iterator<std::string>{ss},{});

    QString res;
    if(words.size() <= a )
        res = "Первое число больше количества слов";
    else if(words.size() <= b)
        res = "Второе число больше количества слов";
    else if(b < a)
        res = "Первое число должно быть меньше или равно второго числа a <= b";
    else
    {
        auto changeBeg = begin(words)+a;
        auto changeEnd = begin(words)+b;
        auto strBeg(std::accumulate(begin(words),changeBeg,std::string{}, [](auto word, auto a){
            return word + " " + a;
        }));
        auto strMid(std::accumulate(changeBeg,changeEnd+1,std::string{}, [](auto word, auto a){
            return word + " " + a;
        }));
        auto strEnd(std::accumulate(changeEnd+1,end(words),std::string{}, [](auto word, auto a){
            return word + " " + a;
        }));

        res = (strMid + strBeg + strEnd).c_str();
    }
    ui->output->setPlainText(res);

}
