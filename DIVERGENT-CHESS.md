# Divergent Chess — Full Ruleset

*Started as chess. Became a fog-of-war strategy game with hidden king, quantum pawns, defection economics, and lesson-based victory.*

## Piece Economics

Each piece has:
- **Code** — deployment cost (weight to put on board)
- **Value** — chess value (P=1, N/B=3, R=5, Q=9, K=hidden)
- **Personality** — Wrecker/Wall/Glitch archetype (for AI stream mode)
- **Backstory** — why they fight (generated or assigned)

## The Hidden King

- King is disguised as a pawn. Identical appearance.
- Acts as a pawn — follows pawn movement rules
- Opponents must DISCOVER which pawn is the king
- The objective: teach the king a lesson (identify + surround), not kill

## Flint-Pawns

Enhanced pawn rules replacing classical pawns:

### Movement
- Forward, backward, sideways (1 square, any cardinal direction)
- CANNOT cross behind their own 2nd rank (invisible wall at rank 1)
- Returning to 2nd rank reactivates double jump

### Capture
- All four diagonals (not just forward)

### Home Abilities (on 2nd rank)
- **Double jump** — standard 2 squares forward
- **Archery** — strike 2 squares ahead, 50% accuracy, no movement required
- **Teleport** — move to any other 2nd rank square
- **Rank jump** — jump to any rank 3 square, or rank 4 only on starting file

### Quantum Entanglement
- Two enemy pawns face-to-face (adjacent, same file) = ENTANGLED
- Entangled pawns cannot move forward/backward, only take diagonally
- Creates deadlocks that must be resolved by higher pieces

### Sticky Chains
- Same-color pawns diagonally adjacent = STICKY
- Moving one moves the entire chain (same rules apply to all)
- Chains can form shapes (L, T, diagonal lines)
- Chains cannot be separated independently
- Frontal/lateral collision with any piece = permanent stick
- Higher piece sphere of influence bypasses stickiness (picks up pawns)

## Higher Pieces

Classical movement (rook/bishop/knight/queen) plus:

### Sphere of Influence
- Radius assigned by king from budget (0-3 squares per piece)
- Within sphere: reveals hidden piece identities (pierces fog)
- **DRAG RULE:** When a high piece moves, ALL pieces in its sphere move 1 square in the same direction
  - If ANY piece in the sphere would collide (friendly or enemy) → ENTIRE MOVE IS ILLEGAL
  - Big sphere = more power but harder to maneuver without collision
  - The sphere is a liability AND an asset — dragging friendlies means checking every square
  - Moving through friendly sticky pawns = picks them up (break chain), but still must check drag collisions
- Sphere-covered ground IS a resource — overlapping enemy spheres = contested territory

## King Orders — Budget System

- King gets a SPHERE BUDGET each turn (total points to distribute)
- Budget = base 5 + bonus from controlled territory (sphere-covered ground)
- Each sphere radius costs: r=1 costs 1pt, r=2 costs 3pt, r=3 costs 6pt (triangular)
- King distributes budget across ALL pieces at start of turn (not just one)
- Giving orders = king cannot move that turn
- If king moves instead: sphere assignments stay from last turn (no redistribution)
- Strategic choices:
  - Many small spheres (1pt each) = wide vision, easy to maneuver
  - One big sphere (6pt) = deep influence but drag makes movement risky
  - Save budget = no spheres, king moves freely, fog covers everything
  
| Radius | Cost | Drag | Use case |
|--------|------|------|----------|
| 0 | 0 | None | Stealth — piece is invisible, moves alone |
| 1 | 1 | Adjacent 8 squares shift | Scout — light influence, low drag |
| 2 | 3 | 24 squares shift | Officer — medium influence, careful movement |
| 3 | 6 | 48 squares shift | General — heavy influence, very hard to move |

## Fog of War

- ALL pieces appear as pawns from a distance
- Identity revealed when:
  - Within a piece's sphere of influence
  - Within direct capture range (vision = threat range)
- **Vet** — active investigation: spend a move to check a piece's identity

## Defection System

- Any piece can DEFECT to opponent (spy)
- Defected piece can be turned back (double agent)
- Maximum depth: 3 (spy → double → triple, no deeper)
- Defection costs: piece keeps personality but serves new master
- **Leave the board** — piece disagrees with leadership, exits
  - Returns half its value as credit for deploying a new piece
  - Cannot be forced to stay

## Win Conditions

Ranked by quality (highest = best):

1. **Lesson taught** — identify hidden king + surround without killing. Opponent learns. (Best)
2. **Agreed draw** — both sides choose peace. Wisdom. (Good)
3. **Economic victory** — opponent can't field pieces worth playing. (Practical)
4. **Resignation** — opponent quits under pressure. (Acceptable)
5. **Checkmate** — classical, but all your dead pieces are gone. (Pyrrhic)

**Score = (pieces surviving on BOTH sides) × (lesson quality)**

The game rewards preservation, not destruction.

## Stream Mode (Idle)

- Player sets up board + assigns personalities to each piece
- Two Flint AIs play using piece personalities
- Viewer watches — stories emerge from personality interactions
- Replay + auto-commentary from the drama
- "The knight defected after the queen sacrificed his friend"

## Network Parallels

| Chess concept | Network equivalent |
|---|---|
| Fog of war | Unknown topology |
| Hidden king | Root authority nobody sees |
| Defection | Route hijacking / BGP leak |
| Sticky pawns | Link aggregation |
| Sphere of influence | Broadcast domain radius |
| Quantum entanglement | Protocol deadlock (two peers waiting for each other) |
| Archery | ICMP ping (remote strike without moving) |
| Teleport on home rank | Loopback address (return to any home interface) |
| Lesson-based victory | Troubleshooting (identify the root cause without destroying the network) |
| Piece leaving the board | Interface administratively shutdown by operator |
