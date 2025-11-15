# Pokemon Overworld Features Analysis
## pokeemerald-expansion Implementation Guide

This document catalogs overworld features introduced across Pokemon generations that add depth, replayability, and extend existing game systems. Each entry includes implementation details specific to pokeemerald-expansion.

---

## Generation 2 (Gold/Silver/Crystal)

### Headbutt Trees
**Description:** Special trees that can be headbutted to trigger wild Pokemon encounters. Different trees have different encounter tables, with some trees being "rare" trees that spawn better Pokemon. Creates exploration incentive and location-specific encounters.

**pokeemerald-expansion Elements:**
- Map event scripting system (`src/scrcmd.c`)
- Custom encounter type in wild encounter system (`src/wild_encounter.c`, `src/data/wild_encounters.json`)
- Field move system for Headbutt trigger
- Map-specific flags to track tree IDs and states
- Metatile behavior system to mark headbuttable trees

**Difficulty:** Medium
- Requires adding new encounter type to JSON wild encounters
- Need to create field move handler similar to Rock Smash
- Map editing to mark appropriate trees
- Encounter table design per location

---

### Apricorns & Kurt's Ball Crafting
**Description:** Collectible fruits that grow on trees and can be crafted into special Poke Balls with unique effects. Time-gated crafting system (one ball per day) adds resource management depth.

**pokeemerald-expansion Elements:**
- Berry system as base (`src/berry.c`) - can be adapted for apricorn trees
- Time-based events system (`src/time_events.c`, RTC support)
- Item system (`src/data/items.h`) for apricorn items and special balls
- Event scripting for NPC crafting dialogue
- Flag/variable system to track crafting requests and timers

**Difficulty:** Medium-High
- Adapt berry system for apricorns (different growth, no mutations)
- Create crafting recipes data structure
- Implement time-based crafting queue
- Design special ball items and effects
- NPC dialogue scripting with time checks

---

### Bug Catching Contest
**Description:** Timed competitive event where players catch Bug-type Pokemon to win prizes based on rarity/size. Adds mini-game variety and social competition element.

**pokeemerald-expansion Elements:**
- Special battle format system (`src/data/battle_frontier/`)
- Timer system using time events
- Custom wild encounter tables for contest area
- Scoring system using flags/variables
- Item reward system
- NPC dialogue and event scripting

**Difficulty:** Medium-High
- Create timer UI overlay
- Implement Pokemon scoring algorithm (size, rarity, level)
- Special encounter mode that allows catching
- Prize distribution system
- Save state management (temporary party storage)
- NPC competitor simulation (optional)

---

## Generation 3 (Ruby/Sapphire/Emerald)

### Secret Bases
**Description:** Customizable player hideouts in specific locations. Players can decorate with furniture and share via link cable. Provides personalization and collection goals.

**pokeemerald-expansion Elements:**
- Map system for base locations (`data/maps/`)
- Metatile behavior for secret spots
- Item system for decorations
- Save data structure for base state
- Object placement system
- Event scripting for base entry/editing

**Difficulty:** High
- Map editor interface for furniture placement
- Save data expansion for multiple bases
- Decoration inventory system
- Collision detection for placed objects
- Graphics for furniture items
- Multiplayer base sharing (if desired)

---

### Battle Frontier
**Description:** Post-game facility with seven unique battle challenges, each with different rules and mechanics. Provides extensive endgame content and variety.

**pokeemerald-expansion Elements:**
- Already implemented! (`src/data/battle_frontier/`)
- Battle Tower, Battle Dome, Battle Factory, Battle Pike, Battle Pyramid, Battle Arena, Battle Palace
- Trainer pools and battle rules system
- Battle points (BP) currency
- Prize exchange system

**Difficulty:** Already Complete
- Battle Frontier is fully implemented in pokeemerald-expansion
- Customization involves trainer/Pokemon pools and rewards

---

### PokeBlock Blending
**Description:** Mini-game where berries are blended to create PokeBlocks for Pokemon Contests. Adds berry utility and Contest stat building.

**pokeemerald-expansion Elements:**
- Berry system (`src/berry.c`)
- Item system for PokeBlock items
- Contest stats system (if Contests are implemented)
- NPC system for multiplayer blending simulation
- Mini-game scripting

