.set LOCALID_BOUNCER, 24

MauvilleCity_GameCorner_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerId_Onframe
	.byte 0
# 4 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 5 "data/maps/MauvilleCity_GameCorner/scripts.pory"
    @ Game Corner prices
# 6 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_DOUBLE_TEAM_COINS, 1500
# 7 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_PSYCHIC_COINS, 3500
# 8 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_FLAMETHROWER_COINS, 4000
# 9 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_THUNDERBOLT_COINS, 4000
# 10 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set TM_ICE_BEAM_COINS, 4000
# 11 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set DOLL_COINS, 1000
	.set RARECANDY_COINS, 4000
	.set SUNSTONE_COINS, 2000
	.set MOONSTONE_COINS, 2000
	.set FIRESTONE_COINS, 2000
	.set THUNDERSTONE_COINS, 2000
	.set WATERSTONE_COINS, 2000
	.set LEAFSTONE_COINS, 2000
	.set CHOICEBAND_COINS, 4500
	.set BRIGHTPOWDER_COINS, 4500

# 13 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set COINS_PRICE_50,  1000
# 14 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.set COINS_PRICE_500, 10000
# 15 "data/maps/MauvilleCity_GameCorner/scripts.pory"

TrainerId_Onframe:
.if GAME_CORNER_VAR_ID_CHECK != 0
	map_script_2 GAME_CORNER_VAR_ID_CHECK, 0, BouncerCheck
.endif
	.2byte 0
	
BouncerCheck::
	lockall
	applymovement LOCALID_BOUNCER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_BOUNCER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_BOUNCER, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Approach
	waitmovement 0
	msgbox MauvilleCity_GameCorner_Text_Bouncer1, MSGBOX_DEFAULT
	closemessage
	setvar GAME_CORNER_VAR_ID_CHECK, 1
	applymovement LOCALID_BOUNCER, Movement_Bouncer_Leave
	waitmovement 0
	releaseall
	end	
	
Movement_Bouncer_Approach:
	walk_left
	walk_left
	step_end	
	
Movement_Bouncer_Leave:
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end		

MauvilleCity_GameCorner_EventScript_Blackjack::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_BlackJack, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
	playbgm MUS_GAME_CORNER, FALSE
	special StartBlackJack
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Derby::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_Derby, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelBJ
	playbgm MUS_RG_PEWTER, FALSE
	special StartDerby
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
MauvilleCity_GameCorner_EventScript_CheckWinnings::
	goto_if_eq GAME_CORNER_VAR_WINNINGS, 0, MauvilleCity_GameCorner_NoWin
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS
	msgbox PB_YOU_WON_TEXT, MSGBOX_DEFAULT
	waitmessage
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
MauvilleCity_GameCorner_CancelVF::
	hidecoinsbox 0, 5
MauvilleCity_GameCorner_CancelBJ::
	closemessage
MauvilleCity_GameCorner_NoWin::
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Snake::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Onix_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Snake, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_NONE, FALSE
	special StartSnake
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_FlappyBird::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Butterfree_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Bird, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_NONE, FALSE
	special StartFlappyBird
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_BlockStacker::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, BlockStacker_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_BS, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_CASINO_PLUS_1, FALSE
	special StartBlockStacker
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

BlockStacker_Not_Enough::
	msgbox BS_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end	
	
Pinball_Not_Enough::
	msgbox PB_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end	
	
Onix_Not_Enough::
	msgbox Snake_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end		
	
Juice_Not_Enough::
	msgbox Bjuice_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end			
	
Butterfree_Not_Enough::
	msgbox Bird_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end			
	
VF_Not_Enough::
	msgbox Flip_Not_Enough, MSGBOX_DEFAULT
	releaseall
	end		
	
MauvilleCity_GameCorner_EventScript_Pachinko::	
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	msgbox MauvilleCity_GameCorner_Text_Pachinko, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	playbgm MUS_RG_ROUTE1, FALSE
	callnative PlayPachinko
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_PinballMeowth::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Meowth, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_CENTER, FALSE
	callnative PlayMeowthPinballGame
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_PinballDiglett::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 50, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Diglett, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 50
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_JUMP, FALSE
	callnative PlayDiglettPinballGame
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_PinballSeel::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 25, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Seel, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 25
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_SS_ANNE, FALSE
	callnative PlaySeelPinballGame
    waitstate 
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_PinballGengar::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 100, Pinball_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Pinball_Gengar, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF	
	removecoins 100
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_POKE_TOWER, FALSE
	callnative PlayGengarPinballGame
    waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto MauvilleCity_GameCorner_EventScript_CheckWinnings

MauvilleCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 50, VF_Not_Enough
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_VF, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	removecoins 50
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	playbgm MUS_RG_OAK, FALSE
	setvar GAME_CORNER_VAR_WINNINGS, 0
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
	goto_if_eq VAR_RESULT, 1, VF_Go_On
	releaseall
	end
	
VF_Come_Again::
	savebgm MUS_DUMMY
	fadedefaultbgm
	msgbox VF_Come_Again_Text, MSGBOX_DEFAULT
	setvar GAME_CORNER_VAR_WINNINGS, 0
	releaseall
	end
	
VF_Go_On::
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, GAME_CORNER_VAR_WINNINGS	
	msgbox MauvilleCity_GameCorner_Text_VF_Keep_Going, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, VF_Cash_Out
	goto VF_Loop
	
