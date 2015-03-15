#include "graphe.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

#define NAME_MATRICE_FILE "matrice.txt"
#define NAME_SOMMETS_FILE "sommets.txt"
#define NAME_ALPHA_FILE "alpha.txt"
#define NAME_BETA_FILE "beta.txt"

Graphe::Graphe() : isDragging_(-1)
{

}

Graphe::~Graphe()
{
}




/*
 * read alpha beta vector from file
 * read sommets vector from file
 * load arcs from alpha beta and sommet
 * return -1 if problem with nb sommet, else 0
 */
int Graphe::loadAlphaBeta()
{
    vectSommet_ = readSommet(NAME_SOMMETS_FILE);
    alpha_ = readVector(NAME_ALPHA_FILE);
    beta_ = readVector(NAME_BETA_FILE);
    if(alpha_.size() - 1 != vectSommet_.size()) return -1;
    for(unsigned int i = 0; i < alpha_.size(); ++i)
    {
        for(int j = alpha_[i]; j < alpha_[i+1]; ++j)
        {
            Arc* a = new Arc(vectSommet_[i], vectSommet_[beta_[j]], WIDTH_ARC, 10,COLOR_ARC_DEFAULT);
            vectArc_.push_back(a);
        }
    }
    return 0;

}

/*
 * read matrice from matrice file
 * read sommets vector from file
 * load arcs from matrice and sommet
 * return -1 if problem with nb sommet, else 0
 */
int Graphe::loadMatrice()
{
    vectSommet_ = readSommet(NAME_SOMMETS_FILE);
    matrAsso_ = readMatrice(NAME_MATRICE_FILE);
    if (matrAsso_.size() != vectSommet_.size()) return -1;
    for(int i = 0; i < matrAsso_.size(); ++i)
    {
        for(int j = 0; j < matrAsso_.size(); ++j)
        {
            if(matrAsso_[i][j] != NO_ARC)
            {
               Arc* a = new Arc(vectSommet_[i], vectSommet_[j], WIDTH_ARC, matrAsso_[i][j],COLOR_ARC_DEFAULT);
               vectArc_.push_back(a);
            }
        }
    }
    return 0;
}


void Graphe::compute(QGraphicsScene* scene)
{
    for(unsigned int i = 0; i < vectArc_.size(); ++i)
    {
        vectArc_[i]->draw(scene);
    }

    for(unsigned int i = 0; i < vectSommet_.size(); ++i)
    {
        vectSommet_[i]->draw(scene);
    }
}


void Graphe::moveSommet(double x, double y)
{
    if(isDragging_ <= 0)
    {
        for(unsigned int i = 0; i < vectSommet_.size(); ++i)
        {
            if(sqrt(pow(x - (vectSommet_[i]->getX() + vectSommet_[i]->getRadius()),2) +
                pow(y - (vectSommet_[i]->getY() + vectSommet_[i]->getRadius()),2)) <= vectSommet_[i]->getRadius())
            {
                isDragging_ = i;
                break;
            }
        }
    }
    if (isDragging_ >= 0)
    {
        vectSommet_[isDragging_]->setX(x - vectSommet_[isDragging_]->getRadius());
        vectSommet_[isDragging_]->setY(y - vectSommet_[isDragging_]->getRadius());
    }
}

void Graphe::addSommet(double x, double y, double radius, QColor color)
{
    Sommet* s = new Sommet(x,y,radius,color);
    //update matrAsso
    for(int i = 0; i < matrAsso_.size(); ++i) matrAsso_[i].push_back(NO_ARC);
    QVector<int> nouv(matrAsso_.size()+1,NO_ARC);
    matrAsso_.push_back(nouv);

    vectSommet_.push_back(s);
    //loadMatrice();
}


void Graphe::addArc(Sommet *origin, Sommet *destination, float width, float cost, QColor color)
{
    Arc* a = new Arc(origin, destination, width, cost, color);
    matrAsso_[origin->getId()][destination->getId()] = cost;

    vectArc_.push_back(a);
}



/*
 * read sommet file
 * create all sommets
 * return vector containing pointer to sommets
 */
 std::vector<Sommet*> readSommet(const char* name)
{
    std::vector<Sommet*> ret;
    std::ifstream fichier(name, std::ios::in);
    if(fichier)
    {
        std::string contenu;
        int height = 0;
        int ite = 0;
        while(std::getline(fichier, contenu))
        {
            std::vector<std::string> v;
            if(ite++)
            {
                std::istringstream buf(contenu);
                for(std::string token; getline(buf, token, ' '); )
                    v.push_back(token);

                Sommet* s;
                if(v.size())
                {
                    QString x = QString::fromStdString(v.at(0));
                    QString y = QString::fromStdString(v.at(1));
                    QString r = QString::fromStdString(v.at(2));
                    QString c = QString::fromStdString(v.at(3));
                    int xPos = x.toInt();
                    int yPos = y.toInt();
                    float rad = r.toFloat();
                    QColor col(c);
                    s = new Sommet(xPos, yPos, rad, col);
                }
                else s = new Sommet();
                ret.push_back(s);
                ++height;
            }
        }
        fichier.close();
    }
    return ret;
}

/*
 * read matrice file
 * return matrice (QVector<QVector<int> >) containing arc between sommets
 * if matrice in file not square => ret matrice is void
 */
QVector<QVector<int> > readMatrice(const char* name)
{
    QVector<QVector<int> > ret;
    std::ifstream fichier(name, std::ios::in);
    if(fichier)
    {
        std::string contenu;
        unsigned int height = 0;
        unsigned int width = 0;
        while(std::getline(fichier, contenu))
        {
            std::vector<std::string> v;
            QVector<int> res;

            std::istringstream buf(contenu);
            for(std::string token; getline(buf, token, ' ');)
                v.push_back(token);

            QString c;
            int b;
            for(unsigned int i = 0; i < v.size(); ++i)
            {
                c = QString::fromStdString(v.at(i));
                b = c.toInt();
                res.push_back(b);
            }
            ret.push_back(res);

            if(width < v.size())
                width = v.size();
            height++;
        }
        fichier.close();
        if(height != width)
        {
            ret.clear();
        }
    }
    return ret;
}






 /*
  * read vector<int> from file
  * return the vector
  */
 std::vector<int> readVector(const char* name)
 {
     std::vector<int> ret;
     std::ifstream fichier(name, std::ios::in);
     if(fichier)
     {
         std::string contenu;
         std::getline(fichier, contenu);
         std::vector<std::string> res;
         std::istringstream buf(contenu);
         for(std::string token; getline(buf, token, ' ');)
             res.push_back(token);
        for(unsigned int i = 0; i < res.size(); ++i)
        {
            QString str = QString::fromStdString(res[i]);
            ret.push_back(str.toInt());
        }
     }
     return ret;
 }


 QVector<int>* Graphe::getSuccDirect(Sommet* s)
 {
     QVector<int>* res = new QVector<int>();
     for(int i = 0; i < matrAsso_.size(); ++i)
     {
         if(matrAsso_[s->getId()][i] != NO_ARC)
             res->push_back(i);
     }
     return res;
 }

 QVector<int> *Graphe::getPredDirect(Sommet* s)
 {
     QVector<int>* res = new QVector<int>();
     for(int i = 0; i < matrAsso_.size(); ++i)
     {
         if(matrAsso_[i][s->getId()] != NO_ARC)
             res->push_back(i);
     }
     return res;
 }
