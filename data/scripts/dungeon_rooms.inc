DungeonRoom_Trainer_0::
# 11 "data/scripts/dungeon_rooms.pory"
	lockall
# 12 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 14 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_0
# 15 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_0, DungeonRoom_Trainer_0_2
# 22 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerIntro
# 23 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 24 "data/scripts/dungeon_rooms.pory"
	closemessage
# 26 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 0
# 27 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 28 "data/scripts/dungeon_rooms.pory"
	waitstate
# 30 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 31 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_0_5
DungeonRoom_Trainer_0_4:
# 38 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 39 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_0_2:
# 16 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 17 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 18 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_0_5:
# 32 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 33 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 34 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 35 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_0
	goto DungeonRoom_Trainer_0_4


DungeonRoom_Trainer_1::
# 44 "data/scripts/dungeon_rooms.pory"
	lockall
# 45 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 47 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_1
# 48 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_1, DungeonRoom_Trainer_1_2
# 55 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerIntro
# 56 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 57 "data/scripts/dungeon_rooms.pory"
	closemessage
# 59 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 1
# 60 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 61 "data/scripts/dungeon_rooms.pory"
	waitstate
# 63 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 64 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_1_5
DungeonRoom_Trainer_1_4:
# 71 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 72 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_2:
# 49 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 50 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 51 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_5:
# 65 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 66 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 67 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 68 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_1
	goto DungeonRoom_Trainer_1_4


DungeonRoom_Trainer_2::
# 77 "data/scripts/dungeon_rooms.pory"
	lockall
# 78 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 80 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_2
# 81 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_2, DungeonRoom_Trainer_2_2
# 88 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerIntro
# 89 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 90 "data/scripts/dungeon_rooms.pory"
	closemessage
# 92 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 2
# 93 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 94 "data/scripts/dungeon_rooms.pory"
	waitstate
# 96 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 97 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_2_5
DungeonRoom_Trainer_2_4:
# 104 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 105 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_2:
# 82 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 83 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 84 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_5:
# 98 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 99 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 100 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 101 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_2
	goto DungeonRoom_Trainer_2_4


DungeonRoom_Trainer_3::
# 110 "data/scripts/dungeon_rooms.pory"
	lockall
# 111 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 113 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_3
# 114 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_3, DungeonRoom_Trainer_3_2
# 121 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerIntro
# 122 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 123 "data/scripts/dungeon_rooms.pory"
	closemessage
# 125 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 3
# 126 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 127 "data/scripts/dungeon_rooms.pory"
	waitstate
# 129 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 130 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_3_5
DungeonRoom_Trainer_3_4:
# 137 "data/scripts/dungeon_rooms.pory"
	setobjectmovementtype VAR_LAST_TALKED, MOVEMENT_TYPE_FACE_DOWN
# 138 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_2:
# 115 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 116 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 117 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_5:
# 131 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 132 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_GetRandomTrainerDefeat
# 133 "data/scripts/dungeon_rooms.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 134 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_3
	goto DungeonRoom_Trainer_3_4


DungeonRoom_ExitTrigger::
# 147 "data/scripts/dungeon_rooms.pory"
	lockall
# 148 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_PrepareNextRoom
# 149 "data/scripts/dungeon_rooms.pory"
	waitstate
# 150 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