VF_Loop::
	hidecoinsbox 0, 5
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, VF_Come_Again
	goto_if_eq VAR_RESULT, 1, VF_Go_On
	releaseall
	end
	
VF_Cash_Out::	
	addcoins GAME_CORNER_VAR_WINNINGS
	setvar GAME_CORNER_VAR_WINNINGS, 0
.if FLIP_VAR_LEVEL != 0
	setvar FLIP_VAR_LEVEL, 0
.endif
	updatecoinsbox 1, 1
	playse SE_SHOP
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 40
	hidecoinsbox 0, 5
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Basic::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	call MauvilleCity_GameCorner_EventScript_GachaCommon
	releaseall
	end

MauvilleCity_GameCorner_EventScript_GachaCommon::
	playbgm MUS_RG_CINNABAR, FALSE
	special StartGacha
	waitstate
	savebgm MUS_DUMMY
	fadedefaultbgm
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MauvilleCity_GameCorner_EventScript_RecieveGachaMonParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MauvilleCity_GameCorner_EventScript_RecieveGachaMonPC
MauvilleCity_GameCorner_EventScript_GachaEnd:
	return

MauvilleCity_GameCorner_EventScript_RecieveGachaMonParty:
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_GachaEnd
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto MauvilleCity_GameCorner_EventScript_GachaEnd

MauvilleCity_GameCorner_EventScript_RecieveGachaMonPC:
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_TransferGachaMonToPC
	call Common_EventScript_NameReceivedBoxMon
MauvilleCity_GameCorner_EventScript_TransferGachaMonToPC:
	call Common_EventScript_TransferredToPC
	goto MauvilleCity_GameCorner_EventScript_GachaEnd

MauvilleCity_GameCorner_EventScript_Gacha_Great::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 2
	call MauvilleCity_GameCorner_EventScript_GachaCommon
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Ultra::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 3
	call MauvilleCity_GameCorner_EventScript_GachaCommon
	releaseall
	end
	
MauvilleCity_GameCorner_EventScript_Gacha_Master::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 4
	call MauvilleCity_GameCorner_EventScript_GachaCommon
	releaseall
	end

MauvilleCity_GameCorner_EventScript_CoinsClerk::
# 17 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 18 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 19 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner, MSGBOX_DEFAULT
# 20 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 21 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
# 22 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WereYouLookingForCoins
# 23 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 24 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showmoneybox 0, 0
# 25 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 6
# 26 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50
# 27 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 28 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault50::
# 29 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 0, FALSE
# 30 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 31 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
# 32 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
# 33 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
# 34 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 35 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 36 "data/maps/MauvilleCity_GameCorner/scripts.pory"
@ Unused
# 37 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseCoinsDefault500::
# 38 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoicedefault 15, 0, MULTI_GAME_CORNER_COINS, 1, FALSE
# 39 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 40 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_Buy50Coins
# 41 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_Buy500Coins
# 42 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelBuyCoins
# 43 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 44 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 45 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Buy50Coins::
# 46 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 47 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 50), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
# 48 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkmoney COINS_PRICE_50
# 49 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
# 50 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 50
# 51 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removemoney COINS_PRICE_50
# 52 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatemoneybox
# 53 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 6
# 54 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 55 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
# 56 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 57 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 58 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 59 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 60 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 61 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Buy500Coins::
# 62 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 63 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, (MAX_COINS + 1 - 500), MauvilleCity_GameCorner_EventScript_NoRoomForCoins
# 64 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkmoney COINS_PRICE_500
# 65 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NotEnoughMoney
# 66 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 500
# 67 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removemoney COINS_PRICE_500
# 68 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatemoneybox
# 69 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 6
# 70 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 71 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins, MSGBOX_DEFAULT
# 72 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 73 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 74 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 75 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 76 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 77 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NeedCoinCase::
# 78 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins, MSGBOX_DEFAULT
# 79 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 80 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 81 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 82 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughMoney::
# 83 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontHaveEnoughMoney, MSGBOX_DEFAULT
# 84 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 85 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 86 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 87 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 88 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 89 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelBuyCoins::
# 90 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontNeedCoinsThen, MSGBOX_DEFAULT
# 91 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 92 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 93 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 94 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 95 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 96 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForCoins::
# 97 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CoinCaseIsFull, MSGBOX_DEFAULT
# 98 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidemoneybox
# 99 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 5
# 100 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 101 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 102 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 103 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerDolls::
# 104 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 105 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 106 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 107 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 108 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage
# 109 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 110 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 111 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 112 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseDollPrizeMessage::
# 113 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 114 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 115 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 116 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 117 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize
# 118 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 119 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize::
# 120 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 121 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 122 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseDollPrize
# 123 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 124 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseDollPrize::
# 125 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoice 12, 0, MULTI_GAME_CORNER_DOLLS, FALSE
# 126 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 127 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_TreeckoDoll
# 128 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_TorchicDoll
# 129 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_MudkipDoll
# 130 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 131 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 132 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 133 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 134 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TreeckoDoll::
# 135 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 1
# 136 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_TREECKO_DOLL
# 137 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 138 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 139 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TorchicDoll::
# 140 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 2
# 141 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_TORCHIC_DOLL
# 142 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 143 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 144 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_MudkipDoll::
# 145 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 3
# 146 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_1, DECOR_MUDKIP_DOLL
# 147 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmDollPrize
# 148 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 149 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ConfirmDollPrize::
# 150 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsX, MSGBOX_YESNO
# 151 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelDollSelect
# 152 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 153 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll
# 154 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_BuyTorchicDoll
# 155 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_BuyMudkipDoll
# 156 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 157 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 158 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTreeckoDoll::
# 159 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 160 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 161 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
# 162 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TREECKO_DOLL
# 163 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 164 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 165 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_TREECKO_DOLL
# 166 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 167 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 168 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 169 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 170 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 171 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 172 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTorchicDoll::
# 173 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 174 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 175 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
# 176 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TORCHIC_DOLL
# 177 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 178 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 179 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_TORCHIC_DOLL
# 180 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 181 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 182 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 183 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 184 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 185 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 186 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyMudkipDoll::
# 187 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 188 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, DOLL_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll
# 189 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
# 190 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_MUDKIP_DOLL
# 191 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForDoll
# 192 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins DOLL_COINS
# 193 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	adddecoration DECOR_MUDKIP_DOLL
# 194 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 195 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 196 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SendToYourHomePC, MSGBOX_DEFAULT
# 197 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 198 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 199 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 200 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForDoll::
# 201 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 202 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 203 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 204 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 205 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForDoll::
# 206 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NoRoomForDecor
# 207 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseDollPrize
# 208 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 209 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 210 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelDollSelect::
# 211 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
# 212 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 213 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 214 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 215 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 216 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PrizeCornerTMs::
# 217 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 218 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 219 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
# 220 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 221 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage
# 222 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 223 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_PrizeCornerNew::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage
	release
	end	
	