**Difficulty:** Medium
- Create blending algorithm (berry combinations)
- PokeBlock stat calculation
- Mini-game UI (timing/rhythm mechanic)
- PokeBlock case inventory
- Integration with Contest system (if present)

---

## Generation 4 (Diamond/Pearl/Platinum/HeartGold/SoulSilver)

### The Underground
**Description:** Expansive underground network for mining, base building, and multiplayer mini-games. Provides fossil/evolution stone acquisition and social gameplay.

**pokeemerald-expansion Elements:**
- Custom map system for underground areas
- Mining mini-game mechanics
- Secret base system (adapted from Gen 3)
- Item discovery system
- Multiplayer flag capture (optional)
- Treasure/sphere item system

**Difficulty:** Very High
- Complex mini-map system
- Mining game UI and mechanics
- Underground item spawn system
- Fossil/treasure data tables
- Network of connected underground maps
- Radar for treasure detection

---

### Swarming Pokemon
**Description:** Daily rotating swarm of rare Pokemon in specific routes. Adds daily check-in incentive and controlled rarity.

**pokeemerald-expansion Elements:**
- Time-based events system (`src/time_events.c`)
- Wild encounter system (`src/wild_encounter.c`)
- Flag/variable system for daily swarm tracking
- NPC dialogue system for swarm reports
- Random number generation for swarm selection

**Difficulty:** Low-Medium
- Daily event handler to select swarm Pokemon/location
- Temporary encounter table modification
- NPC dialogue hooks
- Swarm pool data structure
- Simple flag reset system

---

### Honey Trees
**Description:** Trees that can be coated with honey to attract rare Pokemon after a time delay. Creates anticipation and return-visit gameplay.

**pokeemerald-expansion Elements:**
- Berry tree system as base (`src/berry.c`)
- Time-based events for delay timers
- Custom encounter system
- Metatile behavior for honey trees
- Item system for Honey item
- Map-specific tree tracking

**Difficulty:** Medium
- Adapt berry tree structure for honey state
- Timer system for encounter spawning (6 hours typically)
- Encounter table per tree rarity (common/rare)
- Tree shake animation
- Honey consumption mechanics
- Munchlax rarity system (if desired)

---

### Amity Square
**Description:** Walking park where specific "cute" Pokemon can follow the player. Provides happiness/friendship building and casual gameplay.

**pokeemerald-expansion Elements:**
- Follower system (`src/follower_npc.c`, `src/follower_helper.c`) - already implemented!
- Map boundaries for specific area
- Pokemon eligibility checking
- Hidden item spawning based on steps
- Happiness increase mechanics

**Difficulty:** Low
- Follower system already exists in expansion
- Implement species whitelist check
- Map boundary detection
- Step counter for item spawns
- Simple happiness modification

---

### Pokemon Following (HGSS)
**Description:** First partner Pokemon follows player in overworld with unique interactions. Major feature that enhances bonding and immersion.

**pokeemerald-expansion Elements:**
- Already implemented! (`src/follower_npc.c`)
- Complete HGSS-style follower system
- Bobbing animations, Pokeball emergence
- Weather form changes
- Interaction dialogue system
- Map-specific restrictions

**Difficulty:** Already Complete
- Follower system is fully implemented
- Customization involves dialogue and restrictions
- Configuration: `include/config/follower_npc.h`

---

### Poffin Cooking
**Description:** Cooking mini-game to create Poffins from berries for Contest stat raising. Similar to PokeBlocks but with different mechanics.

**pokeemerald-expansion Elements:**
- Berry system
- Item system for Poffin items
- Contest stats (if implemented)
- Mini-game scripting system
- Timing/input mechanics

**Difficulty:** Medium
- Cooking mini-game UI (stirring mechanic)
- Berry combination algorithm
- Poffin quality calculation
- Smoothness/flavor stat system
- Poffin case inventory

---

## Generation 5 (Black/White/Black2/White2)

### Seasonal System
**Description:** Game world changes appearance and encounters based on real-world months. Adds temporal variety and reason to revisit areas.

