#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void AddPerson();
    void RemovePerson(Person *person);
    void GenerateReport();

    Ui::MainWindow *ui;
    QVector<Person *> m_persons;
};
#endif // MAINWINDOW_H
