#include "nwnx.hpp"

#include "API/CNWSArea.hpp"
#include "API/CAppManager.hpp"
#include "API/CServerExoApp.hpp"
#include "API/CNWSModule.hpp"
#include "API/CNWSTrigger.hpp"
#include "API/CNWSTile.hpp"
#include "API/CNWTileData.hpp"
#include "API/CNWSAmbientSound.hpp"
#include "API/CResStruct.hpp"
#include "API/CResList.hpp"
#include "API/CNWSCreature.hpp"
#include "API/CNWSCreatureStats.hpp"
#include "API/CNWSSoundObject.hpp"
#include "API/CNWSEncounter.hpp"
#include "API/CNWSItem.hpp"
#include "API/CNWSDoor.hpp"
#include "API/CNWSWaypoint.hpp"
#include "API/CNWSPlaceable.hpp"
#include "API/CNWSStore.hpp"
#include "API/CNWSAreaOfEffectObject.hpp"
#include "API/CNWTileSet.hpp"
#include "API/CEncounterSpawnPoint.hpp"

#include <cmath>
#include <set>

using namespace NWNXLib;
using namespace NWNXLib::API;

static std::set<ObjectID> s_ExportExclusionList;

NWNX_EXPORT ArgumentStack GetNumberOfPlayersInArea(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nPlayersInArea;

    return 0;
}

NWNX_EXPORT ArgumentStack GetLastEntered(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_oidLastEntered;

    return Constants::OBJECT_INVALID;
}

NWNX_EXPORT ArgumentStack GetLastLeft(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_oidLastLeft;

    return Constants::OBJECT_INVALID;
}

NWNX_EXPORT ArgumentStack GetPVPSetting(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nPVPSetting;

    return 0;
}

