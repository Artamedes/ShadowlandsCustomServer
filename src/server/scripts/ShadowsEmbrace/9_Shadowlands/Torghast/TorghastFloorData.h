#pragma once

#include "Position.h"

namespace Torghast
{
    enum class FloorType
    {
        Trash = 1,
        Boss,
        Break,
    };

    struct TorghastFloor
    {
        Position TeleportPos;
        FloorType Type;
        uint32 DoorSpawnId;
        uint32 BossSpawnId;
    };

    struct TorghastFloorData
    {
        TorghastFloor Floor;
        bool CheckedFloor = false;
    };

    namespace UpperReaches
    {
        const TorghastFloor TrashFloor[] =
        {
            { { 9609.609, -941.52606, 0.390757  }, FloorType::Trash, 460777, 460746 },
            { { 8241.882, -3937.9583, 40.600838 }, FloorType::Trash, 460982, 460838 },
            { { 10857.234f, 1135.5139f, 34.546436f, 3.117077589035034179f }, FloorType::Trash, 461131, 461096 },
        };

        const TorghastFloor BossFloor[] =
        {
            {{ 10885.356f,-1068.0555f,-19.519989f, 3.0798232555538940429f }, FloorType::Boss, 461144, 461142 },
        };


        const TorghastFloor BreakFloor[] =
        {
            { { 9475.6f, 1067.8f, 0.3f }, FloorType::Break, 461007, 0 },
        };
    }

    namespace AdamaentVaults
    {
        const TorghastFloor TrashFloor[] =
        {
            { { 9629.094f, 8449.239f, 29.862312f, 1.603514790534973144f }, FloorType::Trash, 0, 0 },
        };

        const TorghastFloor BossFloor[] =
        {
            { { 8735.454f, 8431.202f, 93.6035f, 6.271943569183349609f }, FloorType::Boss, 0, 0 },
        };
    }
}
