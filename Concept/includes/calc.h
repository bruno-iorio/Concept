#ifndef CALC_H
#define CALC_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <Qlabel>

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
    QPushButton *clearButton;
    QPushButton *allClearButton;
    QPushButton *closeButton;
    QPushButton *dotButton;
    QPushButton *openParenButton;
    QPushButton *closeParenButton;
    QPushButton *squareButton;
    QPushButton *powerButton;

    double evaluateExpression(const QString &expression);

public slots:
    void handleOpenCalculator();
    void UpdateDisplayVal();

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void Clear();
    void AllClear();
    void DotPressed();
    void OpenParenPressed();
    void CloseParenPressed();
    void SquarePressed();
    void PowerPressed();
};
#endif // CALC_H
