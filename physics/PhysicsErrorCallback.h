#ifndef PHYSX4_PHYSICSERRORCALLBACK_H
#define PHYSX4_PHYSICSERRORCALLBACK_H

#include "foundation/PxErrorCallback.h"

/* Custom implementation of PhysX error callback */
class PhysicsErrorCallback : public physx::PxErrorCallback
{
public:
    PhysicsErrorCallback();
    virtual ~PhysicsErrorCallback();

    virtual void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
};

#endif //PHYSX4_PHYSICSERRORCALLBACK_H
