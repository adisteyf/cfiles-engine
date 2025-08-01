#include "PxFoundation.h"
#include "PxMaterial.h"
#include "PxPhysics.h"
#include "PxPhysicsVersion.h"
#include "extensions/PxDefaultCpuDispatcher.h"
#include "extensions/PxDefaultSimulationFilterShader.h"
#include "pvd/PxPvd.h"
#include "pvd/PxPvdSceneClient.h"
#include "pvd/PxPvdTransport.h"
#include <PxPhysicsAPI.h>
#include "physics.h"
#include <glm/glm.hpp>

Physics::Physics(void)
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);
	if (!mFoundation) { throw("PxCreateFoundation failed"); }

	mPvd = PxCreatePvd(*mFoundation);
	physx::PxPvdTransport *transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	mPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

	mToleranceScale.length = 100;
	mToleranceScale.speed  = 981;

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, mToleranceScale, true, mPvd);
	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.f, -9.81f, 0.f);
	mDispatcher = physx::PxDefaultCpuDispatcherCreate(2);

	sceneDesc.cpuDispatcher = mDispatcher;
	sceneDesc.filterShader  = physx::PxDefaultSimulationFilterShader;
	mScene                  = mPhysics->createScene(sceneDesc);

	physx::PxPvdSceneClient *pvdClient = mScene->getScenePvdClient();
	if (pvdClient) {
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS,   true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS,      true);
		pvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES,  true);
	}

	mMaterial = mPhysics->createMaterial(.5f, .5f, .6f);
}

void Physics::simulate(double dt)
{
	mScene->simulate(dt);
	mScene->fetchResults(true);
}

/*void * Physics::createAABB(double min[3], double max[3])
{
	physx::PxVec3 minB(min[0], min[1], min[2]);
	physx::PxVec3 maxB(max[0], max[1], max[2]);
	physx::PxBounds3 aabb(minB, maxB);
	return aabb;
}*/

void Physics::createStaticShape(glm::vec3 *transform, physx::PxBounds3 collision, glm::vec3 material)
{
	physx::PxTransform pxt(transform->x, transform->y, transform->z);
	physx::PxShape *shape;
	physx::PxRigidStatic *actor = mPhysics->createRigidStatic(pxt);
	physx::PxMaterial *pxm = mPhysics->createMaterial(material[0], material[1], material[2]);

	shape = mPhysics->createShape(physx::PxBoxGeometry(collision.getExtents()), *pxm);
	actor->attachShape(*shape);
	shapevec.push_back(shape);
	sactorvec.push_back(actor);
}

void Physics::createDynamicShape(glm::vec3 *transform, physx::PxBounds3 collision, glm::vec3 material)
{
	physx::PxTransform pxt(transform->x, transform->y, transform->z);
	physx::PxShape *shape;
	physx::PxRigidDynamic *actor = mPhysics->createRigidDynamic(pxt);
	physx::PxMaterial *pxm = mPhysics->createMaterial(material[0], material[1], material[2]);

	shape = mPhysics->createShape(physx::PxBoxGeometry(collision.getExtents()), *pxm);
	actor->attachShape(*shape);
	shapevec.push_back(shape);
	dactorvec.push_back(actor);
}

void Physics::setMass(int actorID, float m) {
	dactorvec[actorID]->setMass(m);
}

Physics::~Physics()
{
	while (!shapevec.empty()) {
		shapevec[0]->release();
		shapevec.erase(shapevec.begin());
	}
}