MauvilleCity_GameCorner_EventScript_PrizeCornerNew2::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage2
	release
	end		

# 225 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseTMPrizeMessage::
# 226 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 227 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 228 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 0
# 229 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	showcoinsbox 1, 1
# 230 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
	
MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize	
	
MauvilleCity_GameCorner_EventScript_ChooseNewPrizeMessage2::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2		

# 232 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize::
# 233 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	message MauvilleCity_GameCorner_Text_WhichPrize
# 234 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmessage
# 235 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ChooseTMPrize
	
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize	
	
MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2::
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	goto MauvilleCity_GameCorner_EventScript_ChooseNewPrize2	

# 237 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ChooseTMPrize::
# 238 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	multichoice 12, 0, MULTI_GAME_CORNER_TMS, FALSE
# 239 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_RESULT
# 240 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_TMDoubleTeam
# 241 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_TMPsychic
# 242 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_TMFlamethrower
# 243 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_TMThunderbolt
# 244 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_TMIceBeam
# 245 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 5, MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 246 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 247 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_ChooseNewPrize::
	@ multichoice 12, 0, MULTI_GAMECORNER_NEW, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_RareCandy
	case 1, MauvilleCity_GameCorner_EventScript_SunStone
	case 2, MauvilleCity_GameCorner_EventScript_MoonStone
	case 3, MauvilleCity_GameCorner_EventScript_ChoiceBand
	case 4, MauvilleCity_GameCorner_EventScript_BrightPowder
	case 7, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end	

MauvilleCity_GameCorner_EventScript_ChooseNewPrize2::
	@ multichoice 12, 0, MULTI_GAMECORNER_NEW2, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_GameCorner_EventScript_FireStone
	case 1, MauvilleCity_GameCorner_EventScript_ThunderStone
	case 2, MauvilleCity_GameCorner_EventScript_WaterStone
	case 3, MauvilleCity_GameCorner_EventScript_LeafStone
	case 4, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	goto MauvilleCity_GameCorner_EventScript_CancelTMSelect
	end		

MauvilleCity_GameCorner_EventScript_ChoiceBand::
	setvar VAR_TEMP_1, 8
	bufferitemname STR_VAR_1, ITEM_CHOICE_BAND
	setvar VAR_0x8004, ITEM_CHOICE_BAND
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
	
MauvilleCity_GameCorner_EventScript_BrightPowder::
	setvar VAR_TEMP_1, 9
	bufferitemname STR_VAR_1, ITEM_BRIGHT_POWDER
	setvar VAR_0x8004, ITEM_BRIGHT_POWDER
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize	
	
MauvilleCity_GameCorner_EventScript_RareCandy::
	setvar VAR_TEMP_1, 1
	bufferitemname STR_VAR_1, ITEM_RARE_CANDY
	setvar VAR_0x8004, ITEM_RARE_CANDY
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize
	
MauvilleCity_GameCorner_EventScript_SunStone::
	setvar VAR_TEMP_1, 2
	bufferitemname STR_VAR_1, ITEM_SUN_STONE
	setvar VAR_0x8004, ITEM_SUN_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_MoonStone::
	setvar VAR_TEMP_1, 3
	bufferitemname STR_VAR_1, ITEM_MOON_STONE
	setvar VAR_0x8004, ITEM_MOON_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_ThunderStone::
	setvar VAR_TEMP_1, 5
	bufferitemname STR_VAR_1, ITEM_THUNDER_STONE
	setvar VAR_0x8004, ITEM_THUNDER_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_WaterStone::
	setvar VAR_TEMP_1, 6
	bufferitemname STR_VAR_1, ITEM_WATER_STONE
	setvar VAR_0x8004, ITEM_WATER_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_LeafStone::
	setvar VAR_TEMP_1, 7
	bufferitemname STR_VAR_1, ITEM_LEAF_STONE
	setvar VAR_0x8004, ITEM_LEAF_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize

