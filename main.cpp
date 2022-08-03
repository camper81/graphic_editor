#include <iostream>
#include <memory>
#include <vector>
#include <list>
//Спроектировать простейший графический векторный редактор. Подготовить макеты классов,
//отражающих структуру будущего проекта.
//Функционал для макетирования следующий:
//- создание нового документа
//- импорт документа из файла
//- экспорт документа в файл
//- создание графического примитива
//- удаление графического примитива
//        Основной упор сделать на шаблон контроллера (MVC) и полиморфизм. Функции, являющиеся
//        обработчиками GUI, собрать в одном файле с функцией `main`.
//Внимание должно быть сосредоточено на декларациях, реализация только в крайнем случае для
//        минимальной демонстрации необходимых вызовов. Проект должен компилироваться, все
//        заголовки должны пройти стадию компиляции.
//Задание считается выполненным успешно, если все файлы прошли стадию компиляции, все классы
//охвачены диаграммами, код успешно прошел анализ.
//Дополнительные рекомендации
//1. Заложить в интерфейсы использование умных указателей, тем самым решив вопрос
//        владения объектами.
//2. Помнить про принцип единственности ответственности, разделить код на логические
//модули (классы, функции).
//3. Избегать дублирования кода.

///////////////////////VIEW/////////////////////////////////////////////////////////
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

class View;

class Widget {
protected:
    Point _pos;
    Size  _size;
    COLOR _color;
    std::vector<Widget*> _child_wgts;
public:
    void move(double offset_x, double offset_y) {
        _pos.x += offset_x;
        _pos.y += offset_y;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_x, offset_y);
        }
    }
    void move(Point& point) {
        auto offset_x = point.x - _pos.x;
        auto offset_y = point.x - _pos.y;
        _pos = point;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_x, offset_y);
        }
    }
    void resize(double offset_w, double offset_h) {
        _size.w += offset_w;
        _size.h += offset_h;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_w, offset_h);
        }
    }
    void resize(Size sz) {
        auto offset_w = sz.w - _size.w;
        auto offset_h = sz.h - _size.h;
        _size = sz;
        for(auto& wgt: _child_wgts) {
            wgt->move(offset_w, offset_h);
        }
    }
    void changeColor(COLOR col) {
        _color = col;
    }

    virtual void draw() = 0;
};

class Circle: public Widget{
public:
    void draw() override{
        std::cout << "Circle draw" << std::endl;
    }
};

class Square: public Widget{
public:
    void draw() override{
        std::cout << "Square draw" << std::endl;
    }
};

class Triangle: public Widget{
public:
    void draw() override{
        std::cout << "Triangle draw" << std::endl;
    }
};

class Rectangle: public Widget{
public:
    void draw() override{
        std::cout << "Rectangle draw" << std::endl;
    }
};

class View{
    Size _size;
    std::list<Widget*> _widgets;
public:
    void handle(){
        redraw();
    }
    void addWidget(Widget* wgt) {
        _widgets.push_back(wgt);
    }
    void removeWidget(Widget* wgt) {
        auto it = std::find(_widgets.begin(), _widgets.end(),wgt);
        if(it != _widgets.end())
            _widgets.erase(it);
    }
    void redraw() const {
        for(auto& wgt: _widgets){
            wgt->draw();
        }
    }
};

class WidgetBuilder{
public:
    static Widget* create(WIDGET_TYPE type) {
        switch(type) {
            case WIDGET_TYPE::CIRCLE:
                return new Circle();
            case WIDGET_TYPE::RECTANGLE:
                return new Rectangle();
            case WIDGET_TYPE::SQUARE:
                return new Square;
            case WIDGET_TYPE::TRIANGLE:
                return new Triangle;
        }
        return nullptr;
    }
};

///////////////////////MODEL////////////////////////////////////////////////////////

class Document;
// Command
class Command{
public:
    virtual void call(Document*) = 0;
    virtual void undo(Document*) = 0;
};

class WidgetModel{

};

class Document{
public:
    Document(const std::string& name) : _name(name) {}

    void addWidget(Widget* wgt) {
        _widgets.push_back(wgt);
        _view->addWidget(wgt);

    }
    void removeWidget(Widget*);

    void moveWidget(Widget*);

    void addCommand(Command* command) {
        command->call(this);
    }
    void notify();
private:
    View* _view;
    std::string _name;
    std::vector<Widget*> _widgets;
    std::vector<Command*> _commands;
};

class CreateWidget : public Command{
    Widget* _wgt;
public:
    CreateWidget(Widget*) {};
    virtual void call(Document* doc) override {
        doc->addWidget(_wgt);
    }
    virtual void undo(Document* doc) override {
        doc->removeWidget(_wgt);
    }
};

class MoveWidget : public Command{
    Widget* _wgt;
    Point _pos;
public:
    MoveWidget(Widget*, Point) {};
    virtual void call(Document*) override;
    virtual void undo(Document*) override;
};

class ResizeWidget : public Command{
    Widget* _wgt;
    Size _sz;
public:
    ResizeWidget(Widget*, Size) {};
    virtual void call(Document*) override;
    virtual void undo(Document*) override;
};

class ChangeColorWidget : public Command{
    Widget* _wgt;
    COLOR _col;
public:
    ChangeColorWidget(Widget*, COLOR) {};
    virtual void call(Document* doc) override {

    }
    virtual void undo(Document*) override;
};



class RemoveWidget : public Command{
    Widget* _wgt;
public:
    RemoveWidget(Widget*) {};
    virtual void call(Document*) override;
    virtual void undo(Document*) override;
};
// ~Command



///////////////////////CONTROLLER///////////////////////////////////////////////////
/* CREATE */
class Editor{
    Editor();
    Editor(const Editor&) = delete;
    Editor(const Editor&&) = delete;
    void operator=(Editor&) = delete;
    void operator=(Editor&&) = delete;
public:
    static Editor* getInstance(){
        return &_instance;
    }
    Document* createDocument(const std::string& name) {
        _docs.push_back(new Document(name));
    }

    void importDocument(Document*);
    void exportDocument(Document*);
private:
    std::vector<Document*> _docs;
    static Editor _instance;
};


int main() {
    Editor* editor = Editor::getInstance();
    auto document = editor->createDocument("doc.ge");
    auto widget = WidgetBuilder::create(WIDGET_TYPE::TRIANGLE);
    document->addCommand(new CreateWidget(widget));
    document->addCommand(new MoveWidget(widget, {.x = 10,.y = 10}));
    document->addCommand(new ResizeWidget(widget, {.w = 10,.h = 10}));
    document->addCommand(new ChangeColorWidget(widget, COLOR::RED));
    document->addCommand(new RemoveWidget(widget));
//    document->addCommand(new WidgetBuilder::(WIDGET_TYPE::TRIANGLE));
    return 0;
}
