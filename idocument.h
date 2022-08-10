#pragma once

class Command;

class IDocument {
public:
    virtual void addWidget(std::shared_ptr <WidgetModel> wgt) = 0;

    virtual void removeWidget(std::shared_ptr <WidgetModel> wgt) = 0;

    virtual void addCommand(std::shared_ptr <Command> command) = 0;
};