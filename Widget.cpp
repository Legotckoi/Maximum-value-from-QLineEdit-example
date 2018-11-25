#include "Widget.h"
#include "ui_Widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->getMaximumValuePushButton, &QPushButton::clicked, this, &Widget::onGetMaximumValuePushButtonClicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onGetMaximumValuePushButtonClicked()
{
    // Создаём вектор из всех полей ввода, которе требуется проверить
    std::vector<QLineEdit*> lineEdits = {ui->lineEdit_1, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4};
    // Создаём вектор для сохранения значений из полеей ввода
    std::vector<double> values;

    // Попытаемся получить значения из всех полей ввода, если текст в них возможно сконвертировать в число
    for (const QLineEdit* lineEdit : lineEdits)
    {
        bool ok = false;
        double value = lineEdit->text().toDouble(&ok);
        if (ok)
        {
            values.push_back(value);
        }
    }

    // Если числа не были найдены
    if (values.empty())
    {
        // То устанавливаем в поле результата значение Nan
        ui->resultlLineEdit->setText("Nan");
    }
    else
    {
        // Иначе пытаемся найти максимальное значение средствами стандартной библиотеки
        double max = *std::max_element(values.begin(), values.end());
        ui->resultlLineEdit->setText(QString::number(max));
    }
}
