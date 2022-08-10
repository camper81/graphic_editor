#pragma once
#include "converter.h"
#include "document.h"

class Editor{
    Editor() : _converter() {}
public:
    Editor(const Editor&) = delete;
    void operator=(Editor&) = delete;
    static Editor& getInstance(){
        static Editor ed;
        return ed;
    }
    Document* createDocument(const std::string& name) {
        _docs.push_back(Document(name));
        return &_docs.back();
    }

    void setConverter(IConverter& converter){
        _converter = &converter;
    }

    void importDocument(Document* doc) {
        if(_converter == nullptr)
            return;
        _converter->imprt(doc);
    }
    void exportDocument(Document* doc) {
        if(_converter == nullptr)
            return;
        _converter->exprt(doc);
    }
private:
    std::vector<Document> _docs;
    IConverter* _converter;
};