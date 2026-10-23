---
title: The Warden of the Foundations
floor_number: "Warden · I"
order: 50
flavor_quote: "Four floors built you a hero. The Warden waits for the hero to use what was built."
covers: "Floors 0–3 · Midterm 1"
---

## The gate

Steil's forge has gone cold behind you. Ahead, a vaulted antechamber — empty but for a single shape standing at its centre, and a closed gate beyond it. On the far side of the gate, you can hear Foust's cart-wheel; Floor 4 is on the other side.

The shape does not move *yet*. It has no face you can name. It is the **Warden of the Foundations** — the first of four — and it does not bring a fifth lesson. It brings every one of the four above, and asks whether they took. To prove they did, **you will build it into the game you have been building — and then fight it**.

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/warden-01.svg' | relative_url }}" alt="The Warden of the Foundations — a hooded, faceless figure in dark iron plate, only two ember-gold eye-points visible inside the deep cowl. Four small sigils on the breastplate: hourglass, magnifying glass, forge flame, anvil. Nameplate blank."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">The Warden, who has no name to give</span>

*Build me into your game — and then strike me.*
*One encounter. Win it, or do not pass.*
</div>
</div>

**This page is your Midterm 1.** It replaces the timed paper exam, and it is one job: **follow along with the recorded Warden I videos, building the encounter in your own project as you watch, then submit the code you end up with** — pushed to GitHub and turned in on Canvas. There are no written trials and no in-class quiz. The code you build with the videos is the whole submission.

<div class="callout check" markdown="1">
<p class="callout-title">When it is due</p>

The due date is posted on Canvas.

Plan your week. Coding along takes longer than watching — pause whenever the video compiles and runs, and do the same at your keyboard. Several short sittings beat one long night.
</div>

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/faith.svg' | relative_url }}" alt="Brother Faith, Abbot of the Sorted Tome — bearded monk in a dark brown robe with a brass clasp and a stopwatch on a brass cord."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Brother Faith stands with you at the gate</span>

I am not going to make you race a paper exam under my stopwatch. I am going to ask you to *use* what these four floors gave you — in the game you have been building, against the Warden in front of you. Search. Sort. Stamp. Catch. If those four words live in your fingers by the time you submit, you will pass. If they live only in your notes, the Warden will see it the moment you step on the floor.
</div>
</div>

## How to complete this Warden

