# BENCHMARK — Performance Evaluation of the RUBIK Solver

This document presents the real performance of our Rubik’s Cube solver, based on:

- the **Kociemba two-phase algorithm**
- a fully **bit-level cube representation**
- high-performance C++ operations designed for constant-time manipulation

The goal of this benchmark is to show the solver’s **execution speed**, **solution quality**, **memory behavior**, and **low-level operation cost**.

---

# 1. Solving Performance (Kociemba Two-Phase)

The solver was tested on **500 runs** for different scramble lengths.

> **Important:**  
> The execution time measured in all benchmarks represents the *full end-to-end pipeline*, including:
>
> - **Input parsing** (tokenizing and validating the move sequence)  
> - **Scramble application** (applying all input moves to the internal cube state)  
> - **Complete solving** using the Kociemba two-phase algorithm (Phase 1 + Phase 2)  
>
> This means the measured time is not just “algorithm speed”, but the *complete solving time* experienced by the user.


## 1.1 Scramble Length: 20 Moves

#### Execution Time (seconds)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **0.1565 s** |
| Median | **0.1033 s** |
| Min | **0.0394 s** |
| Max | **0.9821 s** |
| Std. deviation | **0.1530** |

#### Solution Length (moves)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **23.03** |
| Median | **23** |
| Min | **17** |
| Max | **26** |
| Std. deviation | **1.43** |

#### Errors
| Metric | Value |
|--------|-------|
| KO count | **0 / 500** |

---

## 1.2 Scramble Length: 100 Moves

#### Execution Time (seconds)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **0.1593 s** |
| Median | **0.0870 s** |
| Min | **0.0417 s** |
| Max | **1.1445 s** |
| Std. deviation | **0.1927** |

#### Solution Length (moves)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **22.90** |
| Median | **23** |
| Min | **19** |
| Max | **26** |
| Std. deviation | **1.43** |

#### Errors
| Metric | Value |
|--------|-------|
| KO count | **0 / 500** |

---

## 1.3 Scramble Length: 500 Moves

#### Execution Time (seconds)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **0.1950 s** |
| Median | **0.1015 s** |
| Min | **0.0413 s** |
| Max | **1.0139 s** |
| Std. deviation | **0.1973** |

#### Solution Length (moves)
| Metric | Value |
|--------|-------|
| Total runs | 500 |
| Mean | **23.25** |
| Median | **23** |
| Min | **19** |
| Max | **26** |
| Std. deviation | **1.28** |

#### Errors
| Metric | Value |
|--------|-------|
| KO count | **0 / 500** |

---

## Observed Behavior

| Observation | Conclusion |
|------------|------------|
| Execution time remains ~0.10–0.20 s regardless of scramble length | Solver performance depends on cube *distance to G₁*, not scramble length |
| Solution length remains stable around 22–23 moves | Expected behavior for Kociemba 2-phase |
| 0% failure rate | Implementation is stable and robust |

---

# 2. Memory Performance (Valgrind)

Valgrind tests were executed with short and long scrambles.

### Valgrind Summary
| Metric | Result |
|--------|--------|
| Memory leaks | **0 bytes** |
| Invalid reads/writes | **0 errors** |
| Total heap allocs | ~214 |
| Total frees | ~214 |
| Error summary | **0 errors** |

### Guaranteed properties

- No leaks  
- No dangling pointers  
- No uninitialized memory access  
- Fully deterministic memory behavior  
- Identical memory usage even with long inputs  

---

# 3. Micro-Benchmark: Low-Level Operations

These operations test the raw performance of the 128-bit cube state representation.

### Operation Costs

| Operation | Time |
|----------|-------|
| Cube initialization | **86 ns** |
| Single move (Spin U2) | **179 ns** |
| 1,000,000 Spins (R3) | **37.7869 ms** |
| Cube assignment (copy) | **43 ns** |
| Cube comparison | **52 ns** |

### Highlights

- Moves operate at **nanosecond scale**
- Cube fits entirely in CPU registers
- Assignment & comparison are extremely cheap (16 bytes)
- Perfect for IDA*, or large-scale pruning tables
- Capable of **26+ million moves per second**

---

# 4. Interpretation

### Speed
Solve time for any scramble length (20 → 500):  
**~0.1–0.2 seconds**

### Efficiency
Solution length always around **22–23 moves**  
→ consistent with state-of-the-art Kociemba implementations.

### Reliability  
0 errors detected across 1500 runs  
0 leaks  

### Low-level performance  
Nanosecond-scale operations confirm the effectiveness of the bit-level design.

---

# 5. Conclusion

These results demonstrate that the solver is:

| Property | Assessment |
|----------|------------|
| **Speed** | Excellent |
| **Move optimality** | Stable & competitive |
| **Memory safety** | Fully leak-free |
| **Scalability** | Independent of scramble length |
| **Low-level performance** | Nanosecond operations |

The combination of the Kociemba two-phase algorithm and a minimal 128-bit cube representation results in a solver that is:

- **fast**,  
- **reliable**,  
- **mathematically correct**,  
- **memory-safe**,  
- and suitable for real-time solving or robotics applications.

