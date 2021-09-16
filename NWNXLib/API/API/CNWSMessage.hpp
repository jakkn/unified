#pragma once
#include "nwn_api.hpp"

#include "CExoArrayList.hpp"
#include "CExoLocString.hpp"
#include "CExoString.hpp"
#include "CNWMessage.hpp"
#include "CResRef.hpp"
#include "ObjectVisualTransformData.hpp"
#include "Vector.hpp"
#include <vector>


#ifdef NWN_API_PROLOGUE
NWN_API_PROLOGUE(CNWSMessage)
#endif

struct CEffectIconObject;
struct CGameObject;
struct CGameObjectArray;
struct CItemRepository;
struct CLastUpdateObject;
struct CLastUpdatePartyObject;
struct CLoopingVisualEffect;
struct CNWCCMessageData;
struct CNWSArea;
struct CNWSAreaOfEffectObject;
struct CNWSCombatAttackData;
struct CNWSCreature;
struct CNWSDoor;
struct CNWSItem;
struct CNWSObject;
struct CNWSPlaceable;
struct CNWSPlayer;
struct CNWSPlayerInventoryGUI;
struct CNWSPlayerLUOInventory;
struct CNWSPlayerLUOSortedObjectList;
struct CNWSPlayerLastUpdateObject;
struct CNWSStore;
struct CNWSTrigger;
namespace Hash {
    struct SHA1;
}


typedef int BOOL;
typedef CExoLinkedListNode * CExoLinkedListPosition;
typedef uint32_t OBJECT_ID;
typedef uint16_t RESTYPE;
typedef uint32_t STRREF;


struct CNWSMessage : CNWMessage
{

