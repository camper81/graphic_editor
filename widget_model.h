#pragma once
#include "observer.h"

enum COLOR{
    RED, GREEN, BLUE
};

enum WIDGET_TYPE {
    RECTANGLE, SQUARE, TRIANGLE, CIRCLE
};

struct Point {
    double x, y;
};

struct Size {
    double w, h;
};

struct WidgetModel : Observable<WidgetModel>{
    Point _pos;
    Size  _size;
    COLOR _color;
    WIDGET_TYPE _type;

    WidgetModel* setPos(Point point){
        _pos = point;
        return this;
    }

    WidgetModel* setSize(Size size){
        _size = size;
        return this;
    }
    WidgetModel* setType(WIDGET_TYPE type){
        _type = type;
        return this;
    }
    WidgetModel* setColor(COLOR color){
        _color = color;
        return this;
    }
};