**pokeemerald-expansion Elements:**
- Time events system (`src/time_events.c`, RTC)
- Wild encounter system with seasonal tables
- Tileset/palette swapping system
- Map loading system
- Month tracking via RTC

**Difficulty:** Very High
- Seasonal tileset variants (x4 per tileset)
- Palette modification system
- Encounter table expansion for seasons
- Map script integration for season checks
- Form change handling (Deerling/Sawsbuck)
- Seasonal NPC/item changes

---

### Hidden Grotto
**Description:** Hidden areas with guaranteed encounters, often with hidden abilities or rare items. Regenerates after many steps.

**pokeemerald-expansion Elements:**
- Map event system
- Metatile behavior for hidden entrances
- Special encounter system
- Step counter
- Flag system for grotto state tracking
- Hidden ability system (already supported)

**Difficulty:** Medium
- Grotto entrance detection
- Step counter implementation
- Special encounter tables (HA Pokemon, items)
- Regeneration timer (256 steps typically)
- Location-specific loot tables
- Visibility toggle based on discovery

---

### Abyssal Ruins
**Description:** Underwater dungeon with time limit per visit. Features ancient items and requires multiple visits to fully explore.

**pokeemerald-expansion Elements:**
- Map system for dungeon
- Timer system
- Item placement with flag tracking
- Dive mechanic integration
- Event scripting for forced exit
- Translation puzzle mechanics (optional)

**Difficulty:** Medium-High
- Dungeon map design
- Oxygen/timer UI
- Floor transition system
- Collectible tracking across visits
- Forced warp on timer expiration
- Puzzle mechanics for item access

---

### Join Avenue
**Description:** Social hub that develops based on visitor interactions. Shops improve with use, providing services and items.

**pokeemerald-expansion Elements:**
- Map for avenue location
- NPC system with dynamic shops
- Popularity ranking system
- Item shop system
- Service mechanics (stat boosts, salon)
- Visitor simulation system

**Difficulty:** High
- Dynamic shop generation
- Popularity point tracking
- Shop upgrade system
- Multiple shop types (antique, florist, cafe, salon, dojo)
- NPC rotation system
- Service scripting (stat changes, rare items)

---

### Pokemon World Tournament
**Description:** Battle facility where players face past gym leaders and champions. Provides nostalgia and challenging battles.

**pokeemerald-expansion Elements:**
- Battle Frontier system as base
- Trainer data structures
- Tournament bracket system
- Trainer pool system
- Battle rules configuration
- Reward system (BP)

**Difficulty:** Medium-High
- Tournament bracket UI
- Famous trainer recreation (teams, dialogue)
- Progressive difficulty tiers
- Rental Pokemon option (optional)
- BP reward calculation
- Tournament save state

---

## Generation 6 (X/Y/Omega Ruby/Alpha Sapphire)

### Friend Safari
**Description:** Post-game area where encounter tables are based on friend codes. Each "friend" provides 3 Pokemon of specific type. Adds collection trading incentive.

**pokeemerald-expansion Elements:**
- Map with multiple zone instances
- Encounter system with dynamic tables
- Friend code simulation (NPC list or RNG-based)
- Hidden ability guarantee system
- Type-specific encounter pools
- Save data for safari unlocks

**Difficulty:** High
- Friend simulation system
- Dynamic encounter table generation
- Type-based Pokemon pools (3 per type)
- Progressive unlock system (2 Pokemon → 3 after Elite Four)
- Hidden ability guarantee for 3rd slot
- Safari zone data structure

---

### Berry Fields (Advanced Berry Mechanics)
**Description:** Expanded berry farming with mutations, pests that reduce yield, and fertilizer system for enhanced growth.

**pokeemerald-expansion Elements:**
- Already implemented! (`src/berry.c`)
- XY berry mechanics with mutations
- Pest system (Wingull attacks)
- Mulch/fertilizer system
- Moisture tracking and watering
- 6-stage growth option
- Configuration: `include/config/overworld.h` (lines 33-45)

**Difficulty:** Already Complete
- Berry mutations already implemented
- Pest mechanics exist
- Mulch system functional
- Configurable via config flags

---

### Restaurants & Cafés
**Description:** Battle challenges with entry fees and larger rewards. Rotation, Triple battles, and special conditions provide variety and money-making opportunities.