    CNWSMessage();
    ~CNWSMessage();
    OBJECT_ID ReadOBJECTIDServer();
    void WriteCExoLocStringServer(const CExoLocString & sLocString, uint8_t nGender = 0);
    void WriteOBJECTIDServer(OBJECT_ID oidObjectId);
    BOOL HandlePlayerToServerLevelUpMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerAreaMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerChatMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerCharListMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL SendPlayerToServerGuiInventory_Status(CNWSPlayer * pPlayer, BOOL bIsActive, OBJECT_ID oidInventory = 0x7f000000);
    BOOL HandlePlayerToServerCheatMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerDialogMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerDungeonMasterMessage(CNWSPlayer * pPlayer, uint8_t nMinor, BOOL bGroup = false);
    BOOL HandlePlayerToServerGameObjectUpdate(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGuiInventoryMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGuiContainerMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerCharacterSheetMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerInputDriveControl(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerInputAbortDriveControl(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerInputWalkToWaypoint(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerGroupInputWalkToWaypoint(CNWSPlayer * pPlayer, CNWSCreature * pCreature, OBJECT_ID oidArea, float fX, float fY, float fZ, uint8_t nClientPathNumber, BOOL nRunToPoint, BOOL nClientMoving, OBJECT_ID oidClickedOn);
    BOOL HandlePlayerToServerInputCancelGuiTimingEvent(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerInputMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGroupInputMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerStoreMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGoldMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerInventoryMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerLoginMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerMessage(uint32_t nPlayerId, uint8_t * pBuffer, uint32_t nBufferSize);
    BOOL HandlePlayerToServerModuleMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerParty(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerServerChatMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerServerStatusMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerQuickChatMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerJournalMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGuiQuickbar(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerGuiQuickbar_SetButton(CNWSPlayer * pPlayer, uint8_t nButton, uint8_t nObjectType);
    BOOL HandlePlayerToServerMapPinMessage(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerMapPinSetMapPinAt(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerMapPinDestroyMapPin(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerMapPinChangePin(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerMapPinEnabled(CNWSPlayer * pPlayer, OBJECT_ID oidMapPin, BOOL bEnalbed);
    BOOL SendServerToPlayerMapPinAdded(CNWSPlayer * pPlayer, Vector vPosition, CExoString szNote, uint32_t nReference);
    BOOL SendServerToPlayerMapPinCreated(CNWSPlayer * pPlayer, OBJECT_ID oidMapPin, Vector vPosition, CExoLocString szNote, BOOL bMapPinEnabled);
    BOOL HandlePlayerToServerBarter(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerBarter_StartBarter(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_CloseBarter(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_AddItem(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_RemoveItem(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_MoveItem(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_LockList(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_AcceptTrade(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerBarter_Window(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerPlayerDeath(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerPVPListOperations(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerPortal(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerCharacterDownload(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerShutDownServer(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL SendServerToPlayerShutDownServer(uint32_t nPlayerId, uint32_t nTimeLeft);
    BOOL SendServerToPlayerCamera_ChangeLocation(CNWSPlayer * pPlayer, int32_t nFlags, float fCameraAngle, float fCameraDistance, float fCameraPitch, int32_t nCameraSmoothTranslation);
    BOOL SendServerToPlayerCamera_SetMode(CNWSPlayer * pPlayer, uint8_t nCameraMode);
    BOOL SendServerToPlayerCamera_Store(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerCamera_Restore(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerCamera_SetHeight(CNWSPlayer * pPlayer, float fHeight);
    BOOL SendServerToPlayerCamera_LockPitch(CNWSPlayer * pPlayer, BOOL bLock);
    BOOL SendServerToPlayerCamera_LockDistance(CNWSPlayer * pPlayer, BOOL bLock);
    BOOL SendServerToPlayerCamera_LockYaw(CNWSPlayer * pPlayer, BOOL bLock);
    BOOL SendServerToPlayerLogin_CharacterQuery(CNWSPlayer * pPlayer, uint8_t & nNumClasses, int32_t * pClasses, uint8_t * pLevels, uint32_t & nXP);
    BOOL SendServerToPlayerLogin_NeedCharacter(uint32_t nPlayerId);
    BOOL SendServerToPlayerLoadBar_StartStallEvent(uint32_t nStallEvent);
    BOOL SendServerToPlayerLoadBar_UpdateStallEvent(uint32_t nWorkCompleted, uint32_t nTotalWork = 0xffffffff);
    BOOL SendServerToPlayerLoadBar_EndStallEvent(uint32_t nStallEvent, uint32_t nError = 0);
    BOOL SendServerToPlayerModule_SaveGameStatus(uint8_t nStatus);
    BOOL SendServerToPlayerModule_EndGame(CNWSPlayer * pPlayer, const CExoString & sMovieName, const Hash::SHA1 & nwsync);
    BOOL SendServerToPlayerModule_Loading(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerSaveLoad_Status(CNWSPlayer * pPlayer, uint8_t nStallEventType, uint32_t nStatus);
    BOOL SendServerToPlayerModule_StartStartNewModule();
    BOOL SendServerToPlayerModule_EndStartNewModule(BOOL bSuccess);
    BOOL SendServerToPlayerModule_DumpPlayer(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerArea_ClientArea(CNWSPlayer * pPlayer, CNWSArea * pArea, float fX, float fY, float fZ, const Vector & vNewOrientation, BOOL bPlayerIsNewToModule);
    BOOL SendServerToPlayerArea_VisualEffect(CNWSPlayer * pPlayer, uint16_t nAnim, Vector vPosition, ObjectVisualTransformData ovtd);
    BOOL SendServerToPlayerUpdateBlackoutEffect(CNWSPlayer * pPlayer, BOOL bEnableBlackout);
    BOOL SendServerToPlayerArea_Weather(CNWSPlayer * pPlayer, uint8_t nWeatherType, BOOL bStart);
    BOOL SendServerToPlayerArea_ChangeDayNight(CNWSPlayer * pPlayer, BOOL bDay, float fTransitionTime);
    BOOL SendServerToPlayerArea_RecomputeStaticLighting(OBJECT_ID oidArea);
    BOOL SendServerToPlayerArea_SetName(CNWSPlayer * player, OBJECT_ID oidArea);
    BOOL SendServerToPlayerArea_Destroyed(CNWSPlayer * player, OBJECT_ID oidArea);
    BOOL SendServerToPlayerUpdateSkyBox(int32_t nSkyBox, OBJECT_ID oidArea);
    BOOL SendServerToPlayerUpdateFogColor(uint32_t nSunFogColor, uint32_t nMoonFogColor, OBJECT_ID oidArea);
    BOOL SendServerToPlayerUpdateFogAmount(uint8_t nSunFogAmount, uint8_t nMoonFogAmount, OBJECT_ID oidArea);
    BOOL SendServerToPlayerArea_UpdateWind(CNWSPlayer * pPlayer, Vector vDirection, float fMagnitude, float fYaw, float fPitch);
    BOOL SendServerToPlayerSetCustomToken(uint32_t nPlayerID, int32_t nCustomTokenNumber, const CExoString & sTokenValue);
    BOOL SendServerToPlayerSetCustomTokenList(uint32_t nPlayerID);
    BOOL SendServerToPlayerSetTlkOverride(uint32_t nPlayerID, int32_t nStrRef, const CExoString & sOverride);
    BOOL SendServerToPlayerSetTlkOverrideList(uint32_t nPlayerID);
    BOOL SendServerToPlayerChatMultiLangMessage(uint8_t nChatMessageType, OBJECT_ID oidSpeaker, CExoLocString sSpeakerMessage, OBJECT_ID oidTokenTarget, uint8_t gender, uint32_t * pPlayerIdNoBubble, uint32_t nPlayerIdNoBubble, BOOL bPrivateChat, const CResRef & sSound, BOOL bPlayHelloSound, OBJECT_ID oidLastSpeaker);
    BOOL SendServerToPlayerChatMultiLang_Helper(uint32_t nPlayerID, uint8_t nChatMessageType, OBJECT_ID oidSpeaker, CExoLocString sSpeakerMessage, OBJECT_ID oidTokenTarget, uint8_t gender, BOOL bNoBubble, const CResRef & sSound, BOOL bPlayHelloSound, OBJECT_ID oidLastSpeaker);
    BOOL SendServerToPlayerChatMessage(uint8_t nChatMessageType, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage, uint32_t nTellPlayerId = 0xffffffff, const CExoString & sTellName = "");
    BOOL SendServerToPlayerChatStrRefMessage(uint8_t nChatMessageType, OBJECT_ID oidSpeaker, uint32_t nStrRef);
    BOOL SendServerToPlayerAIActionPlaySound(uint32_t nPlayerId, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerVoiceChat_Play(CNWSPlayer * pPlayer, OBJECT_ID oidCreature, uint8_t nVoiceSetID);
    BOOL SendServerToPlayerChat_Party(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerSoundObject_Play(CNWSPlayer * pPlayer, OBJECT_ID oidSound);
    BOOL SendServerToPlayerSoundObject_Stop(CNWSPlayer * pPlayer, OBJECT_ID oidSound);
    BOOL SendServerToPlayerSoundObject_ChangeVolume(CNWSPlayer * pPlayer, OBJECT_ID oidSound, int32_t nVolume);
    BOOL SendServerToPlayerSoundObject_ChangePosition(CNWSPlayer * pPlayer, OBJECT_ID oidSound, Vector vPos);
    BOOL SendServerToPlayerGameObjUpdate(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerGameObjUpdate(CNWSPlayer * pPlayer, OBJECT_ID oidObjectToUpdate);
    BOOL SendServerToPlayerGameObjUpdateVisEffect(CNWSPlayer * pPlayer, uint16_t nVisualEffectID, OBJECT_ID oidTarget, OBJECT_ID oidSource = 0x7f000000, uint8_t nSourceNode = 0, uint8_t nTargetNode = 0, Vector vTargetPosition = Vector(), float fDuration = 0.0f, ObjectVisualTransformData ovtd = ObjectVisualTransformData());
    BOOL SendServerToPlayerGameObjUpdateFloatyText(CNWSPlayer * pPlayer, uint32_t nStrRef, OBJECT_ID oidTarget);
    BOOL SendServerToPlayerQuickChatMessage(OBJECT_ID oidSpeaker, uint16_t nSoundSetSoundID);
    BOOL SendServerToPlayerStoreConfirmTransaction(CNWSPlayer * pPlayer, BOOL bTransactionSuccessful, OBJECT_ID oidItem, int32_t nStoreGold);
    BOOL SendServerToPlayerCombatRoundStarted(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerWhirlwindAttack(CNWSPlayer * pPlayer, CNWSCreature * pCreature);
    BOOL SendServerToPlayerWhirlwindAttackDamage(CNWSPlayer * pPlayer, CNWSCreature * pCreature);
    BOOL SendServerToPlayerPlaceableUpdate_Useable(CNWSPlaceable * pPlaceable);
    BOOL SendServerToPlayerGUICharacterSheet_NotPermitted(uint32_t nPlayerId, OBJECT_ID oidCharSheetFailure);
    BOOL SendServerToPlayerDestroyDeathGUI(uint32_t nPlayerId);
    BOOL SendServerToPlayerUpdateActiveItemPropertiesUses(CNWSPlayer * pPlayer, OBJECT_ID oidItem, uint8_t nUseableProperties, uint8_t nUseDiff, uint8_t * pUsesLeftPerProperty);
    BOOL SendServerToPlayerUpdateActiveItemProperties(CNWSPlayer * pPlayer, CNWSItem * pItem);
    BOOL SendServerToPlayerUpdateItemName(CNWSPlayer * pPlayer, CNWSItem * pItem);
    BOOL SendServerToPlayerUpdateItemHidden(CNWSPlayer * pPlayer, CNWSItem * pItem);
    BOOL HandlePlayerToServerPlayModuleCharacterList(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerPlayModuleCharacterList_Start(CNWSPlayer * pPlayer);
    BOOL HandlePlayerToServerPlayModuleCharacterList_Stop(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerPlayModuleCharacterListResponse(uint32_t nPlayerId, OBJECT_ID nCharacterId, BOOL bAdd);
    void ComputeGameObjectUpdateForYourselfToo(CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CGameObjectArray * pGameObjectArray, OBJECT_ID oidObjectToUpdate);
    void ComputeGameObjectUpdateForYourself(CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CGameObjectArray * pGameObjectArray, OBJECT_ID oidObjectToUpdate);
    CNWSPlayerLUOSortedObjectList * SortObjectsForGameObjectUpdate(CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CGameObjectArray * pGameObjectArray, int32_t * nMembersInSortedList);
    void ComputeGameObjectUpdateForObject(CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CGameObjectArray * pGameObjectArray, OBJECT_ID oidObjectToUpdate);
    BOOL ComputeGameObjectUpdateForCategory(uint32_t nCategory, uint32_t nMessageLimit, CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CGameObjectArray * pGameObjectArray, CNWSPlayerLUOSortedObjectList * pSortedList, int32_t nSortedListSize);
    void TestPartyObjectUpdateDifferences(CNWSPlayer * pPlayer, CNWSCreature * pPartyCreature, CLastUpdatePartyObject * * pLastUpdatePartyObject, uint32_t * nObjectUpdatesRequired);
    void StoreValuesInLastUpdatePartyObject(CNWSCreature * pPlayerCreature, CLastUpdatePartyObject * pLastUpdatePartyObject, CNWSCreature * pPartyCreature, uint32_t nObjectUpdatesRequired);
    BOOL WriteGameObjUpdate_PartyAIState(CNWSPlayer * pPlayer);
    BOOL WriteGameObjUpdate_DungeonMasterAIState(CNWSPlayer * pPlayer);
    void WriteGameObjUpdate_WorkRemaining(CNWSObject * pPlayerObject, CNWSArea * pPlayerArea, int32_t nStagesCompleted, int32_t nTotalStages);
    void StoreValuesInLastUpdateObject(CNWSPlayer * pPlayer, CLastUpdateObject * pLastUpdateObject, CNWSObject * pAreaObject, uint32_t nObjectUpdatesRequired, uint32_t nObjectAppearanceUpdatesRequired);
    void TestObjectUpdateDifferences(CNWSPlayer * pPlayer, CNWSObject * pAreaObject, CLastUpdateObject * * pLastUpdateObject, uint32_t * nObjectUpdatesRequired, uint32_t * nObjectAppearanceUpdatesRequired);
    BOOL TestObjectVisible(CNWSObject * pAreaObject, CNWSObject * pPlayerGameObject);
    CLastUpdateObject * CreateNewLastUpdateObject(CNWSPlayer * pPlayer, CNWSObject * pAreaObject, uint32_t * nObjectUpdatesRequired, uint32_t * nObjectAppeareanceUpdatesRequired);
    uint32_t SelectCategoryForGameObject(CGameObject * pAreaGameObject, CNWSObject * pPlayerGameObject);
    void DeleteLastUpdateObjectsInOtherAreas(CNWSPlayer * pPlayer);
    void DeleteLastUpdateObjectsForObject(CNWSPlayer * pPlayer, OBJECT_ID oidTargetToRemove);
    void WriteGameObjUpdate_MajorGUIPanels(CNWSPlayer * pPlayer);
    void WriteGameObjUpdate_MajorGUIPanels_Inventory(CNWSPlayer * pPlayer, CNWSPlayerInventoryGUI * pInventory);
    void WriteGameObjUpdate_MinorGUIPanels(CNWSPlayer * pPlayer);
    void WriteGameObjUpdate_MajorGUIPanels_HenchmanInventoryData(CNWSPlayer * pPlayer);
    void TestPlayerUpdateDifferences(CNWSPlayer * pPlayer, CNWSPlayerLastUpdateObject * pPlayerLastUpdateObject, CLastUpdateObject * pCreatureLastUpdateObject, uint16_t & nUpdatesRequired);
    void WriteGameObjUpdate_PlayerUpdate(CNWSPlayer * pPlayer, CNWSPlayerLastUpdateObject * pPlayerLastUpdateObject, CLastUpdateObject * pCreatureLastUpdateObject, uint16_t nUpdatesRequired);
    void StoreValuesInLastPlayerUpdateObject(CNWSPlayer * pPlayer, CNWSPlayerLastUpdateObject * pPlayerLastUpdateObject, CLastUpdateObject * pCreatureLastUpdateObject, uint16_t nUpdatesRequired);
    void WriteGameObjUpdate_UpdateObject(CNWSPlayer * pPlayer, CNWSObject * pAreaObject, CLastUpdateObject * pLastUpdateObject, uint32_t nObjectUpdatesRequired, uint32_t nObjectAppearanceUpdatesRequired);
    void WriteGameObjUpdate_CharacterSheet(CNWSPlayer * pPlayer, uint32_t nUpdatesRequired);
    BOOL SendServerToPlayerExamineGui_CreatureData(CNWSPlayer * pPlayer, OBJECT_ID oidCreatureID);
    BOOL SendServerToPlayerExamineGui_ItemData(CNWSPlayer * pPlayer, OBJECT_ID oidItemID);
    BOOL SendServerToPlayerExamineGui_PlaceableData(CNWSPlayer * pPlayer, OBJECT_ID oidPlaceableID);
    BOOL SendServerToPlayerExamineGui_DoorData(CNWSPlayer * pPlayer, OBJECT_ID oidDoorID);
    BOOL SendServerToPlayerExamineGui_TrapData(CNWSPlayer * pPlayer, OBJECT_ID oidTrapID, CNWSCreature * pCreature, BOOL bSuccess);
    BOOL SendServerToPlayerGameObjUpdate_ObjControl(uint32_t nPlayerID, OBJECT_ID nObjectId);
    BOOL SendServerToPlayerInventory_Drop(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_DropCancel(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_Equip(uint32_t nPlayerID, OBJECT_ID nObjectID, uint32_t nEquipSlot, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_EquipCancel(uint32_t nPlayerID, OBJECT_ID nObjectID, uint32_t nEquipSlot, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_RepositoryMove(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_RepositoryMoveCancel(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_Pickup(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_PickupCancel(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_SelectPanel(uint32_t nPlayerID, uint8_t nPanel);
    BOOL SendServerToPlayerInventory_Unequip(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_UnequipCancel(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerInventory_ConfirmDrop(uint32_t nPlayerID, OBJECT_ID nObjectID, BOOL bRunActionForNonPlayer = false);
    BOOL SendServerToPlayerLogin_Confirm(uint32_t nPlayerID);
    BOOL SendServerToPlayerLogin_GetWaypoint(uint32_t nPlayerID);
    BOOL SendServerToPlayerLogin_Fail(uint32_t nPlayerId, STRREF strReason);
    BOOL SendServerToPlayerModule_Info(uint32_t nPlayerId);
    BOOL SendServerToPlayerModule_SetPauseState(uint8_t nState, BOOL bPause);
    BOOL SendServerToPlayerModule_ExportReply(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerParty_Invite(uint32_t nPlayerID, OBJECT_ID oidInviterCreatureID);
    BOOL SendServerToPlayerParty_List(uint32_t nPlayerID, int32_t nNumMembers, OBJECT_ID * pMemberIDs, uint8_t nPartyListMessageType, OBJECT_ID oidBanned);
    BOOL SendServerToPlayerParty_TransferObjectControl(uint32_t nPlayerID, uint32_t nControllingPlayer, OBJECT_ID oidCreature);
    BOOL SendServerToPlayerPlayerList_Add(uint32_t nPlayerId, CNWSPlayer * pNewPlayer);
    BOOL SendServerToPlayerPlayerList_All(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerPlayerList_Delete(uint32_t nPlayerId, CNWSPlayer * pNewPlayer);
    BOOL SendServerToPlayerPlayerList_ReauthorizeCDKey(uint32_t nPlayerId, const CExoString & sChallenge, const CExoString & sKey);
    BOOL SendServerToPlayerServerStatus_Status(uint32_t nPlayerId);
    BOOL SendServerToPlayerCCMessage(uint32_t nPlayerId, uint8_t nMinor, CNWCCMessageData * pMessageData, CNWSCombatAttackData * pAttackData);
    BOOL SendServerToPlayerStringMessage(OBJECT_ID oidPlayer, uint8_t nMinor, CExoString sFeedbackMessage);
    BOOL SendServerToPlayerDialogEntry(uint32_t nPlayerID, OBJECT_ID oidOwner, OBJECT_ID oidSpeaker, CExoLocString sEntry, OBJECT_ID oidTokenTarget, uint8_t gender);
    BOOL SendServerToPlayerDialogReplies(uint32_t nPlayerID, CExoLocString * pRepliesStr, uint32_t * pRepliesIndex, uint32_t nReplies, uint32_t nInactiveReplies, OBJECT_ID oidTokenTarget, uint8_t gender, BOOL bEndOfDialog, uint32_t currentEntryIndex, BOOL bDisableCameraZoom);
    BOOL SendServerToPlayerDialogReplyChosen(uint32_t nPlayerID, uint32_t nReplyIndex, uint32_t currentEntryIndex, CExoLocString sReply, OBJECT_ID oidTokenTarget, uint8_t gender, BOOL bEndOfDialog);
    BOOL SendServerToPlayerDialogClose(uint32_t nPlayerID);
    BOOL SendServerToPlayerDungeonMasterLoginState(CNWSPlayer * pPlayer, BOOL bIsDM, BOOL bIsDMManifested);
    BOOL SendServerToPlayerDungeonMasterCreatorLists(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerDungeonMasterAreaList(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerDungeonMasterAreaList(uint32_t nPlayerID);
    BOOL SendServerToPlayerDungeonMasterSearchByIdResult(CNWSPlayer * pPlayer, OBJECT_ID oidArea, int32_t objectType, OBJECT_ID oidTarget);
    BOOL SendServerToPlayerDungeonMasterSearchByTagResult(CNWSPlayer * pPlayer, const CExoString & sTag, int32_t objectType, OBJECT_ID oidTarget);
    BOOL SendServerToPlayerDungeonMasterObjectList(CNWSPlayer * pPlayer, OBJECT_ID oidArea, int32_t objectType);
    BOOL SendServerToPlayerDungeonMasterUpdatePartyList(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerDungeonMasterUpdatePartyList(uint32_t nPlayerID);
    BOOL SendServerToPlayerDungeonMastersDifficultyChange(int32_t nDifficulty);
    BOOL SendServerToPlayerQuickChat(uint32_t nPlayerID, OBJECT_ID oidSpeaker, uint16_t nSoundSetSoundID);
    BOOL SendServerToPlayerCheatNasty(uint32_t nPlayerID, OBJECT_ID oidCreature);
    BOOL SendServerToPlayerCheatPonyRide(uint32_t nPlayerID, OBJECT_ID oidCreature);
    BOOL SendServerToPlayerCheatRainOfCows(uint32_t nPlayerID, OBJECT_ID oidCreature);
    BOOL SendServerToPlayerCheatDebugMode(BOOL bDebugMode);
    BOOL SendServerToPlayerGuiContainerObject_Status(CNWSPlayer * pPlayer, OBJECT_ID oidContainer, BOOL bOwnInventory = true);
    BOOL SendServerToPlayerInventory_SelectPage(uint32_t nPlayerID, uint8_t nPage);
    BOOL SendServerToAllPlayersCreatureUpdate_StripEquippedItems(OBJECT_ID oidCreature, BOOL bLeftHandItemIsDroppable, BOOL bRightHandItemIsDroppable);
    BOOL SendServerPlayerItemUpdate_DestroyItem(CNWSPlayer * pPlayer, OBJECT_ID oidItem);
    BOOL SendServerToPlayerModuleUpdate_Time(CNWSPlayer * pPlayer, uint8_t nFlags, uint32_t nYear, uint32_t nMonth, uint32_t nDay, uint32_t nHour, uint8_t nTimeOfDayState, uint32_t nTimeIntoTransition);
    BOOL SendServerToPlayerSafeProjectile(CNWSPlayer * pPlayer, OBJECT_ID oidOriginator, OBJECT_ID oidTarget, Vector vOriginator, Vector vTarget, uint32_t nDeltaTime, uint8_t nProjectileType, uint32_t nSpellID, uint8_t nBaseItemID, uint8_t nAttackResult, uint8_t nProjectilePathType);
    BOOL SendServerToPlayerOpenStoreInventory(CNWSPlayer * pPlayer, OBJECT_ID oidStore, uint8_t nPanel);
    BOOL SendServerToPlayerCloseStoreInventory(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerPopUpGUIPanel(OBJECT_ID oidObject, int32_t nGuiPanel, int32_t bGUIOption1, int32_t bGUIOption2, int32_t nStringReference, CExoString sStringReference);
    BOOL SendServerToPlayerJournalAddWorld(CNWSPlayer * pPlayer, int32_t nIndex, CExoString szEntry, CExoString szTitle, uint32_t nCalendarDay, uint32_t nTimeOfDay);
    BOOL SendServerToPlayerJournalAddWorldStrref(CNWSPlayer * pPlayer, uint32_t nStrrefEntry, uint32_t nStrrefTitle, uint32_t nCalendarDay, uint32_t nTimeOfDay);
    BOOL SendServerToPlayerJournalDeleteWorld(CNWSPlayer * pPlayer, int32_t nIndex);
    BOOL SendServerToPlayerJournalDeleteWorldStrref(CNWSPlayer * pPlayer, uint32_t nStrrefEntry);
    BOOL SendServerToPlayerJournalDeleteWorldAll(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerJournalAddQuest(CNWSPlayer * pPlayer, CExoString szPlotID, int32_t nState, uint32_t nPriority, uint16_t nPictureIndex, int32_t bCompleteQuest, uint32_t nCalendarDay, uint32_t nTimeOfDay, CExoLocString szName, CExoLocString szText);
    BOOL SendServerToPlayerJournalRemoveQuest(CNWSPlayer * pPlayer, CExoString szPlotID);
    BOOL SendServerToPlayerJournalSetQuestPicture(CNWSPlayer * pPlayer, CExoString szPlotID, int32_t nIndex);
    BOOL SendServerToPlayerJournalFullUpdate(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerJournalFullUpdateNotNeeded(CNWSPlayer * pPlayer, BOOL bClearOldEntries = false);
    BOOL SendServerToPlayerJournalUpdated(CNWSPlayer * pPlayer, BOOL bQuest, BOOL bCompleted, CExoLocString locName);
    BOOL SendServerToPlayerGuiQuickbar_SetButton(CNWSPlayer * pPlayer, uint8_t nButton, BOOL bSetAllButtons = false);
    BOOL SendServerToPlayerBarterStartBarter(OBJECT_ID nInitiatorId, OBJECT_ID nRecipientId, OBJECT_ID nInitiatorCreature, OBJECT_ID nRecipientCreature);
    BOOL SendServerToPlayerBarterCloseBarter(uint32_t nInitiatorId, uint32_t nRecipientId, BOOL bAccepted);
    BOOL SendServerToPlayerBarterLockList(uint32_t nInitiatorId, uint32_t nRecipientId, BOOL bInitiator, BOOL bLocked);
    BOOL SendServerToPlayerBarterAcceptTrade(uint32_t nInitiatorId, uint32_t nRecipientId, BOOL bInitiator, BOOL bAccept);
    BOOL SendServerToPlayerBarterReject(uint32_t nSenderId, uint8_t nMessage, uint8_t nFlags, OBJECT_ID oidItem = 0x7f000000);
    BOOL SendServerToPlayerAmbientMusicPlay(OBJECT_ID nPlayer, BOOL bPlay);
    BOOL SendServerToPlayerAmbientMusicSetDelay(OBJECT_ID nPlayer, int32_t nDelay);
    BOOL SendServerToPlayerAmbientMusicChangeTrack(OBJECT_ID nPlayer, BOOL bDay, int32_t nTrack);
    BOOL SendServerToPlayerAmbientBattleMusicPlay(OBJECT_ID nPlayer, BOOL bPlay);
    BOOL SendServerToPlayerAmbientBattleMusicChange(OBJECT_ID nPlayer, int32_t nTrack);
    BOOL SendServerToPlayerAmbientSoundLoopPlay(OBJECT_ID nPlayer, BOOL bPlay);
    BOOL SendServerToPlayerAmbientSoundLoopChange(OBJECT_ID nPlayer, BOOL bDay, int32_t nTrack);
    BOOL SendServerToPlayerAmbientSoundVolumeChange(OBJECT_ID nPlayer, BOOL bDay, int32_t nVolume);
    BOOL SendServerToPlayerResmanOverride(uint32_t nPlayerId, RESTYPE restype, const CResRef & sOldName, const CResRef & sNewName);
    BOOL HandleServerAdminToServerMessage(uint32_t nPlayerId, uint8_t * pMessage, uint32_t nSize);
    BOOL SendServerToServerAdminMessage(uint32_t nPlayerId, CExoString sCommand);
    void SendServerToServerAdminModuleList(uint32_t nPlayerId);
    void SendServerToServerAdminSaveGameList(uint32_t nPlayerId);
    void SendServerToServerAdminPlayerList(uint32_t nPlayerID);
    void SendServerToServerAdminBannedList(uint32_t nPlayerID);
    void SendServerToServerAdminPortalList(uint32_t nPlayerID);
    void SendServerToServerAdminServerStatus(uint32_t nPlayerId);
    void SendServerToServerAdminServerSettings(uint32_t nPlayerId);
    void SendServerToServerAdminSaveStatus(uint32_t nPlayerId, uint8_t nStatus);
    BOOL ParseGetBool(uint8_t * pMsgPortion, uint32_t msgPortionSize, BOOL & pBool);
    BOOL ParseGetString(uint8_t * pMsgPortion, uint32_t msgPortionSize, CExoString & pString, uint32_t nMaxStrLength);
    BOOL ParseToken(const char * token, uint8_t * * pMsgPortion, uint32_t & msgPortionSize, BOOL bDelimeterFollowing);
    BOOL SendServerToPlayerDebugInfo_Creature(CNWSPlayer * pPlayer, OBJECT_ID oidCreature);
    BOOL SendServerToPlayerDebugInfo_Item(CNWSPlayer * pPlayer, OBJECT_ID oidItem);
    BOOL SendServerToPlayerDebugInfo_Placeable(CNWSPlayer * pPlayer, OBJECT_ID oidPlaceable);
    BOOL SendServerToPlayerDebugInfo_Area(CNWSPlayer * pPlayer, OBJECT_ID oidArea);
    BOOL SendServerToPlayerDebugInfo_Door(CNWSPlayer * pPlayer, OBJECT_ID oidDoor);
    BOOL SendServerToPlayerDebugInfo_Trigger(CNWSPlayer * pPlayer, OBJECT_ID oidTrigger);
    BOOL SendServerToPlayerDebugInfo_String(CNWSPlayer * pPlayer, const CExoString & sString);
    BOOL SendServerToPlayerLevelUp_Confirmation(uint32_t nPlayerId, BOOL bValidated);
    BOOL SendServerToPlayerLevelUp_Begin(uint32_t nPlayerId, CNWSCreature * pCreature);
    BOOL SendServerToPlayerActivatePortal(uint32_t nPlayerId, CExoString sIPAddress, CExoString sPassword, CExoString sWaypointTag, BOOL bSeemless);
    BOOL SendServerToPlayerCharacterDownloadReply(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerCharacterDownloadFail(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerPartyBar_PanelButtonFlash(uint32_t nPlayerId, uint8_t nButton, BOOL bEnableFlash);
    BOOL SendServerToPlayerCharList(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerUpdateCharResponse(CNWSPlayer * pPlayer, uint8_t nCharType, CResRef cResRef);
    BOOL SendServerToPlayerGuiTimingEvent(CNWSPlayer * pPlayer, BOOL bStarting, uint8_t nGuiTimingEventID, uint32_t nDuration = 0);
    void UpdateLastUpdate_GuiEffectIcons(CNWSCreature * pCreature, CExoArrayList<CEffectIconObject *> * pLastUpdateEffectArray, BOOL bSendNonPlayerBarIcons = false);
    BOOL ComputeLastUpdate_GuiEffectIcons(CNWSCreature * pCreature, CExoArrayList<CEffectIconObject *> * pLastUpdateEffectArray, BOOL bSendNonPlayerBarIcons = false);
    void WriteGuiEffectIconsUpdate(CNWSCreature * pCreature, CExoArrayList<CEffectIconObject *> * pLastUpdateEffectArray, BOOL bSendNonPlayerBarIcons = false);
    BOOL SendServerToPlayerPVP_Attitude_Change(uint32_t nTargetPlayerId, uint32_t nSourcePlayerId, BOOL bNewAttitude);
    BOOL SendServerToPlayerCutscene_Status(CNWSPlayer * pPlayer, BOOL bIsActive, BOOL bEnableLeftMouseButton);
    BOOL SendServerToPlayerCutscene_FadeToBlack(CNWSPlayer * pPlayer, float fFadeSpeed);
    BOOL SendServerToPlayerCutscene_FadeFromBlack(CNWSPlayer * pPlayer, float fFadeSpeed);
    BOOL SendServerToPlayerCutscene_StopFade(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerCutscene_BlackScreen(CNWSPlayer * pPlayer);
    BOOL SendServerToPlayerCutscene_HideGui(CNWSPlayer * pPlayer, BOOL bHideGui);
    BOOL SendServerToPlayerPolymorph(CNWSPlayer * pPlayer, OBJECT_ID oidMorpher, BOOL bMorphing, BOOL bAllowCancel);
    BOOL HandlePlayerToServerCutscene(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL HandlePlayerToServerPlayerList(CNWSPlayer * pPlayer, uint8_t nMinor);
    BOOL SendServerToPlayerGuiEvent_Disable(uint32_t nPlayerId, int32_t nGuiElement, BOOL bDisable);
    BOOL HandlePlayerToServerDevice(CNWSPlayer * pPlayer, uint8_t nMinor);
    //BOOL SendServerToPlayerNui_Create(CNWSPlayer * pPlayer, Nui::JSON::WindowToken cToken, Nui::JSON::WindowIdentifier sId, const json & jData);
    BOOL SendServerToPlayerNui_CreateClient(CNWSPlayer * pPlayer, Nui::JSON::WindowToken cToken, Nui::JSON::WindowIdentifier sId, const CResRef & cResRef);
    BOOL SendServerToPlayerNui_Destroy(CNWSPlayer * pPlayer, int32_t nToken);
    BOOL SendServerToPlayerNui_Binds(CNWSPlayer * pPlayer, const std::vector<Nui::JSON::BindUpdate> & updates);
    //BOOL SendServerToPlayerNui_SetLayout(CNWSPlayer * pPlayer, Nui::JSON::WindowToken cToken, const CExoString & elementId, const json & jData);
    BOOL HandlePlayerToServerNuiEvent(CNWSPlayer * pPlayer, uint8_t nMinor);
    void AddDoorAppearanceToMessage(CNWSPlayer * pPlayer, CNWSDoor * pDoor);
    void AddPlaceableAppearanceToMessage(CNWSPlayer * pPlayer, CNWSPlaceable * pPlaceable);
    void AddAreaOfEffectObjectToMessage(CNWSAreaOfEffectObject * pSpellImpact);
    void AddTriggerGeometryToMessage(CNWSTrigger * pTrigger);
    void AddActiveItemPropertiesToMessage(CNWSItem * pItem, CNWSCreature * pCreature);
    BOOL ComputeQuickbarItemUseCountUpdateRequired(CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject);
    void WriteGameObjUpdate_UpdateQuickbarItemUseCount(CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject);
    void AddItemAppearanceToMessage(CNWSPlayer * pPlayer, CNWSItem * pItem);
    uint32_t ComputeAppearanceUpdateRequired(CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject);
    BOOL ComputeInventoryUpdateRequired(CNWSPlayer * pPlayer, uint32_t nInventorySlot, CNWSPlayerInventoryGUI * pInventoryGUI);
    BOOL ComputeRepositoryUpdateRequired(CNWSPlayer * pPlayer, CExoLinkedListPosition pPosition, CExoLinkedListPosition pOldPosition);
    void AssignVisualEffectLists(CExoArrayList<CLoopingVisualEffect *> * pTargetList, CExoArrayList<CLoopingVisualEffect *> * pSourceList);
    BOOL CompareVisualEffectLists(CExoArrayList<CLoopingVisualEffect *> * pSourceList1, CExoArrayList<CLoopingVisualEffect *> * pSourceList2);
    void AssignCreatureLists(CExoArrayList<OBJECT_ID> * pSourceList, CExoArrayList<OBJECT_ID> * pTargetList);
    BOOL CompareCreatureLists(CExoArrayList<OBJECT_ID> * pSourceList, CExoArrayList<OBJECT_ID> * pTargetList);
    void UpdateLastUpdateVisibilityList(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeVisibilityLists(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    uint32_t ComputeUpdateRequired(CNWSPlayer * pPlayer, CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject, BOOL bPlayerObject);
    BOOL SendServerToPlayerChat_Talk(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_DM_Talk(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_Tell(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_ServerTell(uint32_t nPlayerID, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_Shout(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_Silent_Shout(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_DM_Silent_Shout(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_StrRef(uint32_t nPlayerID, OBJECT_ID oidSpeaker, uint8_t nChatMessageType, uint32_t nStrRef);
    BOOL SendServerToPlayerChat_Whisper(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerChat_DM_Whisper(uint32_t nPlayerID, OBJECT_ID oidSpeaker, CExoString sSpeakerMessage);
    BOOL SendServerToPlayerMessage(uint32_t nPlayerId, uint8_t nMajor, uint8_t nMinor, uint8_t * pBuffer, uint32_t nBufferSize);
    void UpdateLastUpdateInventory(CNWSPlayer * pPlayer, uint32_t nInventorySlot, CNWSPlayerInventoryGUI * pInventoryGUI);
    void UpdateLastUpdateObject(CNWSPlayer * pPlayer, CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject, uint32_t nObjectUpdatesRequired);
    void UpdateLastUpdateObjectAppearance(CNWSObject * pGameObject, CLastUpdateObject * pLastUpdateObject, uint32_t nObjectAppearanceUpdatesRequired);
    void WriteGameObjUpdate_UpdateAppearance(CNWSObject * pAreaObject, CLastUpdateObject * pLastUpdateObject, uint32_t nUpdatesRequired, CNWSPlayer * pPlayer);
    void WriteGameObjUpdate_WriteInventorySlotAdd(CNWSPlayer * pPlayer, CNWSCreature * pAreaCreature, CNWSItem * pItem, uint32_t nSlot);
    void WriteGameObjUpdate_WriteInventorySlotDelete(CNWSCreature * pAreaCreature, uint32_t nSlot);
    void WriteGameObjUpdate_WriteInventorySlotUpdate(CNWSPlayer * pPlayer, OBJECT_ID oidItem, uint32_t nSlot);
    void WriteRepositoryUpdate(CNWSPlayer * pPlayer, CNWSObject * pPlayerGameObject, CItemRepository * pItemRepository, CNWSPlayerLUOInventory * pLastUpdateInventory, uint8_t nLastUpdateList, char cGuiElementByte, uint8_t nCurrentPanel);
    void WriteStoreInventoryUpdate(CNWSPlayer * pPlayer, CNWSStore * pStore);
    BOOL ComputeLastUpdate_ActionQueue(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    void UpdateLastUpdateActionQueue(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeLastUpdate_AutoMap(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    uint32_t ComputeNumAutoMapUpdatesRequired(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject, uint32_t * pnUnexploredTiles = 0);
    void UpdateLastUpdateAutoMap(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeLastUpdate_GuiFeats(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    uint32_t ComputeLastUpdate_GuiSkills(CNWSCreature * pCreature);
    uint32_t ComputeLastUpdate_PlayerState(CNWSCreature * pCreature);
    uint16_t ComputeLastUpdate_AssociateState(CNWSCreature * pCreature);
    BOOL ComputeLastUpdate_GuiKnownSpells(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeLastUpdate_GuiMemorizedSpells(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeLastUpdate_GuiKnownSpellUses(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL ComputeLastUpdate_GuiNumberMemorizedSpells(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    int32_t ComputeLastUpdate_CompareSpellLikeAbility(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    void ComputeLastUpdate_WriteSpellLikeAbility(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    void ComputeLastUpdate_StoreUpdateSpellLikeAbility(CNWSCreature * pCreature, CNWSPlayerLastUpdateObject * pLastUpdateObject);
    BOOL HasValidString(CExoLocString & sLocString, uint8_t nGender = 0);
    BOOL SendServerToPlayerInventory_LearnScroll(uint32_t nPlayerID, OBJECT_ID nObjectID, uint8_t nMinor);
    BOOL HandlePlayerToServerGuiEvent(CNWSPlayer * pPlayer, uint8_t nMinor);


#ifdef NWN_CLASS_EXTENSION_CNWSMessage
    NWN_CLASS_EXTENSION_CNWSMessage
#endif
};


#ifdef NWN_API_EPILOGUE
NWN_API_EPILOGUE(CNWSMessage)
#endif

