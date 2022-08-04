#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
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

enum class CHANGE_TYPE {
    MOVE, SIZE, COLOR, CREATE, DESTROY
};

struct Point {
    double x, y;
};

struct Size {
    double w, h;
};

template<typename T>
struct Observer {
    virtual void handle(T& source,const CHANGE_TYPE& type) = 0;
};

template<typename T>
struct Observable {
    std::vector<Observer<T>*> observers;

    void addObserver(Observer<T>& observer) {
        observers.push_back(&observer);
    }

    void removeObserver(Observer<T>& observer) {
        observers.erase(std::remove(observers.begin(),observers.end(), observer), observers.end());
    }

    void notify(T& source, const CHANGE_TYPE& type) const{
        for(auto& observer: observers) {
            observer->handle(source, type);
        }
    }
};

class View;

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

std::map<CHANGE_TYPE, std::string> debug_action_output{
        {CHANGE_TYPE::CREATE, "Create"},
        {CHANGE_TYPE::SIZE, "Size"},
        {CHANGE_TYPE::MOVE, "Move"},
        {CHANGE_TYPE::COLOR, "Color"},
        {CHANGE_TYPE::DESTROY, "Destroy"}

};

std::map<WIDGET_TYPE, std::string> debug_widget_output{
        {WIDGET_TYPE::RECTANGLE, "Rectangle"},
        {WIDGET_TYPE::CIRCLE, "Circle"},
        {WIDGET_TYPE::SQUARE, "Square"},
        {WIDGET_TYPE::TRIANGLE, "Triangle"},
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

class WidgetViewBuilder{
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

class View : public Observer<WidgetModel>{
    Size _size;
    std::list<Widget*> _widgets;
public:
    void handle(WidgetModel& model, const CHANGE_TYPE &type) override {
        switch (type) {
            case CHANGE_TYPE::CREATE:
                addWidget(WidgetViewBuilder::create(&model, model._type));
                break;
        }
    }
    void addWidget(Widget* wgt) {
        _widgets.push_back(wgt);
    }
    void removeWidget(Widget* wgt) {
        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), wgt), _widgets.end());
    }
    void redraw() const {
        for(auto& wgt: _widgets){
            wgt->draw();
        }
    }
};



///////////////////////MODEL////////////////////////////////////////////////////////

class Document;
// Command
class Command{
protected:
    WidgetModel* _wgt;
public:
    Command(WidgetModel* wgt) : _wgt(wgt) {}
    virtual void call(Document*) = 0;
    virtual void undo(Document*) = 0;
};

class Document {
public:
    Document(const std::string& name) : _name(name) {}

    void addWidget(WidgetModel* wgt) {
        _widgets.push_back(wgt);
        wgt->addObserver(_view);
        wgt->notify(*wgt, CHANGE_TYPE::CREATE);
    }
    void removeWidget(WidgetModel* wgt) {
        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), wgt), _widgets.end());
    }

    void addCommand(Command* command) {
        command->call(this);
    }
private:
    View _view;
    std::string _name;
    std::vector<WidgetModel*> _widgets;
    std::vector<Command*> _commands;
};

class CreateWidget : public Command{
public:
    CreateWidget(WidgetModel* wgt) : Command(wgt) {};
    virtual void call(Document* doc) override {
        doc->addWidget(_wgt);
    }
    virtual void undo(Document* doc) override {
        doc->removeWidget(_wgt);
    }
};

class MoveWidget : public Command{
    Point _pos;
public:
    MoveWidget(WidgetModel* wgt, Point pos) : Command(wgt), _pos(pos)  {};
    virtual void call(Document* doc) override {
        _wgt->setPos(_pos);
        _wgt->notify(*_wgt, CHANGE_TYPE::MOVE);
    }
    virtual void undo(Document*) override {
        _pos.x = - _pos.x;
        _pos.y = - _pos.y;
        _wgt->setPos(_pos);
    }
};

class ResizeWidget : public Command{
    Size _sz;
    Size _prev_sz;
public:
    ResizeWidget(WidgetModel* wgt, Size sz) : Command(wgt), _sz(sz){};
    virtual void call(Document*) override {
        _prev_sz = _sz;
        _wgt->setSize(_sz);
        _wgt->notify(*_wgt, CHANGE_TYPE::SIZE);
    }
    virtual void undo(Document*) override {
        _wgt->setSize(_prev_sz);
        _prev_sz = _sz;
    }
};

class ChangeColorWidget : public Command{
    COLOR _col;
    COLOR _prev_col;
public:
    ChangeColorWidget(WidgetModel* wgt, COLOR col) : Command(wgt), _col(col) {};
    virtual void call(Document* doc) override {
        _wgt->notify(*_wgt, CHANGE_TYPE::COLOR);
    }
    virtual void undo(Document*) override {

    }
};



class RemoveWidget : public Command{
public:
    RemoveWidget(WidgetModel* wgt): Command(wgt) {};
    virtual void call(Document*) override {

    }
    virtual void undo(Document*) override{

    }
};
// ~Command



///////////////////////CONTROLLER///////////////////////////////////////////////////
/* CREATE */
class Editor{
    Editor() {}
public:
    Editor(const Editor&) = delete;
    void operator=(Editor&) = delete;
    static Editor& getInstance(){
        static Editor ed;
        return ed;
    }
    Document* createDocument(const std::string& name) {
        _docs.push_back(new Document(name));
        return _docs.back();
    }

    void importDocument(Document*) {}
    void exportDocument(Document*) {}
private:
    std::vector<Document*> _docs;
};


int main() {
    Editor& editor = Editor::getInstance();
    auto document = editor.createDocument("doc.ge");
    auto widget = (new WidgetModel())->setColor(COLOR::RED)
            ->setPos({10,10})
            ->setSize({10,10})
            ->setType(RECTANGLE);
    document->addCommand(new CreateWidget(widget));
    document->addCommand(new MoveWidget(widget, {.x = 10,.y = 10}));
    document->addCommand(new ResizeWidget(widget, {.w = 10,.h = 10}));
    document->addCommand(new ChangeColorWidget(widget, COLOR::RED));
    document->addCommand(new RemoveWidget(widget));
//    document->addCommand(new WidgetBuilder::(WIDGET_TYPE::TRIANGLE));
    return 0;
}
