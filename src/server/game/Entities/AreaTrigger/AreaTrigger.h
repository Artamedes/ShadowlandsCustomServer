/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITYCORE_AREATRIGGER_H
#define TRINITYCORE_AREATRIGGER_H

#include "Object.h"
#include "GridObject.h"
#include "MapObject.h"
#include "AreaTriggerTemplate.h"

class AuraEffect;
class AreaTriggerAI;
class SpellInfo;
class Unit;

namespace G3D
{
    class Vector2;
    class Vector3;
}
namespace Movement
{
    template<typename length_type>
    class Spline;
}

class TC_GAME_API AreaTrigger : public WorldObject, public GridObject<AreaTrigger>, public MapObject
{
    public:
        AreaTrigger();
        ~AreaTrigger();

    protected:
        void BuildValuesCreate(ByteBuffer* data, Player const* target) const override;
        void BuildValuesUpdate(ByteBuffer* data, Player const* target) const override;
        void ClearUpdateMask(bool remove) override;

    public:
        void BuildValuesUpdateForPlayerWithMask(UpdateData* data, UF::ObjectData::Mask const& requestedObjectMask,
            UF::AreaTriggerData::Mask const& requestedAreaTriggerMask, Player const* target) const;

        struct ValuesUpdateForPlayerWithMaskSender // sender compatible with MessageDistDeliverer
        {
            explicit ValuesUpdateForPlayerWithMaskSender(AreaTrigger const* owner) : Owner(owner) { }

            AreaTrigger const* Owner;
            UF::ObjectData::Base ObjectMask;
            UF::AreaTriggerData::Base AreaTriggerMask;

            void operator()(Player const* player) const;
        };

        void AddToWorld() override;
        void RemoveFromWorld() override;

        void AI_Initialize();
        void AI_Destroy();

        AreaTriggerAI* AI() { return _ai.get(); }

        bool IsServerSide() const { return _areaTriggerTemplate->Id.IsServerSide; }
        void SetXSpellVisualID(uint32 id);
        bool IsNeverVisibleFor(WorldObject const* seer) const override { return WorldObject::IsNeverVisibleFor(seer) || IsServerSide(); }

    private:
        bool Create(uint32 areaTriggerCreatePropertiesId, Unit* caster, Unit* target, SpellInfo const* spell, Position const& pos, int32 duration, SpellCastVisual spellVisual, ObjectGuid const& castId, AuraEffect const* aurEff, ObjectGuid TargetGUID = ObjectGuid::Empty);
        bool CreateServer(Map* map, AreaTriggerTemplate const* areaTriggerTemplate, AreaTriggerSpawn const& position);

    public:
        static AreaTrigger* CreateAreaTrigger(uint32 areaTriggerCreatePropertiesId, Unit* caster, Unit* target, SpellInfo const* spell, Position const& pos, int32 duration, SpellCastVisual spellVisual, ObjectGuid const& castId = ObjectGuid::Empty, AuraEffect const* aurEff = nullptr, ObjectGuid TargetGUID = ObjectGuid::Empty);
        static ObjectGuid CreateNewMovementForceId(Map* map, uint32 areaTriggerId);
        bool LoadFromDB(ObjectGuid::LowType spawnId, Map* map, bool addToMap, bool allowDuplicate);

        void Update(uint32 diff) override;
        void Remove();
        bool IsRemoved() const { return _isRemoved; }
        bool HaveDestination() const { return _setedDestination; }
        uint32 GetSpellId() const { return m_areaTriggerData->SpellID; }
        AuraEffect const* GetAuraEffect() const { return _aurEff; }
        uint32 GetTimeSinceCreated() const { return _timeSinceCreated; }
        uint32 GetTimeToTarget() const { return m_areaTriggerData->TimeToTarget; }
        uint32 GetTimeToTargetScale() const { return m_areaTriggerData->TimeToTargetScale; }
        void UpdateTimeToTarget(uint32 timeToTarget);
        int32 GetDuration() const { return _duration; }
        int32 GetTotalDuration() const { return _totalDuration; }
        void SetDuration(int32 newDuration);
        void Delay(int32 delaytime) { SetDuration(GetDuration() - delaytime); }
        void SetPeriodicProcTimer(uint32 periodicProctimer) { _basePeriodicProcTimer = periodicProctimer; _periodicProcTimer = periodicProctimer; }

        GuidUnorderedSet const& GetInsideUnits() const { return _insideUnits; }

        AreaTriggerCreateProperties const* GetCreateProperties() const { return _areaTriggerCreateProperties; }
        AreaTriggerTemplate const* GetTemplate() const;
        uint32 GetScriptId() const;

        ObjectGuid GetOwnerGUID() const override { return GetCasterGuid(); }
        ObjectGuid const& GetCasterGuid() const { return m_areaTriggerData->Caster; }
        Unit* GetCaster() const;
        Unit* GetTarget() const;

        uint32 GetFaction() const override;

