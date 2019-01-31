#include "PhysicsErrorCallback.h"

#include <chrono>
#include <cstdio>
#include <thread>
#include "foundation/PxAssert.h"


PhysicsErrorCallback::PhysicsErrorCallback()
{
}

PhysicsErrorCallback::~PhysicsErrorCallback()
{
}

void PhysicsErrorCallback::reportError(physx::PxErrorCode::Enum code, const char *message, const char *file, int line)
{
    const char* errorCode = nullptr;

    switch (code)
    {
        case physx::PxErrorCode::eNO_ERROR:
            errorCode = "no error";
            break;
        case physx::PxErrorCode::eINVALID_PARAMETER:
            errorCode = "invalid parameter";
            break;
        case physx::PxErrorCode::eINVALID_OPERATION:
            errorCode = "invalid operation";
            break;
        case physx::PxErrorCode::eOUT_OF_MEMORY:
            errorCode = "out of memory";
            break;
        case physx::PxErrorCode::eDEBUG_INFO:
            errorCode = "info";
            break;
        case physx::PxErrorCode::eDEBUG_WARNING:
            errorCode = "warning";
            break;
        case physx::PxErrorCode::ePERF_WARNING:
            errorCode = "performance warning";
            break;
        case physx::PxErrorCode::eABORT:
            errorCode = "abort";
            break;
        case physx::PxErrorCode::eINTERNAL_ERROR:
            errorCode = "internal error";
            break;
        case physx::PxErrorCode::eMASK_ALL:
            errorCode = "unknown error";
            break;
    }

    PX_ASSERT(errorCode);
    if(errorCode)
    {
        char buffer[1024];
        sprintf_s(buffer, "%s (%d) : %s : %s\n", file, line, errorCode, message);

        puts(buffer);

        // in debug builds halt execution for abort codes
        PX_ASSERT(code != physx::PxErrorCode::eABORT);

        // in release builds we also want to halt execution
        // and make sure that the error message is flushed
        while (code == physx::PxErrorCode::eABORT)
        {
            puts(buffer);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}
