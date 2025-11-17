Common_DungeonBoss_ShowTrainerBoss::
# 20 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_TEMP_11
# 21 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_12
# 22 "data/scripts/DungeonBossRoom_Common.pory"
	goto Common_DungeonBoss_HideRewards
	return


Common_DungeonBoss_ShowPokemonBoss::
# 27 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_11
# 28 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_TEMP_12
# 29 "data/scripts/DungeonBossRoom_Common.pory"
	goto Common_DungeonBoss_HideRewards
	return


Common_DungeonBoss_HideRewards::
# 34 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_0
# 35 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_1
# 36 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_2
# 37 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_3
	return


Common_DungeonBoss_ShowRewards::
# 43 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_DUNGEON_TRAINER_0
# 44 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_DUNGEON_TRAINER_1
# 45 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_DUNGEON_TRAINER_2
# 46 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_DUNGEON_TRAINER_3
	return


Common_DungeonBoss_TrainerBattle::
# 55 "data/scripts/DungeonBossRoom_Common.pory"
	lockall
# 56 "data/scripts/DungeonBossRoom_Common.pory"
	faceplayer
# 57 "data/scripts/DungeonBossRoom_Common.pory"
	checkflag FLAG_DUNGEON_BOSS_DEFEATED
# 58 "data/scripts/DungeonBossRoom_Common.pory"
	goto_if_set FLAG_DUNGEON_BOSS_DEFEATED, Common_DungeonBoss_TrainerBattle_2
# 64 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossIntro
# 65 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 66 "data/scripts/DungeonBossRoom_Common.pory"
	closemessage
# 69 "data/scripts/DungeonBossRoom_Common.pory"
	special SaveSelectMonsParty
# 70 "data/scripts/DungeonBossRoom_Common.pory"
	fadescreen FADE_TO_BLACK
# 71 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_0x8004, 3
# 72 "data/scripts/DungeonBossRoom_Common.pory"
	special ChoosePartyForStandardBattle
# 73 "data/scripts/DungeonBossRoom_Common.pory"
	waitstate
# 74 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, 0
	goto_if_eq Common_DungeonBoss_TrainerBattle_5
# 80 "data/scripts/DungeonBossRoom_Common.pory"
	special ReducePlayerPartyToSelectedMons
# 81 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_0x8004, 2
# 82 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_0x8005, 4
# 83 "data/scripts/DungeonBossRoom_Common.pory"
	special CallFrontierUtilFunc
# 86 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_1, 1
# 87 "data/scripts/DungeonBossRoom_Common.pory"
	copyvar VAR_0x8004, VAR_DUNGEON_BOSS_TRAINER
# 88 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_SetupTrainerBattle
# 89 "data/scripts/DungeonBossRoom_Common.pory"
	waitstate
# 92 "data/scripts/DungeonBossRoom_Common.pory"
	special LoadSelectMonsParty
# 93 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_0x8004, 0
# 94 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_1, 0
# 95 "data/scripts/DungeonBossRoom_Common.pory"
	special GetBattleOutcome
# 96 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Common_DungeonBoss_TrainerBattle_8
# 101 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_2, 0
Common_DungeonBoss_TrainerBattle_7:
# 103 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonBoss_TrainerBattle_2:
# 59 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossDefeat
# 60 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 61 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonBoss_TrainerBattle_5:
# 75 "data/scripts/DungeonBossRoom_Common.pory"
	special LoadSelectMonsParty
# 77 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonBoss_TrainerBattle_8:
# 97 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_2, 1
	goto Common_DungeonBoss_TrainerBattle_7


Common_DungeonBoss_TrainerVictory::
# 108 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossVictory
# 109 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 110 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossDefeat
# 111 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 112 "data/scripts/DungeonBossRoom_Common.pory"
	closemessage
# 113 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_STARTING_STATUS_CONTROL, 0
# 114 "data/scripts/DungeonBossRoom_Common.pory"
	fadescreenspeed FADE_TO_BLACK, 8
