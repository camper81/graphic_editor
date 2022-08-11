#pragma once
#include "idocument.h"
#include "widget_model.h"

class Command{
protected:
    std::shared_ptr<WidgetModel> _wgt;
public:
    explicit Command(std::shared_ptr<WidgetModel>& wgt) : _wgt(wgt) {}
    virtual void call(IDocument*) = 0;
    virtual void undo(IDocument*) = 0;
};

class CreateWidget : public Command{
public:
    CreateWidget(std::shared_ptr<WidgetModel> wgt) : Command(wgt) {};
    virtual void call(IDocument* doc) override {
        doc->addWidget(_wgt);
    }
    virtual void undo(IDocument* doc) override {
        doc->removeWidget(_wgt);
    }
};

class MoveWidget : public Command{
    Point _pos;
public:
    MoveWidget(std::shared_ptr<WidgetModel> wgt, Point pos) : Command(wgt), _pos(pos)  {};
    virtual void call(IDocument* doc) override {
        _wgt->setPos(_pos);
        _wgt->notify(*_wgt, CHANGE_TYPE::MOVE);
    }
    virtual void undo(IDocument*) override {
        _pos.x = - _pos.x;
        _pos.y = - _pos.y;
        _wgt->setPos(_pos);
    }
};

class ResizeWidget : public Command{
    Size _sz;
    Size _prev_sz;
public:
    ResizeWidget(std::shared_ptr<WidgetModel> wgt, Size sz) : Command(wgt), _sz(sz){};
    virtual void call(IDocument*) override {
        _prev_sz = _sz;
        _wgt->setSize(_sz);
        _wgt->notify(*_wgt, CHANGE_TYPE::SIZE);
    }
    virtual void undo(IDocument*) override {
        _wgt->setSize(_prev_sz);
        _prev_sz = _sz;
    }
};

class ChangeColorWidget : public Command{
    COLOR _col;
    COLOR _prev_col;
public:
    ChangeColorWidget(std::shared_ptr<WidgetModel> wgt, COLOR col) : Command(wgt), _col(col) {};
    virtual void call(IDocument* doc) override {
        _wgt->notify(*_wgt, CHANGE_TYPE::COLOR);
    }
    virtual void undo(IDocument*) override {

    }
};

class RemoveWidget : public Command{
public:
    RemoveWidget(std::shared_ptr<WidgetModel> wgt): Command(wgt) {};
    virtual void call(IDocument*) override {

    }
    virtual void undo(IDocument*) override{

    }
};

