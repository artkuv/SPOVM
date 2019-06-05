#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *m_ui;
    QLabel *m_pic,*m_info;
    QPushButton *m_oKay,*m_cancel;
    QHBoxLayout *m_hlay,*m_hlay0;
    QVBoxLayout *m_vlay,*m_vlay2;
};

#endif // DIALOG_H
