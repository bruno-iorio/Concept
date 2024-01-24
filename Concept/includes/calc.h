#ifndef CALC_H
#define CALC_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>

class Calc : public QDialog
{
    Q_OBJECT

public:
    explicit Calc(QWidget *parent = nullptr);
    ~Calc();

private:
    QLineEdit *display;
    QPushButton *numButtons[10];
    QPushButton *addButton;
    QPushButton *subtractButton;
    QPushButton *multiplyButton;
    QPushButton *divideButton;
    QPushButton *equalsButton;
    QPushButton *changeSignButton;

public slots:
    void handleOpenCalculator();

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
};

#endif // CALC_H
