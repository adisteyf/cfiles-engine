#ifndef __FE_PHYSICS
#define __FE_PHYSICS

#include <PxPhysicsAPI.h>
#include <glm/glm.hpp>
#include <vector>

class Physics {
public:
	physx::PxDefaultAllocator      mDefaultAllocatorCallback;
	physx::PxDefaultErrorCallback  mDefaultErrorCallback;
	physx::PxDefaultCpuDispatcher *mDispatcher;
	physx::PxTolerancesScale       mToleranceScale;
	physx::PxFoundation           *mFoundation;
	physx::PxPhysics              *mPhysics;
	physx::PxScene                *mScene;
	physx::PxMaterial             *mMaterial;
	physx::PxPvd                  *mPvd;

	Physics(void);
	~Physics();

	void simulate(double dt);
	int32_t createStaticShape(glm::vec3 *transform, int32_t collisionID, glm::vec3 material);
	int32_t createDynamicShape(glm::vec3 *transform, int32_t collisionID, glm::vec3 material);
	int32_t createAABB(double min[3], double max[3]);
	void setMass(int actorID, float m);
	glm::vec3 getGlobalPos(int32_t rgID, bool isDynamic);
private:
	std::vector<physx::PxShape *> shapevec;
	std::vector<physx::PxRigidDynamic *> dactorvec;
	std::vector<physx::PxRigidStatic *> sactorvec;
	std::vector<physx::PxBounds3> collisions;
};

#endif // __FE_PHYSICS
