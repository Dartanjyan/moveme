#include "BodyPart.h"

BodyPart::BodyPart(BodyPart *parent, unsigned length) : parent(parent), length(length) {
    this->parent->addChild(this);
}

BodyPart::~BodyPart() {
    for (auto child : children) {
        delete child;
    }
}
