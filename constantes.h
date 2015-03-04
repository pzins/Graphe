#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <QString>
#include <QColor>
//***************************************** SOMMET ********************************
const float OUTLINE_COEFF = 0.1;
const float POSITION_ID_COEFF_X = 0.25;
const float POSITION_ID_COEFF_Y = 0.05;
const QString OUTLINE_COLOR = "#000000";
const QString FONT = "arial";
const float FONT_SIZE_COEFF = 0.5;
//*********************************************************************************


//***************************************** MAINWINDOW ****************************
const int WIN_SIZE_X = 1000;
const int WIN_SIZE_Y = 650;

const int VIEW_SIZE_X = 500;
const int VIEW_SIZE_Y = 650;

const int SCENE_SIZE_X = VIEW_SIZE_X - 5;
const int SCENE_SIZE_Y = VIEW_SIZE_Y - 5;

const int WIDTH_ARC = 5; //GRAPHE

const float MIN_RAD = 10;
const float MAX_RAD = 100;

const int SIZE_WIDGET_SOMMET_X = 150;
const int SIZE_WIDGET_SOMMET_Y = 150;

const int SIZE_WIDGET_ARC_X = 125;
const int SIZE_WIDGET_ARC_Y = 200;


const int DEFAULT_POS_X = 200;
const int DEFAULT_POS_Y = 200;

const int V_OPT_LAYOUT_SPACING = 5;
const int V_ARC_LAYOUT_MARGIN = 25;
const int V_SOMMET_LAYOUT_MARGIN = 25;
//*******************************************************************************




//***************************************** ARC *********************************
const float COEFF_COST_POSITION = 0.05;
const int SIZE_FONT_COST = 14;
//*******************************************************************************


//***************************************** GRAPHE ******************************
const int NO_ARC = 9999;
const QColor COLOR_ARC_DEFAULT = Qt::black;
//*******************************************************************************

#endif
