#include "calc.h"
#include <QGridLayout>
#include <QString>
#include <QRegularExpression>

// Variables for storing the current calculation
double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool newNumber = true;

Calc::Calc(QWidget *parent) : QDialog(parent)
{
    // Create the display
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setText("0");

    // Create a grid layout
    QGridLayout *layout = new QGridLayout(this);

    // Create and place number buttons
    for (int i = 0; i < 10; ++i)
    {
        numButtons[i] = new QPushButton(QString::number(i), this);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    // Create and configure arithmetic buttons
    addButton = new QPushButton("+", this);
    subtractButton = new QPushButton("-", this);
    multiplyButton = new QPushButton("*", this);
    divideButton = new QPushButton("/", this);
    equalsButton = new QPushButton("=", this);
    changeSignButton = new QPushButton("+/-", this);

    // Connect signals and slots for arithmetic buttons
    connect(addButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(subtractButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(multiplyButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(divideButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(equalsButton, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(changeSignButton, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

    // Arrange buttons in the grid layout
    layout->addWidget(display, 0, 0, 1, 4); // Span 4 columns
    // Add number buttons to the layout
    // Example layout (you can modify as needed)
    int pos = 0;
    for (int row = 1; row <= 4; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (row == 4 && col == 0)
            {
                layout->addWidget(changeSignButton, row, col);
            }
            else
            {
                layout->addWidget(numButtons[pos++], row, col);
            }
        }
    }
    // Add operation buttons
    layout->addWidget(addButton, 1, 3);
    layout->addWidget(subtractButton, 2, 3);
    layout->addWidget(multiplyButton, 3, 3);
    layout->addWidget(divideButton, 4, 3);
    layout->addWidget(equalsButton, 4, 2);

    // Set the layout
    setLayout(layout);
}

Calc::~Calc()
{
    // No need to delete UI elements; Qt handles it
}

void Calc::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = display->text();

    if ((displayVal.toDouble() == 0 && displayVal != ".") || newNumber)
    {
        display->setText(butVal);
        newNumber = false;
    }
    else
    {
        QString newVal = displayVal + butVal;
        display->setText(newVal);
    }
}

void Calc::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if (butVal == "/")
    {
        divTrigger = true;
    }
    else if (butVal == "*")
    {
        multTrigger = true;
    }
    else if (butVal == "+")
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }

    display->setText("");
}

void Calc::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTrigger)
    {
        solution = calcVal + dblDisplayVal;
    }
    else if (subTrigger)
    {
        solution = calcVal - dblDisplayVal;
    }
    else if (multTrigger)
    {
        solution = calcVal * dblDisplayVal;
    }
    else
    {
        solution = calcVal / dblDisplayVal;
    }

    display->setText(QString::number(solution));

    newNumber = true;
}

void Calc::ChangeNumberSign()
{
    QString displayVal = display->text();
    QRegularExpression reg("[-+]?[0-9.]*");

    if (reg.match(displayVal).hasMatch())
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        display->setText(QString::number(dblDisplayValSign));
    }
}

void Calc::handleOpenCalculator()
{
    Calc calcPopup;
    calcPopup.exec();
}
