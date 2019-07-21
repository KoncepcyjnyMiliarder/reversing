#pragma once
#include "PEStuff.hpp"

enum PacketEnum
{
	keyInit,
	moveToLocation,
	npcSay,
	charInfo,
	userInfo,
	attack,
	die, // d(CharID)d(d)d(HAsHideout)d(HasCastle)d(flags)d(sweepable)d(access)
	revive, // d(objectId)
	attackOutOfRange, //
	attackinCoolTime, //
	attackDeadTarget, //
	spawnItem, // d(objectId)d(ItemID, // Get.Func01)d(X)d(Y)d(Z)d(Stackable)d(Count)d(d)
	dropItem, // d(PlayerID)d(objectId)d(ItemID, // Get.Func01)d(X)d(Y)d(Z)d(Stackable)d(Count)d(d)
	getItem, // d(PlayerID)d(objectId)d(X)d(Y)d(Z)
	statusUpdate, // d(objectId)d(AttribCount, // For.0002)d(AttrID, // Get.FSup)d(AttrValue)
	npcHtmlMessage, // d(MessageID)s(HTML)d(d)
	sellList, // d(Money)d(Lease)h(SellList, // For.0011)h(ItemType1)d(objectId)d(ItemID, // Get.Func01)d(Count)h(ItemType2)h(h)d(ItemBodyPart)h(EnchantLevel)h(h)h(h)d(refPrice)
	buyList, // d(Money)d(ListID)h(ListCount, // For.0011)h(ItemType1)d(objectId)d(ItemID, // Get.Func01)d(maxcnt)h(ItemType2)h(h)d(ItemBodyPart)h(EnchantLevel)h(h)h(h)d(PriceToSell)
	deleteObject, // d(objectId)d(d)
	charSelectInfo, // d(Count, // For.0065)s(Name)d(CharID)s(LoginName)d(SessionID)d(ClanID)d(d)d(Sex)d(Race)d(ClassID, // Get.ClassID)d(active)d(X)d(Y)d(Z)f(cur_HP)f(cur_MP)d(SP)q(Exp)d(Level)d(Karma)z(0036)d(Under)d(Rear)d(Lear)d(Neck)d(RFinger)d(LFinger)d(Head)d(RHand)d(LHand)d(Gloves)d(Chest)d(Legs)d(Feet)d(Back)d(LRHand)d(Hair)d(Face)d(Under, // Get.Func01)d(Rear, // Get.Func01)d(Lear, // Get.Func01)d(Neck, // Get.Func01)d(RFinger, // Get.Func01)d(LFinger, // Get.Func01)d(Head, // Get.Func01)d(RHand, // Get.Func01)d(LHand, // Get.Func01)d(Gloves, // Get.Func01)d(Chest, // Get.Func01)d(Legs, // Get.Func01)d(Feet, // Get.Func01)d(Back, // Get.Func01)d(LRHand, // Get.Func01)d(Hair, // Get.Func01)d(Face)d(HairStyle)d(HairColor, // Get.FCol)d(Face)f(Max_HP)f(Max_MP)d(DELdays)d(ClassID, // Get.ClassID)d(autSel)c(EnchEffect)h(face)h(face)
	loginFail, // d(reason)
	charSelected, // s(Name)d(CharID)s(Title)d(SessionID)d(ClanID)d(d)d(Sex)d(Race)d(ClassID, // Get.ClassID)d(active)d(X)d(Y)d(Z)f(Cur_HP)f(Cur_MP)d(SP)q(EXP)d(Level)d(Karma)d(d)d(INT)d(STR)d(CON)d(MEN)d(DEX)d(WIT)z(0128)d(inGameTime)z(0072)
	npcInfo, // Get.NpcId)d(IsAttackable)d(X)d(Y)d(Z)d(Heading)d(d)d(Maspd)d(Paspd)d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(FlyRSpd)d(FlyWSpd)f(ProperMul)f(Paspd)f(CollisRadius)f(CollisHeight)d(RHand, // Get.Func01)d(d)d(LHand, // Get.Func01)c(nameabove)c(isRun)c(isInFight)c(isAlikeDead)c(isSummoned)s(Name)s(Title)d(d)d(PvpFlag)d(karma ? )h(abnEffect)h(d)d(d)d(d)d(d)d(d)c(c)c(Team)f(collisRadius)f(collisHeight)d(d)
	itemList = 0x1B,
	inventoryUpdate = 0x27,
	/*
			 17=CharTemplates:d(count:For.0020)d(Race)d(classID:Get.ClassID)d(d)d(base_STR)d(d)d(d)d(base_DEX)d(d)d(d)d(base_CON)d(d)d(d)d(base_INT)d(d)d(d)d(base_WIT)d(d)d(d)d(base_MEN)d(d)
			 18=NewCharFail:
			 19=CharCreateSuccess:d(ok)
			 1A=CharCreateFail:d(reason)
			 //1B=ItemListPacket:h(window)h(ListCount:For.0012)h(itemType1)d(objectId)d(ItemID:Get.Func01)d(count)h(itemType2)h(CustType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(CustType2)d(AugId)d(Shadowtime)
			 1C=SunRise:
			 1D=SunSet:
			 1E=TradeStart:d(objectId)h(ListCount:For.0010)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(h)d(BodyPart)h(EnchantLevel)h(h)h(h)
			 1F=TradeStartOk:
			 20=TradeOwnAdd:h(count:For.0010)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(h)d(BodyPart)h(EnchantLevel)h(h)h(h)
			 21=TradeOtherAdd:h(count:For.0010)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(h)d(BodyPart)h(EnchantLevel)h(h)h(h)
			 22=TradeDone:d(num)
			 23=CharDeleteSuccess:
			 24=CharDeleteFail:d(reason)
			 25=ActionFail:
			 26=SeverClose:
			 //27=InventoryUpdate:h(count:For.0013)h(1add2mod3remove)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(cusType1)h(isEquipped)d(BodyPart)h(EnchantLevel)h(cusType2)d(AugId)d(Shadowtime)
			 28=TeleportToLocation:d(targetId)d(X)d(Y)d(Z)
			 */
	targetSelected = 0x29, //:d(objectId)d(TargetID)d(X)d(Y)d(Z)
	targetUnselected = 0x2A,//:d(TargetID)d(X)d(Y)d(Z)d(d)
							/*
							2B=AutoAttackStart:d(TargetID)
							2C=AutoAttackStop:d(TargetID)
							2D=SocialAction:d(PlayerID)d(Action:Get.Func09)
							2E=ChangeMoveType:d(charID)d(MoveType)d(d)
							2F=ChangeWaitType:d(objectId)d(WaitType)d(X)d(Y)d(Z)
							30=ManagePledgePower:d(d)d(d)d(privils)
							31=CreatePledge:d(d)
							32=AskJoinPledge:d(requestorId)s(pledgeName)
							33=JoinPledge:d(pledgeId)
							34=WithdrawalPledge:d(pledgeId)
							35=OustPledgeMember:d(d)
							36=SetOustPledgeMember:
							37=DismissPledge:d(pledgeId)
							38=SetDismissPledge:
							39=AskJoinParty:s(requestorName)d(itemDistribution)
							3A=JoinParty:d(response)
							3B=WithdrawalParty:d(partyID)
							3C=OustPartyMember:d(d)
							3D=SetOustPartyMember:
							3E=DismissParty:d(partyID)
							3F=SetDismissParty:
							40=MagicAndSkillList:d(objectId)d(CharID)d(d)
							41=WareHouseDepositList:h(WHtype)d(PlayerAdena)h(ListItemst:For.0011)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(h)d(BodyPart)h(EnchantLvl)h(h)h(h)d(objectId)
							42=WareHouseWithdrawList:h(WHtype)d(PlayerAdena)h(ListItemst:For.0011)h(itemType1)d(objectId)d(ItemId:Get.Func01)d(Count)h(itemType2)h(h)d(BodyPart)h(EnchantLvl)h(h)h(h)d(objectId)
							43=WareHouseDone:d(whId)
							44=ShortCutRegister:d(Type)d(Slot)d(_id)d(d)c(c)d(d)
							45=ShortCutInit_:-(Script)
							46=ShortCutDelete:d(shortcutId)
							47=StopMove:d(objectId)d(X)d(Y)d(Z)d(Heading)
							48=MagicSkillUse:d(charID)d(targetID)d(skillID:Get.Skill)d(skillLvl)d(hitTime)d(reuseDelay)d(X)d(Y)d(Z)h(count:for.0003)d(d)d(d)d(d)
							49=MagicSkillCanceled:d(objectId)
							4A=Say2:d(objectId)d(textType:Get.Func02)s(charName)s(Message)
							4B=EquipUpdate:d(change)d(objectId)d(BodyPart)
							4C=DoorInfo:d(objectId)d(DoorID)d(d)d(d)d(d)
							4D=DoorStatusUpdate:d(objectId)d(Open)d(Damage)d(enemy)d(DoorID)
							4E=PartySmallWindowAll:d(objectId)d(Party)d(ListCount:For.0012)d(objID)s(Name)d(cur_CP)d(max_CP)d(cur_HP)d(max_HP)d(cur_MP)d(max_MP)d(lvl)d(classId)d(d)d(d)
							4F=PartySmallWindowAdd:d(playerObjId)d(d)d(memObjId)s(memName)d(cur_CP)d(max_CP)d(cur_HP)d(max_HP)d(cur_MP)d(max_MP)d(lvl)d(classId)d(d)d(d)
							50=PartySmallWindowDeleteAll:
							51=PartySmallWindowDelete:d(memObjId)s(memberName)
							52=PartySmallWindowUpdate:d(memObjId)s(memberName)d(cur_CP)d(max_CP)d(cur_HP)d(max_HP)d(cur_MP)d(max_MP)d(lvl)d(classId)
							53=PledgeShowMemberListAll:d(mainOrSubpledge)d(clanID)d(pledgeType)s(clanName)s(LeaderName)d(clanCrestId)d(clanLvl)d(hasCastle)d(hasHideOut)d(Rank)d(reputation)d(d)d(d)d(AllyID)s(AllyName)d(AllyCrestId)d(isAtWar)d(memberCount:For.0007)s(memberName)d(memLvl)d(memClassId)d(d)d(memObjId)d(isOnLine)d(d)
							54=PledgeShowMemberListUpdate:s(playerName)d(Lvl)d(ClassId)d(d)d(objectId)d(isOnLine)d(pledgeType)d(hasSponsor)
							55=PledgeShowMemberListAdd:s(Name)d(Lvl)d(ClassId)d(d)d(d)d(isOnLine)d(pledgeType)
							56=PledgeShowMemberListDelete:s(playerName)
							57=MagicList:
							*/
	skillList = 0x58,

