#ifndef GRAPHE_H
#define GRAPHE_H
#include <vector>
#include "sommet.h"
#include "arc.h"



class Graphe
{
private:
    std::vector<Sommet*> vectSommet_;
    std::vector<Arc*> vectArc_;
    QVector<QVector<int> > matrAsso_;
    int isDragging_;

public:
    Graphe();
    ~Graphe();

    int readMatrice();
    int readSommet();
    int loadGraphe();
    void compute(QGraphicsScene* scene);
    void moveSommet(double x, double y);
    void addSommet(double x, double y, double radius, QColor color);
    void addArc(Sommet* origin, Sommet* destination, float width, float cost, QColor color);

    std::vector<Sommet*> getVectSommet(){return vectSommet_;}
    std::vector<Arc*> getVectArc(){return vectArc_;}
    QVector<QVector<int> > getMatrAsso(){return matrAsso_;}
    int getIsDragging(){return isDragging_;}


    void setMatrAsso(QVector<QVector<int> > matrAsso){matrAsso_ = matrAsso;}
    void setIsDragging(int i){isDragging_ = i;}
};


#endif // GRAPHE_H
