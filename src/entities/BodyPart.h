#ifndef BODYPART_H
#define BODYPART_H

#include <vector>
#include "Vector2.h"

class BodyPart {
public:
    BodyPart(BodyPart *parent, unsigned length);
    ~BodyPart();

    unsigned getLength() { return length; }
    std::vector<BodyPart *> getChildren() { return children; }
    BodyPart* getParent() { return parent; }
    void addChild(BodyPart *child) { children.push_back(child); }
private:
    unsigned length;
    std::vector<BodyPart *> children;
    BodyPart *parent;
};

#endif
