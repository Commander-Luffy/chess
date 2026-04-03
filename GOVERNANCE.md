# Governance Layer — Victoria Model

*You don't play the village. You govern it. Set policies. Wait for results. Adjust.*

## Layer Architecture (corrected)

```
L3: GoL grid       — cells alive/dead, B3/S23, neighbor count
L2: Village (THIS) — buildings, policies, resources, TW mechanics, Victoria governance
L1: Chess-RTS      — 4 players, pieces, spheres, fog, movement
L0: Digital         — hackers, IP, firewalls, Church shadow
```

Each layer only knows its own rules. Outcomes flow UP. Policies flow DOWN.

## Currency Separation (CRITICAL)

**Two different economies at two different layers. They NEVER mix directly.**

```
L0 Digital: IP (intellectual property = the village's actual IP address/identity)
  → spent on: hacker ops, firewall maintenance, digital board actions
  → IP IS the address. Lose all IP = village has no identity on the network.
  → stays at L0. Chess and Village never touch IP directly.

L1 Chess-RTS: MINERALS (raw, from center 3×3 mine)
  → spent on: pieces, equipment, combat, in-game trades
  → stays at L1. Village never touches minerals.

L2 Village: 4 POINT TYPES (derived from L1+L0 outcomes)
  → TECH points:     from IP income, trade profits, research
  → CYBER points:    from hacker wins, firewall defense, Church intel
  → MILITARY points: from captures, territory held, raids
  → FAITH points:    from Church radius, Statue/Round Table, Nash agreements
  → spent on: buildings, policies, GoL-layer interactions
  → stays at L2. Chess never touches village points.

L3 GoL: VILLAGE CURRENCY (surplus of all L2 points combined)
  → spent on: inter-village trade, expansion, GoL-layer defense
```

**L0 IP is DUAL meaning:**
- In-game: intellectual property (data assets the hackers steal/protect)
- Meta-game: the village's IP ADDRESS on the GoL network grid
- Lose all IP at L0 = your village has no identity = invisible to neighbors = cell effectively dead
- IP is both the RESOURCE and the IDENTITY at L0

**The conversion (outcomes UP, policies DOWN):**
```
L1 produces OUTCOMES:
  "General captured 3 pieces"     → L2 receives +3 MILITARY
  "Noble sold IP license"         → L2 receives +5 TECH  
  "Hacker breached firewall"      → L2 receives +2 CYBER
  "Nash equilibrium reached"      → L2 receives +4 FAITH
  "Trade route earned 10 minerals"→ L2 receives +2 TECH (not minerals!)

L2 sets POLICIES (costs village points, modifies L1):
  "Conscription" (3 MILITARY pts) → L1: new pawns auto-assigned to general
  "Research Grant" (5 TECH pts)   → L1: tech noble gets +2 mineral income in chess
  "Crusade" (8 FAITH pts)         → L1: Crusader spawn conditions relaxed
  "Cyber Shield" (4 CYBER pts)    → L0: all firewalls +1 for 5 ticks
```

**Minerals are chess money. Village points are governance currency. Different games, different wallets.**

## Policy-as-Code

Policies are coded loops injected into the chess-RTS engine (L1). The village player (L2) sets them. The chess engine executes them as behavior modifiers. Results appear in village metrics after N ticks.

| Policy | Chess-RTS effect | Trade-off |
|---|---|---|
| Conscription | New pawns auto-assigned to military | Free pop → army, less workers |
| Free Trade | Trade routes auto-accept offers | Income up, vulnerability up |
| Isolationism | No trade, +2 firewall | Safe but poor |
| War Tax | Military takes 30% tech income | Funded army, resentful tech |
| Research Grant | 3 minerals/tick → tech | Slow investment, long payoff |
| Martial Law | Pieces can't defect | Stable but Church/News amplified |
| Open Borders | Enemy pieces can enter without combat | Spy-friendly, raid-vulnerable |
| Scorched Earth | Retreating pieces destroy their own square's resources | Denies enemy, costs self |

## LOOK / LOCK / UNLOCK / UN_LOOK

Testing and committing policies:

