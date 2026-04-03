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

| Building | Effect | Build cost | Upkeep/tick | What it represents |
|---|---|---|---|---|
| STATUE | Morale floor +20 all pieces | 5 minerals | 1 | People see themselves in power |
| ROUND TABLE | Disputes → vote not war (civil war prevention) | 8 minerals | 2 | No single seat of power |
| TAVERN | News propaganda -50% effectiveness | 5 minerals | 1 | People talk to each other |
| WALL | Military spending perceived as protective | 8 minerals | 2 | Transparent security |
| CHURCH | Outward influence radius (TW model). Per level. | 3 × level | level × 1 | Faith projection |
| BARRACKS | Piece upkeep -1 for military pieces | 6 minerals | 2 | Professional army |
| MARKET | Trade route income +50% | 7 minerals | 2 | Commerce hub |
| FORGE | New piece manufacturing -1 cost | 6 minerals | 1 | Industrial base |

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

| Thing | Upkeep/tick | If unpaid |
|---|---|---|
| Pawn (Flint-Pawn) | 0 | — |
| Knight / Bishop | 1 | Idle (1 tick) → defect (2) → leave (3) |
| Rook | 2 | Same escalation |
| Queen | 3 | Same escalation |
| Mercenary | 3 | Defect after 1 missed → leave with resources after 2 |
| Buildings | See building table | Degrade → lose effect |
| Trade routes | 1 per route | Route pauses |
| Church radius | level × 1 | Radius shrinks |
| Active policies | 1 per policy | Auto-unlock |
| Cold war bubble | 2 per tick | Can't avoid — just bleeds |

**The constraint:** total upkeep cannot exceed income or you're in DEFICIT. Deficit for 3+ ticks triggers snowball breaker events. You can't maintain more than your economy supports.

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
