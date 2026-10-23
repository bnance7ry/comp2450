---
title: The Warden of the Middle Gates
floor_number: "Warden · II"
order: 110
flavor_quote: "Four floors taught you to hold the line. The Warden asks whether the line holds when more than one enemy arrives at once."
covers: "Floors 4 – 7 · Midterm 2"
---

## The gate

Beyond Steward Quill's desk a heavy door opens onto a marshalling yard. Torchlight on wet stone. Four figures stand at the corners, one at each compass point — **Mavren** with her chain-ledger, **Vael** with her lens lifted, **Resh** mouthing the last words spoken to him, **Quill** with his ticket in hand — and at the centre, in dark iron plate, the second Warden waits. Four sigils on its breastplate this time: a chain link, a lens, a coiled echo, a stamped ticket.

It does not move *yet*. It does not need to. Four floors built you a hero who can hold a line of *one*. The Warden of the Middle Gates asks whether the line holds when enemies arrive in waves, when actions need to be undone, when an inventory has to be walked one item at a time without anybody telling you the index.

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/warden-02.svg' | relative_url }}" alt="The Warden of the Middle Gates — a hooded, faceless figure in dark iron plate. Where the first Warden showed two ember-gold eye-points inside the deep cowl, this one shows a single horizontal ember slit — the visor of a great-helm worn beneath the hood. Four small sigils on the breastplate: a chain link, a polished lens, a coiled echo, a stamped ticket. Behind the figure, a marshalling yard with four torch-lit corners."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">The Warden, who has no name to give</span>

*Four keepers stand with me. Each one will see whether their lesson took.*
*One adapter held; you faced one enemy. Now the line moves. Hold it.*
</div>
</div>

**This page is your Midterm 2.** It replaces the timed paper exam, and it is one job: **follow along with the recorded Warden II videos, building the encounter in your own project as you watch, then submit the code you end up with** — pushed to GitHub and turned in on Canvas. There are no written trials and no in-class quiz. The code you build with the videos is the whole submission.

<div class="callout check" markdown="1">
<p class="callout-title">When it is due</p>

The due date is posted on Canvas.

Plan your week. Coding along takes longer than watching — pause whenever the video compiles and runs, and do the same at your keyboard. Several short sittings beat one long night. Floor 8 (Trees) opens the same week; do not let the new floor eat your Warden time.
</div>

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/faith.svg' | relative_url }}" alt="Brother Faith, Abbot of the Sorted Tome — bearded monk in a dark brown robe with a brass clasp and a stopwatch on a brass cord."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Brother Faith stands with you at the gate</span>

Last midterm I asked you to *use* what four floors gave you against one Warden. This midterm I will ask you to *compose* what four floors gave you against more than one foe at a time. Chain. Walk. Echo. Line. If those four words live in your fingers by the time you submit, you will pass. If they live only in your notes, the marshalling yard will see it the moment the first wave arrives.
</div>
</div>

## How to complete this Warden

