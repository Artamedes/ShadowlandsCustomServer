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

#include "Scenario.h"
#include "InstanceSaveMgr.h"
#include "InstanceScenario.h"
#include "InstanceScript.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "ScenarioMgr.h"
#include "ScenarioPackets.h"

Scenario::Scenario(ScenarioData const* scenarioData) : _data(scenarioData), _currentstep(nullptr)
{
    ASSERT(_data);

    for (std::pair<uint8 const, ScenarioStepEntry const*> const& scenarioStep : _data->Steps)
        SetStepState(scenarioStep.second, SCENARIO_STEP_NOT_STARTED);

    if (ScenarioStepEntry const* step = GetFirstStep())
        SetStep(step);
    else
        TC_LOG_ERROR("scenario", "Scenario::Scenario: Could not launch Scenario (id: %u), found no valid scenario step", _data->Entry->ID);

    _scenarioType = SCENARIO_INSTANCE_TYPE_SCENARIO;
}

Scenario::~Scenario()
{
    for (ObjectGuid guid : _players)
        if (Player* player = ObjectAccessor::FindPlayer(guid))
            SendBootPlayer(player);

    _players.clear();
}

void Scenario::Reset()
{
    CriteriaHandler::Reset();
    SetStep(GetFirstStep());
}

void Scenario::CompleteStep(ScenarioStepEntry const* step)
{
    if (Quest const* quest = sObjectMgr->GetQuestTemplate(step->RewardQuestID))
        for (ObjectGuid guid : _players)
            if (Player* player = ObjectAccessor::FindPlayer(guid))
                player->RewardQuest(quest, LootItemType::Item, 0, nullptr, false);

    if (step->IsBonusObjective())
        return;

    ScenarioStepEntry const* newStep = nullptr;
    for (auto const& _step : _data->Steps)
    {
        if (_step.second->IsBonusObjective())
            continue;

        if (GetStepState(_step.second) == SCENARIO_STEP_DONE)
            continue;

        if (!newStep || _step.second->OrderIndex < newStep->OrderIndex)
            newStep = _step.second;
    }

    SetStep(newStep);
    if (IsComplete())
        CompleteScenario();
    else if (!newStep)
        TC_LOG_ERROR("scenario", "Scenario::CompleteStep: Scenario (id: %u, step: %u) was completed, but could not determine new step, or validate scenario completion.", step->ScenarioID, step->ID);
}

void Scenario::CompleteScenario()
{
    SendPacket(WorldPackets::Scenario::ScenarioCompleted(_data->Entry->ID).Write());

    for (ObjectGuid guid : _players)
    {
        if (Player* player = ObjectAccessor::FindPlayer(guid))
        {
            player->UpdateCriteria(CriteriaType::CompleteScenario, GetEntry()->ID, 1);
            player->UpdateCriteria(CriteriaType::CompleteAnyScenario, 1);
        }
    }
}

void Scenario::SetStep(ScenarioStepEntry const* step)
{
    _currentstep = step;
    if (step)
        SetStepState(step, SCENARIO_STEP_IN_PROGRESS);

    WorldPackets::Scenario::ScenarioState scenarioState;
    BuildScenarioState(&scenarioState);
    SendPacket(scenarioState.Write());
}

void Scenario::OnPlayerEnter(Player* player)
{
    _players.insert(player->GetGUID());

    switch (player->GetMapId())
    {
        //case 959: // Shado Pan Monastary
        case 1277: // defense of karabdor
            return;
        default:
            break;
    }

    // send empty TEST
    ///SendBootPlayer(player);

    SendScenarioState(player);
}

void Scenario::OnPlayerExit(Player* player)
{
    _players.erase(player->GetGUID());
    SendBootPlayer(player);
}

bool Scenario::IsComplete()
{
    for (std::pair<uint8 const, ScenarioStepEntry const*> const& scenarioStep : _data->Steps)
    {
        if (scenarioStep.second->IsBonusObjective())
            continue;

        if (GetStepState(scenarioStep.second) != SCENARIO_STEP_DONE)
            return false;
    }

    return true;
}

ScenarioEntry const* Scenario::GetEntry() const
{
    return _data->Entry;
}

ScenarioStepState Scenario::GetStepState(ScenarioStepEntry const* step)
{
    std::map<ScenarioStepEntry const*, ScenarioStepState>::const_iterator itr = _stepStates.find(step);
    if (itr == _stepStates.end())
        return SCENARIO_STEP_INVALID;

    return itr->second;
}

