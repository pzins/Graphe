#include "mainwindow.h"
#include <QApplication>


int Sommet::nb_sommet = 0; //static member graphe : id_ sommets



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("GTK+"));

    MainWindow w;

    w.show();

    return a.exec();
}
