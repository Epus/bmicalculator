#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::AddPerson);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::GenerateReport);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddPerson()
{
    Person *person = new Person();
    m_persons.append(person);
    ui->personsLayout->insertWidget(0, person);
    connect(person, &Person::removed, this, &MainWindow::RemovePerson);
}

void MainWindow::RemovePerson(Person *person)
{
    m_persons.removeOne(person);
    ui->personsLayout->removeWidget(person);
    delete person;
}

void MainWindow::GenerateReport()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "report.csv", "(*.csv)");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    out << "Name, Age(yr), Weight(kg), Height(cm), Gender, BMR, BMI, Status\n";

    QVector<double> optimalMaleBMR;
    QVector<double> optimalFemaleBMR;

    for(auto &person: m_persons)
    {
        if(person->isValid())
        {
            out << person->name() << ", " << person->age() << ", "
                     << person->weight() << ", " << person->height() << ", "
                     << person->gender() << ", " << person->bmr() << ", "
                     << person->bmi() << ", " << person->status() << "\n";
            if (person->status() == "Optimal weight")
            {
                if(person->gender() == "Male")
                    optimalMaleBMR.append(person->bmr());
                else
                    optimalFemaleBMR.append(person->bmr());
            }
        }
    }

    if (!optimalMaleBMR.isEmpty())
    {
        double total = 0;
        for (auto &i: optimalMaleBMR)
        {
            total += i;
        }
        out << "Average BMR for Optimal weighted males: " <<  total / optimalMaleBMR.size() << "\n";
    }

    if (!optimalFemaleBMR.isEmpty())
    {
        double total = 0;
        for (auto &i: optimalFemaleBMR)
        {
            total += i;
        }
        out << "Average BMR for Optimal weighted females: " <<  total / optimalFemaleBMR.size() << "\n";
    }
}