void Scenario::SendCriteriaUpdate(Criteria const * criteria, CriteriaProgress const * progress, Seconds timeElapsed, bool timedCompleted) const
{
    WorldPackets::Scenario::ScenarioProgressUpdate progressUpdate;
    progressUpdate.CriteriaProgress.Id = criteria->ID;
    progressUpdate.CriteriaProgress.Quantity = progress->Counter;
    progressUpdate.CriteriaProgress.Player = progress->PlayerGUID;
    progressUpdate.CriteriaProgress.Date = progress->Date;
    if (criteria->Entry->StartTimer)
        progressUpdate.CriteriaProgress.Flags = timedCompleted ? 1 : 0;

    progressUpdate.CriteriaProgress.TimeFromStart = timeElapsed;
    progressUpdate.CriteriaProgress.TimeFromCreate = Seconds::zero();

    SendPacket(progressUpdate.Write());
}

bool Scenario::CanUpdateCriteriaTree(Criteria const * /*criteria*/, CriteriaTree const * tree, Player * /*referencePlayer*/) const
{
    ScenarioStepEntry const* step = tree->ScenarioStep;
    if (!step)
        return false;

    if (step->ScenarioID != _data->Entry->ID)
        return false;

    ScenarioStepEntry const* currentStep = GetStep();
    if (!currentStep)
        return false;

    if (step->IsBonusObjective())
        return true;

    return currentStep == step;
}

bool Scenario::CanCompleteCriteriaTree(CriteriaTree const* tree)
{
    ScenarioStepEntry const* step = tree->ScenarioStep;
    if (!step)
        return false;

    if (step->ScenarioID != _data->Entry->ID)
        return false;

    if (!step->IsBonusObjective())
        return !IsComplete();

    if (step != GetStep())
        return false;

    // does this always return true?
    //return CriteriaHandler::CanCompleteCriteriaTree(tree);
    return true;
}

void Scenario::CompletedCriteriaTree(CriteriaTree const* tree, Player* referencePlayer)
{
    CriteriaHandler::CompletedCriteriaTree(tree, referencePlayer);

    if (InstanceScenario* instanceScenario = ToInstanceScenario())
        if (InstanceMap* instanceMap = instanceScenario->GetMap()->ToInstanceMap())
            if (InstanceScript* instanceScript = instanceMap->GetInstanceScript())
                instanceScript->OnCompletedCriteriaTree(tree);

    ScenarioStepEntry const* step = tree->ScenarioStep;
    if (!step)
        return;

    // Do not complete if it's a sub-tree
    if (step->Criteriatreeid != tree->ID)
        return;

    if (!step->IsBonusObjective() && step != GetStep())
        return;

    if (GetStepState(step) == SCENARIO_STEP_DONE)
        return;

    SetStepState(step, SCENARIO_STEP_DONE);
    CompleteStep(step);
}

bool Scenario::IsCompletedStep(ScenarioStepEntry const* step)
{
    CriteriaTree const* tree = sCriteriaMgr->GetCriteriaTree(step->Criteriatreeid);
    if (!tree)
        return false;

    return IsCompletedCriteriaTree(tree, nullptr);
}

void Scenario::SendPacket(WorldPacket const* data) const
{
    for (ObjectGuid guid : _players)
        if (Player* player = ObjectAccessor::FindPlayer(guid))
            player->SendDirectMessage(data);
}

void Scenario::BuildScenarioState(WorldPackets::Scenario::ScenarioState* scenarioState)
{
    scenarioState->ScenarioID = _data->Entry->ID;
    if (ScenarioStepEntry const* step = GetStep())
        scenarioState->CurrentStep = step->ID;
    scenarioState->CriteriaProgress = GetCriteriasProgress();
    scenarioState->BonusObjectives = GetBonusObjectivesData();
    // Don't know exactly what this is for, but seems to contain list of scenario steps that we're either on or that are completed
    for (std::pair<ScenarioStepEntry const* const, ScenarioStepState> const& state : _stepStates)
    {
        if (state.first->IsBonusObjective())
            continue;

        switch (state.second)
        {
            case SCENARIO_STEP_IN_PROGRESS:
            case SCENARIO_STEP_DONE:
                break;
            case SCENARIO_STEP_NOT_STARTED:
            default:
                continue;
        }

        scenarioState->PickedSteps.push_back(state.first->ID);
    }
    scenarioState->ScenarioComplete = IsComplete();
}

