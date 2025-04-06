#include <glm/glm.hpp>

class RayCollision {
public:
    glm::vec3 origin = glm::vec3(1.0f);
    glm::vec3 direction = glm::vec3(1.0f);

    RayCollision(glm::vec3 orig, glm::vec3 direct);
    bool intersectRayTriangle(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, float &t);
};
