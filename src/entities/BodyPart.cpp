#include "BodyPart.h"

BodyPart::BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2) : parent(parent), p1(p1), p2(p2) {
    if (parent)  {
        this->parent->addChild(this);
    }
}

BodyPart::~BodyPart() {
    for (auto child : children) {
        delete child;
    }
}