MauvilleCity_GameCorner_EventScript_FireStone::
	setvar VAR_TEMP_1, 4
	bufferitemname STR_VAR_1, ITEM_FIRE_STONE
	setvar VAR_0x8004, ITEM_FIRE_STONE
	goto MauvilleCity_GameCorner_EventScript_ConfirmNewPrize	

MauvilleCity_GameCorner_EventScript_ConfirmNewPrize::
	//special BufferItemName
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
	switch VAR_TEMP_1
	case 1, MauvilleCity_GameCorner_EventScript_BuyRareCandy
	case 2, MauvilleCity_GameCorner_EventScript_BuySunStone
	case 3, MauvilleCity_GameCorner_EventScript_BuyMoonStone
	case 4, MauvilleCity_GameCorner_EventScript_BuyFireStone
	case 5, MauvilleCity_GameCorner_EventScript_BuyThunderStone
	case 6, MauvilleCity_GameCorner_EventScript_BuyWaterStone
	case 7, MauvilleCity_GameCorner_EventScript_BuyLeafStone
	case 8, MauvilleCity_GameCorner_EventScript_BuyChoiceBand
	case 9, MauvilleCity_GameCorner_EventScript_BuyBrightPowder
	
	end

MauvilleCity_GameCorner_EventScript_BuyBrightPowder::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, BRIGHTPOWDER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_BRIGHT_POWDER
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins BRIGHTPOWDER_COINS
	additem ITEM_BRIGHT_POWDER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyChoiceBand::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, CHOICEBAND_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_CHOICE_BAND
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins CHOICEBAND_COINS
	additem ITEM_CHOICE_BAND
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyRareCandy::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, RARECANDY_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_RARE_CANDY
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins RARECANDY_COINS
	additem ITEM_RARE_CANDY
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end
	
MauvilleCity_GameCorner_EventScript_BuySunStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, SUNSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins SUNSTONE_COINS
	additem ITEM_SUN_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyMoonStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, MOONSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew
	checkitemspace ITEM_MOON_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew
	removecoins MOONSTONE_COINS
	additem ITEM_MOON_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end

MauvilleCity_GameCorner_EventScript_BuyFireStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, FIRESTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins FIRESTONE_COINS
	additem ITEM_FIRE_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyThunderStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, THUNDERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_THUNDER_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins THUNDERSTONE_COINS
	additem ITEM_THUNDER_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyWaterStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, WATERSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins WATERSTONE_COINS
	additem ITEM_WATER_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end

MauvilleCity_GameCorner_EventScript_BuyLeafStone::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, LEAFSTONE_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2
	checkitemspace ITEM_LEAF_STONE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForNew2
	removecoins LEAFSTONE_COINS
	additem ITEM_LEAF_STONE
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end	

# 249 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMDoubleTeam::
# 250 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 1
# 251 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_TRAILBLAZE
# 252 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_TRAILBLAZE
# 253 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 254 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 255 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMPsychic::
# 256 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 2
# 257 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_PSYCHIC
# 258 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_PSYCHIC
# 259 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 260 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 261 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMFlamethrower::
# 262 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 3
# 263 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
# 264 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
# 265 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 266 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 267 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMThunderbolt::
# 268 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 4
# 269 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_THUNDERBOLT
# 270 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_THUNDERBOLT
# 271 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 272 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 273 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TMIceBeam::
# 274 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_TEMP_1, 5
# 275 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
# 276 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
# 277 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ConfirmTMPrize
# 278 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 279 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ConfirmTMPrize::
# 280 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	special BufferTMHMMoveName
# 281 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX, MSGBOX_YESNO
# 282 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_CancelTMSelect
# 283 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_TEMP_1
# 284 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam
# 285 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_BuyTMPsychic
# 286 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 3, MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower
# 287 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 4, MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt
# 288 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 5, MauvilleCity_GameCorner_EventScript_BuyTMIceBeam
# 289 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 290 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 291 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMDoubleTeam::
# 292 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 293 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_DOUBLE_TEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 294 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_TRAILBLAZE
# 295 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 296 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_DOUBLE_TEAM_COINS
# 297 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	additem ITEM_TM_TRAILBLAZE
# 298 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 299 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 300 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 301 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 302 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 303 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 304 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMPsychic::
# 305 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 306 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_PSYCHIC_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 307 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_PSYCHIC
# 308 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 309 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_PSYCHIC_COINS
# 310 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	additem ITEM_TM_PSYCHIC
# 311 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 312 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 313 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 314 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 315 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 316 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 317 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMFlamethrower::
# 318 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 319 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 320 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_FLAMETHROWER
# 321 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 322 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_FLAMETHROWER_COINS
# 323 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	additem ITEM_TM_FLAMETHROWER
# 324 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 325 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 326 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 327 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 328 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 329 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 330 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMThunderbolt::
# 331 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 332 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_THUNDERBOLT_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 333 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_THUNDERBOLT
# 334 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 335 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_THUNDERBOLT_COINS
# 336 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	additem ITEM_TM_THUNDERBOLT
# 337 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 338 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 339 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 340 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 341 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 342 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 343 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_BuyTMIceBeam::
# 344 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_2
# 345 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM
# 346 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitemspace ITEM_TM_ICE_BEAM
# 347 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForTM
# 348 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	removecoins TM_ICE_BEAM_COINS
# 349 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	additem ITEM_TM_ICE_BEAM
# 350 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	updatecoinsbox 1, 1
# 351 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 352 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo, MSGBOX_DEFAULT
# 353 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 354 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 355 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 356 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForTM::
# 357 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
# 358 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 359 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end	
	
