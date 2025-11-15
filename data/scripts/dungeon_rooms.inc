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
	setvar VAR_0x8000, 0
# 22 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 23 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 24 "data/scripts/dungeon_rooms.pory"
	dotrainerbattle
# 25 "data/scripts/dungeon_rooms.pory"
	goto DungeonRoom_Trainer_0_PostBattle
	return

DungeonRoom_Trainer_0_2:
# 16 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 17 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Trainer_0_PostBattle::
# 29 "data/scripts/dungeon_rooms.pory"
	lockall
# 30 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 31 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 32 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 33 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_0
# 34 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


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
	setvar VAR_0x8000, 1
# 50 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 51 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 52 "data/scripts/dungeon_rooms.pory"
	dotrainerbattle
# 53 "data/scripts/dungeon_rooms.pory"
	goto DungeonRoom_Trainer_1_PostBattle
	return

DungeonRoom_Trainer_1_2:
# 44 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 45 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Trainer_1_PostBattle::
# 57 "data/scripts/dungeon_rooms.pory"
	lockall
# 58 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 59 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 60 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 61 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_1
# 62 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


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
	setvar VAR_0x8000, 2
# 78 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 79 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 80 "data/scripts/dungeon_rooms.pory"
	dotrainerbattle
# 81 "data/scripts/dungeon_rooms.pory"
	goto DungeonRoom_Trainer_2_PostBattle
	return

DungeonRoom_Trainer_2_2:
# 72 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 73 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Trainer_2_PostBattle::
# 85 "data/scripts/dungeon_rooms.pory"
	lockall
# 86 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 87 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 88 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 89 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_2
# 90 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


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
	setvar VAR_0x8000, 3
# 106 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 107 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Intro, MSGBOX_DEFAULT
# 108 "data/scripts/dungeon_rooms.pory"
	dotrainerbattle
# 109 "data/scripts/dungeon_rooms.pory"
	goto DungeonRoom_Trainer_3_PostBattle
	return

DungeonRoom_Trainer_3_2:
# 100 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 101 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Trainer_3_PostBattle::
# 113 "data/scripts/dungeon_rooms.pory"
	lockall
# 114 "data/scripts/dungeon_rooms.pory"
	faceplayer
# 115 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
# 116 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_DEFAULT
# 117 "data/scripts/dungeon_rooms.pory"
	setflag FLAG_DUNGEON_TRAINER_3
# 118 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


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
	.string "Let's battle!$"

DungeonRoom_PostBattle::
# 142 "data/scripts/dungeon_rooms.pory"
	.string "That was a good fight.$"

DungeonRoom_Text_NotCleared::
# 146 "data/scripts/dungeon_rooms.pory"
	.string "You must defeat all the trainers\n"
	.string "in this room before proceeding!$"