| Action | What | Cost |
|---|---|---|
| LOOK | Simulate a policy on shadow board (fast ticks, projected outcome) | 1 mineral |
| LOCK | Commit policy to real chess engine | 2 minerals |
| UNLOCK | Remove running policy (effects already happened, can't undo) | 1 mineral |
| UN_LOOK | Cancel simulation early | Free (wastes the LOOK cost) |

LOOKing costs a fraction of LOCKing because it runs on a SIMULATED board. The simulation shows projected TP/MP/stability. But simulations can be wrong — they don't account for opponent actions.

## Buildings (Village Layer, NOT chess layer)

Buildings exist at L2. They influence L1 chess and L0 digital through policies, not direct placement.

| Building | Effect | Build cost | Upkeep/tick | Currency |
|---|---|---|---|---|
| STATUE | Morale floor +20 all pieces | 5 FAITH | 1 FAITH | Faith → stability |
| ROUND TABLE | Disputes → vote not war | 4 FAITH + 4 TECH | 1 FAITH + 1 TECH | Shared governance |
| TAVERN | News propaganda -50% | 5 TECH | 1 TECH | Free information |
| WALL | Military perceived as protective | 4 MILITARY + 4 FAITH | 1 MILITARY + 1 FAITH | Security + trust |
| CHURCH | Outward influence radius | 3 FAITH × level | level × 1 FAITH | Faith projection |
| BARRACKS | Piece upkeep -1 mineral in L1 | 6 MILITARY | 2 MILITARY | Professional army |
| MARKET | Trade route income +50% in L1 | 7 TECH | 2 TECH | Commerce hub |
| FORGE | Piece manufacturing -1 mineral in L1 | 6 TECH | 1 TECH | Industrial base |
| FIREWALL HQ | Digital board firewalls +1 | 5 CYBER | 2 CYBER | Cyber defense |
| SPY ACADEMY | Church spy placement free (normally costs CYBER) | 8 CYBER | 2 CYBER | Intelligence infrastructure |

Building degrades if upkeep unpaid. Effect weakens then disappears.

## TW Features Mapped

| TW Feature | Village Layer Implementation |
|---|---|
| Church (radius) | CHURCH building, levels 1-3, each level extends outward influence radius |
| Paladin | CRUSADER emergent piece (Church + Military alignment in L1) |
| Weapon system | FORGE building + policy: equip pieces with upgrades (capture/defense bonus) |
| Noble | Tech noble governance (elected via pieces in L1, trades IP in L0) |
| Militia | Civil war = militia bubble (costs free pop = pieces, timed) |
| Farm/Clay/Iron/Wood | Center 3×3 mine produces raw minerals (dynamic rate) |
| Warehouse | Stockpile cap (default 50, +20 per MARKET building) |
| Wall (TW) | WALL building — defensive bonus + perception management |
| Catapult / Ram | Siege policies: commit resources to break neighbor's WALL |

## Population — Consequential, Not Managed

Population is NOT a slider. It's the CONSEQUENCE of your governance:

- Population = total living pieces across L1 + L0
- More pieces = higher mine output, larger army cap, more election weight
- Pieces SPAWN when surplus minerals > threshold for 3 consecutive ticks
- Pieces DIE from: combat, starvation (no upkeep), defection, civil war
- Population growth/decline is the REPORT CARD of your policies

You don't "produce population." You create conditions where population grows.

## Upkeep — Everything Costs

### L1 Upkeep (MINERALS — chess layer)

| Thing | Minerals/tick | If unpaid |
|---|---|---|
| Pawn (Flint-Pawn) | 0 | — |
| Knight / Bishop | 1 | Idle (1 tick) → defect (2) → leave (3) |
| Rook | 2 | Same escalation |
| Queen | 3 | Same escalation |
| Mercenary | 3 | Defect after 1 missed → leave with resources after 2 |
| Trade routes (L1 path) | 1 mineral per route | Route pauses |

### L2 Upkeep (VILLAGE POINTS — governance layer)

| Thing | Points/tick | Type | If unpaid |
|---|---|---|---|
| Buildings | See building table | Mixed | Degrade → lose effect |
| Church radius | level × 1 | FAITH | Radius shrinks |
| Active policies | 1 per policy | Matching type | Auto-unlock |
| Cold war bubble | 1 MILITARY + 1 FAITH | Mixed | Can't avoid — bleeds |

**Two separate deficit checks:**
- L1: mineral income < mineral upkeep → pieces degrade
- L2: any point type income < that type's upkeep → buildings/policies fail
- L1 deficit doesn't directly cause L2 deficit (but fewer L1 outcomes = less L2 income next tick)
- The layers are coupled through OUTCOMES, not through shared currency

## The Victoria Loop

```
Observe metrics (TP/MP/stability/population)
    ↓
LOOK at potential policies (simulate on shadow board)
    ↓
LOCK chosen policies (commit to real engine)
    ↓
Wait for results (chess-RTS plays out, N ticks)
    ↓
Read new metrics
    ↓
UNLOCK failing policies, LOOK at new ones
    ↓
Repeat
```

You never touch the chess board directly. You govern through policies. The chess game IS your economy running. You're the parliament, not the general.