MauvilleCity_GameCorner_EventScript_NotEnoughCoinsForNew2::
	msgbox MauvilleCity_GameCorner_Text_NotEnoughCoins, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end		

# 361 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForTM::
# 362 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_BagIsFull
# 363 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseTMPrize
# 364 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_NoRoomForNew::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize
	end	
	
MauvilleCity_GameCorner_EventScript_NoRoomForNew2::
	call Common_EventScript_BagIsFull
	goto MauvilleCity_GameCorner_EventScript_ReturnToChooseNewPrize2
	end		

# 366 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_CancelTMSelect::
# 367 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_OhIsThatSo, MSGBOX_DEFAULT
# 368 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	hidecoinsbox 0, 0
# 369 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 370 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 371 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 372 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Woman2::
# 373 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay, MSGBOX_NPC
# 374 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_Dealer::
	msgbox MauvilleCity_GameCorner_Text_Dealer, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end
	
MauvilleCity_GameCorner_EventScript_Dealer2::
	msgbox MauvilleCity_GameCorner_Text_Dealer2, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end	
	
MauvilleCity_GameCorner_EventScript_VFGuy1::
	msgbox MauvilleCity_GameCorner_Text_VFGuy1, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		
	
MauvilleCity_GameCorner_EventScript_VFGuy2::
	msgbox MauvilleCity_GameCorner_Text_VFGuy2, MSGBOX_NPC
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

# 376 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Gentleman::
# 377 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_RouletteOnlyLuck, MSGBOX_NPC
# 378 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 379 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 380 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Girl::
# 381 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 382 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 383 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_set FLAG_RECEIVED_STARTER_DOLL, MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 384 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne, MSGBOX_YESNO
# 385 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_EventScript_DeclineStarterDoll
# 386 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	switch VAR_STARTER_MON
# 387 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 0, MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll
# 388 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 1, MauvilleCity_GameCorner_EventScript_GiveTorchicDoll
# 389 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	case 2, MauvilleCity_GameCorner_EventScript_GiveMudkipDoll
# 390 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 391 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 392 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveTreeckoDoll::
# 393 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TREECKO_DOLL
# 394 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TREECKO_DOLL
# 395 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 396 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 397 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_TREECKO_DOLL
# 398 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 399 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 400 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 401 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 402 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveTorchicDoll::
# 403 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_TORCHIC_DOLL
# 404 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_TORCHIC_DOLL
# 405 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 406 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 407 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_TORCHIC_DOLL
# 408 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 409 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 410 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 411 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 412 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_GiveMudkipDoll::
# 413 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	bufferdecorationname STR_VAR_2, DECOR_MUDKIP_DOLL
# 414 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkdecorspace DECOR_MUDKIP_DOLL
# 415 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll
# 416 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HereYouGo2, MSGBOX_DEFAULT
# 417 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	givedecoration DECOR_MUDKIP_DOLL
# 418 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_STARTER_DOLL
# 419 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll
# 420 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 421 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 422 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoRoomForStarterDoll::
# 423 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	call Common_EventScript_NoRoomForDecor
# 424 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_YouWantItButNotNow, MSGBOX_DEFAULT
# 425 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 426 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 427 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 428 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_DeclineStarterDoll::
# 429 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DontBeNegative, MSGBOX_DEFAULT
# 430 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 431 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 432 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 433 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_ReceivedStarterDoll::
# 434 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CantWinJackpot, MSGBOX_DEFAULT
# 435 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 436 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 437 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 438 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PokefanM::
# 439 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 440 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 441 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 442 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_GameCorner_EventScript_TryGive20Coins
# 443 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor, MSGBOX_DEFAULT
# 444 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 445 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 446 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 447 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_TryGive20Coins::
# 448 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_set FLAG_RECEIVED_20_COINS, MauvilleCity_GameCorner_EventScript_PokefanMNormal
# 449 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkcoins VAR_TEMP_1
# 450 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_ge VAR_TEMP_1, 1, MauvilleCity_GameCorner_EventScript_PokefanMNormal @ Only give 20 coins if player has no coins
# 451 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setflag FLAG_RECEIVED_20_COINS
# 452 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	addcoins 20
# 453 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins, MSGBOX_DEFAULT
# 454 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	playse SE_SHOP
# 455 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_PokefanMNormal
# 456 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 457 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 458 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_PokefanMNormal::
# 459 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone, MSGBOX_DEFAULT
# 460 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 461 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 462 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 463 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_OldMan::
# 464 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 465 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 466 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates, MSGBOX_DEFAULT
# 467 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 468 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
	
MauvilleCity_GameCorner_EventScript_PachinkoGuy::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_PachinkoGuy, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end	
	
MauvilleCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Hiker, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		

MauvilleCity_GameCorner_EventScript_Bouncer::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Bouncer2, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end		
	
MauvilleCity_GameCorner_EventScript_DerbyLady1::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Derby_1, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			
	
MauvilleCity_GameCorner_EventScript_DerbyLady2::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Derby_2, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

MauvilleCity_GameCorner_EventScript_Fisherman::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Fisherman, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			
	
