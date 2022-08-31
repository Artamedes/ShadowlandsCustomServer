#include "ScriptedCosmeticAI.h"

ScriptedCosmeticAI::ScriptedCosmeticAI(Creature * creature) : CreatureAI(creature)
{
    emptyWarned = true;
}

void ScriptedCosmeticAI::AddTimedDelayedOperation(uint32 timeout, std::function<void()>&& function)
{
    emptyWarned = false;

    // Add operation to the queue.
    timedDelayedOperations.push_back(std::pair<uint32, std::function<void()>>(timeout, function));
}

void ScriptedCosmeticAI::UpdateAI(const uint32 diff)
{
    while (!delayedOperations.empty())
    {
        delayedOperations.front()();
        delayedOperations.pop_front();
    }

    for (auto iter = timedDelayedOperations.begin(); iter != timedDelayedOperations.end(); iter++)
    {
        iter->first -= diff;

        if (iter->first <= 0)
        {
            // Call function.
            iter->second();
            iter->second = nullptr;
        }
    }

    uint32 timedDelayedOperationCountToRemove = (uint32)std::count_if(std::begin(timedDelayedOperations), std::end(timedDelayedOperations), [](std::pair<int32, std::function<void()>> const& pair) -> bool
    {
        return (pair.second == nullptr);
    });

    for (uint32 i = 0; i < timedDelayedOperationCountToRemove; i++)
    {
        auto entry = std::find_if(std::begin(timedDelayedOperations), std::end(timedDelayedOperations), [](std::pair<int32, std::function<void()>> const& pair) -> bool
        {
            return (pair.second == nullptr);
        });

        if (entry != std::end(timedDelayedOperations))
            timedDelayedOperations.erase(entry);
    }

    if (timedDelayedOperations.empty() && !emptyWarned)
    {
        emptyWarned = true;
        LastOperationCalled();
    }
}

void ScriptedCosmeticAI::MovementInform(uint32 type, uint32 ID)
{
    if (type == POINT_MOTION_TYPE)
    {
        if (onPointReached.find(ID) != onPointReached.end())
        {
            delayedOperations.push_back([this, ID]() -> void
            {
                if (onPointReached.find(ID) != onPointReached.end())
                    onPointReached[ID]();
            });
        }
    }
}