	/*
	59=VehicleInfo:d(boatObjId)d(boat_X)d(boat_Y)d(boat_Z)d(boat_Heading)
	5A=VehicleDeparture:d(boatObjId)d(spd1)d(spd2)d(X)d(Y)d(Z)
	5B=VehicleCheckLocation:d(boatObjId)d(X)d(Y)d(Z)d(boat_Heading)
	5C=GetOnVehicle:d(objectId)d(boatObjId)d(X)d(Y)d(Z)
	5D=GetOffVehicle:d(objectId)d(boatObjId)d(X)d(Y)d(Z)
	5E=TradeRequest:d(senderID)
	5F=RestartResponse:d(ok)s(Message)
	60=MoveToPawn:d(charID)d(targetId)d(distance)d(X)d(Y)d(Z)
	61=ValidateLocation:d(charID)d(X)d(Y)d(Z)d(Heading)
	62=StartRotating:d(charId)d(degree)d(side)
	63=FinishRotating:d(objectId)d(Heading)
	64=SystemMessage:d(MsgID:Get.MsgID)d(typesCount)
	65=StartPledgeWar:s(char)s(pledgename)
	66=ReplyStartPledgeWar:d(d)
	67=StopPledgeWar:s(pledgename)s(char)
	68=ReplyStopPledgeWar:d(d)
	69=SurrenderPledgeWar:s(pledgename)s(char)
	6A=ReplySurrenderPledgeWar:d(d)
	6B=SetPledgeCrest:
	6C=PledgeCrest:d(crestID)b(IconCrest)
	6D=SetupGauge:d(dat1)d(time)d(time)
	6E=ShowBoard:c(show)s(s1)s(s2)s(s3)s(s4)s(s5)s(s6)s(s7)s(s8)s(curpage)
	6F=ChooseInventoryItem:d(ItemId)
	70=Dummy:
	71=MoveToLocationInVehicle:d(pcID)d(boatID)d(dest_X)d(dest_Y)d(dest_Z)d(orig_X)d(orig_Y)d(orig_Z)
	72=StopMoveInVehicle:d(objId)d(boatId)d(X)d(Y)d(Z)d(Heading)
	73=ValidateLocationInVehicle:d(PlayerID)d(d)d(X)d(Y)d(Z)d(Heading)
	74=TradeUpdate:
	75=TradePressOwnOk:
	76=MagicSkillLaunched:d(charID)d(skillID:Get.Skill)d(skillLvl)d(failed)d(targetId)
	77=FriendAddRequestResult:d(d)
	78=FriendAdd:
	79=FriendRemove:
	7A=FriendList:
	7B=FriendStatus:
	7C=TradePressOtherOk:
	7D=FriendAddRequest:s(requestorName)d(d)
	7E=LogOutOk:
	7F=MagicEffectIcons:h(ListCount:For.0003)d(skillID:Get.Skill)h(Lvl)d(Duration)
	80=QuestList:h(Count:For.0002)d(QuestId)d(cond)h(AllQCount:For.0004)d(drObId)d(drId)d(drItCn)d(d)
	81=EnchantResult:d(result)
	82=PledgeShowMemberListDeleteAll:
	83=PledgeInfo:d(clanId)s(clanName)s(allyName)
	84=PledgeExtendedInfo:
	85=SurrenderPersonally:
	86=Ride:d(_id)d(bRide)d(rideType)d(rideClassId)
	87=Dummy:
	88=PledgeShowInfoUpdate:d(clanId)d(d)d(clanLvl)d(hasCastle)d(hasHideOut)d(d)d(reputation)d(d)d(D)d(d)s(bil)d(d)d(d)
	89=ClientAction:d(d)
	8A=AcquireSkillList:d(orig)d(ListCount:For.0005)d(_id)d(nxtLvl)d(maxLvl)d(spCost)d(require)
	8B=AcquireSkillInfo:d(_id)d(level)d(spCost)d(Mode)d(Count:For.0004)d(type)d(itemId)d(count)d(d)
	8C=ServerObjectInfo:
	8D=GMHide:d(_id)
	8E=AcquireSkillDone:
	8F=GMViewCharacterInfo:d(X)d(Y)d(Z)d(Heading)d(ObjId)s(Name)d(Race)d(Sex)d(ClassId)d(Lvl)q(Exp)d(STR)d(DEX)d(CON)d(INT)d(WIT)d(MEN)d(max_HP)d(cur_HP)d(max_MP)d(cur_MP)d(SP)d(cur_Load)d(max_Load)d(d)d(Under)d(Rear)d(Lear)d(Neck)d(RFinger)d(LFinger)d(Head)d(RHand)d(LHand)d(Gloves)d(Chest)d(Legs)d(Feet)d(Back)d(LRHand)d(Hair)d(Under:Get.Func01)d(Rear:Get.Func01)d(Lear:Get.Func01)d(Neck:Get.Func01)d(RFinger:Get.Func01)d(LFinger:Get.Func01)d(Head:Get.Func01)d(RHand:Get.Func01)d(LHand:Get.Func01)d(Gloves:Get.Func01)d(Chest:Get.Func01)d(Legs:Get.Func01)d(Feet:Get.Func01)d(Back:Get.Func01)d(LRHand:Get.Func01)d(Hair:Get.Func01)d(Patk)d(Paspd)d(PDef)d(Evasion)d(Accuracy)d(Crithit)d(Matk)d(Maspd)d(Paspd)d(MDef)d(PvpFlag)d(Karma)d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(flyRSpd)d(flyWSpd)f(moveMul)f(aspdMul)f(collisRadius)f(collisHeight)d(HairStyle)d(HairColor:Get.FCol)d(Face)d(isGM)s(Title)d(clanId)d(clanCrestId)d(allyId)c(Mount)c(store)c(DwarfCraft)d(PKkills)d(PVPkills)h(RecomLeft)h(RecomHave)d(ClassId)d(d)d(max_CP)d(cur_CP)c(isRun)d(FaceId)d(FaceIt)d(pledgeClass)d(d)d(NameColor:Get.FCol)d(d)
	90=GMViewPledgeInfo:s(charName)d(clanId)s(clanName)s(LeaderName)d(CrestId)d(clanLvl)d(hasCastle)d(hasHideOut)d(d)d(charLvl)d(d)d(d)d(allyId)s(allyName)d(allyCrestId)d(isAtWar)d(membersCount:For.0006)s(memberName)d(memLvl)d(memClassId)d(d)d(d)d(isOnline)
	91=GMViewSkillInfo:s(charName)d(ListCount:For.0004)d(isPassive)d(skillLVL)d(skillID)c(c)
	92=GMViewMagicInfo:
	93=GMViewQuestInfo:s(charName)h(questCount:For.0002)d(questId)d(cond)h(DropList:For.0004)d(dropID)d(dropItemId)d(dropCount)d(d)
	94=GMViewItemList:s(playerName)d(InventLimit)h(window)h(ItemsCount:For.0010)h(type1)d(objectId)d(ItemId:Get.Func01)d(count)h(type2)h(custType1)h(isEquipped)d(BodyPart)h(EnchantLvl)h(custType2)
	95=GMViewWarehouseWithdrawList:s(playerName)d(Money)h(itemCount:For.0011)h(type1)d(objectId)d(ItemId:Get.Func01)d(count)h(type2)h(h)d(BodyPart)h(EnchantLvl)h(ssCount)h(spsCount)d(objectId)
	96=ListPartyWating:d(plcount:For.0010)d(plobjectId)s(playerName)d(lvl)d(classId)d(d)d(clanId)d(d)d(X)d(Y)d(Z)
	97=PartyRoomInfo:d(plobjectId)d(showLvl)d(showClass)d(d)s(partyMemo)
	98=PlaySound:d(d)s(soundFile)d(ship)d(shipObjId)d(X)d(Y)d(Z)d(d)
	99=StaticObject:d(StaticobjectId)d(objectId)
	9A=PrivateStoreManageList:d(playerObjID)d(packSell)d(adena)d(ItemCount:For.0009)d(type2)d(objId)d(ItemId:Get.Func01)d(count)h(h)h(Enchant)h(h)d(BodyPart)d(price)d(SellCount:For.0010)d(type2)d(objId)d(ItemId:Get.Func01)d(count)h(h)h(Enchant)h(h)d(BodyPart)d(price)d(storePrice)
	9B=PrivateStoreList:d(objectId)d(packSale)d(adena)d(ListCount:For.0010)d(type2)d(objId)d(ItemId:Get.Func01)d(count)h(h)h(Enchant)h(h)d(BodyPart)d(price)d(storePrice)
	9C=PrivateStoreMsg:d(objectId)s(storeMsg)
	9D=ShowMinimap:d(mapId)
	9E=ReviveRequest:
	9F=AbnormalVisualEffect:
	A0=TutorialShowHtml:s(Html)
	A1=TutorialShowQuestionMark:d(blnk)
	A2=TutorialEnableClientEvent:d(d)
	A3=TutorialCloseHtml:
	A4=ShowRadar:d(d)d(d)d(d)d(d)d(d)
	A5=DeleteRadar:d(d)d(d)d(d)
	*/
	myTargetSelected = 0xA6,
	/*
	A7=PartyMemberPosition:d(membercount:For.0004)d(objID)d(X)d(Y)d(Z)
	A8=AskJoinAlliance:d(requestorID)s(requestorName)
	A9=JoinAlliance:d(d)
	AA=WithdrawAlliance:d(d)
	AB=OustAllianceMemberPledge:d(d)
	AC=DismissAlliance:d(d)
	AD=SetAllianceCrest:
	AE=AllianceCrest:d(CrestID)b(IconCrest)
	AF=ServerCloseSocket:
	B0=PetStatusShow:d(summonType)
	B1=PetInfo:d(summonType)d(objectId)d(templ)d(d)d(X)d(Y)d(Z)d(Heading)d(d)d(Maspd)d(Paspd)d(runSpd)d(walkSpd)d(swimRSpd)d(swimWSpd)d(flRSpd)d(flWSpd)d(flyRSpd)d(flyWSpd)f(prMul)f(AspdMul)f(collisRadius)f(collisHeight)d(RHand)d(d)d(LHand)c(nameAbove)c(isRun)c(isInFight)c(isAlikeDead)c(isSummon)s(summonName)s(summonTitle)d(d)d(sumPVPflag)d(sumKarma?)d(cur_Fed)d(max_Fed)d(cur_HP)d(max_HP)d(cur_MP)d(max_MP)d(SP)d(LVL)q(Exp)q(ExpThisLvl)q(ExpNextLvl)d(totalLoad)d(maxLoad)d(PAtk)d(PDef)d(MAtk)d(MDef)d(Accuracy)d(Evasion)d(Crit)d(runSpd)d(Paspd)d(Maspd)d(bleedPoisFlame)h(Ride)c(c)h(h)c(TeamAura)d(usedSS)d(usedSpS)
	B2=PetItemList:h(ItemCount:for.0010)h(type1)d(objID)d(ItemID:Get.Func01)d(count)h(type2)h(h)h(isEquipped)d(BodyPart)h(Enchant)h(h)
	B3=PetInventoryUpdate:h(ItemCount:For.0011)h(change)h(type1)d(objID)d(ItemID:Get.Func01)d(count)h(type2)h(h)h(isEquipped)d(BodyPart)h(Enchant)h(h)
	B4=AllianceInfo:
	B5=PetStatusUpdate:d(SummonType)d(objectId)d(X)d(Y)d(Z)s(Title)d(cur_Fed)d(max_Fed)d(cur_HP)d(max_HP)d(cur_MP)d(max_MP)d(Level)q(Exp)q(ExpThisLvl)q(ExpNextLvl)
	B6=PetDelete:d(PetID)d(PetNumber)
	B7=PrivateStoreBuyManageList:d(objectId)d(Adena)d(ItemsCount:For.0007)d(ItemID:Get.Func01)h(h)d(count)d(refPrice)h(h)d(BodyPart)h(type2)d(ByuCount:For.0009)d(ItemID:Get.Func01)h(h)d(count)d(refPrice)h(h)d(BodyPart)h(type2)d(yourPrice)d(refPrice)
	B8=PrivateBuyListBuy:d(objectId)d(adena)d(ItemsCount:For.0010)d(objID)d(ItemID:Get.Func01)h(Enchant)d(count)d(refPrice)h(h)d(BodyPart)h(type2)d(BuyersPrice)d(count)
	B9=PrivateStoreMsgBuy:d(objectId)s(storeMsg)
	BA=VehicleStart:d(d)d(d)
	BB=RequestTimeCheck:d(d)
	BC=StartAllianceWar:s(s)s(s)
	BD=ReplyStartAllianceWar:
	BE=StopAllianceWar:s(s)s(s)
	BF=ReplyStopAllianceWar:
	C0=SurrenderAllianceWar:
	C1=SkillCoolTime:d(d)d(d)d(d)d(d)
	C2=PackageToList:d(d)s(s)d(d)
	C3=PackageSendableList:h(h)d(d)d(d)d(d)
	C4=EarthQuake:d(X)d(Y)d(Z)d(Intensivity)d(Duration)d(d)
	C5=FlyToLoaction:d(ObjID)d(ToX)d(ToY)d(ToZ)d(OrigX)d(OrigY)d(OrigZ)
	C6=BlockList:
	C7=SpecialCamera:d(_id)d(Distantion)d(Yaw)d(Pitch)d(Time)d(Duration)
	C8=NormalCamera:
	C9=CastleSiegeInfo:d(CastleID)d(ActLeader)d(OwnerID)s(name)s(ClanLeader)d(allyID)s(allyName)d(time_ms)d(siege_time)d(num)
	CA=CastleSiegeAttackerList:d(CastleID)d(d)d(d)d(d)d(count)d(count:for.0009)d(ClanID)s(clanName)s(leaderName)d(crestID)d(d)d(allyID)s(allyName)s(allyLeader)d(allyCrestID)
	CB=CastleSiegeDefenderList:d(CastleID)d(d)d(d)d(d)d(count)d(count:for.0020)d(ClanID)s(clanName)s(leaderName)d(crestID)d(signedTime)d(SiegeType)d(allyID)s(allyName)s(allyLeader)d(allyCrestID)d(ClanID)s(clanName)s(leaderName)d(crestID)d(signedTime)d(SiegeType)d(allyID)s(allyName)s(allyLeader)d(allyCrestID)
	CC=NickNameChanged:d(objID)s(NeedName)
	CD=PledgeStatusChanged:d(LeaderID)d(ClanID)d(d)d(clanLVL)d(d)d(d)d(d)
	CE=RelationChanged:d(objId)d(relation)d(autoattackable)d(karma)d(pvpflag)
	CF=EventTrigger:d(_id)c(On)
	D0=MultiSellList_:-(Script)
	D1=SetSummonRemainTime:d(d)d(d)
	D2=SkillRemainSec:d(d)d(d)d(d)d(d)d(d)d(d)d(d)
	D3=NetPing:d(kID)
	D4=Dice:d(PlayerID)d(ItemID:Get.Func01)d(Number)d(X)d(Y)d(Z)
	D5=Snoop:d(ConvoID)s(Name)d(d)d(Type)s(Speaker)s(Msg)
	D6=RecipeBookItemList:d(isDwarven)d(max_MP)d(recipesCount:For.0002)d(recipeId)d(recipeNum)
	D7=RecipeItemMakeInfo:d(_id)d(IsDwarven)d(cur_MP)d(max_MP)d(Success)
	D8=RecipeShopManageList:d(objectId)d(Adena)d(IsDwarven)d(ListCount:For.0002)d(RecipeID)d(recipeNum)d(Listcount:For.0003)d(RecipeID)d(d)d(Cost)
	D9=RecipeShopSellList:d(objectId)d(cur_MP)d(max_MP)d(Adena)d(ListCount:For.0003)d(RecipeID)d(d)d(Cost)
	DA=RecipeShopItemInfo:d(ShopID)d(RecipeID)d(cur_MP)d(max_MP)d(d)
	DB=RecipeShopMsg:d(objectId)s(StoreName)
	DC=ShowCalculator:d(CalculatorID)
	DD=MonRaceInfo:d(d)d(d)d(Count:For.0037)d(monsterObjID)d(npcId)d(OrigX)d(OrigY)d(OrigZ)d(ToX)d(ToY)d(ToZ)f(collisHeight)f(collis(Radius)d(d)c(1)c(2)c(3)c(4)c(5)c(6)c(7)c(8)c(9)c(10)c(11)c(12)c(13)c(14)c(15)c(16)c(17)c(18)c(19)c(20)d(d)d(d)d(d)d(d)d(d)d(d)
	DE=ShowTownMap:s(texture)d(X)d(Y)
	DF=ObservationMode:d(X)d(Y)d(Z)c(c)c(c)c(c)
	E0=ObservationReturn:d(X)d(Y)d(Z)
	E1=ChairSit:d(ActiveobjectId)d(StaticobjectId)
	E2=HennaEquipList:d(PlayerAdena)d(Slots)d(ListCount:For.0005)d(SymbolID)d(ItemDyeID:Get.Func01)d(dyeRequire)d(adenaRequire)d(d)
	E3=HennaItemInfo:d(SymbolID)d(ItemID:Get.Func01)d(DyeRequire)d(Price)d(Draw)d(Adena)d(cur_INT)c(equip_INT)d(cur_STR)c(equip_STR)d(cur_CON)c(equip_CON)d(cur_MEN)c(equip_MEN)d(cur_DEX)c(equip_DEX)d(cur_WIT)c(equip_WIT)
	E4=HennaInfo:c(INT)c(STR)c(CON)c(MEN)c(DEX)c(WIT)d(SlotCount:For.0002)d(slot)d(SymbolID)
	E5=HennaUnequipList:
	E6=HennaUnequipInfo:
	E7=SendMacroList:d(Revision)c(c)c(Count)c(c)d(MacroID)s(Name)s(Descr)s(Acronym)c(Icon)c(Lenght:For.0005)c(idx)c(type)d(SkillID)c(ShortcutID)s(cmdName)
	E8=BuyListSeed:d(money)d(ListID)h(ListCount:for.0007)h(itemType1)d(objectId)d(ItemID:Get.Func01)d(Count)h(itemType2)h(h)d(price)
	E9=SellListProcure:d(money)d(d)h(ListCount:for.0007)h(itemType1)d(objectId)d(ItemID:Get.Func01)d(Count)h(itemType2)h(h)d(price)
	EA=GMHennaInfo:c(INT)c(STR)c(CON)c(MEN)c(DEX)c(WIT)d(SlotCount:For.0002)d(slot)d(SymbolID)
	EB=RadarControl:d(ShowRadar)d(Type)d(X)d(Y)d(Z)
	EC=ClientSetTime:d(d)d(d)
	ED=ConfirmDlg:d(requestID)d(d)d(d)s(name)d(d)d(d)
	EE=PartySpelled:d(Summon)d(ObjecID)d(EffectCount:For.0003)d(SkillID:Get.Skill)h(Data)d(Duration)
	EF=ShopPreviewList:c(c)c(c)c(c)c(c)d(money)d(ListID)h(ListCount:For.0004)d(ItemId:Get.Func01)h(type2)h(BodyPart)d(wearPrice)
	F0=ShopPreviewInfo:
	F1=CameraMode:d(Mode)
	F2=ShowXMasSeal:d(d)
	F3=EtcStatusUpdate:d(d)d(d)d(d)d(d)d(d)
	*/
	shortBuffStatusUpdate = 0xF4,
		/*
	F5=SSQStatus_:-(Script)
	F6=PetitionVote:
	F7=AgitDecoInfo:d(d)
	F8=SSQInfo:h(Sky)
	F9=GameGuardQuery:d(d)d(d)d(d)d(d)
	FA=FriendList:d(FriendCount:For.0005)h(h)d(friendID)s(friendName)d(isOnLine)h(h)
	FB=Friend:
	FC=FriendStatus:
	FD=FriendSay:d(d)s(sender)s(receiver)s(message)
	*/
	error = 0xFF
};
enum Version
{
	L2_IL,
	L2_H5
};

class GameVersion
{
public:
	virtual unsigned int GetEngineEcx() = 0;
	virtual PacketEnum OpcodeToPacket(unsigned char opcode) = 0;
	virtual Version GetGameVersion() = 0;
};