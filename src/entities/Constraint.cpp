#include "Constraint.h"
#include <algorithm>

Constraint::Constraint(BodyPart* partA, BodyPart* partB, Vector2 anchorA, float rest, float stiffness, float damping): 
    partA(partA),
    partB(partB),
    anchorA(anchorA),
    rest(rest), 
    stiffness(stiffness), 
    damping(damping)
{
}

Constraint::~Constraint() {
    // std::cout << "Deleting Joint, id = " << id << "\n";
}

float Constraint::clampAngle(float angle) const
{
    float a = std::clamp(angle, minAngle, maxAngle);
    // char buf[256];
    // snprintf(buf, 256, "rest = %f \tminRest = %f \tneutralRest = %f \tmaxRest = %f \treturn %f\n", rest, minRest, neutralRest, maxRest, a);
    // // std::cout << "rest = " << rest << " \tminRest = " << minRest << " \tmaxRest = " << maxRest << " \treturn " << a << "\n";
    // std::cout << buf;
    return a;
}

