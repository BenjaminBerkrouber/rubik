# MOVES.md — How Moves Are Applied to the Cube State

This document explains how face rotations (U, D, F, B, L, R) are applied to the internal bit-level representation of the cube.

No implementation details are shown here – only the conceptual logic and the mathematical structure behind moves.

The goal is to understand:
- how a single move transforms the cube,
- how edges and corners are permuted,
- how orientations are updated,
- and how these operations map perfectly to the 128-bit `CubeState` format.

---

# 1. The Move List

The cube supports **18 basic moves**, grouped by face:

- **U, U2, U3**  
- **D, D2, D3**  
- **F, F2, F3**  
- **B, B2, B3**  
- **L, L2, L3**  
- **R, R2, R3**

These correspond to:
- clockwise rotation (X)  
- half-turn (X2)  
- counterclockwise rotation (X3)

All moves are defined in the `SpinLst` enumeration.

---

# 2. Conceptual Model: Moves as Piece Cycles

A face rotation affects only **8 pieces**:
- **4 corners**, which cycle among themselves  
- **4 edges**, which also cycle among themselves  

Each move M is therefore represented as:
M = (cycle of 4 corner positions)
- (cycle of 4 edge positions)
- (orientation updates)

This matches perfectly with our compact bit representation.

---

# 3. Corner Movement

Each face move rotates **4 corners** around the face.

Example (conceptual):

URF → UBR → ULB → UFL → back to URF


This is called a **4-cycle**.

Every move behaves like this:
- a clockwise move cycles corners forward,
- a counterclockwise move cycles corners backward,
- a half-turn performs two swaps (a 2-cycle).

The important result:

### The corner permutation is always a cycle of length 4  
(or two swaps for X2 moves)

---

# 4. Corner Orientation (Twist)

A corner piece has 3 possible orientations (0, 1, 2).  
Certain moves change corner orientation.

### Moves on **F** and **B** faces twist corners  
Because these faces “tip” the piece relative to the cube’s axis.

### Moves on **U, D, L, R** faces do *not* twist corners  
Their rotation axis aligns with the cube’s natural orientation frame.

When a move twists corners, two rules apply:

1. **Clockwise 90°** turns twist corners by a specific pattern  
2. **Counterclockwise 90°** turns apply the inverse twist  
3. **180°** turns do NOT affect corner orientation (symmetry)

This is encoded conceptually as:
- some moves add twist offsets (0,1,2) to specific corners
- the twist values always remain mod 3

This ensures valid cube states.

---

# 5. Edge Movement

Just like corners:

- a move affects **4 edges**, cycled in order  
- clockwise and counterclockwise movements reverse the direction of the cycle  
- half-turns swap opposite edges

Example (conceptual):

UF → FR → DF → FL → back to UF


### Every move applies a 4-cycle on edges  
(or two swaps for X2).

This matches the internal representation of edges as 12 × 4-bit positions.

---

# 6. Edge Orientation (Flip)

Edges have only **two orientations** (0 or 1).

Just like corners:

### Only F and B moves can flip edges.

This is because:
- rotating the front or back face breaks the cube’s forward alignment
- other faces rotate around axes that preserve the orientation of edges

A move may apply flips to:
- all 4 moved edges,
- or none of them.

Half-turns (X2) **never** flip edges.

This is consistent with Rubik’s Cube group theory.

---

# 7. Move Types: The Meaning of cycle4 and cycle2

Your move engine internally uses two conceptual operators:

### 4-cycle (cycle4)
Applies a clockwise or counterclockwise rotation of:

- 4 corner positions  
- 4 edge positions  
- (sometimes) corner orientation updates  
- (sometimes) edge flips

This models 90° face turns: **X** and **X3**.

### 2-cycle (cycle2)
Represents 180° turns:

- swaps corner 1 ↔ 3 and 2 ↔ 4  
- swaps edge 1 ↔ 3 and 2 ↔ 4  
- no corner twist  
- no edge flip  

This models the move **X2**.

This abstraction makes the solver extremely fast, because:
- all move types boil down to simple **piece cycles**,
- orientation adjustments are fixed small offsets,
- everything is computed via pure bit manipulation.

---

# 8. Orientation Rules Summary

Here is the complete conceptual summary:

### 🟦 Corners
| Face | Orientation Change |
|------|---------------------|
| U, D, L, R | No twist |
| F, B | Twist corners according to fixed pattern |

Twist direction depends on clockwise vs counterclockwise rotation.

### 🟩 Edges
| Face | Orientation Change |
|------|---------------------|
| U, D, L, R | No flip |
| F, B       | Flips all 4 moved edges |

This matches the real physical cube.

---

# 9. Why the Move System Is Efficient

### Moves operate directly on the 128-bit encoding  
Each move consists of:
- swapping 4-bit blocks (positions)
- rotating orientation slots
- applying XOR or modulo operations
- no loops, no arrays, no allocations

### Constant-time complexity  
Every move is O(1).

### Perfect for IDA\* search  
Moves are extremely light, allowing millions of state expansions per second.

### Faithful to cube group theory  
The orientation and permutation rules ensure:
- no invalid cube states  
- parity consistency  
- twist/flip invariants respected  

This makes the solver robust and mathematically correct.

---

# 10. Move Inverses

Each move X has a natural inverse:

- X ↔ X3  
- X2 is its own inverse  
- moves are grouped by face (U-group, D-group, …)

This allows quick generation of reverse solutions and pruning of redundant branches.

---

# 11. Conclusion

Your move system is a perfect fit for the internal representation:

- moves are minimalistic  
- fully consistent with cube physics  
- extremely fast  
- ideal for Kociemba’s two-phase algorithm  

The interaction between:
- **piece cycles**,  
- **orientation updates**,  
- and **bit-level storage**  

makes this move engine one of the most efficient architectures possible in C++ for high-performance Rubik’s Cube solving.