**pokeemerald-expansion Elements:**
- Special battle format system
- Money calculation system
- Trainer battle system
- Rotation/Triple battle mechanics
- Item reward system
- Daily reset flags

**Difficulty:** Medium
- Restaurant menu UI (battle selection)
- Special trainer pools
- Prize money calculation (entry fee vs. reward)
- Rotation/Triple battle setup
- Daily participation tracking
- Themed restaurants (type-specific, format-specific)

---

### Soaring (Sky Exploration)
**Description:** Fly on Mega Latios/Latias to explore map freely and encounter legendary Pokemon in the sky.

**pokeemerald-expansion Elements:**
- Custom flight movement system
- Overworld map navigation
- Aerial encounter system
- Mega Evolution system (already supported)
- Mirage spot system
- Sky map layer

**Difficulty:** Very High
- Free-flight controls and physics
- Aerial overworld rendering
- Sky-specific encounters
- Mirage spot spawn system
- Landing mechanics
- Camera system for flight view

---

### DexNav
**Description:** Device to track Pokemon in area, revealing hidden Pokemon with egg moves, hidden abilities, or high IVs. Chain for better rewards.

**pokeemerald-expansion Elements:**
- Already implemented! (`src/dexnav.c`)
- Hidden Pokemon detection
- Egg move/ability/IV preview
- Search level system
- Chain streak mechanics
- Sneaking movement
- Configuration: `include/config/dexnav.h`

**Difficulty:** Already Complete
- Full DexNav implementation exists
- Chaining mechanics functional
- Pokemon detection and info display working
- Customizable settings available

---

### Area Nav - Trainer's Eye
**Description:** Map feature showing which trainers are ready for rematches, with visual indicators on the map.

**pokeemerald-expansion Elements:**
- VS Seeker system (`src/vs_seeker.c`) as base
- Region map system
- Trainer flag tracking
- Map popup system
- Trainer rematch system
- Visual indicator system

**Difficulty:** Medium
- Map overlay for trainer locations
- Rematch eligibility tracking
- Integration with VS Seeker or standalone
- Visual indicator sprites
- Trainer position data
- Call/notification system

---

### O-Powers
**Description:** Temporary buffs that players can activate and share. Includes stat boosts, capture boosts, money/EXP multipliers.

**pokeemerald-expansion Elements:**
- Menu system
- Temporary buff flag system
- Battle stat modification
- Experience calculation hooks
- Money calculation hooks
- Timer system for duration

**Difficulty:** Medium-High
- O-Power menu UI
- Power Point (PP) energy system
- Duration timers
- Multiple buff types (8+ powers)
- Level system per power
- Battle integration for stat boosts
- EXP/money calculation hooks

---

## Generation 7 (Sun/Moon/Ultra Sun/Ultra Moon)

### Zygarde Cells & Cores
**Description:** 100 collectible cells scattered across the region that combine to form/power up Zygarde. Provides exploration goals and collection challenge.

**pokeemerald-expansion Elements:**
- Map object system for cell placement
- Flag array for 100+ cells
- Item collection system
- NPC assembly service
- Zygarde form change mechanics
- Completion tracking UI

**Difficulty:** Medium
- 100 cell locations designed
- Collection flag system (100 bits)
- Assembly NPC script
- Form change mechanics (50%/100%)
- Collection tracker UI
- Cell sprite and placement

---

### Berry Trees (Palm Trees/Crabrawler)
**Description:** Tall berry trees with berry piles that attract Crabrawler. Different interaction than standard berries.

**pokeemerald-expansion Elements:**
- Berry system variant
- Special encounter trigger
- Tree shaking mechanic
- Berry pile visual
- Guaranteed encounter system

**Difficulty:** Low-Medium
- Palm tree metatile behavior
- Shake trigger script
- Crabrawler encounter (100% rate)
- Berry pile item generation
- Visual feedback (shaking animation)

---

### Ultra Wormholes
**Description:** Mini-game where players fly through space to find legendary Pokemon and rare encounters. Difficulty affects shiny rate.

**pokeemerald-expansion Elements:**
- Custom mini-game system
- Special encounter tables
- Legendary Pokemon spawning
- Shiny rate modification
- Warp system to special maps
- Score/distance tracking

