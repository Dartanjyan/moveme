#include "Constraint.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>

// Вспомогательная функция: ближайшая точка на отрезке AB к точке P
Vector2 closestPointOnSegment(const Vector2& A, const Vector2& B, const Vector2& P) {
    Vector2 AB = B - A;
    Vector2 AP = P - A;
    
    float ab2 = AB.x * AB.x + AB.y * AB.y;
    float ap_ab = AP.x * AB.x + AP.y * AB.y;
    
    // Параметр t определяет положение проекции на отрезке [0,1]
    float t = ap_ab / ab2;
    
    // Ограничиваем t в пределах отрезка
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    
    return A + AB * t;
}

// Функция для нахождения расстояния между двумя точками
float distance(const Vector2& a, const Vector2& b) {
    return (a - b).length();
}

// Основная функция
Vector2 findBestContactPoint(const BodyPart* part1, const BodyPart* part2) {
    // Получаем точки отрезков
    Vector2 a = part1->getPoint1();
    Vector2 b = part1->getPoint2();
    Vector2 c = part2->getPoint1();
    Vector2 d = part2->getPoint2();
    
    // Векторы направлений
    Vector2 ab = b - a;
    Vector2 cd = d - c;
    
    // Вычисляем определитель
    float det = ab.x * cd.y - ab.y * cd.x;
    
    // Если отрезки не параллельны, проверяем пересечение
    if (std::fabs(det) > std::numeric_limits<float>::epsilon()) {
        Vector2 ac = c - a;
        float t = (ac.x * cd.y - ac.y * cd.x) / det;
        float u = (ac.x * ab.y - ac.y * ab.x) / det;
        
        // Если отрезки пересекаются
        if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
            return a + ab * t; // Точка пересечения
        }
    }
    
    // Если пересечения нет, ищем ближайшие точки между отрезками
    
    // Кандидаты на ближайшие точки
    std::vector<Vector2> candidates;
    
    // Ближайшие точки от концов первого отрезка ко второму отрезку
    candidates.push_back(closestPointOnSegment(c, d, a));
    candidates.push_back(closestPointOnSegment(c, d, b));
    
    // Ближайшие точки от концов второго отрезка к первому отрезку
    candidates.push_back(closestPointOnSegment(a, b, c));
    candidates.push_back(closestPointOnSegment(a, b, d));
    
    // Находим пару ближайших точек
    float minDistance = std::numeric_limits<float>::max();
    Vector2 bestPoint1, bestPoint2;
    
    // Проверяем все пары кандидатов
    for (size_t i = 0; i < candidates.size(); ++i) {
        for (size_t j = i + 1; j < candidates.size(); ++j) {
            float dist = distance(candidates[i], candidates[j]);
            if (dist < minDistance) {
                minDistance = dist;
                bestPoint1 = candidates[i];
                bestPoint2 = candidates[j];
            }
        }
    }
    
    // Возвращаем середину между двумя ближайшими точками
    return (bestPoint1 + bestPoint2) * 0.5f;
}

// Альтернативная версия, которая возвращает просто ближайшую точку на одном отрезке к другому
Vector2 findClosestPoint(const BodyPart* part1, const BodyPart* part2) {
    Vector2 a = part1->getPoint1();
    Vector2 b = part1->getPoint2();
    Vector2 c = part2->getPoint1();
    Vector2 d = part2->getPoint2();
    
    // Находим ближайшие точки на каждом отрезке к другому отрезку
    Vector2 closestOn1to2 = closestPointOnSegment(a, b, closestPointOnSegment(c, d, a));
    Vector2 closestOn2to1 = closestPointOnSegment(c, d, closestPointOnSegment(a, b, c));
    
    // Возвращаем середину между этими точками
    return (closestOn1to2 + closestOn2to1) * 0.5f;
}

Constraint::Constraint(BodyPart* partA, BodyPart* partB, Vector2 anchor, float power): 
    partA(partA),
    partB(partB),
    anchor(anchor),
    power(power)
{
}

Constraint::Constraint(BodyPart *partA, BodyPart *partB, float power): 
    partA(partA),
    partB(partB),
    power(power)
{
    this->anchor = findBestContactPoint(partA, partB);
}

float Constraint::clampAngle(float angle) const
{
    return std::clamp(angle, minAngle, maxAngle);
}