NWNX_EXPORT ArgumentStack SetPVPSetting(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        auto pvpSetting = args.extract<int32_t>();
          ASSERT_OR_THROW(pvpSetting >= Constants::PvPSetting::MIN);
          ASSERT_OR_THROW(pvpSetting <= Constants::PvPSetting::MAX);

        pArea->m_nPVPSetting = pvpSetting;
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetAreaSpotModifier(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nAreaSpotModifier;

    return 0;
}

NWNX_EXPORT ArgumentStack SetAreaSpotModifier(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        pArea->m_nAreaSpotModifier = args.extract<int32_t>();

    return {};
}

NWNX_EXPORT ArgumentStack GetAreaListenModifier(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nAreaListenModifier;

    return 0;
}

NWNX_EXPORT ArgumentStack SetAreaListenModifier(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        pArea->m_nAreaListenModifier = args.extract<int32_t>();

    return {};
}

NWNX_EXPORT ArgumentStack GetNoRestingAllowed(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_bNoRestingAllowed;

    return 0;
}

NWNX_EXPORT ArgumentStack SetNoRestingAllowed(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        pArea->m_bNoRestingAllowed = !!args.extract<int32_t>();

    return {};
}

NWNX_EXPORT ArgumentStack GetWindPower(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nWindAmount;

    return 0;
}

NWNX_EXPORT ArgumentStack SetWindPower(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto windPower = args.extract<int32_t>();
          ASSERT_OR_THROW(windPower >= 0);
          ASSERT_OR_THROW(windPower <= 2);

        pArea->m_nWindAmount = windPower;
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetWeatherChance(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto type = args.extract<int32_t>();
          ASSERT_OR_THROW(type >= 0);
          ASSERT_OR_THROW(type <= 2);

        switch (type)
        {
            case 0: return pArea->m_nChanceOfRain;
            case 1: return pArea->m_nChanceOfSnow;
            case 2: return pArea->m_nChanceOfLightning;
        }
    }

    return 0;
}

NWNX_EXPORT ArgumentStack SetWeatherChance(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto type = args.extract<int32_t>();
          ASSERT_OR_THROW(type >= 0);
          ASSERT_OR_THROW(type <= 2);
        const auto chance = args.extract<int32_t>();
          ASSERT_OR_THROW(chance >= 0);
          ASSERT_OR_THROW(chance <= 100);

        switch (type)
        {
            case 0:
                pArea->m_nChanceOfRain = chance;
                break;
            case 1:
                pArea->m_nChanceOfSnow = chance;
                break;
            case 2:
                pArea->m_nChanceOfLightning = chance;
                break;
        }
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetFogClipDistance(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_fFogClipDistance;

    return 0.0f;
}

NWNX_EXPORT ArgumentStack SetFogClipDistance(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto distance = args.extract<float>();
          ASSERT_OR_THROW(distance >= 0.0);

        pArea->m_fFogClipDistance = distance;
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetShadowOpacity(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_nShadowOpacity;

    return 0;
}

NWNX_EXPORT ArgumentStack SetShadowOpacity(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto shadowOpacity = args.extract<int32_t>();
          ASSERT_OR_THROW(shadowOpacity >= 0);
          ASSERT_OR_THROW(shadowOpacity <= 100);

        pArea->m_nShadowOpacity = shadowOpacity;
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetDayNightCycle(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
        return pArea->m_bUseDayNightCycle ? 0 : pArea->m_bIsNight + 1;

    return 0;
}

NWNX_EXPORT ArgumentStack SetDayNightCycle(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto type = args.extract<int32_t>();
          ASSERT_OR_THROW(type >= 0);
          ASSERT_OR_THROW(type <= 2);

        switch (type)
        {
            case 0:
                pArea->m_bUseDayNightCycle = 1;
                pArea->m_bIsNight = 0;
                break;

            case 1:
                pArea->m_bUseDayNightCycle = 0;
                pArea->m_bIsNight = 0;
                break;

            case 2:
                pArea->m_bUseDayNightCycle = 0;
                pArea->m_bIsNight = 1;
                break;
        }
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetSunMoonColors(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto type = args.extract<int32_t>();
          ASSERT_OR_THROW(type >= 0);
          ASSERT_OR_THROW(type <= 3);

        switch (type)
        {
            case 0: return (int32_t)pArea->m_nMoonAmbientColor;
            case 1: return (int32_t)pArea->m_nMoonDiffuseColor;
            case 2: return (int32_t)pArea->m_nSunAmbientColor;
            case 3: return (int32_t)pArea->m_nSunDiffuseColor;
        }
    }

    return -1;
}

NWNX_EXPORT ArgumentStack SetSunMoonColors(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto type = args.extract<int32_t>();
          ASSERT_OR_THROW(type >= 0);
          ASSERT_OR_THROW(type <= 3);
        const auto color = args.extract<int32_t>();
          ASSERT_OR_THROW(color >= 0);

        // Switch from RGB to BGR
        auto swappedColor = (uint32_t)(((color & 0x000000FF) << 16) | (color & 0x0000FF00) | ((color & 0x00FF0000) >> 16));

        switch (type)
        {
            case 0:
                pArea->m_nMoonAmbientColor = swappedColor;
                break;
            case 1:
                pArea->m_nMoonDiffuseColor = swappedColor;
                break;
            case 2:
                pArea->m_nSunAmbientColor = swappedColor;
                break;
            case 3:
                pArea->m_nSunDiffuseColor = swappedColor;
                break;
        }
    }

    return {};
}

NWNX_EXPORT ArgumentStack CreateTransition(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        auto targetOid = args.extract<ObjectID>();
        auto *pTargetObject = Utils::AsNWSObject(Globals::AppManager()->m_pServerExoApp->GetGameObject(targetOid));
        if (pTargetObject == nullptr ||
            (pTargetObject->m_nObjectType != Constants::ObjectType::Door &&
             pTargetObject->m_nObjectType != Constants::ObjectType::Waypoint))
        {
            LOG_ERROR("Transition destination object is not valid. Valid targets are doors or waypoints.");
            return Constants::OBJECT_INVALID;
        }

        Vector vTransitionPosition;
        vTransitionPosition.x = args.extract<float>();
        ASSERT_OR_THROW(vTransitionPosition.x >= 0.0f);
        ASSERT_OR_THROW(vTransitionPosition.x < pArea->m_nWidth * 10.0f);
        vTransitionPosition.y = args.extract<float>();
        ASSERT_OR_THROW(vTransitionPosition.y >= 0.0f);
        ASSERT_OR_THROW(vTransitionPosition.y < pArea->m_nHeight * 10.0f);
        vTransitionPosition.z = args.extract<float>();

        const auto size = args.extract<float>();
        ASSERT_OR_THROW(size > 0.0f);
        ASSERT_OR_THROW(vTransitionPosition.x + size < pArea->m_nWidth * 10.0f);
        ASSERT_OR_THROW(vTransitionPosition.y + size < pArea->m_nHeight * 10.0f);

        // Create our trigger
        auto *trigger = new CNWSTrigger(API::Constants::OBJECT_INVALID);
        trigger->LoadFromTemplate(CResRef("newtransition")); // Stock nwn Area Transition resRef
        trigger->SetPosition(vTransitionPosition, 0);
        trigger->CreateNewGeometry(size, vTransitionPosition, pArea);

        // Set its tag if supplied
        const auto tag = args.extract<std::string>();
        if (!tag.empty())
        {
            trigger->m_sTag = CExoString(tag.c_str());
            Utils::GetModule()->AddObjectToLookupTable(trigger->m_sTag, trigger->m_idSelf);
        }

        // Create and assign our transition to the trigger
        auto *transition = new CNWSTransition();
        transition->SetTarget(pTargetObject);
        trigger->m_pTransition = *transition;

        // And add to area
        trigger->AddToArea(pArea, vTransitionPosition.x, vTransitionPosition.y, vTransitionPosition.z, false);
        return trigger->m_idSelf;
    }

    return Constants::OBJECT_INVALID;
}

NWNX_EXPORT ArgumentStack GetTileAnimationLoop(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto tileX = args.extract<float>();
          ASSERT_OR_THROW(tileX >= 0.0f);
        const auto tileY = args.extract<float>();
          ASSERT_OR_THROW(tileY >= 0.0f);
        const auto tileAnimLoop = args.extract<int32_t>();
          ASSERT_OR_THROW(tileAnimLoop >= 1);
          ASSERT_OR_THROW(tileAnimLoop <= 3);

        if (auto *pTile = pArea->GetTile({tileX, tileY, 0.0f}))
        {
            switch(tileAnimLoop)
            {
                case 1: return pTile->m_nAnimLoop1;
                case 2: return pTile->m_nAnimLoop2;
                case 3: return pTile->m_nAnimLoop3;
            }
        }
        else
        {
            LOG_ERROR("NWNX_Area_GetTileAnimationLoop: invalid tile specified");
        }
    }

    return -1;
}

NWNX_EXPORT ArgumentStack SetTileAnimationLoop(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto tileX = args.extract<float>();
          ASSERT_OR_THROW(tileX >= 0.0f);
        const auto tileY = args.extract<float>();
          ASSERT_OR_THROW(tileY >= 0.0f);
        const auto tileAnimLoop = args.extract<int32_t>();
          ASSERT_OR_THROW(tileAnimLoop >= 1);
          ASSERT_OR_THROW(tileAnimLoop <= 3);
        const auto tileEnabled = !!args.extract<int32_t>();

        if (auto *pTile = pArea->GetTile({tileX, tileY, 0.0f}))
        {
            switch(tileAnimLoop)
            {
                case 1:
                    pTile->m_nAnimLoop1 = tileEnabled;
                    break;
                case 2:
                    pTile->m_nAnimLoop2 = tileEnabled;
                    break;
                case 3:
                    pTile->m_nAnimLoop3 = tileEnabled;
                    break;
            }
        }
        else
        {
            LOG_ERROR("NWNX_Area_SetTileAnimationLoop: invalid tile specified");
        }
    }

    return {};
}