**Difficulty:** Very High
- Flying mini-game mechanics
- Wormhole spawning algorithm
- Distance/score tracking
- Rarity tier system
- Shiny rate modification
- Special encounter maps
- Multiple legendary pools

---

### SOS Battles
**Description:** Wild Pokemon can call for help, creating 2v1 battles. Chaining call-outs increases shiny rate and guarantees hidden abilities.

**pokeemerald-expansion Elements:**
- Battle system modification
- Wild battle AI enhancement
- Call for help mechanic
- Chain counter system
- Hidden ability guarantee
- Shiny rate modification
- Adrenaline Orb item

**Difficulty:** High
- Battle system changes for 2v1
- Call for help AI decision
- Chain tracking during battle
- Hidden ability enforcement
- Shiny rate calculation
- Help call success rates
- Ally species tables

---

### Totem Stickers
**Description:** 100 collectible stickers hidden throughout the region. Collecting them unlocks Totem-sized Pokemon rewards.

**pokeemerald-expansion Elements:**
- Similar to Zygarde Cells
- Hidden object system
- Flag array for collection
- Size modification system
- Reward distribution NPC
- Collection UI

**Difficulty:** Medium
- 100 sticker locations
- Collection flag tracking
- Totem-sized Pokemon system (scale modifier)
- Reward tier system
- Collection counter UI
- Sticker sprites/objects

---

### Festival Plaza
**Description:** Online hub with mini-games, shops, and facilities that improve with rank. Provides services like rare items and training.

**pokeemerald-expansion Elements:**
- Similar to Join Avenue
- Facility system
- Rank progression
- Festival Coins currency
- Service shops
- Mini-game integration

**Difficulty:** Very High
- Hub map design
- Facility system (Fortune Teller, Dye Shop, Haunted House, etc.)
- Rank point accumulation
- Festival Coin economy
- Multiple mini-games
- Shop inventory system
- Visitor NPC simulation

---

### Poké Pelago
**Description:** Island resort where boxed Pokemon can gather items, train, and develop. Idle game mechanics provide passive benefits.

**pokeemerald-expansion Elements:**
- Island maps (optional)
- Box access system
- Time-based events
- Item generation system
- EXP/EV training automation
- Berry growing
- Bean currency

**Difficulty:** High
- Island progression system
- Automated training calculations
- Item spawn tables
- Time-based completion
- Pokemon assignment UI
- Box integration
- Bean collection mechanics
- 5 different island types

---

## Generation 8 (Sword/Shield)

### Max Raid Dens/Battles
**Description:** Co-op battles against Dynamax Pokemon with special rules. Provide guaranteed high IV Pokemon and rare rewards.

**pokeemerald-expansion Elements:**
- Dynamax system (already supported in expansion)
- Special battle format
- Den location system
- Star rating difficulty
- Item reward pools
- Raid Pokemon data tables
- NPC ally simulation

**Difficulty:** Very High
- Den spawn system
- 4v1 battle mechanics
- Dynamax integration
- Shield breaking mechanics
- Time limit system
- NPC partner AI
- Rare beam system (5-star)
- Gigantamax encounters
- Extensive reward tables

---

### Dynamax Adventures
**Description:** Roguelike dungeon where players use rental Pokemon to battle through series of Dynamax encounters, ending with legendary Pokemon.

**pokeemerald-expansion Elements:**
- Dynamax system
- Rental Pokemon system (Battle Factory-like)
- Dungeon generation
- Path selection system
- Legendary encounter pools
- Endless mode tracking
- Scientist NPC services

**Difficulty:** Very High
- Procedural path generation
- Rental Pokemon pools
- Progressive difficulty
- Path choice system
- Legendary encounter guarantee
- Run tracking
- Scientist shop (HP heal, ability change)
- Shiny charm implementation
- Ore currency

---

### Cram-o-matic (Item Crafting)
**Description:** Machine that combines 4 items to create new items. Recipe system adds experimentation and item utility.

**pokeemerald-expansion Elements:**
- Item system
- Recipe data structure
- Crafting UI
- Item consumption
- Recipe discovery tracking
- Point calculation system

