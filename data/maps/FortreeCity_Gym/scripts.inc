# 1 "data/maps/FortreeCity_Gym/scripts.pory"

# 2 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_MapScripts::
# 3 "data/maps/FortreeCity_Gym/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
# 4 "data/maps/FortreeCity_Gym/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
# 5 "data/maps/FortreeCity_Gym/scripts.pory"
	.byte 0
# 6 "data/maps/FortreeCity_Gym/scripts.pory"

# 7 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_OnTransition:
# 8 "data/maps/FortreeCity_Gym/scripts.pory"
	special RotatingGate_InitPuzzle
# 9 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_TEMP_HIDE_FOLLOWER @ Hide follower bc of rotating gates
# 10 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 11 "data/maps/FortreeCity_Gym/scripts.pory"

# 12 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_OnWarp:
# 13 "data/maps/FortreeCity_Gym/scripts.pory"
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
# 14 "data/maps/FortreeCity_Gym/scripts.pory"
	.2byte 0
# 15 "data/maps/FortreeCity_Gym/scripts.pory"

# 16 "data/maps/FortreeCity_Gym/scripts.pory"
@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_3
# 17 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_InitRotatingGates::
# 18 "data/maps/FortreeCity_Gym/scripts.pory"
	special RotatingGate_InitPuzzleAndGraphics
# 19 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 20 "data/maps/FortreeCity_Gym/scripts.pory"

# 21 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Winona::
# 22 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_selectmons TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_PostBattleHandler, 4
# 23 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 24 "data/maps/FortreeCity_Gym/scripts.pory"

# 25 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_PostBattleHandler::
# 26 "data/maps/FortreeCity_Gym/scripts.pory"
	@ VAR_RESULT contains battle outcome: 1 = win, 0 = loss
# 27 "data/maps/FortreeCity_Gym/scripts.pory"
	switch VAR_RESULT
# 28 "data/maps/FortreeCity_Gym/scripts.pory"
	case 1, FortreeCity_Gym_EventScript_WinonaWon
# 29 "data/maps/FortreeCity_Gym/scripts.pory"
	case 0, FortreeCity_Gym_EventScript_WhiteOut
# 30 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 31 "data/maps/FortreeCity_Gym/scripts.pory"

# 32 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_WinonaWon::
# 33 "data/maps/FortreeCity_Gym/scripts.pory"
	@ Check if first-time victory (badge not received yet)
# 34 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_unset FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_WinonaDefeated
# 35 "data/maps/FortreeCity_Gym/scripts.pory"
	@ Check for rematch
# 36 "data/maps/FortreeCity_Gym/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 37 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
# 38 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_AERIAL_ACE, FortreeCity_Gym_EventScript_GiveAerialAce2
# 39 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
# 40 "data/maps/FortreeCity_Gym/scripts.pory"
	release
# 41 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 42 "data/maps/FortreeCity_Gym/scripts.pory"

# 43 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_WhiteOut::
# 44 "data/maps/FortreeCity_Gym/scripts.pory"
	fadescreen FADE_TO_BLACK
# 45 "data/maps/FortreeCity_Gym/scripts.pory"
	special SetCB2WhiteOut
# 46 "data/maps/FortreeCity_Gym/scripts.pory"
	waitstate
# 47 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 48 "data/maps/FortreeCity_Gym/scripts.pory"

# 49 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_WinonaDefeated::
# 50 "data/maps/FortreeCity_Gym/scripts.pory"
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
# 51 "data/maps/FortreeCity_Gym/scripts.pory"
	waitmessage
# 52 "data/maps/FortreeCity_Gym/scripts.pory"
	call Common_EventScript_PlayGymBadgeFanfare
# 53 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
# 54 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_DEFEATED_FORTREE_GYM
# 55 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_BADGE06_GET
# 56 "data/maps/FortreeCity_Gym/scripts.pory"
	setvar VAR_0x8008, 6
# 57 "data/maps/FortreeCity_Gym/scripts.pory"
	call Common_EventScript_SetGymTrainers
# 58 "data/maps/FortreeCity_Gym/scripts.pory"
	call FortreeCity_Gym_EventScript_GiveAerialAce
# 59 "data/maps/FortreeCity_Gym/scripts.pory"
	closemessage
# 60 "data/maps/FortreeCity_Gym/scripts.pory"
	delay 30
# 61 "data/maps/FortreeCity_Gym/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 62 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
# 63 "data/maps/FortreeCity_Gym/scripts.pory"
	waitfanfare
# 64 "data/maps/FortreeCity_Gym/scripts.pory"
	closemessage
