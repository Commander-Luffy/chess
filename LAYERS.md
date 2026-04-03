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

### CIVIL WAR (Succession Crisis)

**Trigger:** Both tech layers (Church + Elections) oppose ONE military general

When the tech side BOTH hate the same general:
- Church refuses to support (spies withdraw)
- Elections vote against (pieces refuse orders)
- The general's army SPLITS — loyal pieces vs rebel pieces
- A new general candidate emerges from the rebels (highest status pawn)
- Civil war plays out on the SAME quadrant — internal chess within the chess
- During civil war: the quadrant is VULNERABLE (neighbors can invade)
- Resolution: one general wins, loser's pieces defect or die
- The COST: the quadrant is weakened regardless of who wins
- Post-civil war: new general must rebuild trust with tech side

### PATRIOTIC CYBER WAR

**Trigger:** Both military generals (News layers) oppose ONE tech noble

When both generals hate the same tech player:
- News publishes "enemy of the state" propaganda against the tech noble
- Military from BOTH sides temporarily ceases fire to target the tech quadrant
- The tech noble's digital board gets FLOODED — both generals' hackers join as state-sponsored attackers
- Anonymous spawns AGAINST the tech noble (military alignment hijacks the hacktivist)
- The noble's Church network gets exposed by combined military intel
- Tech noble must: surrender IP, flee (leave board), or find the OTHER tech noble as ally
- If other tech noble helps → the war becomes 2v2 (both military vs both tech)
- If other tech noble betrays → the targeted noble is eliminated, their assets split between generals
- Duration: lasts until one general breaks the alliance (they always do — they're competing too)

Patriotic cyber war is the digital equivalent of civil war. Civil war splits a quadrant internally. Patriotic cyber war unites ENEMIES against a shared "threat to the nation."

The irony: both generals are still enemies. They cooperate against tech only because controlling information (News) is easier when tech can't counter it. The moment the tech threat is gone, they turn on each other again.

Civil war is the worst outcome for a quadrant — it's a self-inflicted wound that benefits every neighbor. But sometimes it's the only way to remove a bad leader that elections (tech) and status (military) can't fix alone.

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
