#include "rayCollision.h"


RayCollision::RayCollision(glm::vec3 orig, glm::vec3 direct) : origin(orig), direction(direct) {}
bool RayCollision::intersectRayTriangle(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, float &t) {
    constexpr float epsilon = 1e-16f;

    // Вычисляем векторы рёбер треугольника
    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;

    // Вычисляем нормаль треугольника
    glm::vec3 normal = glm::cross(edge1, edge2);
    float normalLength = glm::length(normal);
    if (normalLength < epsilon) {
        return false; // Вырожденный треугольник
    }

    // Нормализуем нормаль (опционально, для выбора проекции)
    normal /= normalLength;

    // Проверка параллельности луча и плоскости
    float DdotN = glm::dot(direction, normal);
    if (std::fabs(DdotN) < epsilon) {
        return false;
    }

    // Вычисляем параметр t пересечения с плоскостью
    float t_val = glm::dot(v0 - origin, normal) / DdotN;
    if (t_val < 0.0f) {
        return false;
    }

    // Вычисляем точку пересечения с плоскостью
    glm::vec3 P = origin + direction * t_val;

    // Определяем доминантную ось для проекции
    glm::vec3 absNormal = glm::abs(normal);
    int dominantAxis = (absNormal.x > absNormal.y) 
        ? ((absNormal.x > absNormal.z) ? 0 : 2)
        : ((absNormal.y > absNormal.z) ? 1 : 2);

    // Проецируем точки на выбранную плоскость
    auto project = [dominantAxis](const glm::vec3 &p) -> glm::vec2 {
        switch (dominantAxis) {
            case 0: return glm::vec2(p.y, p.z); // Проекция на YZ
            case 1: return glm::vec2(p.x, p.z); // Проекция на XZ
            default: return glm::vec2(p.x, p.y); // Проекция на XY
        }
    };

    glm::vec2 v0p = project(v0);
    glm::vec2 v1p = project(v1);
    glm::vec2 v2p = project(v2);
    glm::vec2 Pp = project(P);

    // Вычисляем векторы в проекции
    glm::vec2 e0 = v1p - v0p;
    glm::vec2 e1 = v2p - v0p;
    glm::vec2 pVec = Pp - v0p;

    // Вычисляем детерминант и барицентрические координаты
    float det = e0.x * e1.y - e0.y * e1.x;
    if (std::fabs(det) < epsilon) {
        return false; // Вырожденная проекция
    }

    float invDet = 1.0f / det;
    float u = (pVec.x * e1.y - pVec.y * e1.x) * invDet;
    float v = (pVec.y * e0.x - pVec.x * e0.y) * invDet;

    // Проверка попадания в треугольник
    if (u >= 0.0f && v >= 0.0f && (u + v) <= 1.0f) {
        t = t_val;
        return true;
    }
    
    return false;
}