# 65 "data/maps/FortreeCity_Gym/scripts.pory"
	delay 30
# 66 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
# 67 "data/maps/FortreeCity_Gym/scripts.pory"
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
# 68 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
# 69 "data/maps/FortreeCity_Gym/scripts.pory"
	release
# 70 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 71 "data/maps/FortreeCity_Gym/scripts.pory"

# 72 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GiveAerialAce2::
# 73 "data/maps/FortreeCity_Gym/scripts.pory"
	giveitem ITEM_TM_TAILWIND
# 74 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 75 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
# 76 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
# 77 "data/maps/FortreeCity_Gym/scripts.pory"
	release
# 78 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 79 "data/maps/FortreeCity_Gym/scripts.pory"

# 80 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GiveAerialAce::
# 81 "data/maps/FortreeCity_Gym/scripts.pory"
	giveitem ITEM_TM_TAILWIND
# 82 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 83 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
# 84 "data/maps/FortreeCity_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_AERIAL_ACE
# 85 "data/maps/FortreeCity_Gym/scripts.pory"
	return
# 86 "data/maps/FortreeCity_Gym/scripts.pory"

# 87 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_WinonaRematch::
# 88 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
# 89 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
# 90 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 91 "data/maps/FortreeCity_Gym/scripts.pory"

# 92 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Jared::
# 93 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
# 94 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
# 95 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 96 "data/maps/FortreeCity_Gym/scripts.pory"

# 97 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Edwardo::
# 98 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
# 99 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
# 100 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 101 "data/maps/FortreeCity_Gym/scripts.pory"

# 102 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Flint::
# 103 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
# 104 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
# 105 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 106 "data/maps/FortreeCity_Gym/scripts.pory"

# 107 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Ashley::
# 108 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
# 109 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
# 110 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 111 "data/maps/FortreeCity_Gym/scripts.pory"

# 112 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Humberto::
# 113 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
# 114 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
# 115 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 116 "data/maps/FortreeCity_Gym/scripts.pory"

# 117 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_Darius::
# 118 "data/maps/FortreeCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
# 119 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
# 120 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 121 "data/maps/FortreeCity_Gym/scripts.pory"

# 122 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GymGuide::
# 123 "data/maps/FortreeCity_Gym/scripts.pory"
	lock
# 124 "data/maps/FortreeCity_Gym/scripts.pory"
	faceplayer
# 125 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
# 126 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
# 127 "data/maps/FortreeCity_Gym/scripts.pory"
	release
# 128 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 129 "data/maps/FortreeCity_Gym/scripts.pory"

# 130 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GymGuidePostVictory::
# 131 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
# 132 "data/maps/FortreeCity_Gym/scripts.pory"
	release
# 133 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 134 "data/maps/FortreeCity_Gym/scripts.pory"

# 135 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_LeftGymStatue::
# 136 "data/maps/FortreeCity_Gym/scripts.pory"
	lockall
# 137 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
# 138 "data/maps/FortreeCity_Gym/scripts.pory"
	goto FortreeCity_Gym_EventScript_GymStatue
# 139 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 140 "data/maps/FortreeCity_Gym/scripts.pory"

# 141 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_RightGymStatue::
# 142 "data/maps/FortreeCity_Gym/scripts.pory"
	lockall
# 143 "data/maps/FortreeCity_Gym/scripts.pory"
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
# 144 "data/maps/FortreeCity_Gym/scripts.pory"
	goto FortreeCity_Gym_EventScript_GymStatue
# 145 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 146 "data/maps/FortreeCity_Gym/scripts.pory"

# 147 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GymStatueCertified::
# 148 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
# 149 "data/maps/FortreeCity_Gym/scripts.pory"
	releaseall
# 150 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 151 "data/maps/FortreeCity_Gym/scripts.pory"

# 152 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_EventScript_GymStatue::
# 153 "data/maps/FortreeCity_Gym/scripts.pory"
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
# 154 "data/maps/FortreeCity_Gym/scripts.pory"
	releaseall
# 155 "data/maps/FortreeCity_Gym/scripts.pory"
	end
# 156 "data/maps/FortreeCity_Gym/scripts.pory"

# 157 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_GymGuideAdvice:
# 158 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Yo, how's it going, CHAMPION-\n"
# 159 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "bound {PLAYER}?\p"
# 160 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "FORTREE GYM LEADER WINONA is\n"
# 161 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "a master of FLYING-type POKéMON.\p"
# 162 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "She's waiting at the back of this GYM,\n"
# 163 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "behind the rotating doors.\p"
# 164 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "She's waiting for new challengers\n"
# 165 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "who are trying to take wing!\p"
# 166 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Okay, go for it!$"
# 167 "data/maps/FortreeCity_Gym/scripts.pory"