**Difficulty:** Medium-High
- Recipe database (100+ combinations)
- Point value per item
- Item type categorization
- Crafting algorithm
- Output determination
- UI for item selection
- Recipe hints/tracking (optional)

---

### Restricted Sparring
**Description:** Training battles with rentals or specific rules. Provides battle practice and rewards without risk.

**pokeemerald-expansion Elements:**
- Battle Frontier system
- Rental Pokemon
- Restricted format battles
- Battle Tower rules
- Reward system

**Difficulty:** Low-Medium
- Rental Pokemon pools
- Battle restrictions (type, species, tier)
- NPC trainer pools
- Reward calculation
- Multiple restriction modes

---

### Curry Cooking
**Description:** Camping mini-game where players cook curry for benefits. Cooking quality affects EXP, friendship, and healing.

**pokeemerald-expansion Elements:**
- Mini-game system
- Berry/ingredient item system
- Cooking quality algorithm
- Party healing mechanics
- Friendship modification
- EXP bonus application
- Recipe collection

**Difficulty:** High
- Cooking mini-game UI (fanning, stirring)
- 151 curry recipes
- Ingredient combination system
- Quality tier calculation
- Visual feedback (cooking animation)
- Curry dex tracking
- Stat bonus application
- Party screen integration

---

### Camping
**Description:** Set up camp to interact with Pokemon, play mini-games, and cook curry. Enhances bonding and provides healing.

**pokeemerald-expansion Elements:**
- Camp map/instance
- Pokemon interaction system
- Toy items (Poke Toy, Feather Wand)
- Curry cooking integration
- Friendship increase
- Party healing
- Animation system

**Difficulty:** Medium-High
- Camp map instance
- Pokemon roaming behavior
- Interaction responses per species
- Toy item mechanics
- Curry integration
- Camera controls (optional)
- Expression/animation system

---

### Digging Duo
**Description:** NPC service where players pay to have items excavated. Stamina-based system provides rare items and fossils.

**pokeemerald-expansion Elements:**
- NPC service system
- Random item generation
- Weighted loot tables
- Money consumption
- Fossil items
- Evolution stones

**Difficulty:** Low
- Simple NPC dialogue script
- Loot table with weights
- Money check and deduction
- Item generation (1-30 items per session)
- Stamina simulation (brother variation)
- Fossil/rare item pool

---

### Watt Traders
**Description:** NPCs that rotate daily, trading Watts currency for rare items, Pokemon, or TRs.

**pokeemerald-expansion Elements:**
- Daily reset system
- Currency system (Watts)
- NPC shop rotation
- Wishing Piece items
- Item/Pokemon rewards
- Location-based traders

**Difficulty:** Medium
- Watt currency implementation
- Daily shop rotation
- Multiple trader locations
- TR/item/Pokemon pools
- Wishing Piece mechanics
- Price scaling

---

## Generation 9 (Scarlet/Violet)

### Tera Raid Battles
**Description:** Evolution of Max Raids with Terastallization. Star ratings determine difficulty and rewards.

**pokeemerald-expansion Elements:**
- Terastallization system (already supported)
- Raid battle system (adapt from Max Raids)
- Den crystal locations
- Star rating system
- Tera Shard rewards
- Time limit mechanics

**Difficulty:** Very High
- Similar to Max Raids complexity
- Terastallization integration
- Shield/timer mechanics
- 7-star raid system
- Tera Shard currency
- Ability Patch/Capsule rewards
- Herba Mystica items
- Event raid system

---

### Gimmighoul Coins
**Description:** 999 collectible coins scattered across the world. Collecting enough allows Gimmighoul to evolve.

**pokeemerald-expansion Elements:**
- Item collection system
- Coin object placement
- High-capacity counter (999)
- Evolution requirement system
- Respawning coins (optional)
- Collection UI

**Difficulty:** Medium
- 999 coin locations designed
- Stack counter (up to 999)
- Map object placement
- Evolution check integration
- Collection tracking
- Respawn timer (optional)
- Coin chest objects

---

### Item Printer (Crafting System)
**Description:** Gacha-style machine that prints items using materials. Bonus ball system adds strategic depth.