NWNX_EXPORT ArgumentStack GetTileModelResRef(ArgumentStack&& args)
{
    if (auto* pArea = Utils::PopArea(args))
    {
        const auto tileX = args.extract<float>();
        ASSERT_OR_THROW(tileX >= 0.0f);
        const auto tileY = args.extract<float>();
        ASSERT_OR_THROW(tileY >= 0.0f);

        if (auto *pTile = pArea->GetTile({tileX, tileY, 0.0f}))
        {
            return pTile->m_pTileData->GetModelResRef().GetResRefStr();
        }
        else
        {
            LOG_ERROR("NWNX_Area_GetTileModelResRef: invalid tile specified");
        }
    }

    return "";
}

NWNX_EXPORT ArgumentStack TestDirectLine(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto fStartX = args.extract<float>();
          ASSERT_OR_THROW(fStartX >= 0.0f);
        const auto fStartY = args.extract<float>();
          ASSERT_OR_THROW(fStartY >= 0.0f);
        const auto fEndX = args.extract<float>();
          ASSERT_OR_THROW(fEndX >= 0.0f);
        const auto fEndY = args.extract<float>();
          ASSERT_OR_THROW(fEndY >= 0.0f);
        const auto fPerSpace = args.extract<float>();
          ASSERT_OR_THROW(fPerSpace >= 0.0f);
        const auto fHeight = args.extract<float>();
            ASSERT_OR_THROW(fHeight >= 0.0f);
        const auto bIgnoreDoors = args.extract<int32_t>();

        return pArea->TestDirectLine(fStartX, fStartY, fEndX, fEndY, fPerSpace, fHeight, bIgnoreDoors);
    }

    return 0;
}

NWNX_EXPORT ArgumentStack GetMusicIsPlaying(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto bBattleMusic = !!args.extract<int32_t>();

        return bBattleMusic ? pArea->m_pAmbientSound->m_bBattlePlaying : pArea->m_pAmbientSound->m_bMusicPlaying;
    }

    return 0;
}

NWNX_EXPORT ArgumentStack CreateGenericTrigger(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        const auto fX = args.extract<float>();
          ASSERT_OR_THROW(fX >= 0.0f);
        const auto fY = args.extract<float>();
          ASSERT_OR_THROW(fY >= 0.0f);
        const auto fZ = args.extract<float>();
        const auto tag = args.extract<std::string>();
        const auto fSize = args.extract<float>();
          ASSERT_OR_THROW(fSize >= 0.0f);

        Vector vPosition = {fX, fY, fZ};

        auto *pTrigger = new CNWSTrigger();
        pTrigger->LoadFromTemplate(CResRef("newgeneric"));
        pTrigger->m_oidCreator = Constants::OBJECT_INVALID;
        pTrigger->SetPosition(vPosition, 0);
        pTrigger->CreateNewGeometry(fSize, vPosition, pArea);

        if (!tag.empty())
        {
            pTrigger->m_sTag = CExoString(tag.c_str());
            Utils::GetModule()->AddObjectToLookupTable(pTrigger->m_sTag, pTrigger->m_idSelf);
        }

        pTrigger->AddToArea(pArea, vPosition.x, vPosition.y, vPosition.z);

        return pTrigger->m_idSelf;
    }

    return Constants::OBJECT_INVALID;
}

NWNX_EXPORT ArgumentStack AddObjectToExclusionList(ArgumentStack&& args)
{
    const auto oidObject = args.extract<ObjectID>();
      ASSERT_OR_THROW(oidObject != Constants::OBJECT_INVALID);

    s_ExportExclusionList.emplace(oidObject);

    return {};
}

NWNX_EXPORT ArgumentStack RemoveObjectFromExclusionList(ArgumentStack&& args)
{
    const auto oidObject = args.extract<ObjectID>();
      ASSERT_OR_THROW(oidObject != Constants::OBJECT_INVALID);

    s_ExportExclusionList.erase(oidObject);

    return {};
}

