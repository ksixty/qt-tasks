#include "tasks.h"
#include "ui_tasks.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QListWidget>
#include <QStringListModel>
#include <QDateTime>
#include <QAbstractItemView>

#define DELIMITER "    "

struct task
{
    QString title;
    long long time;
    bool done;
};

extern QString current_file;
extern QVector<struct task> current_tasks;
extern unsigned int current_todo;

Tasks::Tasks(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tasks)
{
    ui->setupUi(this);
    current_file = "";
    update_view();
}

Tasks::~Tasks()
{
    delete ui;
}

void Tasks::read_current_file()
{
    QFile file(current_file);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        alert("Could not open the file");
        return;
    }

    current_todo = 0;

    current_tasks.clear();
    QTextStream current_ts(&file);
    while (!current_ts.atEnd()) {
       QStringList item = current_ts.readLine().split(DELIMITER);
       if (item.size() == 3) {
           struct task task
           {
                   item[0],
                   item[1].toInt(),
                   item[2] == "DONE" ? true : false
           };
           current_tasks.append(task);
           if (!task.done) current_todo++;
       }
    }
    file.close();
}

void Tasks::save_current_file()
{
    if (current_file.length() > 0) {
       QFile file(current_file);
       if (!file.open(QFile::ReadWrite | QFile::Truncate | QFile::Text)) {
           alert("Could not save the file");
           return ;
       }
       QTextStream current_ts(&file);
       for (int i = 0; i < current_tasks.size(); i++) {
           struct task task = current_tasks[i];
           current_ts << task.title << DELIMITER
                      << task.time << DELIMITER
                      << (task.done ? "DONE" : "TODO") << endl;
       }

    }
}

void Tasks::update_view()
{
    model = new QStringListModel(this);
    QStringList items;

    for (int i = 0; i < current_tasks.size(); i++) {
        QString time = QDateTime
                ::fromSecsSinceEpoch(current_tasks[i].time)
                .toString("yyyy-MM-dd HH:mm:ss");

        items.append((current_tasks[i].done ? "★ " : "☆ ") +
                     current_tasks[i].title + " [" +
                     time + "]");
    }
    model->setStringList(items);
    ui->listView->setModel(model);
    Tasks::setWindowTitle((current_file.length() > 0
                           ? current_file
                           : "Unsaved File") + " — " +
                          (current_todo > 0
                           ? QString::number(current_todo) + " To Do — Tasks"
                           : "Tasks"));
    ui->listView->setCurrentIndex(model->index(0, 0));
}

void Tasks::add_task(QString title)
{
    current_todo++;
    struct task task { title, QDateTime::currentSecsSinceEpoch(), false };
    current_tasks.prepend(task);
    update_view();
}

void Tasks::remove_task(int id)
{
    if (current_tasks.size() > 0 && id > -1) {
        if (!current_tasks[id].done) current_todo--;
        current_tasks.remove(id);
        update_view();
    }
}

void Tasks::toggle_task(int id)
{
    if (current_tasks.size() > 0 && id > -1) {
        current_tasks[id].done ^= 1;
        if (current_tasks[id].done) {
            current_todo--;
        } else {
            current_todo++;
        }
        update_view();
    }
}

void Tasks::alert(QString text)
{
       QMessageBox alertbox;
       alertbox.setText(text);
       alertbox.exec();
}

void Tasks::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Tasks List"),
                                                    QDir::homePath(), tr("Text Documents (*.txt)"));
    current_file = filename;
    read_current_file();
    update_view();
}

void Tasks::on_actionNew_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Tasks List"),
                               QDir::homePath() + "/list.txt", tr("Text Documents (*.txt)"));
    current_file = filename;
    update_view();
}

void Tasks::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text().simplified();
    if (text.length()) {
        add_task(text);
        save_current_file();
    }
    ui->lineEdit->setText("");
}

void Tasks::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text().simplified();
    if (text.length()) {
        add_task(text);
        save_current_file();
    }
    ui->lineEdit->setText("");
}

void Tasks::on_removeButton_clicked()
{
    remove_task(ui->listView->currentIndex().row());
    save_current_file();
}

void Tasks::on_doneButton_clicked()
{
    toggle_task(ui->listView->currentIndex().row());
    save_current_file();
}

void Tasks::on_actionToggle_Status_triggered()
{
    toggle_task(ui->listView->currentIndex().row());
    save_current_file();
}

void Tasks::on_actionRemove_Selected_Task_triggered()
{
    remove_task(ui->listView->currentIndex().row());
    save_current_file();
}