# 168 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_GymGuidePostVictory:
# 169 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You did it!\n"
# 170 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You've achieved liftoff!$"
# 171 "data/maps/FortreeCity_Gym/scripts.pory"

# 172 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_JaredIntro:
# 173 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Behold the elegant battle style of\n"
# 174 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "BIRD POKéMON!$"
# 175 "data/maps/FortreeCity_Gym/scripts.pory"

# 176 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_JaredDefeat:
# 177 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You…\n"
# 178 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You're strong…$"
# 179 "data/maps/FortreeCity_Gym/scripts.pory"

# 180 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_JaredPostBattle:
# 181 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "A TRAINER has to be smart to keep\n"
# 182 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "up with unexpected turns of events.\p"
# 183 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Do you have the smarts to get to\n"
# 184 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "our LEADER?$"
# 185 "data/maps/FortreeCity_Gym/scripts.pory"

# 186 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_EdwardoIntro:
# 187 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "The lovers of BIRD POKéMON aspire\n"
# 188 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "to join this GYM.\p"
# 189 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "As a member of the FORTREE GYM,\n"
# 190 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I'm not allowed to lose!$"
# 191 "data/maps/FortreeCity_Gym/scripts.pory"

# 192 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_EdwardoDefeat:
# 193 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "It was too much of a load for me\n"
# 194 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "to bear…$"
# 195 "data/maps/FortreeCity_Gym/scripts.pory"

# 196 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_EdwardoPostBattle:
# 197 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "The world is huge, and there are\n"
# 198 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "countless tough TRAINERS.\p"
# 199 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I'm going to keep training and make\n"
# 200 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "myself even stronger.$"
# 201 "data/maps/FortreeCity_Gym/scripts.pory"

# 202 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_FlintIntro:
# 203 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "There's no need for WINONA, our GYM\n"
# 204 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "LEADER, to deal with you!\p"
# 205 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I'm plenty good enough for you!$"
# 206 "data/maps/FortreeCity_Gym/scripts.pory"

# 207 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_FlintDefeat:
# 208 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA, I…\n"
# 209 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I lost!$"
# 210 "data/maps/FortreeCity_Gym/scripts.pory"

# 211 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_FlintPostBattle:
# 212 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA is cute and she's strong.\n"
# 213 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "She's the ultimate LEADER!\p"
# 214 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Blush…$"
# 215 "data/maps/FortreeCity_Gym/scripts.pory"

# 216 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_AshleyIntro:
# 217 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA taught me personally!\n"
# 218 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You can't beat me easily!$"
# 219 "data/maps/FortreeCity_Gym/scripts.pory"

# 220 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_AshleyDefeat:
# 221 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I was beaten…$"
# 222 "data/maps/FortreeCity_Gym/scripts.pory"

# 223 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_AshleyPostBattle:
# 224 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Thanks to WINONA, the people of\n"
# 225 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "FORTREE can live without fear.$"
# 226 "data/maps/FortreeCity_Gym/scripts.pory"

# 227 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_HumbertoIntro:
# 228 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "When WINONA takes to battle, her face\n"
# 229 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "shines with beautiful determination…\p"
# 230 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I'm not letting you witness that\n"
# 231 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "lovely sight!$"
# 232 "data/maps/FortreeCity_Gym/scripts.pory"

# 233 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_HumbertoDefeat:
# 234 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Urk!\n"
# 235 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I couldn't stop you.$"
# 236 "data/maps/FortreeCity_Gym/scripts.pory"

# 237 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_HumbertoPostBattle:
# 238 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You'd better watch it!\n"
# 239 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Don't get distracted staring at WINONA\l"
# 240 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "or you'll go crashing down in a heap!$"
# 241 "data/maps/FortreeCity_Gym/scripts.pory"

# 242 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_DariusIntro:
# 243 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You'd better know that there are all\n"
# 244 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "sorts of FLYING-type POKéMON.\p"
# 245 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You do know that, right?$"
# 246 "data/maps/FortreeCity_Gym/scripts.pory"

# 247 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_DariusDefeat:
# 248 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You seem to know your stuff!$"
# 249 "data/maps/FortreeCity_Gym/scripts.pory"

# 250 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_DariusPostBattle:
# 251 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Sure, you beat me all right.\n"
# 252 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "But you'd better watch it! Our LEADER\l"
# 253 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA's POKéMON are all business.$"
# 254 "data/maps/FortreeCity_Gym/scripts.pory"

