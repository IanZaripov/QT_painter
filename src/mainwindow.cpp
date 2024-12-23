#include "moc_mainwindow.cpp"
#include "mainwindow.h"
#include "Design_window.h"
#include <exception>


std::unordered_set<std::shared_ptr<Figure>> all_drawn_figures;
std::shared_ptr<Figure> current_drawing_figure = nullptr;
std::shared_ptr<Figure> current_moving_figure = nullptr;
std::shared_ptr<Figure> first_connecting_figure = nullptr;
std::shared_ptr<Figure> second_connecting_figure = nullptr;


lineWidget::lineWidget(QWidget* parent) : QWidget(parent), ui(new Ui::lineWidget) {
    ui->setupUi(this);
    mPix = QPixmap(800, 700);
    mPix.fill(Qt::white);
    firstcleack = false;
    mouseRightButtonPressed = false;
    mouseWasPressedInFigureArea = false;
    selecttool = selectTool::Remove;
    selectfigure = selectFigure::Ellipse;
}


std::shared_ptr<Figure> lineWidget::FindClosestFigure(QMouseEvent* mouse_click_pos) {
    std::shared_ptr<Figure> res = nullptr;
    int curMin = 1000000;
    for (const auto& fig : all_drawn_figures) {
        if (fig->isMouseClickInsideFigure(mouse_click_pos) == true) {
            auto dist = std::sqrt(std::pow(mouse_click_pos->x() - fig->GetCenter().x(), 2) + std::pow(mouse_click_pos->y() - fig->GetCenter().y(), 2));
            if (dist < curMin) {
                curMin = dist;
                res = fig;
            }
        }
    }
    return res;
}


void lineWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        switch (selecttool)
        {
        case lineWidget::Ffigure:
            current_drawing_figure = nullptr;
            break;
        case lineWidget::Connection:
            first_connecting_figure = nullptr;
            second_connecting_figure = nullptr;
            firstcleack = false;
            update();
            break;
        case lineWidget::Move:
            current_moving_figure = nullptr;
            break;
        case lineWidget::Remove:
            break;
        default:
            break;
        }
    }
    update();
}

FigureType lineWidget::convert(lineWidget::selectFigure selectfigure) {
    if (selectfigure == selectFigure::Rectangle) {
        return FigureType::Rectangle_;
    }
    else if (selectfigure == selectFigure::Ellipse) {
        return FigureType::Ellipse_;
    }
    else if (selectfigure == selectFigure::Triangle) {
        return FigureType::Triangle_;
    }
}

void lineWidget::mousePressEvent(QMouseEvent* event) {
    switch (selecttool)
    {
    case lineWidget::Ffigure:
        if (event->button() == Qt::LeftButton) {
            current_drawing_figure = build_figure(convert(selectfigure));
            current_drawing_figure->StartDrawFigure(event);
        }
        break;
    case lineWidget::Connection:
        this->setMouseTracking(true);
        if (!firstcleack) {
            first_connecting_figure = FindClosestFigure(event);
            if (first_connecting_figure != nullptr) {
                first_connecting_figure->StartDrawConnection(event);
                firstcleack = true;
            }
        }
        else {
            second_connecting_figure = FindClosestFigure(event);
            if (second_connecting_figure != nullptr && first_connecting_figure != second_connecting_figure) {
                first_connecting_figure->FinishDrawConnection(second_connecting_figure);
                second_connecting_figure->FinishDrawConnection(first_connecting_figure);
            }
            firstcleack = false;
            first_connecting_figure = nullptr;
            second_connecting_figure = nullptr;
            update();
            this->setMouseTracking(false);
        }
        break;
    case lineWidget::Move:
        current_moving_figure = FindClosestFigure(event);
        if (current_moving_figure != nullptr) {
            this->setCursor(QCursor(Qt::ClosedHandCursor));
            current_moving_figure->StartMoveFigure(event);
        }
        break;
    case lineWidget::Remove:
        {
            auto current_removing_figure = FindClosestFigure(event);
            if (current_removing_figure != nullptr) {
                for (const auto& fig : all_drawn_figures) {
                    fig->RemoveConnectionWithFigure(current_removing_figure);
                }
                all_drawn_figures.erase(current_removing_figure);
                update();
            }
        }
        break;
    default:
        break;
    }

}

