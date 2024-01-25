#include "calc.h"
#include <QGridLayout>
#include <QString>
#include <QRegularExpression>
#include <QJSEngine>
#include <QJSValue>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool newNumber = true;
QString displayVal = "";

Calc::Calc(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Feel free to use the keyboard!");

    display = new QLineEdit("", this);
    display->setReadOnly(false); // You can edit the line of computations if you want
    display->setAlignment(Qt::AlignRight);
    display->setText("");

    QGridLayout *layout = new QGridLayout(this);

    for (int i = 0; i < 10; ++i)
    {
        numButtons[i] = new QPushButton(QString::number(i), this);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    addButton = new QPushButton("+", this);
    subtractButton = new QPushButton("-", this);
    multiplyButton = new QPushButton("*", this);
    divideButton = new QPushButton("/", this);
    equalsButton = new QPushButton("=", this);
    equalsButton->setDefault(true); // Pressing Enter -> Pressing equal
    changeSignButton = new QPushButton("+/-", this);
    clearButton = new QPushButton("Clear", this);
    allClearButton = new QPushButton("All Clear", this);
    closeButton = new QPushButton("Close", this);
    dotButton = new QPushButton(".", this);
    openParenButton = new QPushButton("(", this);
    squareButton = new QPushButton("x**2", this);
    powerButton = new QPushButton("x**y", this);
    closeParenButton = new QPushButton(")", this);

    connect(addButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(subtractButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(multiplyButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(divideButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(equalsButton, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(changeSignButton, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(clearButton, SIGNAL(released()), this, SLOT(Clear()));
    connect(allClearButton, SIGNAL(released()), this, SLOT(AllClear()));
    connect(closeButton, SIGNAL(released()), this, SLOT(close()));
    connect(dotButton, SIGNAL(released()), this, SLOT(DotPressed()));
    connect(openParenButton, SIGNAL(released()), this, SLOT(OpenParenPressed()));
    connect(closeParenButton, SIGNAL(released()), this, SLOT(CloseParenPressed()));
    connect(squareButton, SIGNAL(released()), this, SLOT(SquarePressed()));
    connect(powerButton, SIGNAL(released()), this, SLOT(PowerPressed()));

    connect(display, SIGNAL(textChanged(const QString &)), this, SLOT(UpdateDisplayVal()));

    layout->addWidget(display, 0, 0, 1, 4);
    layout->addWidget(openParenButton, 1, 0);
    layout->addWidget(closeParenButton, 1, 1);
    layout->addWidget(squareButton, 1, 2);
    layout->addWidget(powerButton, 1, 3);
    layout->addWidget(addButton, 1, 4);
    layout->addWidget(numButtons[1], 2, 0);
    layout->addWidget(numButtons[2], 2, 1);
    layout->addWidget(numButtons[3], 2, 2);
    layout->addWidget(addButton, 2, 3);
    layout->addWidget(numButtons[4], 3, 0);
    layout->addWidget(numButtons[5], 3, 1);
    layout->addWidget(numButtons[6], 3, 2);
    layout->addWidget(subtractButton, 3, 3);
    layout->addWidget(numButtons[7], 4, 0);
    layout->addWidget(numButtons[8], 4, 1);
    layout->addWidget(numButtons[9], 4, 2);
    layout->addWidget(multiplyButton, 4, 3);
    layout->addWidget(changeSignButton, 5, 0);
    layout->addWidget(numButtons[0], 5, 1);
    layout->addWidget(dotButton, 5, 2);
    layout->addWidget(divideButton, 5, 3);
    layout->addWidget(allClearButton, 6, 0);
    layout->addWidget(clearButton, 6, 1);
    layout->addWidget(equalsButton, 6, 2);
    layout->addWidget(closeButton, 6, 3);

    setLayout(layout);
}

Calc::~Calc(){};

void Calc::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    displayVal += butVal;
    display->setText(displayVal);
}

void Calc::MathButtonPressed()
{

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    displayVal += " " + butVal + " ";
    display->setText(displayVal);
}

void Calc::EqualButtonPressed()
{
    double solution = evaluateExpression(displayVal);
    display->setText(QString::number(solution));
    displayVal = "";
    newNumber = true;
}

double Calc::evaluateExpression(const QString &expression)
{
    QJSEngine engine;
    QJSValue result = engine.evaluate(expression);
    return result.toNumber();
}

void Calc::ChangeNumberSign()
{
    if (displayVal.endsWith("-"))
    {
        // If the last character is a "-", remove it
        displayVal.chop(1);
    }
    else
    {
        displayVal += "-";
    }

    // Update the display
    display->setText(displayVal);
}

void Calc::DotPressed()
{
    displayVal += ".";
    display->setText(displayVal);
}

void Calc::OpenParenPressed()
{
    displayVal += "(";
    display->setText(displayVal);
}

void Calc::CloseParenPressed()
{
    displayVal += ")";
    display->setText(displayVal);
}

void Calc::SquarePressed()
{
    displayVal += "**2";
    display->setText(displayVal);
}

void Calc::PowerPressed()
{
    displayVal += "**";
    display->setText(displayVal);
}

void Calc::Clear()
{
    displayVal.chop(1);
    display->setText(displayVal);
}

void Calc::AllClear()
{
    displayVal = "";
    display->setText("");
    newNumber = true;
}

void Calc::handleOpenCalculator()
{
    Calc calcPopup;
    calcPopup.exec();
}

void Calc::UpdateDisplayVal()
{
    displayVal = display->text();
}
