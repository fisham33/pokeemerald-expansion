DungeonRoom_Trainer_0::
# 11 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_MARCEL, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_0
# 12 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_1::
# 17 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_ALBERTO, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_1
# 18 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_2::
# 23 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_MARCEL, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_2
# 24 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_3::
# 29 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_MARCEL, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_3
# 30 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_OnDefeat_0::
# 39 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
	return


DungeonRoom_OnDefeat_1::
# 43 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
	return


DungeonRoom_OnDefeat_2::
# 47 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
	return


DungeonRoom_OnDefeat_3::
# 51 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_OnTrainerDefeated
	return


DungeonRoom_ExitTrigger::
# 59 "data/scripts/dungeon_rooms.pory"
	lock
# 60 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_CheckRoomCleared
# 61 "data/scripts/dungeon_rooms.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq DungeonRoom_ExitTrigger_2
DungeonRoom_ExitTrigger_1:
# 64 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_Text_NotCleared, MSGBOX_DEFAULT
# 65 "data/scripts/dungeon_rooms.pory"
	release
	return

DungeonRoom_ExitTrigger_2:
# 62 "data/scripts/dungeon_rooms.pory"
	goto DungeonRoom_DoAdvance
	goto DungeonRoom_ExitTrigger_1


DungeonRoom_DoAdvance::
# 69 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_AdvanceToNextRoom
# 70 "data/scripts/dungeon_rooms.pory"
	waitstate
# 71 "data/scripts/dungeon_rooms.pory"
	release
	return


DungeonRoom_Intro::
# 78 "data/scripts/dungeon_rooms.pory"
	.string "Let's battle!$"

DungeonRoom_Defeated::
# 82 "data/scripts/dungeon_rooms.pory"
	.string "I lost!$"

DungeonRoom_PostBattle::
# 86 "data/scripts/dungeon_rooms.pory"
	.string "That was a good fight.$"

DungeonRoom_Text_NotCleared::
# 90 "data/scripts/dungeon_rooms.pory"
	.string "You must defeat all the trainers\n"
	.string "in this room before proceeding!$"
