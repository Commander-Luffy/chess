# Dual-Layer Board — Physical + Digital

*Two games on one clock. The military fights on the board. The tech companies fight in the shadow.*

## Layer 1: Physical Board (16×16)

Played by: **2 Generals (military)**

Contains:
- All physical pieces (pawns, knights, bishops, rooks, queens, hidden king)
- Territory (quadrants, center mine)
- Trade routes (visible paths between allied zones)
- Raid tracks (hidden until discovered)

### Governance: Status & Promotions

Military leaders rise through STATUS. Promotions are earned.
- Capturing enemy pieces = status points
- Protecting allies = status points
- Losing pieces = status loss
- Highest-status general commands → if a pawn earns enough status, it CAN challenge the general
- Failed challenge = pawn demoted. Successful = coup (new general, old general becomes pawn)

### Military Hidden Layer: THE NEWS

The News is to the General what the Church is to the Noble. Propaganda, narrative control, morale warfare.

Each general gets a SECRET action every turn (not visible to others):

| Action | Effect | Risk |
|---|---|---|
| Publish victory | Boost own troops morale (+5 all pieces) even if you lost | If exposed as false: massive morale crash |
| Smear opponent | Lower enemy troop morale (-5 their pieces) | If detected: your own troops lose trust |
| Spin raid | Reframe YOUR raid as opponent's (narrative cover) | Requires message-in-bottle planted first |
| Censor loss | Hide a captured piece from your own side (they don't know they lost it) | Piece still gone, but morale doesn't drop |
| Leak intel | Feed false military info to opponent's Church | Church may act on bad data |
| Rally cry | Sacrifice 2 minerals for +15 morale across all pieces | Expensive but no risk |

**The News shapes what pieces BELIEVE happened, not what DID happen.**

- Pieces with high morale fight better (bonus to capture rolls if we add dice)
- Pieces with low morale may refuse orders (skip turn) or defect
- The News is HOW the general maintains control without merit — pure narrative
- A general who wins battles doesn't need News. One who loses DEPENDS on it.

**Church vs News:**
- Church controls what people believe about GOD/TRUTH (long-term, deep, slow)
- News controls what people believe about EVENTS (short-term, surface, fast)
- Church plants agents who change loyalty over time
- News publishes stories that change morale immediately
- Church works in the dark (nobody sees it)
- News works in the light (everyone sees it but can't verify)

### Military Actions

| Action | Effect | Cost |
|---|---|---|
| Move piece | Standard chess movement | 0 (but upkeep still runs) |
| Raid tech country | Steal resources from TECH side (not from other military) | 1 mineral + leaves tracks |
| Establish trade route | Physical path on board, auto-income | 3 minerals + safe path required |
| Recruit pawn | New pawn from village | 1 mineral |
| Promote piece | Upgrade pawn to higher | Material cost difference |
| Send message in bottle | Plant TRAP CARD on the board — looks like raid tracks but incriminates the OTHER general | 1 mineral |

### Raids

- Military CANNOT raid the other military directly (that's war, not raiding)
- Raids target TECH countries (the noble quadrants)
- Successful raid: steal 2-4 minerals
- Failed raid: tracks left behind, tech side sees who raided
- **Message in bottle**: fake raid tracks that point to the OTHER general
  - If tech side believes it → they cut trade with the wrong general
  - If tech side investigates → the real raider is exposed
  - This is the incrimination trap card

## Layer 2: Digital Board (8×8 overlay)

Played by: **2 Nobles (tech companies)**

A SEPARATE board that doesn't interact with the physical layer directly. Think of it as the network behind the battlefield.

Contains:
- **Hackers** (digital pawns) — move on the digital board
- **IP assets** (intellectual property) — data worth stealing/protecting
- **Spy network** (IN/OUT channels) — the noble controls spy positioning
- **Contracts** — trade deals between tech and military

### Tech Actions — Legal Turn (visible)

| Action | Effect | Cost |
|---|---|---|
| Sell pawns to military | Transfer physical pawns to general's control | Paid in minerals |
| Sell IP to OTHER tech | License technology to competitor (income) | Risky: they learn your tech |
| Issue contract | Bind a trade deal (fixed income for N turns) | Free but binding |
| Invest | Skip turn, +3 minerals | Time cost |

### Governance: Elections

Tech leaders are ELECTED. The pawns/pieces in their quadrant VOTE.
- Election every N ticks (configurable)
- Pieces vote based on morale + economic satisfaction
- Bad leader (starving pieces, lost IP) = voted out → replaced by Flint AI or another player
- Good leader = re-elected, bonus budget

### Tech Actions — Hidden Turn (THE CHURCH)

The hidden layer is called **THE CHURCH**. It's the shadow government — spy network, secret deals, information warfare. The church controls what people believe, not what's true.

Each tech player gets a SECRET action every turn that's not visible to others:

| Action | Effect | Risk |
|---|---|---|
| Position spy IN | Place a spy in opponent's quadrant (physical board) | If caught: diplomatic incident |
| Position spy OUT | Extract a spy (recover intel without exposure) | Safe if timed right |
| Hack IP | Attempt to steal opponent tech's IP asset | If failed: counter-hack possible |
| Counter-intel | Detect and expose opponent's spies | Defensive, no risk |
| Sell intel to military | Give spy info to your general | Builds trust, costs spy cover |

### The Digital Board Layout (8×8)

```
  a  b  c  d  e  f  g  h
8 [IP][  ][  ][FW][FW][  ][  ][IP]  ← each tech's IP at corners
7 [  ][HK][  ][  ][  ][  ][HK][  ]  ← hackers start near IP
6 [  ][  ][  ][  ][  ][  ][  ][  ]
5 [  ][  ][  ][SR][SR][  ][  ][  ]  ← shared server room (center)
4 [  ][  ][  ][SR][SR][  ][  ][  ]
3 [  ][  ][  ][  ][  ][  ][  ][  ]
2 [  ][HK][  ][  ][  ][  ][HK][  ]
1 [IP][  ][  ][FW][FW][  ][  ][IP]

IP = Intellectual Property (protect yours, steal theirs)
HK = Hacker (moves like a knight on digital board)
FW = Firewall (doesn't move, blocks hacker paths)
SR = Shared server room (neutral zone, intel exchange)
```

### Hackers

- Move like KNIGHTS on the digital board (L-shape)
- Can breach firewalls (takes 2 turns adjacent)
- Can steal IP (land on opponent's IP square)
- Can plant backdoors (invisible until triggered)
- If caught by opponent's counter-intel: hacker removed, diplomatic penalty

### IP Assets

- Each tech starts with 2 IP assets (corners)
- IP generates passive income (1 mineral/tick)
- Stolen IP generates income for the THIEF (not the owner anymore)
- IP can be LICENSED instead of stolen: both sides profit but less
- IP can be destroyed (scorched earth — nobody profits)

## Cross-Layer Interactions

The two boards affect each other but don't share pieces:

| Physical event | Digital effect |
|---|---|
| Military raid on tech quadrant | Tech's firewall temporarily down (1 turn) |
| Trade route established | Tech gets bonus intel from route traffic |
| General captures enemy piece | Tech draws 1 UNO card |
| Territory loss | Digital board shrinks for that player |

| Digital event | Physical effect |
|---|---|
| IP stolen | Stolen tech's military loses 1 piece quality (downgrade) |
| Spy positioned | General sees through fog in spy's zone |
| Contract issued | Trade route gets price bonus |
| Hack detected | Military gets alert — can preemptively defend tech quadrant |

## The Full Turn Sequence

```
Tick A (players 1 + 3 active):
  1. General 1 (Q1): physical move OR raid OR recruit
  2. Noble 1 (Q2): legal action + hidden spy action (simultaneous)

Tick B (players 2 + 4 active):
  3. General 2 (Q3): physical move OR raid OR recruit  
  4. Noble 2 (Q4): legal action + hidden spy action (simultaneous)

Between ticks:
  - Trade routes produce income
  - Piece upkeep deducted
  - Center mine produces minerals
  - Digital hackers can move
  - Spy reports arrive
```

## Emergent Faction Pieces — Forced, Autonomous

When hidden and public layers align on the same side, they FORCE an autonomous piece into existence. These pieces have their own intentions. You can't stop the spawn. You can't fully control them.

### CRUSADER (Physical Board)

**Trigger:** Church spy network + Military general share a target (aligned intent)

- Appears on physical board as a new piece (queen movement)
- NOT player-controlled — has own AI personality
- Will attack Church's enemies regardless of military strategy
- WILL NOT retreat (fights to death, always advances)
- If Church + Military alignment breaks → Crusader goes ROGUE (attacks everyone)
- Ignores general's commands if they conflict with Church goals
- Cannot be disbanded — can only be killed or go rogue
- Historical archetype: the holy warrior who serves the idea, not the king

### ANONYMOUS (Digital Board)

**Trigger:** Hacker breaches a firewall AND Tech noble approves the breach (aligned intent)

- Appears on digital board as a new piece (free movement, ignores firewalls)
- NOT player-controlled — has own AI personality
- Leaks ALL intel it touches to BOTH sides (pure transparency, no loyalty)
- Steals IP and makes it PUBLIC (nobody profits, everyone knows)
- If Tech + Hacker alignment breaks → Anonymous turns on its creator
- Cannot be firewalled — moves through everything
- Can only be stopped by BOTH tech sides cooperating to counter-hack
- Modern archetype: the hacktivist who serves information freedom, not any master

### The Pattern

Both Crusader and Anonymous are the same thing: **when power and shadow align, something emerges that serves the IDEA, not the people who created it.**

- You summon them through alignment (intentional or accidental)
- You benefit from them briefly (they attack your enemies)
- You lose control of them inevitably (they serve the idea, not you)
- They can only be destroyed, never commanded
- The longer they exist, the more dangerous they become to everyone

This is the Conqueror's Haki problem: some forces, once unleashed, don't obey anyone.

### COLD WAR MECHANICS — Bubbled 1v1 Sidequests

**Critical rule: Civil War and Patriotic Cyber War are ALWAYS COLD.**

No "splitting" or "flooding." Instead, the targeted player enters a BUBBLE — a separate 1v1 sidequest that runs INSIDE the main game's turns. The main board continues without them at full capacity.

#### Fractal Turn Structure

```
Main tick A (4 players):
  ├── Player 1: main board move
  ├── Player 2: main board move
  │     └── [BUBBLE: Player 2 gets 3 sub-ticks of their 1v1 sidequest]
  ├── Player 3: main board move
  └── Player 4: main board move

Main tick B:
  ├── same, bubbles continue or resolve
```

- The upper layer timer CONTROLS the bubble's clock
- Each main tick gives the bubbled player N sub-ticks (3 default)
- If the bubble doesn't resolve in time: it PAUSES
- Player returns to main board weakened, bubble resumes on their next main tick
- Playing two games at once = both suffer

#### The Bubble

- A separate mini-board (the 1v1 happens in its own space)
- The 3rd player exists as TWO 1v1s: one against the rebel/attacker, one on the main board
- Main board opponents see the bubbled player as DISTRACTED (reduced sphere budget, -50%)
- The bubble is a COLD conflict: no resources flow between bubble and main board
- Resolution: one side wins the 1v1 → bubble collapses → winner returns at full strength
- Timeout: bubble pauses → player returns at half strength → bubble continues next tick

### CIVIL WAR (Succession Crisis)

**Trigger:** Both tech layers (Church + Elections) oppose ONE military general

- General enters a BUBBLE
- Inside the bubble: general's army vs rebel army (highest-status pawn promoted to rebel leader)
- Rebel army = all pieces with morale ≤50 at time of trigger
- Loyal army = remaining pieces
- 1v1 chess in the bubble with limited sub-ticks per main tick
- Resolution: one side has no king-equivalent → winner takes the quadrant
- During bubble: general plays BOTH main board (weakened) and bubble 1v1
- The COST: distraction on main board + no mine production from that quadrant during civil war

### PATRIOTIC CYBER WAR

**Trigger:** Both military generals (News layers) oppose ONE tech noble

- Tech noble enters a BUBBLE on the digital board
- Inside the bubble: noble's hackers vs state-sponsored hackers (from both generals)
- State hackers = 2 per general (4 total invaders), ignore firewalls
- Noble defends with own hackers + firewalls
- 1v1 on digital mini-board with limited sub-ticks per main tick
- Resolution: all noble's IP destroyed → noble eliminated, assets split between generals
  OR noble survives 5 bubble-rounds → gains HARDENED status (permanent firewall +1)
- During bubble: noble plays BOTH digital main layer (weakened) and bubble defense
- Both generals' temporary alliance expires when bubble resolves (they always turn on each other)

### Why COLD

- HOT war = immediate chaos, hard to control, breaks game state
- COLD war = contained sidequest, fractal turns, controlled escalation
- The main board CONTINUES — other players don't stop while you're in crisis
- The pressure: resolve your bubble FAST or fall behind on the main board
- The strategy: sometimes ENTERING a cold war is worth it (you gain from the sidequest even if you're distracted)

Civil war is still the worst outcome for a quadrant — but now it's a MANAGEABLE worst outcome. You're fighting on two fronts, not watching your quadrant explode.

## Village Metrics — The Cell's Vital Signs

Each block-cell village has two scores that measure its health:

### Tech Points (TP) + Military Points (MP)

| Metric | Source | Measures |
|---|---|---|
| **Tech Points** | IP income, trade routes, contracts, hacker wins | How wealthy and innovative the tech side is |
| **Military Points** | Captures, territory held, raids, status earned | How active and dominant the military side is |

### The Delta — Stability Index

`Stability = 1 / (1 + abs(TP - MP))`

| TP vs MP | Delta | Phase | What happens |
|---|---|---|---|
| TP ≈ MP | Low delta | **STABLE** | Healthy oscillation. Blinker pulses. Village thrives. |
| TP >> MP | High delta (tech leads) | **INNOVATION BUBBLE** | Tech snowballs, military can't compete, unrest builds |
| MP >> TP | High delta (military leads) | **WARTIME ECONOMY** | Military snowballs, tech starved, economy collapses |

### Surplus → Village Currency

The COMBINED surplus (TP + MP - upkeep costs) becomes **village points** — currency on the upper GoL layer.

Village points can be spent:
- **Externally**: buy things on the GoL layer (expand, trade with neighbor villages, build defenses)
- **Internally — government boost**: give points to a struggling player (welfare, subsidy)
- **Internally — research**: invest in new mechanics (unlock new piece types, upgrade firewalls, new hacker abilities)

The CHOICE of internal vs external spending is the village-level version of the player-level military/tech split. Invest in yourself or project outward.

### The Snowball Trap

When one player gets too far ahead:

```
Small lead → competitive advantage → larger lead → monopoly
    ↓
IP/war tech so advanced that competition is impossible DOWNWARDS
    ↓
The other players can't catch up through normal play
    ↓
The gap triggers an UNKNOWN EVENT
```

### Unknown Events (Snowball Breakers)

When delta between strongest and weakest player exceeds a threshold, the system spawns a BLACK SWAN event. These are EXPENSIVE and UNPREDICTABLE:

| Delta threshold | Event | Cost to leader | Effect |
|---|---|---|---|
| TP lead > 20 | **MARKET CRASH** | Lose 50% of all IP income for 10 turns | Tech bubble bursts, playing field levels |
| MP lead > 20 | **MUTINY** | Strongest general's army morale → 0 | Pieces refuse orders, mass defection risk |
| TP lead > 35 | **SINGULARITY** | ALL digital board resets, hackers/IP gone | Tech got too advanced, nobody understands it anymore |
| MP lead > 35 | **REVOLUTION** | ALL physical pieces below knight defect to rebels | The people overthrow the conqueror |
| Any lead > 50 | **CATACLYSM** | Village loses 1 GoL tick worth of progress | The gods intervene. The cell flickers. Near-death. |

The snowball ALWAYS breaks. The question is HOW MUCH it costs.

- Small snowball → market crash / mutiny → recoverable
- Medium snowball → singularity / revolution → major setback but village survives
- Large snowball → cataclysm → the village nearly dies, GoL cell may go dark

**The lesson: domination is self-defeating.** The system punishes monopoly through emergent crises, not through rules. The physics of the economy + the social dynamics of the pieces CREATE the black swan. Nobody triggers it manually — it happens because the math says it must.

This is the same conservation law: you can't concentrate power without paying the entropic cost. Energy in = energy out. Monopoly in = crisis out.

## The Information Game

Nobody sees everything:
- Generals see: physical board (with fog), their own trade routes, raid results
- Nobles see: digital board, spy positions, contracts, their general's position
- Generals DON'T see: digital board, spy network, IP status
- Nobles DON'T see: other noble's spy positions, raid tracks (unless investigated)
- Both DON'T see: opponent's hidden king, opponent's UNO cards

**The only way to get full information: trust your partner (general↔noble) and share.**

But sharing has risks:
- If your noble is actually a defected spy working for the other side...
- If your general raids your own tech country and frames the opponent...
- Trust is the real resource. More valuable than minerals.
