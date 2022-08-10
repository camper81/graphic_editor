#pragma once
#include "document.h"

class IConverter{
public:
    virtual void imprt(Document* ) = 0;
    virtual void exprt(Document* ) = 0;
};

class JsonConverter : public IConverter{
public:
    void imprt(Document *document) override {
        std::cout << "Import JSON Document" << std::endl;
    }

    void exprt(Document *document) override {
        std::cout << "Export JSON Document" << std::endl;
    }
};