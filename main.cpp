#include <iostream>
#include <memory>
#include <vector>
#include <vector>
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

struct Point{
    double x, y;
};

struct Size{
    double w, h;
};

class Widget{
    Point _pos;
    Size  _size;
    COLOR _color;
public:
    void resize(int w, int h);
    void changePosition(double x, double y);
    void changePosition(Point point);
    void changeSize(double w, double h);
    void changeSize(Size sz);
    void changeColor(COLOR col);
    virtual void show() = 0;
};

class View{
    std::vector<Widget*>
};

///////////////////////MODEL////////////////////////////////////////////////////////

// Command
class Command{
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class MoveWidget : public Command{
    Widget* _wgt;
    Point _pos;
public:
    MoveWidget(Widget*, Point) {};
    virtual void undo();
    virtual void redo();
};

class resizeWidget : public Command{
    Widget* _wgt;
    Size _sz;
public:
    resizeWidget(Widget*, Size) {};
    virtual void undo();
    virtual void redo();
};

class changeColorWidget : public Command{
    Widget* _wgt;
    COLOR _col;
public:
    changeColorWidget(Widget*, COLOR) {};
    virtual void undo();
    virtual void redo();
};

class createWidget : public Command{
    Widget* _wgt;
public:
    createWidget(Widget*) {};
    virtual void undo();
    virtual void redo();
};
// ~Command

class Document{
public:
    Document(const std::string& name) : _name(name) {}
    void addWidget(Widget*);
    void removeWidget(Widget*);

    void addCommand(Command*);
    void notify();
private:
    std::string _name;
    std::vector<Widget*> _widgets;
    std::vector<Command*> _commands;
};

///////////////////////CONTROLLER///////////////////////////////////////////////////
/* CREATE */
class Editor{
public:
    Document* createDocument(const std::string& );
    void importDocument();
    void exportDocument();

    void createWidget(WIDGET_TYPE);
private:
    std::vector<Document> _docs;
};


int main() {
    Editor editor;
    auto document = editor.createDocument("doc.ge");

    return 0;
}
