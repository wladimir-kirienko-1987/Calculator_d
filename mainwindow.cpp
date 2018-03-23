#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_plus_minus,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_procent,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sqr,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_one_div,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_m_save,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_m_res,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_m_clear,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_m_plus,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_m_minus,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_pi,SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_e,SIGNAL(clicked()), this, SLOT(operations()));


    connect(ui->pushButton_divide,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus,SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus,SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);

    memory_save = 0;

    operation_flag = false;

    ui->result_show->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    if (operation_flag){
        ui->result_show->setText("");
        operation_flag = false;
    }

    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label, temp;

    if ((ui->result_show->text().size() > digits_count) ||
        (ui->result_show->text().contains("e")) )
        return;

    if (ui->result_show->text().contains(".") && button->text() == "0"){
        new_label = ui->result_show->text() + button->text();
    } else {
        all_numbers = (ui->result_show->text() + button->text()).toDouble();
        new_label = ui->result_show->text();
        temp = QString::number(all_numbers, 'g', digits_count);
        if (!(temp.contains("e")))
            new_label = temp;
    }

    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (!(ui->result_show->text().contains('.')))
        ui->result_show->setText(ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);

    operation_flag = false;

    QPushButton *button = (QPushButton *)sender();

    double all_numbers;
    QString new_label;
    bool out_flag = true;

    if(button->text() == "+/-"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers *= -1;
        new_label = QString::number(all_numbers, 'g', digits_count);
    } else if(button->text() == "%"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers *= 0.01;
        new_label = QString::number(all_numbers, 'g', digits_count);
    } else if(button->text() == "sqrt"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = qSqrt(all_numbers);
        new_label = QString::number(all_numbers, 'g', digits_count);
    } else if(button->text() == "sqr"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers *= all_numbers;
        new_label = QString::number(all_numbers, 'g', digits_count);
    } else if(button->text() == "1/x"){
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = 1/all_numbers;
        new_label = QString::number(all_numbers, 'g', digits_count);
    } else if(button->text() == "MS"){
        all_numbers = (ui->result_show->text()).toDouble();
        memory_save = all_numbers;
        out_flag = false;
    } else if(button->text() == "MR"){
        all_numbers = (ui->result_show->text()).toDouble();
        new_label = QString::number(memory_save, 'g', digits_count);
    } else if(button->text() == "MC"){
        memory_save = 0;
        out_flag = false;
    } else if(button->text() == "M+"){
        all_numbers = (ui->result_show->text()).toDouble();
        memory_save += all_numbers;
        out_flag = false;
    } else if(button->text() == "M-"){
        all_numbers = (ui->result_show->text()).toDouble();
        memory_save -= all_numbers;
        out_flag = false;
    } else if(button->text() == "Pi"){
        new_label = QString::number(M_PI, 'g', digits_count);
    } else if(button->text() == "E"){
        new_label = QString::number(M_E, 'g', digits_count);
    }

    if(out_flag)
        ui->result_show->setText(new_label);

}

void MainWindow::math_operations()
{
    QPushButton *button = (QPushButton *)sender();

    num_first = (ui->result_show->text()).toDouble();

    //ui->result_show->setText("");

    operation_flag = true;

    button->setChecked(true);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);

    operation_flag = false;

    ui->result_show->setText("0");
}

void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, num_second;
    QString new_label;

    num_second = ui->result_show->text().toDouble();

    if(ui->pushButton_plus->isChecked()){
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber, 'g', digits_count);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    }else if(ui->pushButton_minus->isChecked()){
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber, 'g', digits_count);
        ui->result_show->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    }else if(ui->pushButton_divide->isChecked()){
        if (num_second == 0){
            ui->result_show->setText("0");
        } else{
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber, 'g', digits_count);
            ui->result_show->setText(new_label);
        }
        ui->pushButton_divide->setChecked(false);
    }else if(ui->pushButton_multiply->isChecked()){
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber, 'g', digits_count);
        ui->result_show->setText(new_label);
        ui->pushButton_multiply->setChecked(false);
    }
}