NWNX_EXPORT ArgumentStack ExportGIT(ArgumentStack&& args)
{
    int32_t retVal = false;

    if (auto *pArea = Utils::PopArea(args))
    {
        auto fileName = args.extract<std::string>();
          ASSERT_OR_THROW(fileName.size() <= 16);
        if (fileName.empty())
            fileName = pArea->m_cResRef.GetResRefStr();

        const auto exportVarTable = !!args.extract<int32_t>();
        const auto exportUUID = !!args.extract<int32_t>();
        const auto objectFilter = args.extract<int32_t>();

        auto alias = args.extract<std::string>();

        if (!Utils::IsValidCustomResourceDirectoryAlias(alias))
        {
            LOG_WARNING("NWNX_Area_ExportGIT() called with an invalid alias: %s, defaulting to 'NWNX'", alias);
            alias = "NWNX";
        }

        CResGFF    resGff;
        CResStruct resStruct{};

        if (resGff.CreateGFFFile(&resStruct, "GIT ", "V3.2"))
        {
            CExoArrayList<ObjectID> creatures, items, doors, triggers, encounters, waypoints, sounds, placeables, stores, aoes;
            std::unordered_map<ObjectID, ObjectID> creatureAreaMap;

            for (int i = 0; i < pArea->m_aGameObjects.num; i++)
            {
                if (auto *pGameObject = Utils::GetGameObject(pArea->m_aGameObjects[i]))
                {
                    if (s_ExportExclusionList.find(pGameObject->m_idSelf) != s_ExportExclusionList.end())
                        continue;

                    if (auto *pCreature = Utils::AsNWSCreature(pGameObject))
                    {
                        if (pCreature->m_pStats->m_bIsPC ||
                            pCreature->m_pStats->GetIsDM() ||
                            (pCreature->m_nAssociateType > Constants::AssociateType::None &&
                            pCreature->m_nAssociateType < Constants::AssociateType::DominatedByPC))
                            continue;

                        // Temporarily set pCreature's areaID to OBJECT_INVALID
                        // When loading the creatures from the GIT, if the creature's areaID is the same as pArea's it
                        // won't call AddToArea() which leaves all the creatures in limbo.
                        creatureAreaMap.emplace(pGameObject->m_idSelf, pCreature->m_oidArea);
                        pCreature->m_oidArea = Constants::OBJECT_INVALID;

                        creatures.Add(pGameObject->m_idSelf);
                    }
                    else if (Utils::AsNWSItem(pGameObject))
                        items.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSDoor(pGameObject))
                        doors.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSTrigger(pGameObject))
                        triggers.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSEncounter(pGameObject))
                        encounters.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSWaypoint(pGameObject))
                        waypoints.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSSoundObject(pGameObject))
                        sounds.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSPlaceable(pGameObject))
                        placeables.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSStore(pGameObject))
                        stores.Add(pGameObject->m_idSelf);
                    else if (Utils::AsNWSAreaOfEffectObject(pGameObject))
                        aoes.Add(pGameObject->m_idSelf);
                    else
                        continue;
                }
            }

            if (objectFilter != 32767)
            {
                if (!(objectFilter & 1))
                    pArea->SaveCreatures(&resGff, &resStruct, creatures, false);
                if (!(objectFilter & 2))
                    pArea->SaveItems(&resGff, &resStruct, items, false);
                if (!(objectFilter & 4))
                    pArea->SaveTriggers(&resGff, &resStruct, triggers, false);
                if (!(objectFilter & 8))
                    pArea->SaveDoors(&resGff, &resStruct, doors, false);
                if (!(objectFilter & 16))
                    pArea->SaveAreaEffects(&resGff, &resStruct, aoes, false);
                if (!(objectFilter & 32))
                    pArea->SaveWaypoints(&resGff, &resStruct, waypoints, false);
                if (!(objectFilter & 64))
                    pArea->SavePlaceables(&resGff, &resStruct, placeables, false);
                if (!(objectFilter & 128))
                    pArea->SaveStores(&resGff, &resStruct, stores, false);
                if (!(objectFilter & 256))
                    pArea->SaveEncounters(&resGff, &resStruct, encounters, false);

                // No NWScript OBJECT_TYPE_* constant for Sound Objects
                pArea->SaveSounds(&resGff, &resStruct, sounds, false);
            }

            pArea->SaveProperties(&resGff, &resStruct);

            if (exportVarTable)
                pArea->m_ScriptVars.SaveVarTable(&resGff, &resStruct);
            if (exportUUID)
                pArea->m_pUUID.SaveToGff(&resGff, &resStruct);

            retVal = resGff.WriteGFFFile(alias + ":" + fileName, Constants::ResRefType::GIT);

            // Restore the areaIDs of all creatures
            for (auto pair : creatureAreaMap)
            {
                if (auto *pCreature = Utils::AsNWSCreature(Utils::GetGameObject(pair.first)))
                    pCreature->m_oidArea = pair.second;
            }
        }
    }

    return retVal;
}

NWNX_EXPORT ArgumentStack GetTileInfo(ArgumentStack&& args)
{
    int32_t id = -1, height = -1, orientation = -1, x = -1, y = -1;

    if (auto *pArea = Utils::PopArea(args))
    {
        const auto tileX = args.extract<float>();
          ASSERT_OR_THROW(tileX >= 0.0f);
        const auto tileY = args.extract<float>();
          ASSERT_OR_THROW(tileY >= 0.0f);

        if (auto *pTile = pArea->GetTile({tileX, tileY, 0.0f}))
        {
            id = pTile->m_nID;
            height = pTile->m_nHeight;
            orientation = pTile->m_nOrientation;
            x = pTile->m_nGridX;
            y = pTile->m_nGridY;
        }
    }

    return {id, height, orientation, x, y};
}

