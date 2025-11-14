DungeonRoom_Trainer_0::
# 11 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_VICTOR, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_0
# 12 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_1::
# 17 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_VICTORIA, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_1
# 18 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_2::
# 23 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_VICKY, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_2
# 24 "data/scripts/dungeon_rooms.pory"
	msgbox DungeonRoom_PostBattle, MSGBOX_AUTOCLOSE
	end


DungeonRoom_Trainer_3::
# 29 "data/scripts/dungeon_rooms.pory"
	trainerbattle_single TRAINER_CLAUDE, DungeonRoom_Intro, DungeonRoom_Defeated, DungeonRoom_OnDefeat_3
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
	lockall
# 60 "data/scripts/dungeon_rooms.pory"
	callnative Script_Dungeon_PrepareNextRoom
# 61 "data/scripts/dungeon_rooms.pory"
	waitstate
# 62 "data/scripts/dungeon_rooms.pory"
	releaseall
	end


DungeonRoom_Intro::
# 70 "data/scripts/dungeon_rooms.pory"
	.string "Let's battle!$"

DungeonRoom_Defeated::
# 74 "data/scripts/dungeon_rooms.pory"
	.string "I lost!$"

DungeonRoom_PostBattle::
# 78 "data/scripts/dungeon_rooms.pory"
	.string "That was a good fight.$"

DungeonRoom_Text_NotCleared::
# 82 "data/scripts/dungeon_rooms.pory"
	.string "You must defeat all the trainers\n"
	.string "in this room before proceeding!$"
