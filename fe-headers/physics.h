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
	void createStaticShape(glm::vec3 *transform, physx::PxBounds3 collision, glm::vec3 material);
	void createDynamicShape(glm::vec3 *transform, physx::PxBounds3 collision, glm::vec3 material);
	//void * createAABB(double min[3], double max[3]);
	void setMass(int actorID, float m);
private:
	std::vector<physx::PxShape *> shapevec;
	std::vector<physx::PxRigidDynamic *> dactorvec;
	std::vector<physx::PxRigidStatic *> sactorvec;
};

#endif // __FE_PHYSICS
