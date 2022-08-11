#pragma once
#include "widget.h"

class View : public Observer<WidgetModel> {
    Size _size;
    std::list<std::shared_ptr<Widget>> _widgets;
public:
    void handle(WidgetModel& model, const CHANGE_TYPE &type) override {
        switch (type) {
            case CHANGE_TYPE::CREATE:
                addWidget(WidgetViewBuilder::create(&model, model._type));
                break;
        }
    }
    void addWidget(std::shared_ptr<Widget> wgt) {
        _widgets.push_back(wgt);
    }
    void removeWidget(std::shared_ptr<Widget> wgt) {
        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), wgt), _widgets.end());
    }
    void redraw() const {
        for(auto& wgt: _widgets){
            wgt->draw();
        }
    }
};