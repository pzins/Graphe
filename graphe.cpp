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


Graphe::Graphe() : isDragging_(-1)
{

}

Graphe::~Graphe()
{

}
int Graphe::readMatrice()
{
    std::ifstream fichier("matrice.txt", std::ios::in);
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
            matrAsso_.push_back(res);

            if(width < v.size())
                width = v.size();
            height++;
        }
        fichier.close();
        if(height != width)
        {
            matrAsso_.clear();
            return -1;
        }
        return height;
    }
    return -1;
}

int Graphe::readSommet()
{
    std::ifstream fichier("sommets.txt", std::ios::in);  // on ouvre en lecture
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
                vectSommet_.push_back(s);
                ++height;
            }
        }
        fichier.close();
        return height;
    }
    return -1;
}


int Graphe::loadGraphe()
{
    int nb_sommet = readSommet();
    int matrice = readMatrice();
    if (nb_sommet == -1 || matrice == -1 || nb_sommet != matrice) return -1;
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
    vectSommet_.push_back(s);
}

void Graphe::addArc(Sommet *origin, Sommet *destination, float width, float cost, QColor color)
{
    Arc* a = new Arc(origin, destination, width, cost, color);
    vectArc_.push_back(a);
}
