# Floor 7 — The Cisterns — starter

Read [the public Floor 7 page](https://hogred.github.io/comp2450/floors/floor-07/) before you start. It has the full week's narrative, objectives, and lab requirements. This README only covers the starter scaffold and the swap-in path from your Floor 6 submission.

## What's new for Floor 7

- `hero/Queue.h` — `Queue<T>`, a FIFO adapter over `Chain<T>`. **Four method bodies are stubbed** (`enqueue`, `dequeue`, `size`, `empty`); `front()` ships written — a reference-returning `T&` can't be honestly stubbed. Your work is here Monday. Deliberately mirrors `Stack.h` from Floor 6; the difference is which end of `chain_` each operation touches.
- `hero/Potato.h` and `hero/Potato.cpp` — `std::string hotPotato(names, k)` runs the classical FIFO elimination ("pass-the-potato") game and returns the survivor. **Body is stubbed.** Your work, Wednesday.
- `hero/QueueTests.h/.cpp` — `selftest queue` harness with five phases. **Provided** (you do not edit). Phase 3 is the FIFO-vs-LIFO assertion: `front()` after three enqueues must be the FIRST, not the LAST.
- `hero/Hero.h` — `Hero` now owns a `Queue<std::string> enemyActionQueue` in addition to its Floor 6 `Stack<UndoAction> undoStack`.
- `main.cpp` — pre-wired:
  - `provoke <name>` — enqueues a synthesized action ("`<name>` stirs in the dark") onto `hero.enemyActionQueue`. Becomes useful once `Queue::enqueue` is implemented.
  - `simulate` — body is **stubbed** (prints "not yet implemented"). Your work, Friday. Drains the queue in FIFO order, printing each turn.
  - `potato <name>... <k>` — calls `hotPotato(names, k)`. Starts working once you implement it.
  - `selftest queue` — runs the QueueTests harness.

Everything from Floors 0–6 is in place. Stack, Lint, undo — all reference now.

## Build & run

```
cmake -B build
cmake --build build
./build/the_descent          # macOS / Linux
build\the_descent.exe        # Windows cmd
```

You should land at the `> ` prompt with everything from previous floors working. The new commands work-but-do-nothing-useful-yet:

- `selftest queue` — Phase 1 passes (empty-queue invariants — the stubbed `size()` returns 0, so they accidentally agree). Phases 2–5 FAIL with one-line diagnostics that name the likely stubbed method.
- `provoke Goblin` — prints "Goblin takes a number and joins the line", but the underlying `enqueue` is a no-op until `Queue::enqueue` works. So `simulate` will find the line empty.
- `potato Grix Skrit Quill 2` — prints "Survivor: (hotPotato unimplemented)" until you write the algorithm.
- `simulate` — prints "(simulate not yet implemented — TODO Friday in main.cpp)".

By Friday, all four should be producing real output.

## Bringing your own Floor 6 code forward

If you customized anything on `hero/Stack.h`, `hero/Lint.cpp`, or the `undo` dispatcher in `main.cpp`, feel free to bring it across — but the reference versions shipped here are simple and work; you only need to swap in your own if there's a reason. Same with everything earlier in the stack: keep your `Chain<T>`, `Bag<T>`, and `Battle.cpp` if you prefer.

If you modified `hero/Hero.cpp` (printInventory formatting, extra event-log calls in `battle/Battle.cpp`, etc.), drop your versions over the reference ones. Floor 7 does not change those files structurally — only `Hero.h` grew a new field (`enemyActionQueue`).

## What you write this week

| Day | File | Work |
|-----|------|------|
| **Mon** | `hero/Queue.h` | Four one-line bodies: `enqueue`, `dequeue`, `size`, `empty`. (`front()` — two overloads, same body — ships written; a reference-returning `T&` can't be honestly stubbed.) After this, `selftest queue` passes every phase. |
| **Wed** | `hero/Potato.cpp` | `hotPotato` body — the classical FIFO elimination algorithm using `Queue<std::string>`. After this, `potato <names...> <k>` returns real survivors. |
| **Fri** | `main.cpp`     | The `simulate` dispatcher. Drain `hero.enemyActionQueue` front-to-back, printing each turn. After this, `provoke` → `simulate` resolves the line in arrival order. |

Commit at least three times — Mon, Wed, Fri.

## Lab notes

`floor-07/lab-notes.md` (in your project repo, not in this starter) — items 1–5 are spelled out on [the Floor 7 page](https://hogred.github.io/comp2450/floors/floor-07/).
