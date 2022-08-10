#pragma once
#include "observer.h"
#include "widget_model.h"

std::map<WIDGET_TYPE, std::string> debug_widget_output{
        { WIDGET_TYPE::RECTANGLE, "Rectangle" },
        { WIDGET_TYPE::CIRCLE, "Circle" },
        { WIDGET_TYPE::SQUARE, "Square" },
        { WIDGET_TYPE::TRIANGLE, "Triangle" }
};

class Widget : Observer<WidgetModel>{
protected:
    WidgetModel* _model;
    std::vector<Widget*> _child_wgts;
public:
    Widget(WidgetModel* wgt) : _model(wgt) {
        _model->addObserver(*this);
        std::cout << "Create widget " << debug_widget_output[_model->_type] << std::endl;
    }

    void move(double offset_x, double offset_y) {
        _model->_pos.x += offset_x;
        _model->_pos.y += offset_y;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_x, offset_y);
        }
    }
    void move(Point& point) {
        std::cout << "Move widget " << debug_widget_output[_model->_type] << std::endl;
        auto offset_x = point.x - _model->_pos.x;
        auto offset_y = point.x - _model->_pos.y;
        _model->_pos = point;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_x, offset_y);
        }
    }
    void resize(double offset_w, double offset_h) {
        _model->_size.w += offset_w;
        _model->_size.h += offset_h;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_w, offset_h);
        }
    }
    void resize(Size sz) {
        std::cout << "Resize widget " << debug_widget_output[_model->_type] << std::endl;
        auto offset_w = sz.w - _model->_size.w;
        auto offset_h = sz.h - _model->_size.h;
        _model->_size = sz;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_w, offset_h);
        }
    }
    void changeColor(COLOR col) {
        std::cout << "Change widget color " << debug_widget_output[_model->_type] << std::endl;
        _model->_color = col;
    }

    void handle(WidgetModel& model, const CHANGE_TYPE &type) override{
        switch(type) {
            case CHANGE_TYPE::COLOR:
                changeColor(model._color);
                break;
            case CHANGE_TYPE::MOVE:
                move(model._pos);
                break;
            case CHANGE_TYPE::SIZE:
                resize(model._size);
                break;
        }
    }

    virtual void draw() = 0;
};

class Circle: public Widget{
public:
    Circle(WidgetModel* wgt) : Widget(wgt) { std::cout << "Circle create" << std::endl;}
    void draw() override{
        std::cout << "Circle draw" << std::endl;
    }
};

class Square: public Widget{
public:
    Square(WidgetModel* wgt) : Widget(wgt) { std::cout << "Square create" << std::endl;}
    void draw() override{
        std::cout << "Square draw" << std::endl;
    }
};

class Triangle: public Widget{
public:
    Triangle(WidgetModel* wgt) : Widget(wgt) { std::cout << "Triangle create" << std::endl;}
    void draw() override{
        std::cout << "Triangle draw" << std::endl;
    }
};

class Rectangle: public Widget{
public:
    Rectangle(WidgetModel* wgt) : Widget(wgt) { std::cout << "Rectangle create" << std::endl;}
    void draw() override{
        std::cout << "Rectangle draw" << std::endl;
    }
};

class WidgetViewBuilder {
public:
    static Widget* create(WidgetModel* wgt,WIDGET_TYPE type) {
        switch(type) {
            case WIDGET_TYPE::CIRCLE:
                return new Circle(wgt);
            case WIDGET_TYPE::RECTANGLE:
                return new Rectangle(wgt);
            case WIDGET_TYPE::SQUARE:
                return new Square(wgt);
            case WIDGET_TYPE::TRIANGLE:
                return new Triangle(wgt);
        }
        return nullptr;
    }
};
