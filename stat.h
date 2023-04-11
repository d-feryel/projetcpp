#ifndef STAT_H
#define STAT_H

#include <QDialog>

namespace Ui {
class stat;
}

class stat : public QDialog
{
    Q_OBJECT

public:
    explicit stat(QWidget *parent = nullptr);
    ~stat();

private:
    Ui::stat *ui;
};

#endif // STAT_H
