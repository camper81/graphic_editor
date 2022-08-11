# graphic_editor
Спроектировать простейший графический векторный редактор. Подготовить макеты классов,
отражающих структуру будущего проекта.
Функционал для макетирования следующий:
- [ ] создание нового документа
- [ ] импорт документа из файла
- [ ] экспорт документа в файл
- [ ] создание графического примитива
- [ ] удаление графического примитива
____
Основной упор сделать на шаблон контроллера (MVC) и полиморфизм. Функции, являющиеся обработчиками GUI, собрать в одном файле с функцией `main`. Внимание должно быть сосредоточено на декларациях, реализация только в крайнем случае для
минимальной демонстрации необходимых вызовов. Проект должен компилироваться, все заголовки должны пройти стадию компиляции. Задание считается выполненным успешно, если все файлы прошли стадию компиляции, все классы
охвачены диаграммами, код успешно прошел анализ. Дополнительные рекомендации
1. Заложить в интерфейсы использование умных указателей, тем самым решив вопрос
владения объектами.
2. Помнить про принцип единственности ответственности, разделить код на логические
модули (классы, функции).
3. Избегать дублирования кода.

Структура классов Document
```mermaid
classDiagram
class IDocument {
    +addWidget(ModelWidget)
    +removeWidget(ModelWidget)
    +addCommand(Command)
}

class Document {
    -View view
    -string name
    -vector<WidgetModel> widgets
    -vector<Command> commands
    +addWidget(ModelWidget)
    +removeWidget(ModelWidget)
    +addCommand(Command)
}

IDocument <|.. Document

class Command {
    -WidgetModel wgt
    +call(IDocument)
    +undo(IDocument)
}
```

```mermaid
class CreateWidget {
    -WidgetModel wgt
    +call(IDocument)
    +undo(IDocument)
}

class MoveWidget {
    Point position
    -WidgetModel wgt
    +call(IDocument)
    +undo(IDocument)
}

class ResizeWidget {
    Size size
    -WidgetModel wgt
    +call(IDocument)
    +undo(IDocument)
}

class ChangeColorWidget {
    COLOR color
    -WidgetModel wgt
    +call(IDocument)
    +undo(IDocument)
}

Command <|.. CreateWidget
Command <|.. MoveWidget
Command <|.. ResizeWidget
Command <|.. ChangeColorWidget
```

```mermaid
class View {
    -Size size
    -list<Widget> widgets
    +handle(WidgetModel, CHANGE_TYPE)
    +addWidget(Widget)
    +removeWidget(Widget)
    +redraw()
}

class Widget {
    +move(Point)
    +resize(Size)
    +changeColor(COLOR)
    +handle(WidgetModel&, CHANGE_TYPE)
    <<Interface>> +draw() 
}

class Observer {
    +handle(Source, CHAGNE_TYPE)
}

class Observable {
    -vector<Observer> obsrervers
    +addObserver(Observer)
    +removeObserver(Observer)
    +notify(Source, CHANGE_TYPE)
}

class WidgetModel {
    +setPos(Point)
    +setSize(Size)
    +setType(WIDGET_TYPE)
    +setColor(COLOR)
}

Observable <|.. WidgetModel

Observer <|.. Widget
Observer <|.. View

Widget <|.. Circle  
Widget <|.. Rectangle  
Widget <|.. Square  
Widget <|.. Triangle  

```