MauvilleCity_GameCorner_EventScript_Gachalady::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Gachalady, MSGBOX_DEFAULT
	closemessage
	end			

MauvilleCity_GameCorner_EventScript_Employee::
	lock
	faceplayer
	msgbox MauvilleCity_GameCorner_Text_Employee, MSGBOX_DEFAULT
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
	end			

# 470 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Cook::
# 471 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 472 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 473 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime, MSGBOX_DEFAULT
# 474 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 475 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 476 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 477 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Man::
# 478 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 479 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 480 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed, MSGBOX_DEFAULT
# 481 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 482 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 483 "data/maps/MauvilleCity_GameCorner/scripts.pory"

MauvilleCity_GameCorner_EventScript_JuiceLady::	
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase2
	showcoinsbox 1, 1
	msgbox MauvilleCity_GameCorner_Text_Juice, MSGBOX_YESNO
	closemessage
	goto_if_eq VAR_RESULT, NO, MauvilleCity_GameCorner_CancelVF
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, 10, Juice_Not_Enough
	removecoins 10
	updatecoinsbox 1, 1
	playse SE_SHOP
	delay 40
	hidecoinsbox 0, 5
	giveitem ITEM_BERRY_JUICE
	release
	end

MauvilleCity_GameCorner_EventScript_NPCReturnToSlots::
# 485 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	closemessage
# 486 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 487 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	waitmovement 0
# 488 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	release
# 489 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 490 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 491 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Maniac::
# 492 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 493 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 494 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_DifficultToStopOn7, MSGBOX_DEFAULT
# 495 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 496 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 497 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 498 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_Woman::
# 499 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lock
# 500 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	faceplayer
# 501 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo, MSGBOX_DEFAULT
# 502 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto MauvilleCity_GameCorner_EventScript_NPCReturnToSlots
# 503 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 504 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 505 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine0::
# 506 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 507 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 508 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 509 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 0
# 510 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 512 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 513 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 514 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 515 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine1::
# 516 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 517 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 518 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 519 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 1
# 520 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 522 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 523 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 524 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 525 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine2::
# 526 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 527 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 528 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 529 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 2
# 530 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 532 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 533 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 534 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 535 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine3::
# 536 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 537 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 538 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 539 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 3
# 540 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 542 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 543 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 544 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 545 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine4::
# 546 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 547 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 548 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 549 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 4
# 550 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 552 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 553 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 554 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 555 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine5::
# 556 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 557 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 558 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 559 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 5
# 560 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 562 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 563 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 564 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 565 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine6::
# 566 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 567 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 568 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 569 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 6
# 570 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 572 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 573 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 574 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 575 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine7::
# 576 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 577 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 578 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 579 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 7
# 580 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 582 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 583 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 584 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 585 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine8::
# 586 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 587 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 588 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 589 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 8
# 590 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 592 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 593 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 594 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 595 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine9::
# 596 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 597 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 598 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 599 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 9
# 600 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 602 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 603 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 604 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 605 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine10::
# 606 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 607 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 608 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 609 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 10
# 610 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 612 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 613 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 614 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 615 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_SlotMachine11::
# 616 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	lockall
# 617 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	checkitem ITEM_COIN_CASE
# 618 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
# 619 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	setvar VAR_0x8004, 11
# 620 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	specialvar VAR_RESULT, GetSlotMachineId
	playbgm MUS_GAME_CORNER, FALSE
	playslotmachine VAR_RESULT
# 622 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 623 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 624 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 625 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_EventScript_NoCoinCase::
# 626 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	msgbox MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase, MSGBOX_DEFAULT
# 627 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	releaseall
# 628 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	end
# 629 "data/maps/MauvilleCity_GameCorner/scripts.pory"

MauvilleCity_GameCorner_EventScript_NoCoinCase2::
	msgbox MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase, MSGBOX_DEFAULT
	releaseall
	end	

MauvilleCity_GameCorner_Text_ThisIsMauvilleGameCorner:
# 631 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This is MAUVILLE GAME CORNER.$"
# 632 "data/maps/MauvilleCity_GameCorner/scripts.pory"

MauvilleCity_GameCorner_Text_PachinkoGuy:
	.string "I used to own one of these dusty old\n"
	.string "DROPSPIN MACHINES.\p"
	.string "The manual always said 'Use the\n"
	.string "DIRECTIONAL BUTTONS to TILT and\l"
	.string "change the DROP SPEED…'\p"
	.string "I've always wondered what that\n"
	.string "means.$"

MauvilleCity_GameCorner_Text_Hiker:
	.string "Gah!\n"
	.string "I blew it all on that ONIX game.\p"
	.string "You need to be careful…\p"
	.string "You only win 2 COINS for\n"
	.string "every point in these machines.$"
	
MauvilleCity_GameCorner_Text_Derby_1:
	.string "Looking to bet on the DERBY?\n"
	.string "We've gone digital!\p"
	.string "Use one of the tablets\n"
	.string "in front of the counter.$"	
	
MauvilleCity_GameCorner_Text_Derby_2:
	.string "It's not all about CONDITION.\p"
	.string "At the end of the day, it's\n"
	.string "really all luck.\p"
	.string "Sometimes it's best to just\n"
	.string "pick your favorite!$"	
	
MauvilleCity_GameCorner_Text_Fisherman:
	.string "I come here for the food.\p"
	.string "It's no CELADON CAFE…\n"
	.string "But it'll do.$"		
	
