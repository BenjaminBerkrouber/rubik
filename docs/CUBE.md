# Cube Representation (Bit-Level Encoding)

This document describes how the Rubik’s Cube state is encoded inside the `CubeState` structure.  
The goal of this format is to achieve the **fastest possible manipulation** while maintaining **extreme memory efficiency**.

The entire cube — all pieces, positions, and orientations — is stored inside **two 64-bit integers**:

```cpp
uint64_t edges;
uint64_t corners;
```


This means the complete Rubik’s Cube fits in **128 bits (16 bytes)**,  
which is dramatically smaller than classical facelet models (typically **54 bytes → 432 bits**).

---

# 1. Overview

A Rubik’s Cube contains:

| Piece Type | Count | Possible Positions | Orientation |
|------------|--------|-------------------|-------------|
| Edges      | 12     | 12! permutations  | 0–1 (flip)  |
| Corners    | 8      | 8! permutations   | 0–2 (twist) |
| Center     | 6      | 6                 | 0           |

To represent the cube efficiently, we store:

- **the permutation** of each edge and corner  
- **their orientation** (flip or twist)

Instead of storing colors or faces, we store the cube as a **set of moving pieces**, which is how speedsolvers (and fast solvers) think about the cube.

---

# 2. Edge Encoding (64-bit)

The `edges` field encodes:

| Content                        | Size               | Bit Range |
|--------------------------------|--------------------|-----------|
| 12 edge positions (0–11)       | 12 × 4 bits = 48b  | 0 – 47    |
| 12 edge orientations (0–1)     | 12 × 1 bit = 12b   | 48 – 59   |
| Padding                        | 4 bits             | 60 – 63   |

Total used: **60 bits**  
Stored in a `uint64_t`.

### 2.1 Why This Encoding? (Understanding Positions & Orientations)

A Rubik’s Cube contains **12 edge pieces**.  
Each of these edges can be in one of **12 possible positions**.

To encode any number from **0 to 11**, we need at least:

> log2(12) = 3.58 bits → rounded to 4 bits


This means:

- every edge position must be stored using **4 bits**,  
- so storing all 12 positions requires:  
  **12 × 4 bits = 48 bits**, which occupy the range **0 to 47**.

Each edge also has an **orientation** (flip), which is either:

- `0` → correctly oriented  
- `1` → flipped  

A single orientation therefore fits naturally in **1 bit**.

For 12 edge pieces, this uses:

- **12 × 1 bit = 12 bits**, placed in the range **48 to 59**.

This leaves bits **60 to 63** unused.  
Those bits are simply **padding** and ensure that the full structure fits nicely into a 64-bit integer.

---

### 2.2 Layout (Edges)

The **layout** simply describes *where* each part of the encoded cube is located inside the 64-bit number.

Here is a visual representation:


This diagram shows:

- **bits 0–47** → the 12 edge positions encoded in blocks of 4 bits  
- **bits 48–59** → the 12 orientation bits  
- **bits 60–63** → unused padding bits

This layout is chosen because it is:

- **compact** (uses only 60 bits total),  
- **CPU-friendly** (groups related data cleanly),  
- and **fast to manipulate** using bit shifts and masks.

---

### 2.3 Accessing Edge Data

#### Reading an edge position:
Each position is stored in 4 bits:

```cpp
uint8_t pos = (edges >> (i * 4)) & 0xF;
```
These operations are extremely fast because they rely purely on bit shifts and bit masks, which the CPU handles in a single cycle.


# 3. Corner Encoding (64-bit)

The `corners` field contains all the information needed to describe the **8 corner pieces** of a Rubik’s Cube:

| Content                          | Size               | Bit Range |
|----------------------------------|--------------------|-----------|
| 8 corner positions (0–7)         | 8 × 4 bits = 32b   | 0 – 31    |
| 8 corner orientations (0–2)      | 8 × 2 bits = 16b   | 32 – 47   |
| Padding                          | 16 bits            | 48 – 63   |

Total used: **48 bits**  
Stored in a single `uint64_t`.

---

### 3.1 Why This Encoding? (Positions & Twists)

A Rubik’s Cube contains **8 corner pieces**.  
Each corner can be in one of **8 different positions**.

To encode any number from **0 to 7**, we need:

> log2(8) = 3 bits → rounded to 4 bits 

This means:

- every corner position requires **4 bits**,  
- and all 8 corners require:  
  **8 × 4 bits = 32 bits**, stored in the range **0 to 31**.

 corner has **3 possible orientations**:

- `0` → correctly oriented  
- `1` → twisted clockwise  
- `2` → twisted counterclockwise  

To encode the numbers 0, 1, or 2, we need:
> log2(3) = 1.58 bits → rounded to 2 bits


Thus:

- each corner twist uses **2 bits**,  
- all 8 corners use:  
  **8 × 2 bits = 16 bits**, stored in the range **32 to 47**.

The remaining **16 bits (48–63)** are unused padding, ensuring alignment in a 64-bit integer.

---

### 3.2 Layout (Corners)

This diagram shows how all corner data is arranged:


Meaning:

- **bits 0–31** → 8 corner positions (4 bits each)  
- **bits 32–47** → 8 corner orientations (2 bits each)  
- **bits 48–63** → unused  

This layout matches the edge encoding spirit:

- positions grouped together  
- orientations grouped together  
- padding at the top  

---

### 3.3 Accessing Corner Data

#### Reading a corner position (4 bits):