void lineWidget::mouseMoveEvent(QMouseEvent* event) {
    switch (selecttool)
    {
    case lineWidget::Ffigure:
        if (current_drawing_figure != nullptr) {
            current_drawing_figure->UpdateDrawFigure(event);
        }
        update();
        break;
    case lineWidget::Connection:
        if (first_connecting_figure != nullptr) {
            first_connecting_figure->UpdateDrawConnection(event);
            update();
        }
        break;
    case lineWidget::Move:
        if (current_moving_figure != nullptr) {
            current_moving_figure->DoMoveFigure(event);
            update();
        }
        else {
            mouseReleaseEvent(event);
        }
        break;
    case lineWidget::Remove:
        break;
    default:
        break;
    }

}

void lineWidget::mouseReleaseEvent(QMouseEvent* event) {
    switch (selecttool)
    {
    case lineWidget::Ffigure:
        if (current_drawing_figure != nullptr) {
            all_drawn_figures.insert(current_drawing_figure);
        }
        current_drawing_figure = nullptr;
        update();
        break;
    case lineWidget::Connection:
        update();
        break;
    case lineWidget::Move:
        current_moving_figure = nullptr;
        this->setCursor(QCursor(Qt::ArrowCursor));
        break;
    case lineWidget::Remove:
        break;
    default:
        break;
    }
}


void lineWidget::paintEvent(QPaintEvent* event) {
    mPix.fill(Qt::white);
    painter.begin(this);
    painter.drawPixmap(0, 0, mPix);
    painter.setPen(QPen(Qt::black, 2));
    for (const auto& fig : all_drawn_figures) {
        QPainter temp_painter(&mPix);
        temp_painter.setPen(QPen(Qt::black, 2));
        fig->DrawFigure(temp_painter);
        fig->RedrawConnection(temp_painter);
    }
    if (current_drawing_figure != nullptr) {
        QPainter temp_painter(&mPix);
        temp_painter.setPen(QPen(Qt::black, 2));
        current_drawing_figure->DrawFigure(temp_painter);
    }
    if (first_connecting_figure != nullptr && firstcleack) {
        QPainter temp_painter(&mPix);
        temp_painter.setPen(QPen(Qt::black, 2));
        first_connecting_figure->DrawConnection(temp_painter);
    }
    
    painter.drawPixmap(0, 0, mPix);
    painter.end();
}

lineWidget::~lineWidget()
{
    delete ui;
}

void lineWidget::ChangeStyleSheet() {
    ui->Rectangle->setStyleSheet("color:black");
    ui->Triangle->setStyleSheet("color:black");
    ui->Ellipse->setStyleSheet("color:black");
    ui->Move->setStyleSheet("color:black");
    ui->Remove->setStyleSheet("color:black");
    ui->Connection->setStyleSheet("color:black");
    ui->Load->setStyleSheet("color:black");
    ui->Save->setStyleSheet("color:black");
}