1. **Watch the Warden II videos and code along.** Type the encounter into your own project as the video builds it — pause, compile, and run every time the video does.
2. **Make sure it builds and runs.** `battle waves 2` should start the encounter, and both endings should be reachable. The Warden's own checks further down this page are a quick way to confirm.
3. **Submit your code** — push to GitHub, then turn it in on Canvas. See [Submission](#submission) below.

That is everything. The rest of this page describes what the videos build, so you can check your version against it.

## The encounter — *The Marshalling Yard*

This is what the videos build. You will program a **wave-survival encounter** into your dungeon app — the Warden does not fight you directly; the Warden sends waves at you, and the waves are how the four floors get exercised at once.

**Do.** In your floor-07 project (the one you've been building through stacks and queues), add a **`battle waves N`** command to `main.cpp` — where `N` is the number of waves the player wants to face. Factor the encounter into `battle/Battle.cpp` (the file already exists from Warden 1; add a second function alongside `runWardenBattle`). When the player types `battle waves 3`, the encounter begins with three waves queued up.

**You will receive (in your starter drop).** The public drop at `project/warden-02-starter/` ships everything the yard assumes, so the only thing left to build is the encounter itself:

- The **post-Floor-7 reference baseline** — `Chain` with its iterators, `Stack`, `Queue`, the Floor 7 commands, and the Warden 1 battle, all working. This is the state your own project should already be in.
- **`battle/Battle.cpp`** with the `runWaveSurvival` TODO scaffold — and, in its comments, the per-tie checklist and the self-check script.
- **`hero/UndoAction.h`** already carrying the one `playerHP` field the wave-survival undo needs — on Path A you add the same field to your own copy.
- The **README** with the exact Path A wiring diffs — the `UndoAction` field, the `Battle.h` declaration, the `main.cpp` dispatch.

Even on Path A — building in your own project, which is the preferred route — read the starter's battle file and README first: the checklist and wiring diffs in them are the map.

**What the encounter does:**

- **Stats.** Player starts at 40 HP. Each enemy has its own HP (suggested: imp 8, rat 5, skeleton 12 — numbers are yours to tune; document them in a comment).
- **Wave loop.** For each wave 1..N: enqueue a small group of enemies (suggested: wave *i* spawns *i + 1* enemies; pick the lineup however you like). The wave is over when its queue is empty. Then the next wave starts.
- **Turn loop within a wave.** Each turn: print current state (player HP, wave *i*/*N*, enemies remaining in this wave, the **front** enemy and its HP), present a numbered menu, read input, execute, repeat.
- **Menu — at least five options:**
  1. **Attack** — deal damage to the *front* enemy of the current wave. If its HP drops to 0 or below, dequeue it; the next-oldest enemy becomes the new front. If it survives, *it* retaliates this turn.
  2. **Use item** — display the inventory (which is still `hero.inventory`, a `Bag<Item>` — same as every prior floor) and prompt for an item name; apply the item's effect; turn ends. The front enemy retaliates after.
  3. **Inspect log** — print the last few entries of `hero.eventLog` in reverse-chronological order via the same `printLog` function template your Floor 5 iterators brought to life. **Free action** — does not consume a turn.
  4. **Undo** — reverse the most recent turn by popping the action stack and restoring its snapshot (player HP + inventory). **Free action** — does not consume a turn, and the front enemy does not retaliate. Maximum one undo per turn (no chained undo-undo loops). The wave queue is *not* rewound; see the F6 tie below for why.
  5. **Flee** — leave the encounter. The Warden does not chase; the marshalling yard remains closed and any uncleared waves remain.
- **Win condition.** All N waves cleared (every queue emptied) → print a victory message and the inner gate opens. Note your hero's surviving HP in the closing line.
- **Lose condition.** Player HP ≤ 0 → print a defeat message; the run ends.

**How it ties back to Floors 4 – 7** — the videos wire one tie from each floor into the battle code:

- **Floors 4 / 4½ (linked lists):** every turn — both the player's action and the front enemy's retaliation — must append a one-line string to `hero.eventLog` (already a `Chain<std::string>` from Floor 4½). The log grows forward, never backward; even `undo` appends an "(undo) reverted: <description>" entry rather than rewinding the chain. The log is what the **Inspect log** menu option reads.
- **Floor 5 (iterators):** the **Inspect log** menu option must call your Floor 5 `printLog` function template over `hero.eventLog`. Because every push elsewhere in the program is `push_front`, the most recent entry is at the chain's head — `begin()/end()` is newest-first; `rbegin()/rend()` is oldest-first (a "battle replay" framing). Pick whichever direction matches what Inspect log should mean for your encounter and document the choice in a one-line comment. The point is *iterator pair into `printLog`* — no subscripting the chain, no `chain.at(i)`, no manual `head()`-chase anywhere in your battle.
- **Floor 6 (stacks):** the undo history must be a `Stack<UndoAction>`. Every attack and every use-item pushes one `UndoAction` (with a snapshot of player HP and inventory) onto the stack *before* executing. `undo` pops the top entry and restores both. Your Floor 6 `UndoAction` holds a description and an inventory snapshot — no HP — so extend `hero/UndoAction.h` with one `int playerHP` field to make the snapshot cover both; the starter README shows the exact three-line diff. A comment above the stack's declaration must say in one line: *why a stack and not a queue.* A second comment above the `undo` body must name **one thing undo intentionally does not restore** (the wave queue is the obvious answer — pick that or another, and defend it).
- **Floor 7 (queues):** the current wave's enemies must be held in a `Queue<Enemy>`, with `front()` always returning the currently-targeted enemy and `dequeue()` only called when that enemy dies. The waves themselves may *also* be a `Queue<Wave>` (encouraged) — if you do that, document the nested-queue choice in a comment.

**Demo target.** Below is a real transcript of the reference encounter (`battle waves 2`), captured over piped input — so what the player typed (attack, inspect, undo, undo again, a bad `9`, then attacks to the end) is not echoed, and the bracketed lines are trims, not program output. It shows the required *behaviours*, not required text — your wording, your numbers, and your menu order may all differ. (One nuance: the reference shows the hero's surviving HP in its last state line; your win condition above asks for it in the closing line itself — do that.)

```
  >> Wave 1 enters: 2 enemies.

  -- Wave 1/2 --   you HP 40    enemies remaining: 2
    front of line: Imp #1  (HP 8, ATK 3)
    1. Attack front
    2. Use item
    3. Inspect log
    4. Undo
    5. Flee
  >   You strike Imp #1 for 7.  HP -> 1.
  Imp #1 retaliates for 3.  Your HP -> 37.

  -- Wave 1/2 --   you HP 37    enemies remaining: 2
    front of line: Imp #1  (HP 1, ATK 3)
  [same 5-line menu prints every turn — trimmed from here on]
  >   -- recent log (newest first; free action) --
   1.  Imp #1 struck for 3
   2.  struck Imp #1 for 7
   3.  wave 1 enters (2 enemies)
   4.  battle waves 2 — yard opens
   5.  began session as "Aria"
  (newest first; chain length 5)

  -- Wave 1/2 --   you HP 37    enemies remaining: 2
    front of line: Imp #1  (HP 1, ATK 3)
  >   Undid: attack Imp #1.  Your HP -> 40.  (wave queue is NOT rewound — front of line still acts next.)

  -- Wave 1/2 --   you HP 40    enemies remaining: 2
    front of line: Imp #1  (HP 1, ATK 3)
  >   You may only undo once per turn.
  [unchanged state block trimmed]
  >   index 9 out of bounds for size 5 — try again.

  -- Wave 1/2 --   you HP 40    enemies remaining: 2
    front of line: Imp #1  (HP 1, ATK 3)
  >   You strike Imp #1 for 7.  HP -> 0.
  Imp #1 falls.  Next in line steps forward.

  -- Wave 1/2 --   you HP 40    enemies remaining: 1
    front of line: Rat #2  (HP 5, ATK 2)
  >   You strike Rat #2 for 7.  HP -> 0.
  Rat #2 falls.  Next in line steps forward.
  >> Wave 1 cleared.

  >> Wave 2 enters: 3 enemies.

  -- Wave 2/2 --   you HP 40    enemies remaining: 3
    front of line: Imp #1  (HP 8, ATK 3)
  [four attack turns trimmed — Imp #1 falls (retaliation took you to 37), Rat #2 falls, Skeleton #3 wounded 12 -> 5 and retaliates for 4 -> you HP 33]
  >   You strike Skeleton #3 for 7.  HP -> 0.
  Skeleton #3 falls.  Next in line steps forward.
  >> Wave 2 cleared.

The yard quiets. The inner gate opens.
```

And the other ending, so you know both are reachable — the last two turns of a `battle waves 5` run that went all-attack:

```
  -- Wave 5/5 --   you HP 3    enemies remaining: 4
    front of line: Skeleton #3  (HP 5, ATK 4)
    1. Attack front
    2. Use item
    3. Inspect log
    4. Undo
    5. Flee
  >   You strike Skeleton #3 for 7.  HP -> 0.
  Skeleton #3 falls.  Next in line steps forward.

  -- Wave 5/5 --   you HP 3    enemies remaining: 3
    front of line: Imp #4  (HP 8, ATK 3)
    1. Attack front
    2. Use item
    3. Inspect log
    4. Undo
    5. Flee
  >   You strike Imp #4 for 7.  HP -> 1.
  Imp #4 retaliates for 3.  Your HP -> 0.

You fall in the yard. The gate stays shut.
```

<div class="callout check" markdown="1">
<p class="callout-title">The Warden's own checks — run these before you push</p>

A quick self-check, also printed in the header comments of the starter's `battle/Battle.cpp`. Every line is something you can verify at your own keyboard.

**Phase 1 — the skeleton holds.**
- `battle waves 2` starts an encounter, and the state line (your HP, wave *i*/*N*, enemies remaining, the front enemy and its HP) prints every turn.
- Both endings are reachable: you can clear every wave to the victory banner, and you can die to the defeat banner.

**Phase 2 — the yard holds.**
- Typing `9` or `abc` at the menu neither crashes nor exits — it re-prompts the *same* turn.
- **Inspect log** prints recent entries newest-first (or in the direction your one-line comment documents) and costs nothing — the same state line comes back, with no retaliation in between.
- Every action *and* every retaliation lands in the log: attack, take the retaliation, inspect — both lines are there.

**Phase 3 — the memory holds.**
- Attack, then **Undo**: your HP and inventory rewind, and the front enemy keeps its wounds.
- A second consecutive **Undo** is refused.
- **Flee** exits with waves uncleared — the run ends as Fled, not Victory.

If all three phases pass at your keyboard, your encounter matches the video's and you are ready to submit.

</div>

## Submission

**The due date is posted on Canvas.**

1. **Push to GitHub.** Commit the code you built along with the videos — at minimum `main.cpp`, `battle/Battle.h`, `battle/Battle.cpp`, and `hero/UndoAction.h` — and push it to your fork of the course repo.
2. **Submit on Canvas.** Turn in the Warden II assignment with the link to your GitHub repo.

Your code must build. If it does not compile, the Warden has won by default.

**Folder + code shape:**

```
[your project repo]/
  floor-07/
    main.cpp                          <-- new `battle waves N` command lives here
    battle/Battle.h, Battle.cpp       <-- add runWaveSurvival(...) alongside runWardenBattle
    hero/Chain.h                      <-- already there from Floor 4/4½
    hero/Stack.h, Queue.h             <-- already there from Floors 6, 7
    hero/UndoAction.h                 <-- from Floor 6; you add one playerHP field
```

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/mavren.svg' | relative_url }}" alt="Quartermistress Mavren, Keeper of the Chain Vault — a tall, narrow-shouldered keeper in a slate-grey coat, an iron link-ledger on a chain at her belt, hands clasped behind her back."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Mavren, from the north corner of the yard</span>

Write your encounter the way you write the ledger: *one link at a time*. Wire the wave queue first and run the battle — *just* the attack against one wave of one enemy, no items, no undo, no log. Compile. Run. *Then* push to `eventLog` on every turn and add the **Inspect log** option that walks it in reverse. Compile. Run. *Then* the stack of snapshots and the `undo` that restores HP and inventory. Compile. Run. *Then* multi-enemy waves and the `use item` branch. Compile. Run. A chain that is forged in one piece is a chain that breaks in one piece. *Add the next link only after the previous one held weight.*
</div>
</div>

<div class="callout bestiary" markdown="1">
<p class="callout-title">Bestiary · Warden of the Middle Gates</p>

**The Warden of the Middle Gates** — *HP: not measured here; the Warden does not fight the hero directly. Strength: equal to whichever floor of 4, 4½, 5, 6, 7 the hero understands least. Weakness: a hero whose four containers compose cleanly.*

The second of four wardens. Cataloguers caught its silhouette in the marshalling yard at the bottom of the Cisterns; the page they pinned to its entry shows armour, four sigils — chain link, lens, coiled echo, stamped ticket — and a single ember slit where eyes should be. The Warden does not strike; it *commands the yard*. Waves of small enemies arrive in arrival order, retaliate when struck, and only the hero whose inventory walks cleanly under an iterator and whose mistakes can be undone from a stack will see the inner gate open.

The Warden does not punish you for choosing the wrong container; the *yard* does. Pick `Bag<Item>` for the inventory and the iterator question is still answerable but the *reason* you needed iterators evaporates. Pick a queue for the undo stack and the most-recent action is the *last* one available, not the first — your `undo` will reverse the wrong turn at the worst time. The Warden watches. The Warden does not explain.

You will fight this creature inside the game you wrote. That fact, again, is the test.

Counter by:

- **Snapshot *before* you strike.** Push the `UndoAction` first, mutate second. Reversed, your undo faithfully restores the already-damaged state — it "works", and does nothing.
- **Never hold a reference to `front()` past a `dequeue()`.** The node is gone; the reference dangles. Read what you need out of the front enemy, *then* dequeue.
- **A free action ends nothing.** **Inspect log** and **Undo** must reach the top of the loop without the enemy moving — retaliation-on-inspect is the most common bug in this yard.
- **Catch inside the wave loop, not around it.** A `BagException` caught around the whole encounter unwinds the yard; caught inside the turn, it costs one re-prompt.

</div>

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/grix.svg' | relative_url }}" alt="Grix the Opportunist — green-skinned goblin with pointed ears, yellow eyes, gap-toothed grin, patched mismatched tunic, and a stolen brass key on a leather collar."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Grix has a study tip</span>

*Friend!* Wave survival — easy! Just make the wave a `std::vector<Enemy>`, attack `enemies[0]`, and when it dies, `enemies.erase(enemies.begin())`. Same shape, friend! Who needs a queue! (It is the same shape until the third wave, when erasing the front of a vector for the hundredth time has copied every later enemy a hundred times. The yard will not notice; the *Warden* will. Grix's hero has been stuck on wave one since Floor 4.)
</div>
</div>

---

*The yard ends one way or the other. The Warden does not announce the result; the inner gate opens, or it does not. Beyond the inner gate, the stair to Floor 8 — the **Hall of Lineages** — climbs back up. McCown is waiting at the top with his bestiary; this time, his entries have children.*
