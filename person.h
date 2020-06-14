#ifndef PERSON_H
#define PERSON_H

#include <QWidget>

namespace Ui {
class Person;
}

class Person : public QWidget
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = nullptr);
    ~Person();

    bool isValid() const;
    int age() const;
    double weight() const;
    double height() const;
    double bmr() const;
    double bmi() const;
    QString status() const;
    QString name() const;
    QString gender() const;


signals:
    void removed(Person *person);

private:
    Ui::Person *ui;
};

#endif // PERSON_H
