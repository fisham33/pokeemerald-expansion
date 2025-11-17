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
# 34 "data/scripts/dungeon_rooms.pory"
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
# 39 "data/scripts/dungeon_rooms.pory"
	lockall
# 40 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 42 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_1
# 43 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_1, DungeonRoom_Trainer_1_2
# 49 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 50 "data/scripts/dungeon_rooms.pory"
	closemessage
# 52 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 1
# 53 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 54 "data/scripts/dungeon_rooms.pory"
	waitstate
# 56 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 57 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_1_5
DungeonRoom_Trainer_1_4:
# 62 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_2:
# 44 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 45 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_1_5:
# 58 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 59 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 60 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_1
	goto DungeonRoom_Trainer_1_4


DungeonRoom_Trainer_2::
# 67 "data/scripts/dungeon_rooms.pory"
	lockall
# 68 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 70 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_2
# 71 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_2, DungeonRoom_Trainer_2_2
# 77 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 78 "data/scripts/dungeon_rooms.pory"
	closemessage
# 80 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 2
# 81 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 82 "data/scripts/dungeon_rooms.pory"
	waitstate
# 84 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 85 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_2_5
DungeonRoom_Trainer_2_4:
# 90 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_2:
# 72 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 73 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_2_5:
# 86 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 87 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 88 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_2
	goto DungeonRoom_Trainer_2_4


DungeonRoom_Trainer_3::
# 95 "data/scripts/dungeon_rooms.pory"
	lockall
# 96 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 98 "data/scripts/dungeon_rooms.pory"
	checkflag FLAG_DUNGEON_TRAINER_3
# 99 "data/scripts/dungeon_rooms.pory"
	goto_if_set FLAG_DUNGEON_TRAINER_3, DungeonRoom_Trainer_3_2
# 105 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 106 "data/scripts/dungeon_rooms.pory"
	closemessage
# 108 "data/scripts/dungeon_rooms.pory"
	setvar VAR_0x8000, 3
# 109 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 110 "data/scripts/dungeon_rooms.pory"
	waitstate
# 112 "data/scripts/dungeon_rooms.pory"
	special GetBattleOutcome
# 113 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq DungeonRoom_Trainer_3_5
DungeonRoom_Trainer_3_4:
# 118 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_2:
# 100 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 101 "data/scripts/dungeon_rooms.pory"
	releaseall
	end

DungeonRoom_Trainer_3_5:
# 114 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 115 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 116 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_3
	goto DungeonRoom_Trainer_3_4


DungeonRoom_ExitTrigger::
# 127 "data/scripts/dungeon_rooms.pory"
	lockall
# 128 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_PrepareNextRoom
# 129 "data/scripts/dungeon_rooms.pory"
	waitstate
# 130 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Intro::
# 138 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_Intro$"

DungeonRoom_PostBattle::
# 142 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_PostBattle$"

DungeonRoom_Text_NotCleared::
# 146 "data/scripts/dungeon_rooms.pory"
	.string "del: DungeonRoom_Text_NotCleared$"