# 115 "data/scripts/DungeonBossRoom_Common.pory"
	waitmessage
# 116 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_BOSS_DEFEATED
# 117 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_11
# 118 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_12
	return


Common_DungeonBoss_PokemonBattle::
# 127 "data/scripts/DungeonBossRoom_Common.pory"
	lock
# 128 "data/scripts/DungeonBossRoom_Common.pory"
	faceplayer
# 129 "data/scripts/DungeonBossRoom_Common.pory"
	checkflag FLAG_DUNGEON_BOSS_DEFEATED
# 130 "data/scripts/DungeonBossRoom_Common.pory"
	goto_if_set FLAG_DUNGEON_BOSS_DEFEATED, Common_DungeonBoss_PokemonBattle_2
# 136 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossIntro
# 137 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 138 "data/scripts/DungeonBossRoom_Common.pory"
	closemessage
# 139 "data/scripts/DungeonBossRoom_Common.pory"
	settotemboost 1, 1, 1, 1, 1, 1, 1, 1
# 140 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_StartBossPokemonBattle
# 141 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_SMART_WILD_POKEMON
# 142 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_NO_CATCHING
# 143 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_NO_RUNNING
# 144 "data/scripts/DungeonBossRoom_Common.pory"
	dowildbattle
# 145 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_SMART_WILD_POKEMON
# 146 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_NO_CATCHING
# 147 "data/scripts/DungeonBossRoom_Common.pory"
	clearflag FLAG_NO_RUNNING
# 148 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Common_DungeonBoss_PokemonBattle_5
# 163 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_2, 0
Common_DungeonBoss_PokemonBattle_4:
# 165 "data/scripts/DungeonBossRoom_Common.pory"
	release
	return

Common_DungeonBoss_PokemonBattle_2:
# 131 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossDefeat
# 132 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 133 "data/scripts/DungeonBossRoom_Common.pory"
	release
	return

Common_DungeonBoss_PokemonBattle_5:
# 149 "data/scripts/DungeonBossRoom_Common.pory"
	lock
# 150 "data/scripts/DungeonBossRoom_Common.pory"
	faceplayer
# 151 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRandomBossVictory
# 152 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox gStringVar4, MSGBOX_DEFAULT
# 153 "data/scripts/DungeonBossRoom_Common.pory"
	closemessage
# 154 "data/scripts/DungeonBossRoom_Common.pory"
	fadescreenspeed FADE_TO_BLACK, 8
# 155 "data/scripts/DungeonBossRoom_Common.pory"
	waitmessage
# 156 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_BOSS_DEFEATED
# 157 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_11
# 158 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_TEMP_12
# 159 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_STARTING_STATUS_CONTROL, 0
# 160 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_2, 1
	goto Common_DungeonBoss_PokemonBattle_4


Common_DungeonBoss_PokemonVictoryEnd::
# 170 "data/scripts/DungeonBossRoom_Common.pory"
	fadescreenspeed FADE_FROM_BLACK, 8
# 171 "data/scripts/DungeonBossRoom_Common.pory"
	waitmessage
	return


Common_DungeonReward_Bronze::
# 180 "data/scripts/DungeonBossRoom_Common.pory"
	lockall
# 181 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_0, 0
# 182 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRewardItem
# 183 "data/scripts/DungeonBossRoom_Common.pory"
	copyvar VAR_0x8000, VAR_0x8004
# 184 "data/scripts/DungeonBossRoom_Common.pory"
	checkitemspace VAR_0x8000
# 185 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Common_DungeonReward_Bronze_2
Common_DungeonReward_Bronze_1:
# 188 "data/scripts/DungeonBossRoom_Common.pory"
	giveitem VAR_0x8000
# 189 "data/scripts/DungeonBossRoom_Common.pory"
	bufferitemname STR_VAR_1, VAR_0x8000
# 190 "data/scripts/DungeonBossRoom_Common.pory"
	removeobject VAR_LAST_TALKED