void lineWidget::on_Rectangle_clicked()
{
    ChangeStyleSheet();
    selecttool = selectTool::Ffigure;
    selectfigure = selectFigure::Rectangle;
    ui->Rectangle->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

void lineWidget::on_Triangle_clicked()
{
    ChangeStyleSheet();
    selecttool = selectTool::Ffigure;
    selectfigure = selectFigure::Triangle;
    ui->Triangle->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

void lineWidget::on_Ellipse_clicked()
{
    ChangeStyleSheet();
    selecttool = selectTool::Ffigure;
    selectfigure = selectFigure::Ellipse;
    ui->Ellipse->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

void lineWidget::on_Connection_clicked() {
    ChangeStyleSheet();
    selecttool = selectTool::Connection;
    ui->Connection->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

void lineWidget::on_Move_clicked() {
    ChangeStyleSheet();
    selecttool = selectTool::Move;
    ui->Move->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

void lineWidget::on_Remove_clicked() {
    ChangeStyleSheet();
    selecttool = selectTool::Remove;
    ui->Remove->setStyleSheet(QString("QPushButton {background-color: rgb(173,212,182);}"));
}

std::ofstream& operator <<(std::ofstream& ofs, const QPoint& coordinate) {
    ofs << coordinate.x() << ';' << coordinate.y();
    return ofs;
}

int parseNumbers(const std::string& line) {
    int num = 0;
    for (int i = 0; i < line.size(); i++) {
        num *= 10;
        int char_to_int = line[i] - '0';
        num += char_to_int;
    }
    return num;
}

void lineWidget::parseAndSetCondition(std::ifstream& inpt) {
    std::string line;
    int uId;
    std::unordered_map<int,std::shared_ptr<Figure>> uId_to_figure;
    bool haveToSetLeftTop = true;
    if (inpt) {
        while (std::getline(inpt, line,';')) {
            if (line == "Rectangle") {
                current_drawing_figure = build_figure(FigureType::Rectangle_);
                std::getline(inpt, line);
                uId = parseNumbers(line);
                uId_to_figure[uId] = current_drawing_figure;
            }
            else if (line == "Triangle") {
                current_drawing_figure = build_figure(FigureType::Triangle_);
                std::getline(inpt, line);
                uId = parseNumbers(line);
                uId_to_figure[uId] = current_drawing_figure;
            }
            else if (line == "Ellipse") {
                current_drawing_figure = build_figure(FigureType::Ellipse_);
                std::getline(inpt, line);
                uId = parseNumbers(line);
                uId_to_figure[uId] = current_drawing_figure;
            }
            else if (haveToSetLeftTop && current_drawing_figure != nullptr) {
                auto x = parseNumbers(line);
                std::getline(inpt, line);
                auto y = parseNumbers(line);
                current_drawing_figure->setLeftTopCorner(QPoint(x,y));
                haveToSetLeftTop = false;
            }
            else if (!haveToSetLeftTop && current_drawing_figure != nullptr) {
                auto x = parseNumbers(line);
                std::getline(inpt, line);
                auto y = parseNumbers(line);
                current_drawing_figure->setBottomRightCorner(QPoint(x, y));
                all_drawn_figures.insert(current_drawing_figure);
                update();
                current_drawing_figure = nullptr;
                haveToSetLeftTop = true;
            }
            else {
                int uId_first_figure = parseNumbers(line);
                std::getline(inpt, line);
                int uId_second_figure = parseNumbers(line);
                uId_to_figure[uId_first_figure]->FinishDrawConnection(uId_to_figure[uId_second_figure]);
                uId_to_figure[uId_second_figure]->FinishDrawConnection(uId_to_figure[uId_first_figure]);
            }
        }
    }
}

void lineWidget::on_Load_clicked() {
    ChangeStyleSheet();
    current_drawing_figure = nullptr;
    current_moving_figure = nullptr;
    first_connecting_figure = nullptr;
    second_connecting_figure = nullptr;
    all_drawn_figures.clear();
    QString file = QFileDialog::getOpenFileName(this, "Open a File","C:/qtGOD","Text file (*.txt)");
    const std::string path = file.toStdString();
    std::ifstream inpt(path);
    parseAndSetCondition(inpt);
}

void lineWidget::on_Save_clicked() {
    ChangeStyleSheet();
    QString file = QFileDialog::getSaveFileName(this,"Save as...", "MyFile","TXT (*.txt)");
    const std::string path = file.toStdString();
    int uId = 0;
    std::unordered_map<std::shared_ptr<Figure>, int> figure_to_uId;
    std::ofstream fout(path);
    for (const auto& fig : all_drawn_figures) {
        auto type = fig->GetFigureType();
        if (type == FigureType::Rectangle_) {
            fout << "Rectangle" << ';' << uId << std::endl;
        }
        else if (type == FigureType::Triangle_) {
            fout << "Triangle" << ';' << uId << std::endl;
        }
        else if(type == FigureType::Ellipse_){
            fout << "Ellipse" << ';' << uId << std::endl;
        }
        figure_to_uId[fig] = uId;
        fout << fig->GetLeftTopCorner() << std::endl;
        fout << fig->GetBottomRightCorner() << std::endl;
        uId++;
    }
    for (const auto& first_connected_figure : all_drawn_figures) {
        auto first_figure = figure_to_uId.find(first_connected_figure);
        auto connected_figure = first_connected_figure->GetConnectedFigure(); //unordered_set
        for (const auto& second_connected_figure : connected_figure) {
            auto second_figure = figure_to_uId.find(second_connected_figure);
            if (second_figure != figure_to_uId.end()) {
                fout << first_figure->second << ";" << second_figure->second << std::endl;
            }
        }
    }
    /*QString file = QFileDialog::getSaveFileName(this, "Save as...", "MyPicture", "PNG (*.png);; BMP (*.bmp);;TIFF (*.tiff *.tif);; JPEG (*.jpg *.jpeg)");
    mPix.save(file);*/
}