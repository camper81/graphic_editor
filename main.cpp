#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include "converter.h"
#include "editor.h"

int main() {
    Editor& editor = Editor::getInstance();
    auto converter = std::make_unique<JsonConverter>();
    editor.setConverter(*converter);
    auto document = editor.createDocument("doc.ge");
    std::shared_ptr<WidgetModel> widget = std::make_shared<WidgetModel>();
    widget->setColor(COLOR::RED)
            ->setPos({10,10})
            ->setSize({10,10})
            ->setType(RECTANGLE);
    document->addCommand(std::make_shared<CreateWidget>(widget));
    document->addCommand(std::make_shared<MoveWidget>(widget, Point{.x = 2,.y = 2}));
    document->addCommand(std::make_shared<ResizeWidget>(widget, Size{.w = 10,.h = 10}));
    document->addCommand(std::make_shared<ChangeColorWidget>(widget, COLOR::RED));
    document->addCommand(std::make_shared<RemoveWidget>(widget));
    editor.importDocument(document);
    editor.exportDocument(document);
//    document->addCommand(new WidgetBuilder::(WIDGET_TYPE::TRIANGLE));
    return 0;
}