# 191 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_0
# 192 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonReward_Bronze_2:
# 186 "data/scripts/DungeonBossRoom_Common.pory"
	goto Common_EventScript_ShowBagIsFull
	goto Common_DungeonReward_Bronze_1


Common_DungeonReward_Silver::
# 196 "data/scripts/DungeonBossRoom_Common.pory"
	lockall
# 197 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRewardTier
# 198 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, 2
	goto_if_lt Common_DungeonReward_Silver_2
# 203 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_0, 1
# 204 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRewardItem
# 205 "data/scripts/DungeonBossRoom_Common.pory"
	copyvar VAR_0x8000, VAR_0x8004
# 206 "data/scripts/DungeonBossRoom_Common.pory"
	checkitemspace VAR_0x8000
# 207 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Common_DungeonReward_Silver_5
Common_DungeonReward_Silver_4:
# 210 "data/scripts/DungeonBossRoom_Common.pory"
	giveitem VAR_0x8000
# 211 "data/scripts/DungeonBossRoom_Common.pory"
	bufferitemname STR_VAR_1, VAR_0x8000
# 212 "data/scripts/DungeonBossRoom_Common.pory"
	removeobject VAR_LAST_TALKED
# 213 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_1
# 214 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonReward_Silver_2:
# 199 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox Common_DungeonReward_Silver_Text_0, MSGBOX_DEFAULT
# 200 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	end

Common_DungeonReward_Silver_5:
# 208 "data/scripts/DungeonBossRoom_Common.pory"
	goto Common_EventScript_ShowBagIsFull
	goto Common_DungeonReward_Silver_4


Common_DungeonReward_Gold::
# 218 "data/scripts/DungeonBossRoom_Common.pory"
	lockall
# 219 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRewardTier
# 220 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, 3
	goto_if_lt Common_DungeonReward_Gold_2
# 225 "data/scripts/DungeonBossRoom_Common.pory"
	setvar VAR_TEMP_0, 2
# 226 "data/scripts/DungeonBossRoom_Common.pory"
	callnative Script_Dungeon_GetRewardItem
# 227 "data/scripts/DungeonBossRoom_Common.pory"
	copyvar VAR_0x8000, VAR_0x8004
# 228 "data/scripts/DungeonBossRoom_Common.pory"
	checkitemspace VAR_0x8000
# 229 "data/scripts/DungeonBossRoom_Common.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Common_DungeonReward_Gold_5
Common_DungeonReward_Gold_4:
# 232 "data/scripts/DungeonBossRoom_Common.pory"
	giveitem VAR_0x8000
# 233 "data/scripts/DungeonBossRoom_Common.pory"
	bufferitemname STR_VAR_1, VAR_0x8000
# 234 "data/scripts/DungeonBossRoom_Common.pory"
	removeobject VAR_LAST_TALKED
# 235 "data/scripts/DungeonBossRoom_Common.pory"
	setflag FLAG_DUNGEON_TRAINER_2
# 236 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	return

Common_DungeonReward_Gold_2:
# 221 "data/scripts/DungeonBossRoom_Common.pory"
	msgbox Common_DungeonReward_Gold_Text_0, MSGBOX_DEFAULT
# 222 "data/scripts/DungeonBossRoom_Common.pory"
	releaseall
	end

Common_DungeonReward_Gold_5:
# 230 "data/scripts/DungeonBossRoom_Common.pory"
	goto Common_EventScript_ShowBagIsFull
	goto Common_DungeonReward_Gold_4


Common_DungeonReward_Silver_Text_0:
# 199 "data/scripts/DungeonBossRoom_Common.pory"
	.string "This reward is locked.\nDefeat more trainers for Silver rank!$"

Common_DungeonReward_Gold_Text_0:
# 221 "data/scripts/DungeonBossRoom_Common.pory"
	.string "This reward is locked.\nDefeat all trainers for Gold rank!$"