        AreaTriggerShapeInfo const& GetShape() const { return _shape; }
        float GetMaxSearchRadius() const { return _maxSearchRadius; }
        Position const& GetRollPitchYaw() const { return _rollPitchYaw; }
        Position const& GetTargetRollPitchYaw() const { return _targetRollPitchYaw; }
        void InitSplineOffsets(std::vector<Position> const& offsets, uint32 timeToTarget);
        void InitSplines(std::vector<G3D::Vector3> splinePoints, uint32 timeToTarget);
        bool HasSplines() const;
        ::Movement::Spline<int32> const& GetSpline() const { return *_spline; }
        uint32 GetElapsedTimeForMovement() const { return GetTimeSinceCreated(); } /// @todo: research the right value, in sniffs both timers are nearly identical

        void InitOrbit(AreaTriggerOrbitInfo const& orbit, uint32 timeToTarget);
        bool HasOrbit() const;
        bool SetDestination(Position const& pos, uint32 timeToTarget, bool followTerrain = false);
        bool SetDestinationPig(WorldObject* target);
        Optional<AreaTriggerOrbitInfo> const& GetCircularMovementInfo() const { return _orbitInfo; }
        void SetMaxSearchRadius(float radius);

        void UpdateShape();

        float GetRadius() { return _radius; }
        float GetCurrentTimePercent();
        UF::UpdateField<UF::AreaTriggerData, 0, TYPEID_AREATRIGGER> m_areaTriggerData;

        float OverrideRadiusTarget;
        float OverrideRadius;

        // exposed for script access
        bool _reachedDestination;

        void SetTargetGUID(ObjectGuid const& guid);
        void SetExtraScaleCurveParameter(uint32 param) { SetUpdateFieldValue(m_values.ModifyValue(&AreaTrigger::m_areaTriggerData).ModifyValue(&UF::AreaTriggerData::ExtraScaleCurve).ModifyValue(&UF::ScaleCurve::ParameterCurve), param); }
        void SetExtraScaleOverrideActive(bool over) { SetUpdateFieldValue(m_values.ModifyValue(&AreaTrigger::m_areaTriggerData).ModifyValue(&UF::AreaTriggerData::ExtraScaleCurve).ModifyValue(&UF::ScaleCurve::OverrideActive), over); }

        void SetSpellForVisuals(uint32 spellId) { SetUpdateFieldValue(m_values.ModifyValue(&AreaTrigger::m_areaTriggerData).ModifyValue(&UF::AreaTriggerData::SpellForVisuals), spellId); }
        void SetDecalPropertiesId(uint32 decalPropertiesId) { SetUpdateFieldValue(m_values.ModifyValue(&AreaTrigger::m_areaTriggerData).ModifyValue(&UF::AreaTriggerData::DecalPropertiesID), decalPropertiesId); }

        uint32 CreateTimeMS = 0;

    protected:
        Unit* m_Caster;
        void _UpdateDuration(int32 newDuration);
        float GetProgress() const;

        void UpdateTargetList();
        void SearchUnits(std::vector<Unit*>& targetList, float radius, bool check3D);
        void SearchUnitInSphere(std::vector<Unit*>& targetList);
        void SearchUnitInBox(std::vector<Unit*>& targetList);
        void SearchUnitInPolygon(std::vector<Unit*>& targetList);
        void SearchUnitInCylinder(std::vector<Unit*>& targetList);
        void SearchUnitInDisk(std::vector<Unit*>& targetList);
        bool CheckIsInPolygon2D(Position const* pos) const;
        void HandleUnitEnterExit(std::vector<Unit*> const& targetList);

        void DoActions(Unit* unit);
        void UndoActions(Unit* unit);

        void UpdatePolygonOrientation();
        void UpdateOrbitPosition(uint32 diff);
        void UpdateSplinePosition(uint32 diff);

        Position const* GetOrbitCenterPosition() const;
        Position CalculateOrbitPosition() const;

        void DebugVisualizePosition(); // Debug purpose only

        ObjectGuid::LowType _spawnId;

        ObjectGuid _targetGuid;

        AuraEffect const* _aurEff;

        AreaTriggerShapeInfo _shape;
        float _maxSearchRadius;
        int32 _duration;
        int32 _totalDuration;
        uint32 _timeSinceCreated;
        uint32 _periodicProcTimer;
        uint32 _basePeriodicProcTimer;
        float _previousCheckOrientation;
        float _radius;
        bool _isRemoved;
        bool _setedDestination;

        Position _rollPitchYaw;
        Position _targetRollPitchYaw;
        std::vector<Position> _polygonVertices;
        std::unique_ptr<::Movement::Spline<int32>> _spline;

        int32 _lastSplineIndex;
        uint32 _movementTime;

        Optional<AreaTriggerOrbitInfo> _orbitInfo;

        AreaTriggerCreateProperties const* _areaTriggerCreateProperties;
        AreaTriggerTemplate const* _areaTriggerTemplate;
        GuidUnorderedSet _insideUnits;

        std::unique_ptr<AreaTriggerAI> _ai;
};

#endif
