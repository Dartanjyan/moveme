#include "Limb.h"
#include <cmath>

Limb::Limb(std::vector<BodyPart *> &bodyParts, std::vector<Constraint *> &constraints)
        : bodyParts(bodyParts), constraints(constraints)
{
}

void Limb::forwardReach(Vector2 target) {
    if (bodyParts.empty()) return;
    
    // Последний сегмент тянется к цели
    int lastIndex = bodyParts.size() - 1;
    bodyParts[lastIndex]->setPoint2(target);
    
    // Идем от конца к началу
    for (int i = lastIndex; i > 0; i--) {
        BodyPart* current = bodyParts[i];
        BodyPart* previous = bodyParts[i - 1];
        
        Vector2 p2 = current->getPoint2();
        Vector2 p1 = current->getPoint1();
        
        // Вычисляем длину сегмента
        float length = (p2 - p1).length();
        
        // Направление от p2 к p1
        Vector2 direction = (p1 - p2).normalized();
        
        // Новая позиция p1
        Vector2 newP1 = p2 + direction * length;
        current->setPoint1(newP1);
        previous->setPoint2(newP1);
    }
}

void Limb::backwardReach(Vector2 base) {
    if (bodyParts.empty()) return;
    
    // Первый сегмент закреплен в базовой точке
    bodyParts[0]->setPoint1(base);
    
    // Идем от начала к концу
    for (size_t i = 0; i < bodyParts.size() - 1; i++) {
        BodyPart* current = bodyParts[i];
        BodyPart* next = bodyParts[i + 1];
        
        Vector2 p1 = current->getPoint1();
        Vector2 p2 = current->getPoint2();
        
        // Вычисляем длину сегмента
        float length = (p2 - p1).length();
        
        // Направление от p1 к p2
        Vector2 direction = (p2 - p1).normalized();
        
        // Новая позиция p2
        Vector2 newP2 = p1 + direction * length;
        current->setPoint2(newP2);
        next->setPoint1(newP2);
    }
}

void Limb::reachTowards(Vector2 target, int iterations) {
    if (bodyParts.empty()) return;
    
    // Сохраняем базовую точку (начало щупальца)
    Vector2 base = bodyParts[0]->getPoint1();
    
    // Вычисляем общую длину всех сегментов
    float totalLength = 0.0f;
    std::vector<float> segmentLengths;
    for (auto* part : bodyParts) {
        float length = (part->getPoint2() - part->getPoint1()).length();
        segmentLengths.push_back(length);
        totalLength += length;
    }
    
    // Проверяем, достижима ли цель
    float distanceToTarget = (target - base).length();
    
    // Если цель слишком далеко, вытягиваем щупальце в направлении цели
    if (distanceToTarget > totalLength) {
        Vector2 direction = (target - base).normalized();
        Vector2 currentPos = base;
        
        for (size_t i = 0; i < bodyParts.size(); i++) {
            bodyParts[i]->setPoint1(currentPos);
            currentPos = currentPos + direction * segmentLengths[i];
            bodyParts[i]->setPoint2(currentPos);
        }
        return;
    }
    
    // Итеративный процесс FABRIK
    for (int iter = 0; iter < iterations; iter++) {
        // Forward reaching: от конца к началу
        bodyParts.back()->setPoint2(target);
        
        for (int i = bodyParts.size() - 1; i > 0; i--) {
            Vector2 p2 = bodyParts[i]->getPoint2();
            Vector2 p1 = bodyParts[i]->getPoint1();
            
            Vector2 direction = (p1 - p2).normalized();
            Vector2 newP1 = p2 + direction * segmentLengths[i];
            
            bodyParts[i]->setPoint1(newP1);
            bodyParts[i - 1]->setPoint2(newP1);
        }
        
        // Backward reaching: от начала к концу
        bodyParts[0]->setPoint1(base);
        
        for (size_t i = 0; i < bodyParts.size() - 1; i++) {
            Vector2 p1 = bodyParts[i]->getPoint1();
            Vector2 p2 = bodyParts[i]->getPoint2();
            
            Vector2 direction = (p2 - p1).normalized();
            Vector2 newP2 = p1 + direction * segmentLengths[i];
            
            bodyParts[i]->setPoint2(newP2);
            bodyParts[i + 1]->setPoint1(newP2);
        }
    }
}