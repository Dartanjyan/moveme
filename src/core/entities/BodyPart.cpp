#include "BodyPart.h"

BodyPart::BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2, float width1, float width2)
    : parent(parent), p1(p1), p2(p2), width1(width1), width2(width2) {
    if (parent)  {
        this->parent->addChild(this);
    }

    const float len = (p2 - p1).length();
    if (width1 == 0) this->width1 = len * len / 2;
    if (width2 == 0) this->width2 = len * len / 2;
}

BodyPart::~BodyPart() {
    for (auto child : children) {
        delete child;
    }
}