NWNX_EXPORT ArgumentStack ExportARE(ArgumentStack&& args)
{
    int32_t retVal = false;

    if (auto *pArea = Utils::PopArea(args))
    {
        const auto fileName = args.extract<std::string>();
          ASSERT_OR_THROW(!fileName.empty());
          ASSERT_OR_THROW(fileName.size() <= 16);
        const auto newName = args.extract<std::string>();
        const auto newTag = args.extract<std::string>();
        auto alias = args.extract<std::string>();
          ASSERT_OR_THROW(!alias.empty());

        if (!Utils::IsValidCustomResourceDirectoryAlias(alias))
        {
            LOG_WARNING("NWNX_Area_ExportARE() called with an invalid alias: %s, defaulting to 'NWNX'", alias);
            alias = "NWNX";
        }

        CResGFF    resGff;
        CResStruct resStruct{};

        if (resGff.CreateGFFFile(&resStruct, "ARE ", "V3.2"))
        {
            char field[32];

            // Important Stuff
            std::sprintf(field, "Name");
            resGff.WriteFieldCExoLocString(&resStruct, newName.empty() ? pArea->m_lsName : Utils::CreateLocString(newName), field);
            std::sprintf(field, "Tag");
            resGff.WriteFieldCExoString(&resStruct, newTag.empty() ? pArea->m_sTag : CExoString(newTag).AsTAG(), field);
            std::sprintf(field, "ResRef");
            resGff.WriteFieldCExoString(&resStruct, CResRef(fileName), field);
            std::sprintf(field, "Width");
            resGff.WriteFieldINT(&resStruct, pArea->m_nWidth, field);
            std::sprintf(field, "Height");
            resGff.WriteFieldINT(&resStruct, pArea->m_nHeight, field);
            std::sprintf(field, "Tileset");
            resGff.WriteFieldCResRef(&resStruct, pArea->m_refTileSet, field);

            // Less Important Stuff
            std::sprintf(field, "ChanceLightning");
            resGff.WriteFieldINT(&resStruct, pArea->m_nChanceOfLightning, field);
            std::sprintf(field, "ChanceRain");
            resGff.WriteFieldINT(&resStruct, pArea->m_nChanceOfRain, field);
            std::sprintf(field, "ChanceSnow");
            resGff.WriteFieldINT(&resStruct, pArea->m_nChanceOfSnow, field);
            std::sprintf(field, "DayNightCycle");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_bUseDayNightCycle, field);
            std::sprintf(field, "Flags");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nFlags, field);
            std::sprintf(field, "FogClipDist");
            resGff.WriteFieldFLOAT(&resStruct, pArea->m_fFogClipDistance, field);
            std::sprintf(field, "IsNight");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_bIsNight, field);
            std::sprintf(field, "LightingScheme");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nLightingScheme, field);
            std::sprintf(field, "LoadScreenID");
            resGff.WriteFieldWORD(&resStruct, pArea->m_nLoadScreenID, field);
            std::sprintf(field, "ModListenCheck");
            resGff.WriteFieldINT(&resStruct, pArea->m_nAreaListenModifier, field);
            std::sprintf(field, "ModSpotCheck");
            resGff.WriteFieldINT(&resStruct, pArea->m_nAreaSpotModifier, field);
            std::sprintf(field, "MoonAmbientColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nMoonAmbientColor, field);
            std::sprintf(field, "MoonDiffuseColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nMoonDiffuseColor, field);
            std::sprintf(field, "MoonFogAmount");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nMoonFogAmount, field);
            std::sprintf(field, "MoonFogColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nMoonFogColor, field);
            std::sprintf(field, "MoonShadows");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_bMoonShadows, field);
            std::sprintf(field, "NoRest");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_bNoRestingAllowed, field);
            std::sprintf(field, "OnHeartbeat");
            resGff.WriteFieldCResRef(&resStruct, pArea->m_sScripts[0], field);
            std::sprintf(field, "OnUserDefined");
            resGff.WriteFieldCResRef(&resStruct, pArea->m_sScripts[1], field);
            std::sprintf(field, "OnEnter");
            resGff.WriteFieldCResRef(&resStruct, pArea->m_sScripts[2], field);
            std::sprintf(field, "OnExit");
            resGff.WriteFieldCResRef(&resStruct, pArea->m_sScripts[3], field);
            std::sprintf(field, "PlayerVsPlayer");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nPVPSetting, field);
            std::sprintf(field, "ShadowOpacity");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nShadowOpacity, field);
            std::sprintf(field, "SkyBox");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nSkyBox, field);
            std::sprintf(field, "SunAmbientColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nSunAmbientColor, field);
            std::sprintf(field, "SunDiffuseColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nSunDiffuseColor, field);
            std::sprintf(field, "SunFogAmount");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_nSunFogAmount, field);
            std::sprintf(field, "SunFogColor");
            resGff.WriteFieldDWORD(&resStruct, pArea->m_nSunFogColor, field);
            std::sprintf(field, "SunShadows");
            resGff.WriteFieldBYTE(&resStruct, pArea->m_bSunShadows, field);
            std::sprintf(field, "WindPower");
            resGff.WriteFieldINT(&resStruct, pArea->m_nWindAmount, field);

            // Tile Stuff
            CResList resList{};
            std::sprintf(field, "Tile_List");
            resGff.AddList(&resList, &resStruct, field);
            auto numTiles = pArea->m_nWidth * pArea->m_nHeight;

            for (int tileNum = 0; tileNum < numTiles; tileNum++)
            {
                auto *pTile = &pArea->m_pTile[tileNum];

                resGff.AddListElement(&resStruct, &resList, 1);

                std::sprintf(field, "Tile_ID");
                resGff.WriteFieldINT(&resStruct, pTile->m_nID, field);
                std::sprintf(field, "Tile_Orientation");
                resGff.WriteFieldINT(&resStruct, pTile->m_nOrientation, field);
                std::sprintf(field, "Tile_Height");
                resGff.WriteFieldINT(&resStruct, pTile->m_nHeight, field);

                std::sprintf(field, "Tile_MainLight1");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nMainLight1Color == 255 ? 0 : pTile->m_nMainLight1Color, field);
                std::sprintf(field, "Tile_MainLight2");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nMainLight2Color == 255 ? 0 : pTile->m_nMainLight2Color, field);

                std::sprintf(field, "Tile_SrcLight1");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nSourceLight1Color == 255 ? 0 : pTile->m_nSourceLight1Color, field);
                std::sprintf(field, "Tile_SrcLight2");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nSourceLight2Color == 255 ? 0 : pTile->m_nSourceLight2Color, field);

                std::sprintf(field, "Tile_AnimLoop1");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nAnimLoop1, field);
                std::sprintf(field, "Tile_AnimLoop2");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nAnimLoop2, field);
                std::sprintf(field, "Tile_AnimLoop3");
                resGff.WriteFieldBYTE(&resStruct, pTile->m_nAnimLoop3, field);
            }

            retVal = resGff.WriteGFFFile(alias + ":" + fileName, Constants::ResRefType::ARE);
        }
    }

    return retVal;
}