MauvilleCity_GameCorner_Text_Gachalady:
	.string "The LOTTERY MACHINES have odds,\n"
	.string "but nothing is guaranteed.\p"
	.string "Some machines are better than\n"
	.string "others, and there are different\l"
	.string "rarities in all of them.\p"
	.string "New POKéMON are also weighted\n"
	.string "By your POKéDEX, so be wary.$"	
	
MauvilleCity_GameCorner_Text_Employee:
	.string "I'm on the lookout for cheaters.\n"
	.string "Nobody likes a cheater!$"
	
MauvilleCity_GameCorner_Text_Bouncer1:
	.string "You need a valid TRAINER ID\n"
	.string "to enter the GAME CORNER.\p"
	.string "Let's see…\p"
	.string "…\p"
	.string "Hmm…\p"
	.string "…\p"
	.string "Everything looks good here.\n"
	.string "Enjoy the GAME CORNER!$"	
	
MauvilleCity_GameCorner_Text_Bouncer2:
	.string "Enjoy the GAME CORNER!$"	
	
MauvilleCity_GameCorner_Text_Pachinko:
	.string "A DROPSPIN MACHINE!\n"
	.string "It's 3 COINS per BALL.$"
	
MauvilleCity_GameCorner_Text_NeedCoinCaseForCoins:
# 634 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Okay, you wanted some COINS for\n"
# 635 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the games?\p"
# 636 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "But you don't have a COIN CASE for\n"
# 637 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "stowing the COINS.$"
# 638 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 639 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_WereYouLookingForCoins:
# 640 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Were you looking for COINS?\p"
# 641 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's ¥1000 for 50 COINS.\n"
# 642 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Would you like some?$"
# 643 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 644 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_ThankYouHereAreYourCoins:
# 645 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Thank you very much!\n"
# 646 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here are your COINS!$"
# 647 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 648 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontHaveEnoughMoney:
# 649 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Um… You don't appear to have\n"
# 650 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "enough money…$"
# 651 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 652 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CoinCaseIsFull:
# 653 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh?\n"
# 654 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Your COIN CASE is full.$"
# 655 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 656 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontNeedCoinsThen:
# 657 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh… You don't need COINS, then?\n"
# 658 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Good luck on your adventure!$"
# 659 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 660 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes:
# 661 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Welcome.\p"
# 662 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can exchange your COINS for\n"
# 663 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "prizes here.$"
# 664 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 665 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_WhichPrize:
# 666 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Which prize would you like?$"
# 667 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 668 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SoYourChoiceIsTheTMX:
# 669 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "So your choice is\n"
# 670 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the {STR_VAR_1} {STR_VAR_2}?$"
	
MauvilleCity_GameCorner_Text_SoYourChoiceIsTheNewX:
	.string "So your choice is\n"
	.string "the {STR_VAR_1}?$"

MauvilleCity_GameCorner_Text_BlackJack:
	.string "It's a BLACKJACK TABLE!\n"
	.string "Want to play?$"
	
MauvilleCity_GameCorner_Text_Derby:
	.string "It's the MAUVILLE DERBY!\n"
	.string "Want to place a bet?$"	
	
MauvilleCity_GameCorner_Text_Snake:
	.string "It's ONIX!\n"
	.string "It costs 25 COINS to play.$"		
	
MauvilleCity_GameCorner_Text_Bird:
	.string "It's FLUTTERFREE!\n"
	.string "It costs 25 COINS to play.$"		
	
MauvilleCity_GameCorner_Text_Pinball_Meowth:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 25 COINS to play.$"

MauvilleCity_GameCorner_Text_BS:
	.string "It's BLOCK BUILDER!\n"
	.string "It costs 25 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Seel:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 25 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Diglett:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 50 COINS to play.$"
	
MauvilleCity_GameCorner_Text_Pinball_Gengar:
	.string "It's a PINBALL MACHINE!\n"
	.string "It costs 100 COINS to play.$"
	
MauvilleCity_GameCorner_Text_VF:
	.string "It's VOLTORB FLIP!\n"
	.string "It costs 50 COINS to play.$"

VF_Come_Again_Text:
	.string "Too bad.\n"
	.string "Try again soon!$"

# 672 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SendToYourHomePC:
# 673 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Thank you!\n"
# 674 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "We'll send it to your PC at home.$"
# 675 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 676 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NotEnoughCoins:
# 677 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You don't have enough COINS.$"
# 678 "data/maps/MauvilleCity_GameCorner/scripts.pory"

PB_YOU_WON_TEXT:
	.string "You won\n"
	.string "{STR_VAR_1} COINS!$"

PB_Not_Enough:
	.string "It's a PINBALL MACHINE!\p"
	.string "You don't have enough COINS…$"
	
Snake_Not_Enough:
	.string "It's ONIX!\p"
	.string "You don't have enough COINS…$"	
	
Bjuice_Not_Enough:
	.string "You don't have enough COINS.$"	
	
Bird_Not_Enough:
	.string "It's FLUTTERFREE!\p"
	.string "You don't have enough COINS…$"		
	
BS_Not_Enough:
	.string "It's BLOCK BUILDER!\p"
	.string "You don't have enough COINS…$"	

Flip_Not_Enough:
	.string "It's VOLTORB FLIP!\p"
	.string "You don't have enough COINS…$"