**pokeemerald-expansion Elements:**
- Material currency system
- Gacha algorithm
- Bonus ball system
- Item rarity tiers
- Print job queue
- Rare item pool

**Difficulty:** High
- Material collection/currency
- Gacha pull algorithm
- Bonus ball accumulation
- Rarity tier system (1-5 stars)
- Animation/UI for printing
- Extensive item pool
- Material cost scaling

---

### Sandwiches & Picnics
**Description:** Evolved camping system with sandwich crafting. Different ingredients provide temporary buffs (encounter rate, shiny rate, EXP, etc.).

**pokeemerald-expansion Elements:**
- Picnic map instance
- Ingredient item system
- Recipe/freeform crafting
- Buff duration system
- Encounter rate modification
- Shiny rate modification
- EXP boost
- Type-specific encounter boost

**Difficulty:** Very High
- Picnic map setup
- Ingredient system (80+ ingredients)
- Sandwich building mini-game
- Recipe database
- Buff calculation algorithm
- Multiple buff types simultaneously
- Duration timer (30 minutes typically)
- Encounter/shiny rate hooks
- Egg power for breeding
- Visual sandwich building

---

### Let's Go Auto-Battles
**Description:** Lead Pokemon can auto-battle wild Pokemon in overworld. Provides passive EXP and item farming.

**pokeemerald-expansion Elements:**
- Overworld encounter system
- Auto-battle AI
- EXP calculation
- Item drop system
- Simultaneous encounters
- Pokemon health tracking

**Difficulty:** Very High
- Overworld Pokemon AI
- Auto-battle calculation
- EXP distribution
- Item drop determination
- Multi-target engagement
- Health depletion without battle screen
- Return to ball on faint
- Level disparity handling

---

### Stake Collection (Legendary Unlocks)
**Description:** Collect colored stakes to break seals on legendary Pokemon shrines. Creates exploration-based legendary encounters.

**pokeemerald-expansion Elements:**
- Collectible object system
- Color-coded flags (4 colors x 8 stakes = 32)
- Shrine location maps
- Legendary encounter triggers
- Collection UI
- Seal-breaking cutscene

**Difficulty:** Medium
- 32 stake locations designed
- Collection flag tracking (32 bits)
- Four shrine locations
- Seal status checking
- Legendary encounter triggers (Wo-Chien, Chien-Pao, Ting-Lu, Chi-Yu)
- Visual seal effects
- Collection counter per color

---

### Academy Classes
**Description:** Multiple-choice quiz system that provides rewards and lore. Creates educational content and item rewards.

**pokeemerald-expansion Elements:**
- Quiz system
- NPC teacher dialogue
- Question database
- Answer checking
- Progressive unlocks
- Item rewards
- Flag tracking for completion

**Difficulty:** Low-Medium
- Question/answer database
- Quiz UI
- Multiple teachers (6+ subjects)
- Progressive class unlocks
- Midterm/Final exams
- Item rewards per completion
- Completion flags
- Answer validation

---

### Tera Type Hunting
**Description:** Wild Pokemon have random Tera types. Specific Tera types can be found more commonly in certain areas, encouraging hunting.

**pokeemerald-expansion Elements:**
- Terastallization system (already supported)
- Wild Pokemon generation
- Tera Type randomization
- Location-based Tera Type weighting
- Tera Type display in battle

**Difficulty:** Medium
- Random Tera Type assignment
- Location-based biases
- Tera Type storage in Pokemon data
- Visual indicators
- Integration with existing Tera system

---

## Additional Notable Features

### VS Seeker (Gen 4/remakes)
**Description:** Device that detects trainers ready for rematches. Rechargeable via steps.

**pokeemerald-expansion Elements:**
- Already implemented! (`src/vs_seeker.c`)
- Trainer rematch system
- Step counter for recharge
- Visual indicators for ready trainers
- Level scaling

**Difficulty:** Already Complete
- Full VS Seeker implementation
- Trainer detection functional
- Rechargeable via steps

---

### Pokeathlon (HGSS)
**Description:** Sports mini-game competition with different events based on Pokemon stats. Provides variety and rewards.

**pokeemerald-expansion Elements:**
- Mini-game system
- Pokemon stat checking
- Multiple event types
- Scoring system
- Medal/point rewards
- Prize exchange