# 255 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaIntro:
# 256 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I am WINONA. I am the LEADER of\n"
# 257 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the FORTREE POKéMON GYM.\p"
# 258 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I have become one with BIRD POKéMON\n"
# 259 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "and have soared the skies…\p"
# 260 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "However grueling the battle, we have\n"
# 261 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "triumphed with grace…\p"
# 262 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Witness the elegant choreography\n"
# 263 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "of BIRD POKéMON and I!$"
# 264 "data/maps/FortreeCity_Gym/scripts.pory"

# 265 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaDefeat:
# 266 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Never before have I seen a TRAINER\n"
# 267 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "command POKéMON with more grace\l"
# 268 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "than I…\p"
# 269 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "In recognition of your prowess,\n"
# 270 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I present to you this GYM BADGE.$"
# 271 "data/maps/FortreeCity_Gym/scripts.pory"

# 272 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_ReceivedFeatherBadge:
# 273 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "{PLAYER} received the FEATHER BADGE\n"
# 274 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "from WINONA.$"
# 275 "data/maps/FortreeCity_Gym/scripts.pory"

# 276 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
# 277 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "With the FEATHER BADGE, all POKéMON up\n"
# 278 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "to LV 70, even those received through\l"
# 279 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "trades, will obey your every command.\p"
# 280 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You will also be able to use\n"
# 281 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the HM move FLY outside of battle.\p"
# 282 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "And this…\n"
# 283 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "This is a gift from me.$"
# 284 "data/maps/FortreeCity_Gym/scripts.pory"

# 285 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_ExplainAerialAce:
# 286 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "TM52 contains TAILWIND.\p"
# 287 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "It increases the speed of your team\n"
# 288 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "temporarily. It can seriously turn\n"
# 289 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the tide of a battle.\p"
# 290 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "… … … … … …$"
# 291 "data/maps/FortreeCity_Gym/scripts.pory"

# 292 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_RegisteredWinona:
# 293 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Registered GYM LEADER WINONA\n"
# 294 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "in the POKéNAV.$"
# 295 "data/maps/FortreeCity_Gym/scripts.pory"

# 296 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaPostBattle:
# 297 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Though I fell to you, I will remain\n"
# 298 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "devoted to BIRD POKéMON.$"
# 299 "data/maps/FortreeCity_Gym/scripts.pory"

# 300 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_GymStatue:
# 301 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "FORTREE CITY POKéMON GYM$"
# 302 "data/maps/FortreeCity_Gym/scripts.pory"

# 303 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_GymStatueCertified:
# 304 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "FORTREE CITY POKéMON GYM\p"
# 305 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA'S CERTIFIED TRAINERS:\n"
# 306 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "{PLAYER}$"
# 307 "data/maps/FortreeCity_Gym/scripts.pory"

# 308 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaPreRematch:
# 309 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA: We humans can never escape\n"
# 310 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "gravity's pull on the ground.\p"
# 311 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "But by striving for excellence,\n"
# 312 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "we have the power to soar!\p"
# 313 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You have scaled the pinnacle as\n"
# 314 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the reigning CHAMPION.\p"
# 315 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Please, allow me to see your power\n"
# 316 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "at full flight!$"
# 317 "data/maps/FortreeCity_Gym/scripts.pory"

# 318 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaRematchDefeat:
# 319 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I failed to reach your height again…$"
# 320 "data/maps/FortreeCity_Gym/scripts.pory"

# 321 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaPostRematch:
# 322 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA: Even though I have lost,\n"
# 323 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the wings of my heart remain unbroken.\p"
# 324 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I can rise and soar again and\n"
# 325 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "yet again.\p"
# 326 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "I am convinced of it!$"
# 327 "data/maps/FortreeCity_Gym/scripts.pory"

# 328 "data/maps/FortreeCity_Gym/scripts.pory"
FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
# 329 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "WINONA: We humans can never escape\n"
# 330 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "gravity's pull on the ground.\p"
# 331 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "But by striving for excellence,\n"
# 332 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "we have the power to soar!\p"
# 333 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "You have scaled the pinnacle as\n"
# 334 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "the reigning CHAMPION.\p"
# 335 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Please, allow me to see your power\n"
# 336 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "at full flight!\p"
# 337 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Oh, no… Do you have but one\n"
# 338 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "POKéMON with you?\p"
# 339 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "Please return with two POKéMON\n"
# 340 "data/maps/FortreeCity_Gym/scripts.pory"
	.string "at the very least.$"
