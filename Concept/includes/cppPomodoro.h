#include <QRect>
#include <QLayout>
#include <QLabel>
#include <QQuickItem>
#include <QQuickView>
#include <QWidget>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class Pomodoro : public QWidget {
Q_OBJECT

public:
    Pomodoro(QWidget *parent = nullptr);
    ~Pomodoro();
private:
    QWidget* studyTimerBlock;
    QLabel* studyTimerText; 
    QWidget* timerBlock;

    QVBoxLayout* rowLayout;
    QPushButton* studyButton;
    QWidget* spacerButtonsTimerBlock;
    QPushButton* breakButton;
};

class PomodoroQML : public QObject {
Q_OBJECT

public:
    PomodoroQML(QObject *parent = nullptr);
    ~PomodoroQML();
private:
    
}

class CalendarQML : public QObject {
    Q_OBJECT
public:
    CalendarQML(QObject *parent = nullptr);

public slots:
    void showCalendar();

private:
    Calendar *myCalendar;

signals:
    void File();
};