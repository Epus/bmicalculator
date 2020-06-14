#include "person.h"
#include "ui_person.h"
#include <QDebug>

Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
    ui->gender->addItems(QStringList{"Male", "Female"});
    connect(ui->removeButton, &QPushButton::clicked, [this]{emit removed(this);});
}

Person::~Person()
{
    delete ui;
}

bool Person::isValid() const
{
    if (name() == "") return false;
    if (age() <= 0) return false;
    if (weight() <= 0) return false;
    if (height() <= 0) return false;
    return true;
}

int Person::age() const
{
    return ui->age->text().toInt();
}

double Person::weight() const
{
    return ui->weight->text().toDouble();
}

double Person::height() const
{
    return ui->height->text().toDouble();
}

double Person::bmr() const
{
    double bmr;
    if (gender() == "Female")
        bmr = 655 + 9.6 * weight() + 1.8 * height() - 4.7 * age();
    else
        bmr = 66 + 13.7* weight() + 5 * height() - 6.8 * age();
    return bmr;
}

double Person::bmi() const
{
    double heightInMeters = height() / 100;
    return weight() / (heightInMeters * heightInMeters);
}

QString Person::status() const
{
    QString status;
    if (bmi() < 18.5) status = "Underweight";
    else if (bmi() <= 25) status = "Optimal weight";
    else status = "Overweight";
    return status;
}

QString Person::name() const
{
    return ui->name->text();
}

QString Person::gender() const
{
    return ui->gender->currentText();
}
