#ifndef SCRIPTEDCOSMETIC_H_
#define SCRIPTEDCOSMETIC_H_

#include "CreatureAI.h"
#include "Creature.h"
#include "MotionMaster.h"

struct TC_GAME_API ScriptedCosmeticAI : public CreatureAI
{
public:
    std::map<uint32, std::function<void()>>                 onPointReached;           
    std::list<std::function<void()>>                        delayedOperations;        
    std::vector<std::pair<int32, std::function<void()>>>    timedDelayedOperations;   
    bool                                                    emptyWarned;

    explicit ScriptedCosmeticAI(Creature* creature);
    virtual ~ScriptedCosmeticAI() { };

    // Methods.
    void AddTimedDelayedOperation(uint32 timeout, std::function<void()>&& function);
    virtual void LastOperationCalled() { }

    // VIRTUAL: From CreatureAI
    virtual void UpdateAI(const uint32 diff) override;
    virtual void MovementInform(uint32 type, uint32 ID) override;
};

#endif // SCRIPTEDCOSMETIC_H_
