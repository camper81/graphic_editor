#pragma once
#include "view.h"
#include "widget_model.h"
#include "command.h"

class Document :public IDocument {
public:
    explicit Document(const std::string& name) : _name(name) {}

    void addWidget(std::shared_ptr<WidgetModel> wgt) {
        _widgets.push_back(wgt);
        wgt->addObserver(_view);
        wgt->notify(*wgt, CHANGE_TYPE::CREATE);
    }
    void removeWidget(std::shared_ptr<WidgetModel> wgt) {
        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), wgt), _widgets.end());
    }

    void addCommand(std::shared_ptr<Command> command) {
        _commands.push_back(command);
        command->call(this);
    }
private:
    View _view;
    std::string _name;
    std::vector<std::shared_ptr<WidgetModel>> _widgets;
    std::vector<std::shared_ptr<Command>> _commands;
};