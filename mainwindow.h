#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_Insertion_sort_clicked();

    void on_Quicksort_clicked();

    void on_Heap_sort_clicked();

    void on_Counting_clicked();

    void on_Show_list_clicked();

    void on_Show_tree_clicked();

    void on_Generate_clicked();

    void on_Add_clicked();

private:
    Ui::MainWindow *ui;
};