@ Unused
# 680 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NoRoomForPlacingDecor:
# 681 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "There isn't any room available for\n"
# 682 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "placing {STR_VAR_1}.$"
	
MauvilleCity_GameCorner_Text_VF_Keep_Going:
	.string "You've made {STR_VAR_1} COINS.\n"
	.string "Keep going?$"

# 684 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_OhIsThatSo:
# 685 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, is that so? \n"
# 686 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You need to save some COINS before\l"
# 687 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "coming back here.$"
# 688 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 689 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_SoYourChoiceIsX:
# 690 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "So your choice is {STR_VAR_1}?$"
# 691 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 692 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HereYouGo:
# 693 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here you go!$"
# 694 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 695 "data/maps/MauvilleCity_GameCorner/scripts.pory"
@ Unused
# 696 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantCarryAnyMore:
# 697 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, you can't carry any more than that.$"
# 698 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 699 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_GotTwoOfSameDollWantOne:
# 700 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I made a mistake and got two of\n"
# 701 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the same DOLLS.\p"
# 702 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Would you like one of them?$"
# 703 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 704 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HereYouGo2:
# 705 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here you go!$"
# 706 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 707 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_YouWantItButNotNow:
# 708 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Huh?\n"
# 709 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You want it, but not right now?$"
# 710 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 711 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DontBeNegative:
# 712 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Oh, don't be so negative!\n"
# 713 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can have this!$"
# 714 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 715 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantWinJackpot:
# 716 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "There's a prize I want, but I can't win\n"
# 717 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the jackpot.$"
# 718 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 719 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_NeedCoinCaseGoNextDoor:
# 720 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Hey, kid, if you want to play here,\n"
# 721 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "you need a COIN CASE.\p"
# 722 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I think the young lady next door\n"
# 723 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "had one. Go see her!$"
# 724 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 725 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_LuckOnlyLastSoLongTakeCoins:
# 726 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "My luck can only last so long.\n"
# 727 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This is too much for me.\l"
# 728 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here, take some COINS!$"
# 729 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 730 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_MauvilleSomethingForEveryone:
# 731 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "MAUVILLE has something for\n"
# 732 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "everyone.\p"
# 733 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "For me, it's the GAME CORNER.$"
# 734 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 735 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_RouletteTablesDifferentRates:
# 736 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The ROULETTE tables have different\n"
# 737 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "rates.\p"
# 738 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Check your COINS if you're going to\n"
# 739 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "pick a table.$"
# 740 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 741 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_EasyToLoseTrackOfTime:
# 742 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's easy to lose track of time in here. \n"
# 743 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "I should get back to work.$"
# 744 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 745 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CoinsAreNeededToPlay:
# 746 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "COINS are needed to play here\n"
# 747 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "in the GAME CORNER.$"
	
	MauvilleCity_GameCorner_Text_Dealer:
	.string "Some say BLACKJACK is about skill.\n"
	.string "Others say it's about luck.\p"
	.string "I say it's about having fun…\n"
	.string "and maybe winning big!$"
	
	MauvilleCity_GameCorner_Text_Dealer2:
	.string "You can bet anything divisible\n"
	.string "by 10 here.\p"
	.string "Maybe you should go all in!$"	

MauvilleCity_GameCorner_Text_VFGuy1:
	.string "You want to play VOLTORB FLIP?\p"
	.string "You need to be on the other\n"
	.string "side of the table.$"
	
MauvilleCity_GameCorner_Text_VFGuy2:
	.string "Try the other side of\n"
	.string "the table, pal.$"	

# 749 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_RouletteOnlyLuck:
# 750 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "This ROULETTE thing…\n"
# 751 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's rather demanding.\p"
# 752 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Win or lose, it's only by luck.$"
# 753 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 754 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_UpTo3CoinsCanBeUsed:
# 755 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Up to three COINS can be used to play\n"
# 756 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the SLOTS.$"
# 757 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 758 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_DifficultToStopOn7:
# 759 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It's very difficult to make it stop\n"
# 760 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "right on “7.”\p"
# 761 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "If it stops on “7” during the REEL TIME\n"
# 762 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "bonus game, you'll receive extra COINS.$"
# 763 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 764 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_HeresSomeSlotsInfo:
# 765 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "Here's some information for you\n"
# 766 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "about the SLOTS.\p"
# 767 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "The more lightning bolts you stock,\n"
# 768 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "the more REEL TIME chances you get.\p"
# 769 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "In a game with the maximum five\n"
# 770 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "REEL TIME chances…\p"
# 771 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "It is possible to receive four regular\n"
# 772 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "bonuses, then a big bonus.\p"
# 773 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "That would total 660 COINS, but it's\n"
# 774 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "very difficult to get.$"
# 775 "data/maps/MauvilleCity_GameCorner/scripts.pory"

# 776 "data/maps/MauvilleCity_GameCorner/scripts.pory"
MauvilleCity_GameCorner_Text_CantPlayWithNoCoinCase:
# 777 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "You can't play if you don't have\n"
# 778 "data/maps/MauvilleCity_GameCorner/scripts.pory"
	.string "a COIN CASE.$"

MauvilleCity_GameCorner_Text_CantBuyWithNoCoinCase:
	.string "Huh? Looks like you need\n"
	.string "a COIN CASE.$"
	
MauvilleCity_GameCorner_Text_Juice:
	.string "BERRY JUICE!\n"
	.string "Just 10 COINS.$"	