NWNX_EXPORT ArgumentStack GetAmbientSoundDay(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        if (pArea->m_pAmbientSound != nullptr)
            return pArea->m_pAmbientSound->m_nSoundDayTrack;
    }

    return 0;
}

NWNX_EXPORT ArgumentStack GetAmbientSoundNight(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        if (pArea->m_pAmbientSound != nullptr)
            return pArea->m_pAmbientSound->m_nSoundNightTrack;
    }

    return 0;
}

NWNX_EXPORT ArgumentStack GetAmbientSoundDayVolume(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        if (pArea->m_pAmbientSound != nullptr)
            return pArea->m_pAmbientSound->m_nDayVolume;
    }

    return 0;
}

NWNX_EXPORT ArgumentStack GetAmbientSoundNightVolume(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        if (pArea->m_pAmbientSound != nullptr)
            return pArea->m_pAmbientSound->m_nNightVolume;
    }

    return 0;
}

NWNX_EXPORT ArgumentStack CreateSoundObject(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        Vector v;
        v.x = args.extract<float>();
        v.y = args.extract<float>();
        v.z = args.extract<float>();

        const std::string sResRef = args.extract<std::string>();
        if(!sResRef.empty())
        {
            CResGFF resGFF(Constants::ResRefType::UTS, (char*)"UTS ", sResRef.c_str());
            if(resGFF.m_bResourceLoaded)
            {
                CResStruct resStruct{};
                resGFF.GetTopLevelStruct(&resStruct);
                CNWSSoundObject *pSound = new CNWSSoundObject();
                if(pSound->Load(&resGFF, &resStruct))
                {
                    pSound->AddToArea(pArea);
                    pSound->ChangePosition(v);
                    return pSound->m_idSelf;
                }
                else
                {
                    delete pSound;
                }
            }
        }
    }

    return Constants::OBJECT_INVALID;
}

