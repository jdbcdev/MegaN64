#pragma once

#include <memory>
#include <vector>
#include <mutex>
#include "opengl_ObjectPool.h"

namespace opengl {

class OpenGlCommand : public PoolObject {
public:
    void performCommandSingleThreaded();

    void performCommand();

    void waitOnCommand();

protected:
    OpenGlCommand(bool _synced, bool _logIfSynced, const std::string &_functionName,
                  bool _isGlCommand = true);

    virtual void commandToExecute() = 0;

    template<typename CoomandType>
    static std::shared_ptr<CoomandType> getFromPool(int _poolId) {
        auto poolObject = OpenGlCommandPool::get().getAvailableObject(_poolId);
        if (poolObject == nullptr) {
            poolObject = std::shared_ptr<CoomandType>(new CoomandType);
            OpenGlCommandPool::get().addObjectToPool(_poolId, poolObject);
        }

        poolObject->setInUse(true);
        return std::static_pointer_cast<CoomandType>(poolObject);
    }

protected:

#ifdef GL_DEBUG
    const bool m_logIfSynced;
    const std::string m_functionName;
    const bool m_isGlCommand;
#endif

private:
    std::atomic<bool> m_synced;
    bool m_executed;
    std::mutex m_condvarMutex;
    std::condition_variable m_condition;
};
}
