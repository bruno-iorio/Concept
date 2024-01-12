#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>

class FontSizeWindow : public QWidget {
public:
    FontSizeWindow(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *label = new QLabel("Font Size", this);
        layout->addWidget(label);

        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setRange(1, 100);
        layout->addWidget(slider);

        connect(slider, &QSlider::valueChanged, this, &FontSizeWindow::onSliderValueChanged);
    }

private slots:
    void onSliderValueChanged(int value) {
        // Handle font size change here
        // You can update the font size of your application or any other widget
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FontSizeWindow window;
    window.show();

    return app.exec();
}
