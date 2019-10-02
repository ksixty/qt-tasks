#ifndef TASKS_H
#define TASKS_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Tasks; }
QT_END_NAMESPACE

class Tasks : public QMainWindow
{
    Q_OBJECT

public:
    Tasks(QWidget *parent = nullptr);
    ~Tasks();

private slots:
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_removeButton_clicked();
    void on_doneButton_clicked();

    void on_actionToggle_Status_triggered();

    void on_actionRemove_Selected_Task_triggered();

private:
    Ui::Tasks *ui;
    void alert(QString text);
    void set_current_file(QString filename);
    void read_current_file();
    void update_view();
    QString current_file;
    QVector<struct task> current_tasks;
    QStringListModel *model;
    unsigned int current_todo;

    void add_task(QString title);
    void remove_task(int id);
    void toggle_task(int id);
    void save_current_file();
};
#endif // TASKS_H
