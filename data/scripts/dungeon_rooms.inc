DungeonRoom_Trainer_0::
# 11 "data/scripts/dungeon_rooms.pory"
	lockall
# 12 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 14 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_0
# 15 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_0, DungeonRoom_Trainer_0_2
# 21 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 22 "data/scripts/dungeon_rooms.pory"
	closemessage
# 24 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 0
# 25 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 26 "data/scripts/dungeon_rooms.pory"
	waitstate
# 28 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 29 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_0_5
DungeonRoom_Trainer_0_4:
# 35 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 36 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_0_2:
# 16 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 17 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_0_5:
# 30 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 31 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 32 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_0
	goto DungeonRoom_Trainer_0_4


DungeonRoom_Trainer_1::
# 41 "data/scripts/dungeon_rooms.pory"
	lockall
# 42 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 44 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_1
# 45 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_1, DungeonRoom_Trainer_1_2
# 51 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 52 "data/scripts/dungeon_rooms.pory"
	closemessage
# 54 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 1
# 55 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 56 "data/scripts/dungeon_rooms.pory"
	waitstate
# 58 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 59 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_1_5
DungeonRoom_Trainer_1_4:
# 65 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 66 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_2:
# 46 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 47 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_5:
# 60 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 61 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 62 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_1
	goto DungeonRoom_Trainer_1_4


DungeonRoom_Trainer_2::
# 71 "data/scripts/dungeon_rooms.pory"
	lockall
# 72 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 74 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_2
# 75 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_2, DungeonRoom_Trainer_2_2
# 81 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 82 "data/scripts/dungeon_rooms.pory"
	closemessage
# 84 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 2
# 85 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 86 "data/scripts/dungeon_rooms.pory"
	waitstate
# 88 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 89 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_2_5
DungeonRoom_Trainer_2_4:
# 95 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 96 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_2:
# 76 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 77 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_5:
# 90 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 91 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 92 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_2
	goto DungeonRoom_Trainer_2_4


DungeonRoom_Trainer_3::
# 101 "data/scripts/dungeon_rooms.pory"
	lockall
# 102 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 104 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_3
# 105 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_3, DungeonRoom_Trainer_3_2
# 111 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 112 "data/scripts/dungeon_rooms.pory"
	closemessage
# 114 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 3
# 115 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 116 "data/scripts/dungeon_rooms.pory"
	waitstate
# 118 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 119 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_3_5
DungeonRoom_Trainer_3_4:
# 125 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 126 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_2:
# 106 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 107 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_5:
# 120 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 121 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 122 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_3
	goto DungeonRoom_Trainer_3_4


DungeonRoom_ExitTrigger::
# 135 "data/scripts/dungeon_rooms.pory"
	lockall
# 136 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_PrepareNextRoom
# 137 "data/scripts/dungeon_rooms.pory"
	waitstate
# 138 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Intro::
# 146 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_Intro$"

DungeonRoom_PostBattle::
# 150 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_PostBattle$"

DungeonRoom_Text_NotCleared::
# 154 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_Text_NotCleared$"