NWNX_EXPORT ArgumentStack RotateArea(ArgumentStack&& args)
{
    if (auto *pArea = Utils::PopArea(args))
    {
        auto Rotation = args.extract<int>();
          ASSERT_OR_THROW(Rotation >= 1);
          ASSERT_OR_THROW(Rotation <= 3);

        //Rotate Area Tiles
        int32_t InitHeight = pArea->m_nHeight;
        int32_t InitWidth = pArea->m_nWidth;
        int32_t NumTiles = InitWidth * InitHeight;

        if(Rotation == 1 || Rotation == 3)//turn on side
        {
            pArea->m_nHeight = InitWidth;
            pArea->m_nWidth = InitHeight;
        }

        auto *pOriginalTiles = pArea->m_pTile;
        auto *pNewTiles = new CNWSTile[NumTiles];

        for (int TileIndex = 0; TileIndex < NumTiles; TileIndex++)
        {
            int OrigTileIndex = 0;
            switch(Rotation) //Math to map new Tile Index to the original Tile Index, based on rotation
            {
                case 1: OrigTileIndex = (InitWidth - 1) + (InitWidth * (TileIndex % InitHeight)) - (TileIndex / InitHeight); break;
                case 2: OrigTileIndex = InitHeight * InitWidth - TileIndex - 1; break;
                case 3: OrigTileIndex = (InitWidth * (InitHeight - 1 - (TileIndex % InitHeight))) + (TileIndex / InitHeight); break;
            }

            auto *pOriginalTile = &pOriginalTiles[OrigTileIndex];
            auto *pNewTile = &pNewTiles[TileIndex];

            pNewTile->SetID(pOriginalTile->m_nID);
            pNewTile->SetTileData(pArea->m_pTileSet->GetTileData(pOriginalTile->m_nID));
            pNewTile->SetPosition(TileIndex % pArea->m_nWidth,
                                  TileIndex / pArea->m_nWidth,
                                  pOriginalTile->m_nHeight,
                                  pArea->m_pTileSet->GetHeightTransition());
            pNewTile->SetOrientation((pOriginalTile->m_nOrientation + 4 - Rotation) % 4);
            pNewTile->SetMainLightColor(pOriginalTile->m_nMainLight1Color, pOriginalTile->m_nMainLight2Color);
            pNewTile->SetSourceLightColor(pOriginalTile->m_nSourceLight1Color, pOriginalTile->m_nSourceLight2Color);
            pNewTile->SetReplaceTexture(pOriginalTile->m_nReplaceTexture);
            pNewTile->SetAnimLoop(pOriginalTile->m_nAnimLoop1, pOriginalTile->m_nAnimLoop2, pOriginalTile->m_nAnimLoop3);
            pNewTile->m_bMainLightColorChange = pOriginalTile->m_bMainLightColorChange;
            pNewTile->m_bSourceLightColorChange = pOriginalTile->m_bSourceLightColorChange;
            pNewTile->m_bFlaggedAsProblem = pOriginalTile->m_bFlaggedAsProblem;
            pNewTile->m_nTriggerSize = pOriginalTile->m_nTriggerSize;
            pNewTile->m_nTriggers = pOriginalTile->m_nTriggers;
            pNewTile->m_poidTriggers = new ObjectID[pOriginalTile->m_nTriggerSize];
            for(int count = 0; count < pOriginalTile->m_nTriggers; count++)
            {
                pNewTile->m_poidTriggers[count] = pOriginalTile->m_poidTriggers[count];
            }
            pNewTile->m_aDoors = pOriginalTile->m_aDoors;
        }

        delete[] pArea->m_pTile;
        pArea->m_pTile = pNewTiles;

        auto GetNewPosition = [&](Vector vPosition) -> Vector
        {
            switch(Rotation)
            {
                case 1:
                {
                    auto tempPos = vPosition.y;
                    vPosition.y = (InitWidth * 10.0) - vPosition.x;
                    vPosition.x = tempPos;
                    break;
                }
                case 2:
                {
                    vPosition.x = (InitWidth * 10.0) - vPosition.x;
                    vPosition.y = (InitHeight * 10.0) - vPosition.y;
                    break;
                }
                case 3:
                {
                    auto tempPos = vPosition.x;
                    vPosition.x = (InitHeight * 10.0) - vPosition.y;
                    vPosition.y = tempPos;
                    break;
                }
            }
            return vPosition;
        };

        auto GetNewOrientation = [&](Vector vOrientation) -> Vector
        {
            switch(Rotation)
            {
                case 1:
                {
                    vOrientation.x = (std::cos(std::acos(vOrientation.x) - (M_PI/2)));//less half-radian
                    vOrientation.y = (std::sin(std::asin(vOrientation.y) - (M_PI/2)));
                    break;
                }
                case 2:
                {
                    vOrientation.x = (std::cos(std::acos(vOrientation.x) + M_PI));//add 1 radian
                    vOrientation.y = (std::sin(std::asin(vOrientation.y) + M_PI));
                    break;
                }
                case 3:
                {
                    vOrientation.x = (std::cos(std::acos(vOrientation.x) + (M_PI/2)));//Add half-radian
                    vOrientation.y = (std::sin(std::asin(vOrientation.y) + (M_PI/2)));
                    break;
                }
            }
            return vOrientation;
        };

        // We need to make a temp list because SetPosition() will move things around
        std::vector<ObjectID> objectIds;
        for (int32_t i = 0; i < pArea->m_aGameObjects.num; i++)
        {
            objectIds.emplace_back(pArea->m_aGameObjects[i]);
        }

        for (auto oid : objectIds)
        {
            if (auto *pGameObject = Utils::GetGameObject(oid))
            {
                if (auto *pCreature = Utils::AsNWSCreature(pGameObject))
                {
                    if (pCreature->m_pStats->m_bIsPC ||
                        pCreature->m_pStats->GetIsDM() ||
                        (pCreature->m_nAssociateType > Constants::AssociateType::None &&
                         pCreature->m_nAssociateType < Constants::AssociateType::DominatedByPC))
                        continue;

                    pCreature->SetPosition(GetNewPosition(pCreature->m_vPosition));
                    pCreature->SetOrientation(GetNewOrientation(pCreature->m_vOrientation));
                }
                else if (auto *pTrigger = Utils::AsNWSTrigger(pGameObject))
                {
                    for(int vertice = 0; vertice < pTrigger->m_nVertices; vertice++)
                    {
                        pTrigger->m_pvVertices[vertice] = GetNewPosition(pTrigger->m_pvVertices[vertice]);
                    }
                    pTrigger->SetPosition(GetNewPosition(pTrigger->m_vPosition));
                    pTrigger->SetOrientation(GetNewOrientation(pTrigger->m_vOrientation));
                }
                else if (auto *pEncounter = Utils::AsNWSEncounter(pGameObject))
                {
                    for(int vertice = 0; vertice < pEncounter->m_nNumActivateVertices; vertice++)
                    {
                        pEncounter->m_pvActivateVertices[vertice] = GetNewPosition(pEncounter->m_pvActivateVertices[vertice]);
                    }

                    for (int spawnpoint = 0; spawnpoint < pEncounter->m_nNumSpawnPoints; spawnpoint++)
                    {
                        pEncounter->m_pSpawnPointList[spawnpoint].m_vPosition = GetNewPosition(pEncounter->m_pSpawnPointList[spawnpoint].m_vPosition);
                        pEncounter->m_pSpawnPointList[spawnpoint].m_fOrientation = pEncounter->m_pSpawnPointList[spawnpoint].m_fOrientation + ((float)Rotation * 90.0f);
                    }
                    for (int vertice = 0; vertice < pEncounter->m_nNumActivateVertices; vertice++)
                    {
                        if (vertice == 0)
                        {
                            pEncounter->m_fMinActivateX = pEncounter->m_pvActivateVertices[vertice].x;
                            pEncounter->m_fMaxActivateX = pEncounter->m_pvActivateVertices[vertice].x;
                            pEncounter->m_fMinActivateY = pEncounter->m_pvActivateVertices[vertice].y;
                            pEncounter->m_fMaxActivateY = pEncounter->m_pvActivateVertices[vertice].y;
                        }
                        else
                        {
                            if (pEncounter->m_pvActivateVertices[vertice].x < pEncounter->m_fMinActivateX)
                                pEncounter->m_fMinActivateX = pEncounter->m_pvActivateVertices[vertice].x;
                            if (pEncounter->m_pvActivateVertices[vertice].x > pEncounter->m_fMaxActivateX)
                                pEncounter->m_fMaxActivateX = pEncounter->m_pvActivateVertices[vertice].x;
                            if (pEncounter->m_pvActivateVertices[vertice].y < pEncounter->m_fMinActivateY)
                                pEncounter->m_fMinActivateY = pEncounter->m_pvActivateVertices[vertice].y;
                            if (pEncounter->m_pvActivateVertices[vertice].y > pEncounter->m_fMaxActivateY)
                                pEncounter->m_fMaxActivateY = pEncounter->m_pvActivateVertices[vertice].y;
                        }
                    }
                    pEncounter->SetPosition(GetNewPosition(pEncounter->m_vPosition));
                    pEncounter->SetOrientation(GetNewOrientation(pEncounter->m_vOrientation));
                }
                else if (auto *pItem = Utils::AsNWSItem(pGameObject))
                {
                    pItem->SetPosition(GetNewPosition(pItem->m_vPosition));
                    pItem->SetOrientation(GetNewOrientation(pItem->m_vOrientation));
                }
                else if (auto *pDoor = Utils::AsNWSDoor(pGameObject))
                {
                    pDoor->SetPosition(GetNewPosition(pDoor->m_vPosition));
                    pDoor->SetOrientation(GetNewOrientation(pDoor->m_vOrientation));
                }
                else if (auto *pWaypoint = Utils::AsNWSWaypoint(pGameObject))
                {
                    pWaypoint->SetPosition(GetNewPosition(pWaypoint->m_vPosition));
                    pWaypoint->SetOrientation(GetNewOrientation(pWaypoint->m_vOrientation));
                }
                else if (auto *pSound = Utils::AsNWSSoundObject(pGameObject))
                {
                    pSound->SetPosition(GetNewPosition(pSound->m_vPosition));
                    pSound->SetOrientation(GetNewOrientation(pSound->m_vOrientation));
                }
                else if (auto *pPlaceable = Utils::AsNWSPlaceable(pGameObject))
                {
                    pPlaceable->SetPosition(GetNewPosition(pPlaceable->m_vPosition));
                    pPlaceable->SetOrientation(GetNewOrientation(pPlaceable->m_vOrientation));
                }
                else if (auto *pStore = Utils::AsNWSStore(pGameObject))
                {
                    pStore->SetPosition(GetNewPosition(pStore->m_vPosition));
                    pStore->SetOrientation(GetNewOrientation(pStore->m_vOrientation));
                }
                else if (auto *pAOE = Utils::AsNWSAreaOfEffectObject(pGameObject))
                {
                    pAOE->SetPosition(GetNewPosition(pAOE->m_vPosition));
                    pAOE->SetOrientation(GetNewOrientation(pAOE->m_vOrientation));
                }
            }
        }
    }
    return {};
}

NWNX_EXPORT ArgumentStack GetTileInfoByTileIndex(ArgumentStack&& args)
{
    int32_t id = -1, height = -1, orientation = -1, x = -1, y = -1;

    if (auto *pArea = Utils::PopArea(args))
    {
        const auto index = args.extract<int32_t>();
          ASSERT_OR_THROW(index >= 0);
        if (index < (pArea->m_nWidth * pArea->m_nHeight))
        {
            auto *pTile = &pArea->m_pTile[index];
            id = pTile->m_nID;
            height = pTile->m_nHeight;
            orientation = pTile->m_nOrientation;
            x = pTile->m_nGridX;
            y = pTile->m_nGridY;
        }
    }

    return {id, height, orientation, x, y};
}
