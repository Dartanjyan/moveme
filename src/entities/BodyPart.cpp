#include "BodyPart.h"

BodyPart::BodyPart(BodyPart *parent, Vector2 p1, Vector2 p2, float width1, float width2) : parent(parent), p1(p1), p2(p2) {
    if (parent)  {
        this->parent->addChild(this);
    }

    if (width1 == 0) {
        width1 = (p2 - p1).length();
        width1 *= width1;
        width1 /= 2;
    }
    if (width2 == 0) {
        width2 = (p2 - p1).length();
        width2 *= width2;
        width2 /= 2;
    }
}

BodyPart::~BodyPart() {
    for (auto child : children) {
        delete child;
    }
}
