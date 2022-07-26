#include <iostream>
#include <memory>
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

////////////////////////////////////////////////////////////////////////////////////
struct Application {

};

struct Editor {

};

struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
};

enum class ShapeType{
    A, B
};

struct CreateShape : Command{
    CreateShape(IShape* shape) {
    }
};

struct MoveShape : Command{
    int _x, _y;
    MoveShape(IShape* shape, int x, int y) : _x(x), _y(y) {

    }
};

struct ShapeCreator {
    std::unique_ptr<Command> create(ShapeType type);
};

struct DocumentView {
    std::vector<Shapes> _shapes;
    void redraw();
};

struct Document {
    std::string _path;
    std::string _data;
    std::vector<Command> _command_queue;

    std::string getData(){
        return _data;
    }
};

struct Converter {

};

int main() {
    app.exec();

    Editor editor();
    editor.create();
    std::string path;
    IDocument doc = editor.import(path);
    editor.export(path);
    editor.create(ShapeType);
    return 0;
}
