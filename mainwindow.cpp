#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(WIN_SIZE_X,WIN_SIZE_Y);

    h_main_layout_ = new QHBoxLayout();
    v_opt_layout_ = new QVBoxLayout();
    v_arc_layout_ = new QVBoxLayout();
    v_sommet_layout_ = new QVBoxLayout();

    v_arc_layout_->setMargin(V_ARC_LAYOUT_MARGIN);
    v_opt_layout_->setAlignment(Qt::AlignCenter);
    v_opt_layout_->setSpacing(V_OPT_LAYOUT_SPACING);
    v_sommet_layout_->setMargin(V_SOMMET_LAYOUT_MARGIN);

    main_widget_ = new QWidget(this);
    main_widget_->setLayout(h_main_layout_);

    this->setCentralWidget(main_widget_);

    opt_widget_ = new QWidget(main_widget_);
    opt_widget_->setLayout(v_opt_layout_);
    opt_widget_->setStyleSheet("border: 2px solid black; border-radius: 25px;");

    arc_widget_ = new QWidget(opt_widget_);
    arc_widget_->setLayout(v_arc_layout_);
    arc_widget_->setMaximumSize(SIZE_WIDGET_ARC_X, SIZE_WIDGET_ARC_Y);

    sommet_widget_ = new QWidget();
    sommet_widget_->setLayout(v_sommet_layout_);
    sommet_widget_->setMaximumSize(SIZE_WIDGET_SOMMET_X, SIZE_WIDGET_SOMMET_Y);

    scene_ = new QGraphicsScene(main_widget_);
    scene_->setSceneRect(0,0,SCENE_SIZE_X,SCENE_SIZE_Y);

    view_ = new MyGraphicsView(scene_,main_widget_);
    view_->setFixedSize(VIEW_SIZE_X,VIEW_SIZE_Y);
    view_->setBackgroundBrush(Qt::white);


    bt_add_sommet_ = new QPushButton("Add Sommet",sommet_widget_);

    combo_color_sommet_ = new QComboBox(sommet_widget_);
    edit_radius_ = new QLineEdit(sommet_widget_);

    bt_add_arc = new QPushButton("Add Arc", arc_widget_);
    combo_origin_ = new QComboBox(arc_widget_);
    combo_dest_ = new QComboBox(arc_widget_);
    combo_color_arc_ = new QComboBox(arc_widget_);
    edit_cost_ = new QLineEdit(arc_widget_);

    edit_cost_->setText("Cost");
    edit_radius_->setText("Radius");
    computeColorCombo(combo_color_sommet_);
    computeColorCombo(combo_color_arc_);


    h_main_layout_->addWidget(view_);
    h_main_layout_->addWidget(opt_widget_);
    v_opt_layout_->addWidget(sommet_widget_);
    v_opt_layout_->addWidget(arc_widget_);

    v_sommet_layout_->addWidget(bt_add_sommet_);
    v_sommet_layout_->addWidget(edit_radius_);
    v_sommet_layout_->addWidget(combo_color_sommet_);

    v_arc_layout_->addWidget(bt_add_arc);
    updateComboArc();
    v_arc_layout_->addWidget(edit_cost_);
    v_arc_layout_->addWidget(combo_color_arc_);


    sommet_widget_->setStyleSheet("font: bold 14px; color: black;");
    arc_widget_->setStyleSheet("font: bold 14px; color: black;");
    edit_cost_->setStyleSheet("font: italic 12px; color: rgb(100, 100, 100);");
    edit_radius_->setStyleSheet("font: italic 12px; color: rgb(100, 100, 100);");


    connect(bt_add_sommet_, SIGNAL(clicked()), this, SLOT(handleAddSommet()));
    connect(bt_add_sommet_, SIGNAL(clicked()), this, SLOT(updateComboArc()));
    connect(bt_add_arc, SIGNAL(clicked()), this, SLOT(handleAddArc()));

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::handleAddSommet()
{
    QColor col = getColorCombo(combo_color_sommet_->currentIndex());
    QString rad = edit_radius_->text();
    float res = getLineEdit(rad);
    if(res == -1 || res > MAX_RAD || res < MIN_RAD)
        QMessageBox::critical(this, "ERROR", "Please enter a radius!");
    else
    {
        view_->getGraphe()->addSommet(DEFAULT_POS_X,DEFAULT_POS_Y,res,col);
        scene_->clear();
        view_->getGraphe()->compute(scene_);
    }
}

void MainWindow::handleAddArc()
{
    QColor col = getColorCombo(combo_color_arc_->currentIndex());
    QString dest = combo_dest_->currentText();
    QString ori= combo_origin_->currentText();
    QString cost = edit_cost_->text();
    float res = getLineEdit(cost);
    if(res == -1)
            QMessageBox::critical(this, "ERROR", "Please enter a cost!");
    else
    {
        int d = dest.toInt();
        int o = ori.toInt();
        view_->getGraphe()->addArc(view_->getGraphe()->getVectSommet().at(o),
                                   view_->getGraphe()->getVectSommet().at(d),
                                   WIDTH_ARC,res, col);
        scene_->clear();
        view_->getGraphe()->compute(scene_);
    }
}

void MainWindow::updateComboArc()
{
    combo_dest_->clear();
    combo_origin_->clear();
    for(unsigned int i = 0; i < view_->getGraphe()->getVectSommet().size(); ++i)
    {
        QString str = QString::number(view_->getGraphe()->getVectSommet().at(i)->getId());
        combo_origin_->addItem(str);
        combo_dest_->addItem(str);
    }
    v_arc_layout_->addWidget(combo_origin_);
    v_arc_layout_->addWidget(combo_dest_);
}

void computeColorCombo(QComboBox* combo)
{
    combo->addItem("Blue");
    combo->addItem("Dark Blue");
    combo->addItem("Red");
    combo->addItem("Dark Red");
    combo->addItem("Green");
    combo->addItem("Dark Green");
    combo->addItem("Yellow");
    combo->addItem("Dark Yellow");
    combo->addItem("Cyan");
    combo->addItem("Dark Cyan");
    combo->addItem("Magenta");
    combo->addItem("Dark Magenta");
    combo->addItem("Grey");
    combo->addItem("Dark Grey");
}

QColor getColorCombo(int a)
{
    switch (a) {
    case 0: return Qt::blue;
    case 1: return Qt::darkBlue;
    case 2: return Qt::red;
    case 3: return Qt::darkRed;
    case 4: return Qt::green;
    case 5: return Qt::darkGreen;
    case 6: return Qt::yellow;
    case 7: return Qt::darkYellow;
    case 8: return Qt::cyan;
    case 9: return Qt::darkCyan;
    case 10: return Qt::magenta;
    case 11: return Qt::darkMagenta;
    case 12: return Qt::gray;
    case 13: return Qt::darkGray;
    }
    return Qt::blue;
}

float getLineEdit(QString str)
{
    bool ok;
    float value = str.toFloat(&ok);
    if(!ok) return -1;
    else return value;
}