1. **Watch the Warden I videos and code along.** Type the encounter into your own project as the video builds it — pause, compile, and run every time the video does.
2. **Make sure it builds and runs.** `battle warden` should start the encounter, and both endings should be reachable. The Warden's own checks further down this page are a quick way to confirm.
3. **Submit your code** — push to GitHub, then turn it in on Canvas. See [Submission](#submission) below.

That is everything. The rest of this page describes what the videos build, so you can check your version against it.

## The encounter

This is what the videos build. You will program the Warden of the Foundations into your dungeon app as a real, playable boss battle, and you will fight it.

**Do.** The encounter lives in one fixed place: `runWardenBattle` in `battle/Battle.h` + `battle/Battle.cpp`. If you are continuing your own floor-03 project (the one you've been building all term), copy the starter's `battle/` folder in and add the one-line **`battle warden`** dispatch to your `main.cpp` — the starter README shows the exact snippets. If you are starting fresh from the warden starter drop, the dispatch is already pre-wired. Either way, how you decompose the code *inside* those two files — helpers, private types, the shape of the loop — is entirely yours. When the player types `battle warden`, the encounter begins.

**You will receive (in your starter drop).** The starter, `project/warden-01-starter/`, ships everything except the battle itself:

- a pre-wired `main.cpp` — on Path B the `battle warden` dispatch is already in place;
- `battle/Battle.h` — the ready `BattleException` and the `BattleOutcome` contract `main.cpp` depends on;
- `battle/Battle.cpp` — the requirements checklist, a suggested outline, and a self-check script, all in its comments;
- the README, with the exact Path A wiring diffs if you are continuing your own `floor-03` project.

Even on Path A — your own project — read the starter's battle file and README first: the checklist and wiring diffs in them are the map.

**What the encounter does:**

- **Stats.** Player starts at 30 HP. Warden starts at 50 HP. (Numbers are yours to tune; document them.)
- **Turn loop.** Each turn: print current state (both HPs, last action), present a numbered menu, read input, execute, repeat.
- **Menu — at least four options:**
  1. **Attack** — deal damage to the Warden. Warden retaliates the same turn.
  2. **Use item** — pick from your inventory; apply effect; turn ends.
  3. **Inspect Warden** — print the Warden's HP and one of its sigils as a hint (free action — turn does *not* end).
  4. **Flee** — leave the encounter. The Warden does not chase; the gate stays closed.
- **Win condition.** Warden HP ≤ 0 → print a victory message and the gate opens.
- **Lose condition.** Player HP ≤ 0 → print a defeat message; the run ends.

**How it ties back to Floors 0 – 3** — the videos wire one tie from each floor into the battle code:

- **Floor 0 (ADT):** the available menu actions for the current turn must be held in a container of your choice. In a comment above the declaration, name the ADT and defend it in one sentence.
- **Floor 1 (search):** the "Use item" branch must call `findByName<Item>` (your Floor 3 function template) on the hero's inventory to look up the item the player typed.
- **Floor 2 (sort):** when the "Use item" menu is displayed, the inventory must be sorted at display time with a comparator (via `std::sort` or your Floor 2 `sortInventory`) — by `value` (the healing-power stand-in), `weight`, or `name`, your call — and the choice documented in a comment.
- **Floor 3 (templates + exceptions):** invalid menu input (out-of-range number, unknown item name) must `throw BattleException` (a ready skeleton ships in `battle/Battle.h`) — or `BagException` where a bad index really is the fault; either way, a type derived from `std::exception`. The throw must be caught **inside the battle loop** so the player gets a clean error and another menu prompt — not a crash, not an exit. The player's inventory must remain a `Bag<Item>`.

**Demo target.** Below is a captured run from the reference solution, so you can see the shape of a passing battle. It shows the required *behaviours*, not required text — your wording, your numbers, and your menu order may differ:

```
> battle warden
  -- Your turn --   you HP 30    Warden HP 50
    1. Attack
    2. Use item
    3. Inspect Warden
    4. Flee
  > 1
  You strike for 6.  Warden HP -> 44.
  The Warden retaliates for 4.  Your HP -> 26.

  -- Your turn --   you HP 26    Warden HP 44
    ...
  > 3
  Warden of the Foundations.  HP 44 / 50.  No visible weakness.  (free action)

  -- Your turn --   you HP 26    Warden HP 44
    ...
  > 9
  index 9 out of bounds for size 4 — try again.

  -- Your turn --   you HP 26    Warden HP 44
    ...
  > abc
  'abc' is not a menu number (enter 1 to 4) — try again.

  -- Your turn --   you HP 26    Warden HP 44
    ...
  > 2
  Choose an item by name:
   1.  Cloak of shadows  (wt 1.5, val 80)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Rusty sword       (wt 4.0, val 5)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Iron key          (wt 0.1, val 0)
  > Healing potion
  You drink Healing potion. HP -> 30.
  The Warden strikes while you fumble.  Your HP -> 26.

[... one failed item lookup, seven Attack turns, and two more Healing potions trimmed ...]

  -- Your turn --   you HP 14    Warden HP 2
    ...
  > 1
  You strike for 6.  Warden HP -> 0.

The Warden falls. The gate opens.
```

And the other ending, so you know both are reachable:

```
  -- Your turn --   you HP 2    Warden HP 8
    1. Attack
    2. Use item
    3. Inspect Warden
    4. Flee
  > 1
  You strike for 6.  Warden HP -> 2.
  The Warden retaliates for 4.  Your HP -> 0.

You fall. The gate stays shut.
```

<div class="callout check" markdown="1">
<p class="callout-title">The Warden's own checks — run these before you push</p>

A quick self-check, also printed in the header comments of the starter's `battle/Battle.cpp`. Every line is something you can verify at your own keyboard.

**Phase 1 — the skeleton holds.**

- `battle warden` starts the encounter from the main prompt.
- The state line — both HPs — prints at the top of every turn.
- Both endings are reachable: win one run, lose one on purpose.

**Phase 2 — the gate holds.**

- Type `9` at the menu: clean error, re-prompt, *same* turn — no crash, no damage taken.
- Type a word like `abc`: same story.
- Inspect the Warden: no retaliation, and the turn does not end.

**Phase 3 — the ties hold.**

- The items menu appears sorted by your documented criterion.
- A mistyped item name errors cleanly and re-prompts.
- Open your own file and put a finger on each of the four ties — [F0], [F1], [F2], [F3].

If all three phases pass at your keyboard, your encounter matches the video's and you are ready to submit.

</div>

## Submission

**The due date is posted on Canvas.**

1. **Push to GitHub.** Commit the code you built along with the videos — at minimum `main.cpp`, `battle/Battle.h`, and `battle/Battle.cpp` — and push it to your fork of the course repo.
2. **Submit on Canvas.** Turn in the Warden I assignment with the link to your GitHub repo.

Your code must build. If it does not compile, the Warden has won by default.

**Folder + code shape:**

```
[your project repo]/
  floor-03/
    main.cpp                       <-- one-line `battle warden` dispatch lives here
    battle/
      Battle.h, Battle.cpp         <-- runWardenBattle lives here
    hero/Bag.h, BagException.h     <-- already there from Floor 3 starter
```

The `battle/` location is fixed — the starter's `CMakeLists.txt` points at `battle/Battle.cpp`. What's yours to decide is how you organise the code *inside* those two files.

Steil catches you at the gate on your way in.

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/steil.svg' | relative_url }}" alt="Forgemaster Steil, Master of the Cold Forge — long brown hair streaked with gray, heavy beard, dark leather apron with brass anvil pin over a rust-red tunic."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Steil, leaning on his hammer at the gate</span>

When you write the battle, do not write it all at once. Write *one turn* — print, prompt, read, attack, retaliate. Compile. *Run it.* Then write the next move. Builders who write the whole forge before lighting the fire end up with a forge that does not light. The Warden knows this. So does any compiler that has shouted at you. Read the first line of every error message; ignore the rest until the first one is solved.
</div>
</div>

<div class="callout bestiary" markdown="1">
<p class="callout-title">Bestiary · Warden of the Foundations</p>

**The Warden of the Foundations** — *HP: 50 (default). ATK: 4 per turn. Weakness: a hero who has actually used what the four floors taught.*
The first of four wardens. Cataloguers caught its silhouette but never its name; the page they pinned to its entry shows armour, four sigils, and two ember points where eyes should be. Below the figure, the name slot is struck through. The Warden fights at the strength of whichever floor you understand *least* — a hero who is strong on three floors and weak on one is a hero the Warden picks apart at the seam.

The Warden does not punish you for using your tools. It punishes you for **letting your tools punish your understanding**. A hero who types the battle along with the video, runs it, breaks it, fixes it, and knows what each line is for — passes. A hero who copies the finished file without ever running it — learns nothing the Warden cannot see through.

You will fight this creature inside the game you wrote. That fact is the test.

Counter by:

- **Catch *inside* the loop, not around it.** A `catch` outside the loop turns one typo into a forfeit — the player is ejected from the encounter instead of re-prompted.
- **Validate before you mutate.** Read the input, validate it, *then* apply damage — or a bad turn half-executes.
- **Inspect must not retaliate.** Free means free — test it.
- **Sort at display time, not at startup.** A battle changes the inventory under you; a menu sorted once in `main` lies by the third turn.

</div>

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/grix.svg' | relative_url }}" alt="Grix the Opportunist — green-skinned goblin with pointed ears, yellow eyes, gap-toothed grin, patched mismatched tunic, and a stolen brass key on a leather collar."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Grix has a study tip</span>

*Friend!* The boss battle — easy! Skip the videos, jump to the last minute, squint at the screen, and copy whatever code is showing! Push it, friend! Works *every time.* (The last minute shows forty lines of a three-hundred-line file. It does not work any time. Grix has tried. Grix's build has not compiled since Floor 1.)
</div>
</div>

---

*The battle ends one way or the other. The Warden does not announce the result; it falls, or you do. Beyond the gate, the stair to Floor 4 — the **Chain Vault** — descends into the dark. Foust is already there with his cart, sorting maps.*
