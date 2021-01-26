//
// Created by nullobsi on 2021/01/25.
//

#ifndef CLIGHT_GUI_SCROLLSYSTRAY_H
#define CLIGHT_GUI_SCROLLSYSTRAY_H
#include <QSystemTrayIcon>
#include <QEvent>
#include <QWheelEvent>
class ScrollSysTray : public QSystemTrayIcon {
    Q_OBJECT
public:
    explicit ScrollSysTray(QObject *parent = nullptr);
    explicit ScrollSysTray(const QIcon &icon, QObject *parent = nullptr);

public slots:

signals:
    void ScrollUp();
    void ScrollDown();

protected:
    bool event(QEvent *e) override;

private:
    int combinedDelta = 0;
};


#endif //CLIGHT_GUI_SCROLLSYSTRAY_H
