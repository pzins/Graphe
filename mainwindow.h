#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>

#include "sommet.h"
#include "arc.h"
#include "graphe.h"
#include "mygraphicsview.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget* main_widget_;
    QWidget* opt_widget_;
    QWidget* sommet_widget_;
    QWidget* arc_widget_;

    QGraphicsScene* scene_;
    MyGraphicsView* view_;
    QComboBox* combo_origin_;
    QComboBox* combo_dest_;
    QComboBox* combo_color_arc_;
    QComboBox* combo_color_sommet_;
    QPushButton* bt_add_sommet_;
    QPushButton* bt_add_arc_;
    QPushButton* bt_compute_;
    QLineEdit* edit_radius_;
    QLineEdit* edit_cost_;

    QHBoxLayout* h_main_layout_;
    QVBoxLayout* v_opt_layout_;
    QVBoxLayout* v_arc_layout_;
    QVBoxLayout* v_sommet_layout_;

private slots:
    void handleAddSommet();
    void handleAddArc();
    void updateComboArc();
    void compute();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
};

void computeColorCombo(QComboBox* combo);
QColor getColorCombo(int a);
float getLineEdit(QString str);

#endif // MAINWINDOW_H