**Difficulty:** Very High
- 10 different mini-games
- Touch controls adaptation to buttons
- Team selection UI
- Competition AI
- Athlete point currency
- Prize shop
- Course rotation system

---

### Dream World/Dream Radar (Gen 5)
**Description:** External app integration that unlocks hidden ability Pokemon. Could be adapted as in-game system.

**pokeemerald-expansion Elements:**
- Hidden ability system (already supported)
- Special encounter method
- Dream World Pokemon pool
- Item rewards
- Sleep-based mechanics (optional)

**Difficulty:** High (if recreated in-game)
- Dream World map/instance
- Hidden ability Pokemon pool
- Mini-game or sleep timer
- Special items (Dream Balls)
- Integration with save file
- Berries/items collection

---

### Mantine Surf (USUM)
**Description:** Surfing mini-game between islands with score tracking. Provides BP rewards and transportation variety.

**pokeemerald-expansion Elements:**
- Custom surfing movement
- Trick/score system
- Beach scoring NPCs
- BP reward calculation
- Regional transportation

**Difficulty:** High
- Surfing physics and tricks
- Scoring algorithm
- UI for trick input
- Beach landing detection
- High score tracking
- BP reward tiers

---

## Implementation Priority Recommendations

### Quick Wins (Low-Medium Difficulty)
1. Swarming Pokemon - Daily variety with minimal new systems
2. Academy Classes - Content-heavy but simple mechanics
3. Digging Duo - Simple service NPC
4. Stake Collection - Collectathon with existing systems
5. Headbutt Trees - Simple custom encounter type

### High Value (Medium Difficulty)
1. Honey Trees - Time-based encounters with anticipation
2. Hidden Grotto - Exploration rewards with HA Pokemon
3. Zygarde Cells/Totem Stickers - Collection goals
4. Gimmighoul Coins - Large-scale collection
5. Area Nav/Trainer's Eye - QoL for rematches
6. Restaurants - Battle variety with rewards

### Major Features (High-Very High Difficulty)
1. Seasonal System - Massive visual/mechanical changes
2. Tera Raid Battles - Complex battle system expansion
3. Sandwiches - Comprehensive buff system with crafting
4. Cram-o-matic - Item crafting adds depth
5. Max Raid Dens - Co-op style battles
6. Item Printer - Gacha mechanics
7. Curry/Camping - Bonding and healing system

### Endgame Projects (Very High Difficulty)
1. The Underground - Massive subsystem
2. Soaring - Flight overworld mechanics
3. Dynamax Adventures - Roguelike dungeon crawler
4. Ultra Wormholes - Space flight mini-game
5. Let's Go Auto-Battles - Fundamental battle system change
6. Festival Plaza/Join Avenue - Social hub simulation

---

## Notes on pokeemerald-expansion Strengths

The expansion project already includes many modern Pokemon features:
- **Complete Gen 9 mechanics** (moves, abilities, items, Terastallization)
- **Battle gimmicks** (Mega Evolution, Z-Moves, Dynamax, Tera)
- **DexNav system** - Full implementation
- **Follower Pokemon** - HGSS-style complete
- **Advanced Berry System** - XY mechanics with mutations/pests
- **Battle Frontier** - All 7 facilities
- **VS Seeker** - Trainer rematches
- **Time/Day system** - RTC with configurable ratios
- **Comprehensive documentation** - Tutorials for major systems

This foundation makes many overworld features significantly easier to implement than building from scratch.

---

## Configuration Files Reference

Key configuration headers for feature toggles:
- `/home/user/pokeemerald-expansion/include/config/overworld.h` - Overworld features, berries, time, followers
- `/home/user/pokeemerald-expansion/include/config/battle.h` - Battle mechanics
- `/home/user/pokeemerald-expansion/include/config/general.h` - General settings
- `/home/user/pokeemerald-expansion/include/config/item.h` - Item behaviors
- `/home/user/pokeemerald-expansion/include/config/dexnav.h` - DexNav settings
- `/home/user/pokeemerald-expansion/include/config/follower_npc.h` - Follower configuration

---

*Document generated for pokeemerald-expansion project*
*Last updated: 2025-11-15*