```cpp
uint8_t pos = (corners >> (i * 4)) & 0xF;
```
Reading a corner twist (2 bits):
```cpp
uint8_t ori = (corners >> (32 + i * 2)) & 0x3;
```
Note:
Orientation values will only be 0, 1, or 2.
A value of 3 cannot appear in a legal Rubik’s Cube because it violates the parity constraints of the cube group.

These operations are extremely fast thanks to pure bitwise arithmetic (no loops, no allocations).

# 4. Design Rationale (Why This Representation?)

This encoding is the result of several technical constraints and design goals:

- the cube must fit into as few bits as possible  
- move simulation must be extremely fast  
- hashing and equality comparison must be constant-time (O(1))  
- the structure must be compatible with large-scale search algorithms (IDA\*, A\*, pruning tables, etc.)  
- cloning a cube state must be trivial and cache-friendly  

The result is the **128-bit CubeState**, which packs the entire cube into two compact 64-bit integers.

---

## 4.1 Why This Layout Is Ideal

Both edges and corners follow the same design philosophy:

### Minimal memory footprint  
Only the mathematically necessary bits are used:  
- **60 bits** for edges  
- **48 bits** for corners  
- total cube size **≈ 108 bits** stored in 128 bits (two registers)

This is dramatically smaller than traditional face-based models.

### CPU- and cache-friendly  
Small objects → fit inside L1/L2 cache → near-zero copy overhead.

Cloning a cube state is just:

```cpp
CubeState next = current;
```
Only 16 bytes are copied.

**Extremely fast move simulation**

Moves consist of:
 - permuting 4-bit blocks (corner/edge positions)
- flipping XOR bits for edges
- rotating 2-bit twist values mod 3 for corners

All operations are pure **bit shifts**, **masks**, **swaps**, and **XORs**.
No heap, no loops, no allocations = extremely cheap.


## Explicative Shema 

> CORNERS color order           EDGES color order
```
    ⎽⎽⎽⎽⎽⎽⎽⎽⎽                   ⎽⎽⎽⎽⎽⎽⎽⎽
   ╱         ╱ ⎸              ╱         ╱⎸
  ╱    0    ╱   ⎸            ╱    0    ╱ ⎸
 ╱         ╱    ⎸           ╱        ╱   ⎸
⎸⎺⎺⎺⎺⎺  ⎸    ⎸           ⎸⎺⎺⎺⎺⎺ ⎸ ⎸
⎸         ⎸ 1  ⎸           ⎸    1    ⎸ ⎸
⎸         ⎸    ⎸           ⎸         ⎸/
⎸   2     ⎸  /              ⎸⎽⎽⎽⎽⎽ /
⎸         ⎸/
⎸⎽⎽⎽⎽⎽ /  
```
> **CORNERS LST** - **EDGES LST**
```
╔════╤═════════╗    ╔═════╤═════════╗
║ ID ║ VALUE   ║    ║ ID  ║ VALUE   ║
╠════╪═════════╣    ╠═════╪═════════╣
║ 0  ║ UFR     ║    ║ 00  ║ UF      ║
║ 1  ║ UFL     ║    ║ 01  ║ UL      ║
║ 2  ║ UBL     ║    ║ 02  ║ UB      ║
║ 3  ║ UBR     ║    ║ 03  ║ UR      ║
╠════╧═════════╣    ╠═════╪═════════╣
║ 4  ║ DFR     ║    ║ 04  ║ FR      ║
║ 5  ║ DFL     ║    ║ 05  ║ FL      ║
║ 6  ║ DBL     ║    ║ 06  ║ BL      ║
║ 7  ║ DBR     ║    ║ 07  ║ BR      ║
╚════╧═════════╝    ╠═════╧═════════╣
                    ║ 08  ║ DF      ║
                    ║ 09  ║ DL      ║
                    ║ 10  ║ DB      ║
                    ║ 11  ║ DR      ║
                    ╚═════╧═════════╝
```
>  PATRON WITH ID
```
                     [2]════[02]════[3]
                      ║              ║
                     [01]     U     [03]
                      ║              ║
                     [1]════[00]════[0]

[2]════[01]════[1]   [1]════[00]════[0]   [0]════[03]════[3]   [3]════[02]════[2]
 ║              ║     ║              ║     ║              ║     ║              ║   
[06]     L     [05] [05]      F     [04]  [04]     R     [07]  [07]     B     [06]   
 ║              ║     ║              ║     ║              ║     ║              ║
[6]════[09]════[5]   [5]════[08]════[4]   [4]════[11]════[7]   [7]════[10]════[6]

                     [5]════[08]════[4]
                      ║              ║
                     [09]     B     [11]
                      ║              ║
                     [6]════[10]════[7]
```
> EXEMPLE FACE UP
```
╔═══════╤═══════╤═══════╗
║ UBL.0 ║ UB.0  ║ UFR.0 ║
╠═══════╪═══════╪═══════╣
║ UL.0  ║ U.0   ║ UR.0  ║
╠═══════╪═══════╪═══════╣
║ UFL.0 ║ UF.0  ║ UFR.0 ║
╚═══════╧═══════╧═══════╝
```
> EXEMPLE FACE FRONT
```
╔═══════╤═══════╤═══════╗
║ UFL.1 ║ UF.1  ║ UFR.1 ║
╠═══════╪═══════╪═══════╣
║ FL.0  ║ U.0   ║ FR.0  ║
╠═══════╪═══════╪═══════╣
║ DFL.2 ║ DF.1  ║ DFR.1 ║
╚═══════╧═══════╧═══════╝
```