ScenarioStepEntry const* Scenario::GetFirstStep() const
{
    // Do it like this because we don't know what order they're in inside the container.
    ScenarioStepEntry const* firstStep = nullptr;
    for (std::pair<uint8 const, ScenarioStepEntry const*> const& scenarioStep : _data->Steps)
    {
        if (scenarioStep.second->IsBonusObjective())
            continue;

        if (!firstStep || scenarioStep.second->OrderIndex < firstStep->OrderIndex)
            firstStep = scenarioStep.second;
    }

    return firstStep;
}

ScenarioStepEntry const* Scenario::GetLastStep() const
{
    // Do it like this because we don't know what order they're in inside the container.
    ScenarioStepEntry const* lastStep = nullptr;
    for (std::pair<uint8 const, ScenarioStepEntry const*> const& scenarioStep : _data->Steps)
    {
        if (scenarioStep.second->IsBonusObjective())
            continue;

        if (!lastStep || scenarioStep.second->OrderIndex > lastStep->OrderIndex)
            lastStep = scenarioStep.second;
    }

    return lastStep;
}

void Scenario::SendScenarioState(Player* player)
{
    WorldPackets::Scenario::ScenarioState scenarioState;
    BuildScenarioState(&scenarioState);
    scenarioState.PlayerGUID = player->GetGUID(); // todo fix this, might be party leader
    player->SendDirectMessage(scenarioState.Write());
}

std::vector<WorldPackets::Scenario::BonusObjectiveData> Scenario::GetBonusObjectivesData()
{
    std::vector<WorldPackets::Scenario::BonusObjectiveData> bonusObjectivesData;
    for (std::pair<uint8 const, ScenarioStepEntry const*> const& scenarioStep : _data->Steps)
    {
        if (!scenarioStep.second->IsBonusObjective())
            continue;

        if (sCriteriaMgr->GetCriteriaTree(scenarioStep.second->Criteriatreeid))
        {
            WorldPackets::Scenario::BonusObjectiveData bonusObjectiveData;
            bonusObjectiveData.BonusObjectiveID = scenarioStep.second->ID;
            bonusObjectiveData.ObjectiveComplete = GetStepState(scenarioStep.second) == SCENARIO_STEP_DONE;
            bonusObjectivesData.push_back(bonusObjectiveData);
        }
    }

    return bonusObjectivesData;
}

std::vector<WorldPackets::Achievement::CriteriaProgress> Scenario::GetCriteriasProgress()
{
    std::vector<WorldPackets::Achievement::CriteriaProgress> criteriasProgress;

    if (!_criteriaProgress.empty())
    {
        for (std::pair<uint32 const, CriteriaProgress> const& progressPair : _criteriaProgress)
        {
            WorldPackets::Achievement::CriteriaProgress criteriaProgress;
            criteriaProgress.Id = progressPair.first;
            criteriaProgress.Quantity = progressPair.second.Counter;
            criteriaProgress.Date = progressPair.second.Date;
            criteriaProgress.Player = progressPair.second.PlayerGUID;
            criteriasProgress.push_back(criteriaProgress);
        }
    }

    return criteriasProgress;
}

CriteriaList const& Scenario::GetCriteriaByType(CriteriaType type, uint32 /*asset*/) const
{
    return sCriteriaMgr->GetScenarioCriteriaByTypeAndScenario(type, _data->Entry->ID);
}

void Scenario::SendBootPlayer(Player* player)
{
    WorldPackets::Scenario::ScenarioVacate scenarioBoot;
    scenarioBoot.ScenarioID = _data->Entry->ID;
    player->SendDirectMessage(scenarioBoot.Write());
}

void Scenario::SendScenarioEvent(Player* player, uint32 eventId)
{
    UpdateCriteria(CriteriaType::AnyoneTriggerGameEventScenario, eventId, 0, 0, nullptr, player);
}

void Scenario::SendScenarioEventToPlayers(uint32 eventId)
{
    for (ObjectGuid guid : _players)
        if (Player* player = ObjectAccessor::FindPlayer(guid))
            CriteriaHandler::UpdateCriteria(CriteriaType::AnyoneTriggerGameEventScenario, eventId, 0, 0, nullptr, player);
}
