#include "sommet.h"



Sommet::Sommet(float x, float y, float radius, QColor color):
               id_(nb_sommet), x_(x), y_(y), radius_(radius), color_(color)
{
    nb_sommet++;
}

Sommet::~Sommet()
{

}


void  Sommet::draw(QGraphicsScene* scene)
{
    QRect sommet(0,0,radius_,radius_);
    sommet.moveTo(x_,y_);
    QColor color(OUTLINE_COLOR);
    QPen pen(color, radius_ * OUTLINE_COEFF, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush(color_);
    scene->addEllipse(sommet,pen, brush);

    QFont font(FONT, radius_ * FONT_SIZE_COEFF);
    font.setBold(true);
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setFont(font);
    io->setPos(x_ + radius_ * POSITION_ID_COEFF_X, y_ + radius_ * POSITION_ID_COEFF_Y);
    io->setPlainText(QString::number(id_));
    io->setDefaultTextColor(Qt::black);

    scene->addItem(io);
}
