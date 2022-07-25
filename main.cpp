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

struct IShape {
    virtual void create() = 0;
    virtual void erase() = 0;
    virtual ~IShape() = default;
};

namespace FlatShapes{
    struct Circle : IShape{
        void create() override{
            std::cout << "Draw 2D Circle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 2D Circle" << std::endl;
        }
    };
    struct Rectangle : IShape{
        void create() override{
            std::cout << "Draw 2D Rectangle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 2D Rectangle" << std::endl;
        }
    };
    struct Triangle : IShape{
        void create() override{
            std::cout << "Draw 2D Triangle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 2D Triangle" << std::endl;
        }
    };
    struct Null : IShape{
        void create() override{
            std::cout << "Draw dummy" << std::endl;
        }
        void erase() override{
            std::cout << "Erase dummy" << std::endl;
        }
    };
}

namespace VolumeShapes{
    struct Circle : IShape{
        void create() override{
            std::cout << "Draw 3D Circle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 3D Circle" << std::endl;
        }
    };
    struct Rectangle : IShape{
        void create() override{
            std::cout << "Draw 3D Rectangle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 3D Rectangle" << std::endl;
        }
    };
    struct Triangle : IShape{
        void create() override{
            std::cout << "Draw 3D Triangle" << std::endl;
        }
        void erase() override{
            std::cout << "Erase 3D Triangle" << std::endl;
        }
    };
    struct Null : IShape{
        void create() override{
            std::cout << "Draw dummy" << std::endl;
        }
        void erase() override{
            std::cout << "Erase dummy" << std::endl;
        }
    };
}


enum class ShapeType{
    Circle,
    Triangle,
    Rectangle,
    Null
};

struct IShapeCreator{
    virtual std::unique_ptr<IShape> create(ShapeType type) = 0;
};

struct Shape2DCreator : IShapeCreator {
    virtual std::unique_ptr<IShape> create(ShapeType type) override{
        std::unique_ptr<IShape> shape;
        switch(type) {
            case ShapeType::Circle:
                return std::make_unique<FlatShapes::Circle>();
            case ShapeType::Triangle:
                return std::make_unique<FlatShapes::Triangle>();
            case ShapeType::Rectangle:
                return std::make_unique<FlatShapes::Rectangle>();
        }
        return std::make_unique<FlatShapes::Null>();
    }
};

struct Shape3DCreator : IShapeCreator {
    virtual std::unique_ptr<IShape> create(ShapeType type) override{
        switch(type) {
            case ShapeType::Circle:
                return std::make_unique<VolumeShapes::Circle>();
            case ShapeType::Triangle:
                return std::make_unique<VolumeShapes::Triangle>();
            case ShapeType::Rectangle:
                return std::make_unique<VolumeShapes::Rectangle>();
        }
        return std::make_unique<VolumeShapes::Null>();
    }
};

////////////////////////////////////////////////////////////////////////////////////

enum class DocumentType{
    Xml, Json
};

struct IDocument{
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string path_;

    virtual void open(const std::string& path) = 0;
    virtual void save() = 0;
    virtual void saveAs(const std::string& path) = 0;
//    virtual void importFrom(const std::string& path) = 0;
//    virtual void exportTo(const std::string& path) = 0;
};

struct XMLDocument : IDocument{

    void open(const std::string& path) override{
        path_ = path;

        /* parse file to objects */

    }

    void save() override{
    }

    void saveAs(const std::string& path) override{

    }
};

struct JSONDocument : IDocument{
    void open(const std::string& path) override{
        path_ = path;

        /* parse file to objects */

    }

    void save() override{
    }

    void saveAs(const std::string& path) override{

    }
};

struct DocumentCreator{
    static std::unique_ptr<IDocument> create(DocumentType type) {
        switch(type) {
            case DocumentType::Json:
                return std::make_unique<JSONDocument>();
            case DocumentType::Xml:
                return std::make_unique<XMLDocument>();
        }
    }
};


struct Command {
    virtual void call() = 0;
    virtual void undo() = 0;
};


struct CreateShape : Command {
    enum Action{ create, erase } _action;
    std::shared_ptr<IShape> _shape;

    CreateShape(IShape* shape, Action action) : _shape(shape), _action(action){

    }
    void call() override{
        switch(_action){
            case create:
                _shape->create();
                break;
            case erase:
                _shape->erase();
                break;
        }
    }
    void undo() override{
        switch(_action){
            case create:
                _shape->erase();
                break;
            case erase:
                _shape->create();
                break;
        }
    }
};

struct CoxmmandInterpreter{
    std::vector<Command> _commands;
};

struct Editor {
    std::unique_ptr<IDocument> createDocument(DocumentType type) {
        switch(type) {
            case DocumentType::Xml:
                return std::make_unique<XMLDocument>();
            case DocumentType::Json:
                return std::make_unique<JSONDocument>();
        }
    }
};

int main() {

    return 0;
}
