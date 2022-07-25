#include <memory>

struct MainWindow {
    std::vector<IShape> _shapes;
    std::shared_ptr<DocumentModel> _model;
    init() {
        _model->getData();

    }
};
