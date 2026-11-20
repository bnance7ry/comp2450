---
title: The Hall of Names
floor_number: Floor 10
order: 150
flavor_quote: "A tree you must walk. A name you need only speak. The Hall keeps every name beside its meaning, and asks for nothing but the word."
week: 13
zybook: "Chapter 11 (Sets and Maps) — full chapter; class focus §11.1, §11.3–11.6"
---

## The briefing

The stair out of the Balanced Hall does not climb. It opens, level, into a long room you can see the end of — and the end is *quiet*. There is no chart here. Where McCown spent two floors straightening a tree that would not stay straight, this hall is lined with **shelves of name-plates**, each plate with a beast's whole record engraved beside it, and the plates are already in order — Bone Spider, Cave Troll, Cinder Bat — running off into the dark in a line so even it might have been ruled. Against the far wall stands a second, smaller shelf: every *kind* of weakness listed exactly once, no matter how many beasts share it. McCown is here, and for the first time in the stretch his hands are empty. He is not straightening anything.

"On the last two floors," he says, "I taught you to build the shelf, and then to keep it level. I will not make you build this one." He lays a hand flat on the nearest shelf, the way you rest a hand on something you trust. "It is already built — better than I could have, and it never leans. I do not tend it. I only have to know the *name*." He speaks a name to the shelf — *Lich* — and the plate answers, the whole record there at once, with no descent, no comparing, no walk. "The library tends it now. I am, at last, only *using* it."

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/mccown.svg' | relative_url }}" alt="Scrivener McCown, Keeper of the Bestiary — an aging scholar-monk in grey robes with ink-stained fingers and spectacles, at rest for the first time in the stretch: no chart to straighten, one hand resting on a long shelf of alphabetized name-plates, a single smaller shelf of distinct 'weaknesses' on the wall behind him."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Scrivener McCown, Keeper of the Bestiary</span>

Look at the shelf and tell me what you do not see. You do not see me sorting it. I added these plates in the order the beasts were *caught* — Goblin, then Wraith, then Skeleton, no order to it at all — and yet the shelf reads top to bottom in clean alphabet, Bone Spider to Wraith, because the shelf *orders itself on every plate I set down*. That is the thing you spent Floor 9 earning from a walk, and Floor 9½ learning not to build by hand: a balanced tree, keeping order for free. The library handed it to me finished — and laid a second gift on top: every plate has its *meaning* beside it, so I do not search for a name, I simply *ask*, and the answer is already there. A `std::set` for the names I only need to *know* are present. A `std::map` for the names whose *meaning* I need. You will not write the shelf. You will write the six small motions that *use* it — and you will be done by Friday, and you will have given up nothing you needed.
</div>
</div>

For five floors you built containers on raw pointers — `Chain`, `Stack`, `Queue`, `Tree`, `BST`, and the AVL balancing you deliberately stopped one step short of. The whole lesson of the Balanced Hall was an honest admission: *don't hand-roll the balanced tree; reach for `std::set` and `std::map`, which **are** balanced trees.* This floor is where you finally reach. You will write **client code** against `std::set`, `std::map`, and `std::pair` — you do **not** implement an associative container. The Trees stretch proper was Floors 8–9½; the Hall of Names begins the **associative-structures run** (Floors 10–11), and it cashes the promise the Bard sang you out on: *you stop building the shelves and start, at last, only using them.*

You will learn three things this week, and the first is a debt from last floor being *paid back to you*:

1. **The balanced tree you studied is already in the box.** `std::set` and `std::map` are balanced search trees (red-black trees). Declare one, insert into it in any order you like, and it keeps itself sorted and shallow on every insert — the exact property you earned from an in-order walk on Floor 9 and proved the library guarantees on Floor 9½. The payoff, said plainly: the structure you spent a floor *not* finishing is one declaration away, finished and tested. *(That `std::set`/`std::map` order ascending because they are balanced trees is the connective tissue this course draws — the ZyBook describes the classes but does not frame them as "the balanced tree from Chapter 10." That link is ours.)*
2. **A map is a set with a value bolted on.** A `std::set<std::string>` answers one question — *is this name present?* — in a single `count()` call, no loop. A `std::map<std::string, Monster>` answers a richer one — *given this name, hand me the whole record* — in a single `find()`. The thing Floor 9's `recall` did with a whole recursive descent is now one library call that returns a pointer to the value. You give up nothing you needed; you gain correctness, guaranteed balance, and far less code.
3. **Iterating a map hands you `std::pair`s, and the key is `const`.** Walk a `std::map` with a range-based `for` and each step yields a `std::pair<const Key, Value>` — which C++17 lets you unpack with **structured bindings**: `for (const auto& [name, m] : registry.byName())`. The key half is `const` because the map's whole order depends on it; let someone edit a key in place and the tree would be filed wrong and silently broken. *(Structured bindings are a language feature, not a ZyBook section.)*

<figure class="diagram">
  <img src="{{ '/assets/diagrams/registry-three-views.svg' | relative_url }}" alt="The same monster records, loaded from data/monsters.txt in file order (Goblin, Wraith, Skeleton, Bone Spider, and so on — not alphabetical), are fed into three standard containers. A std::map keyed by name comes out alphabetical: Bone Spider, Cave Troll, Cinder Bat. A std::set of distinct weaknesses collapses the duplicate fire, holy, blunt, light, water, slashing entries into six and keeps them sorted: blunt, fire, holy, light, slashing, water. A std::map from weakness to count records how many monsters share each: blunt 2, fire 6, holy 3, light 2, slashing 1, water 1. None were sorted by hand; std::set and std::map order on insert."/>
  <figcaption>One bestiary, three standard views. The records go in <strong>in file order</strong> — Goblin, Wraith, Skeleton, not alphabetical — and every view comes out <strong>sorted</strong>, because <code>std::set</code> and <code>std::map</code> are balanced trees that order on insert. <code>byName_</code> (a <code>map</code>) is the key→value index; <code>weaknesses_</code> (a <code>set</code>) collapses the duplicates to six distinct kinds; <code>weaknessCounts_</code> (a <code>map</code>) tallies how many fear each. <em>The free in-order sort of Floor 9, handed to you finished — and you wrote one declaration per view, no tree code at all.</em></figcaption>
</figure>

There is a fourth thing, and it is the trap that gives this floor its monster. A `std::map`'s `operator[]` is *not* a read. Use `m[key]` on a key that is missing and the map **default-constructs a value and inserts it** — so a query that only meant to *look* silently *grows the container*. Ask a counts-map "how many fear thunder?" with `weaknessCounts["thunder"]` and you do not just get `0`; you get a brand-new `thunder → 0` entry, a weakness no beast has, now haunting your distinct-weakness shelf. The fix is mechanical: ask with `count()`/`find()`, reserve `[]` for keys you mean to *set*, and make read-only query methods `const` so `[]` cannot even compile. We meet that one head-on Wednesday.

<figure class="diagram">
  <img src="{{ '/assets/diagrams/phantom-key.svg' | relative_url }}" alt="Two ways to ask a std::map of weakness counts how many monsters fear thunder, a weakness none have. Left, the wrong way: weaknessCounts of thunder via square brackets returns 0 but, because operator[] default-constructs and inserts a missing key, the map silently grows a new thunder-to-0 entry and size() creeps from 6 to 7. Right, the correct way: weaknessCounts.find of thunder returns the end iterator, the method returns 0 without touching the map, and the container is unchanged at 6 entries."/>
  <figcaption>The same question — <em>how many fear thunder?</em> (none do) — asked two ways. With <code>operator[]</code> (left) the missing key is <strong>default-constructed and inserted</strong>: you get <code>0</code>, but the map silently grows a phantom <code>thunder → 0</code> and <code>size()</code> creeps from 6 to 7. With <code>find()</code> (right) the iterator lands on <code>end()</code>, the method returns <code>0</code>, and the map is untouched. <strong>Reading is not free — <code>operator[]</code> is a writer wearing a reader's hat.</strong></figcaption>
</figure>

## Objectives

By the end of Floor 10 you will be able to:

- Choose between `std::set` (membership / uniqueness, no value) and `std::map` (key→value lookup) for a given problem, and justify the choice with a bestiary example of each.
- Use `std::set` operations — `insert`, `count` — to build a **distinct** collection that collapses duplicates and answers membership in one call, without a loop.
- Use `std::map` operations — `operator[]`/`emplace` to insert-or-update, `find` to look up a value or detect absence, `at`/`count` — and explain what each returns.
- Explain why a `std::set`/`std::map` comes out **sorted with no sort step** — that it *is* a balanced search tree — and name the floor where you built that thing by hand.
- Replace a hand-written recursive BST descent (`recall`) with a single `map::find`, and articulate honestly what you gave up (nothing you needed) and gained (correctness, guaranteed balance, less code).
- Iterate a `std::map` with a range-based `for` and **structured bindings** over `std::pair<const Key, Value>`, and explain why the key half is `const`.
- Identify and avoid the **`operator[]`-inserts-on-read** trap, and use `const` methods + `find`/`count` to make the bug impossible by design.
- Mutate one associative index (`forget`) while keeping a derived index consistent, and explain why three independent views of the same data (the Bag, the BST, the Registry) may legitimately disagree after a mutation.

## Pre-class

### Reading (ZyBook Ch. 11, *Sets and Maps* — the whole chapter; class focus §11.1, §11.3–11.6)

This is new reading, and it is the chapter that lets you stop building. Read **all of Chapter 11**; the sections called out below are only where class lives. One section is special: **§11.2 *Implementing a set ADT with a BST*** is the chapter *showing you* the BST-backed set you spent Floors 9–9½ learning **not** to hand-roll. Read it as "here is what is under the hood I am choosing not to build" — `std::set` already *is* this. You implement none of it.

- Before **Monday** — §11.1 **"Set abstract data type (ADT)"**: what a set *is* — distinct elements, add/remove, membership, cardinality, subset, union/intersection/difference. Then §11.3 **"Set"** — the STL `set` class (`insert()`, `erase()`, `count()`, and what `insert()`/`erase()` return). *(The section is titled simply "Set"; in prose we write `std::set` for clarity, but cite it as titled.)*
- Before **Wednesday** — §11.4 **"Map ADT"**: what a map/dictionary *is* — keys associated with values; insert (insert-or-*update*), get (returns a value or nothing). Then §11.5 **"Map"** — the STL `map` class (`emplace()`, `at()`, `count()`, and the `[]` operator with its **insert-on-access aside** — read that aside twice; it is this floor's monster).
- Before **Friday** — §11.6 **"Pair"**: `std::pair`, `make_pair()`, `.first` / `.second` — the element type a map iterator hands you. (The chapter's own labs, §11.7 *LAB: Unique random integers (set)* and §11.8 *LAB: Student grades (map)*, are optional extra practice; our project supersedes them.)

> **The connective tissue, stated once.** The ZyBook describes `std::set` and `std::map` as classes; it does not tell you they are the balanced tree from Chapter 10. They are — red-black trees — which is *why* they come out sorted and stay shallow. That is the through-line of this whole stretch: Floor 9 built the tree, Floor 9½ proved order isn't enough without balance and that the library guarantees both, and Floor 10 is you finally reaching for it. When `weaknesses` and `names` print in alphabetical order this week with no sort in your code, that order *is* the balanced tree, doing on every insert what your in-order walk did once.

There are no pre-class videos beyond the chapter's own animations. Class is live coding all three days.

## In-class (MWF)

| Day | Focus | Activity |
|-----|-------|----------|
| **M** | The set & the indexed map: build once, ask in one call | Open `bestiary/Registry.h` — a thin wrapper that re-indexes McCown's bestiary into a `std::map<std::string, Monster>`, a `std::set<std::string>` of distinct weaknesses, and a `std::map<std::string, int>` of counts. Read the **provided** constructor (it walks the bestiary and calls `index` once per monster) and the trivial accessors. Write `index` — three lines, one per container — and `knows` (membership via `map::count`, **not** a loop). Run `selftest registry` (phases 1–2 green) → `knows Lich` / `knows Drake`. Then `weaknesses`: the distinct set is **already sorted** — you inserted in file order and the order came free. That sorted-on-insert is the balanced tree from Floor 9½, with no traversal of your own. |
| **W** | Lookup, membership, and counts — three containers, three one-liners | Write `recall` (`map::find`, return `&it->second` or `nullptr` — the one-liner that replaces Floor 9's whole recursive descent), `hasWeakness` (`set::count` on `weaknesses_`), and `countWeakness` (`weaknessCounts_.find`, **never `[]`** — the method is `const`, so `[]` won't compile, which makes the Phantom Key bug *impossible*). Phases 3–5 go green. Demo: `lookup Lich` (full record, one `find`) → `weakness fire` (membership via the set, count via the map) → `names`, which lists the whole bestiary **in name order** via `for (const auto& [name, m] : registry.byName())` — the `std::pair` + structured-binding moment. |
| **F** | Mutating consistently — and why you stopped hand-rolling | Write `forget`: `erase` from `byName_`, decrement the count, and when a weakness's count hits 0 `erase` it from **both** `weaknessCounts_` and `weaknesses_`. Phase 6 goes green; `selftest registry` is all green. Demo: `strike Goblin` (gone from `names`; `fire` drops 6→5) — but `recall Goblin`, the **Floor 9 BST** command, *still finds it*: three independent indexes legitimately diverge after a mutation. Close with `benchmark names`: `std::map::find` vs Floor 9's `BST::find` vs Floor 1's linear scan — the map matches the balanced tree and crushes the scan, in **one line of code**. Then the whisper into Floor 11. |

**A note on two verbs named `recall`/`forget`.** Floor 9 already gave you `recall <name>` and `forget <name>`, bound to the **BST** — and they are still here, unchanged. The `Registry`'s own methods are *also* named `recall` and `forget` internally (that is the story echo — the same words McCown used on Floor 9), but their **REPL verbs are different on purpose**: you call the Registry's lookup with **`lookup <name>`** and its removal with **`strike <name>`**, so Floor 9's commands stay exactly as they were. When you `strike` a monster from the Hall of Names and then `recall` it from the tree and it is *still there*, nothing is broken — you mutated one of three independent indexes.

## The project — Floor 10

This week's increment is **the bestiary as standard associative containers** — McCown's catalogue re-indexed as a `std::map` keyed by name and a `std::set` of distinct weaknesses, added *in parallel* to the working `Bag<Monster>` and `BST<Monster>` from earlier floors. Nothing earlier is touched or removed; you write client code against the library's balanced trees.

You will receive (in your starter drop):

- Everything through Floor 9½, fully working — `Bag`, `Chain` with iterators, `Stack`, `Queue`, the whole `Tree<T>`, your **complete** `BST<T>` and its balance helpers, every benchmark and self-test. The prior floors' work ships as finished reference code; this starter is self-contained.
- A new `bestiary/Registry.h` — a small `Registry` class (header-only, like `BST.h`) wrapping three associative containers, with **six method bodies stubbed** in a clearly marked `// ===== YOU WRITE =====` block: `index`, `knows` (Monday); `recall`, `hasWeakness`, `countWeakness` (Wednesday); `forget` (Friday). The three members, the constructor, `size()`/`empty()`, and the three const accessors (`byName()`, `weaknesses()`, `weaknessCounts()`) are **provided**.
- A `bestiary/RegistryTests.cpp` harness — `selftest registry` runs a **fixed inline sample** `Registry` through **six phases** (it does *not* depend on `data/monsters.txt`, so the expected values are pinned). The stubs ship returning empty/false answers, so the harness **FAILs with a diagnostic** rather than failing to build.
- New REPL commands, all wired for you: `knows <name>`, `names`, `weaknesses`, `weakness <w>`, `lookup <name>` (→ the Registry's `recall`), `strike <name>` (→ the Registry's `forget`), and `benchmark names [N]`. **`benchmark names` builds its comparison `std::map` inline**, so it works from day one regardless of your stubs — it is the *comparison*, not your code.

You will write:

1. **Monday:** `index`, `knows`. After this, `selftest registry` passes phases 1–2, `knows <name>` answers truthfully, and `weaknesses` prints the distinct set already in order.
2. **Wednesday:** `recall`, `hasWeakness`, `countWeakness`. After this, phases 3–5 pass, `lookup <name>` returns a full record in one `find`, and `names` lists the bestiary in name order via structured bindings.
3. **Friday:** `forget`. After this, phase 6 passes and `selftest registry` is all green; then read `benchmark names` and explain why the map matches the balanced tree and beats the scan.

Demo target (Friday):

```
> selftest registry
  index: size==5, distinct weaknesses==3, count[holy]==3: OK
  knows: Lich present, Drake absent: OK
  recall: Wraith->hp==14, Drake==nullptr: OK
  hasWeakness: holy present, water absent: OK
  countWeakness: holy==3, water==0: OK
  forget: drop a shared weakness (count--), drop a last weakness (erased), absent==false: OK
  all phases OK

> knows Lich
  McCown knows 'Lich'.
> knows Drake
  McCown does not know 'Drake'.

> weaknesses
  blunt  (2 monsters)
  fire  (6 monsters)
  holy  (3 monsters)
  light  (2 monsters)
  slashing  (1 monsters)
  water  (1 monsters)
  (6 distinct weaknesses)

> lookup Lich
Lich   HP 35   ATK 6   weakness: holy
  (looked up in the Registry)

> weakness fire
  6 monsters fear fire.

> names
Bone Spider   HP 6   ATK 2   weakness: fire
Cave Troll   HP 28   ATK 7   weakness: fire
Cinder Bat   HP 4   ATK 1   weakness: water
Frostmaw   HP 22   ATK 6   weakness: fire
Goblin   HP 8   ATK 2   weakness: fire
Ironclaw Bear   HP 24   ATK 5   weakness: slashing
Lich   HP 35   ATK 6   weakness: holy
Marsh Lurker   HP 18   ATK 3   weakness: fire
Necrothrall   HP 16   ATK 4   weakness: light
Ratking   HP 9   ATK 2   weakness: fire
Shadow Hound   HP 12   ATK 4   weakness: light
Skeleton   HP 10   ATK 3   weakness: blunt
Stone Sentinel   HP 30   ATK 5   weakness: blunt
Wisp   HP 3   ATK 1   weakness: holy
Wraith   HP 14   ATK 4   weakness: holy
  (15 names, alphabetical — std::map keeps them ordered)

> strike Goblin
  Struck 'Goblin' from the Hall of Names. (14 remain.)
> weakness fire
  5 monsters fear fire.
> recall Goblin
Goblin   HP 8   ATK 2   weakness: fire
  (recalled from the tree)

> benchmark names
-- The Hall of Names: linear scan vs BST vs std::map (1000 iterations per cell) --
  N=    100  query=last    linear=     0.678 us  BST=   0.071 us  std::map=   0.082 us  (tree height 13)
  N=    100  query=absent  linear=     0.047 us  BST=   0.047 us  std::map=   0.053 us  (tree height 13)
  N=   1000  query=last    linear=     7.474 us  BST=   0.097 us  std::map=   0.121 us  (tree height 21)
  N=   1000  query=absent  linear=     0.441 us  BST=   0.057 us  std::map=   0.071 us  (tree height 21)
  N=  10000  query=last    linear=    54.031 us  BST=   0.153 us  std::map=   0.187 us  (tree height 30)
  N=  10000  query=absent  linear=     4.670 us  BST=   0.082 us  std::map=   0.100 us  (tree height 30)
  N= 100000  query=last    linear=   585.573 us  BST=   0.143 us  std::map=   0.239 us  (tree height 40)
  N= 100000  query=absent  linear=   156.566 us  BST=   0.087 us  std::map=   0.124 us  (tree height 40)

std::map::find tracks the BST — both grow with log N, both crush
the linear scan. The difference is the code: the BST was a class you
wrote across a whole floor; std::map was one declaration. And unlike
your plain BST, std::map is balanced (a red-black tree), so it NEVER
degenerates into a stick — the library gives you the balanced tree of
Floor 9½ and a key->value index on top of it, for free.

> quit
McCown notes your departure. "You leave in order."
```

*(The `benchmark names` microsecond numbers above are wall-clock — they vary run to run and machine to machine. What is reproducible and quotable: linear grows with N while BST and `std::map` stay flat, `std::map` tracks the BST, and the tree-height column climbs by about 10 each row as N grows. In Visual Studio the N=1000 row says height 22 instead of 21: the benchmark shuffles the names before building the tree, and Visual Studio's `std::shuffle` mixes them a little differently. The closing argument the command prints — that `std::map` is the balanced red-black tree of Floor 9½ with a key→value index on top, for free — is fixed text.)*

### Lab 10 — *The Word and the Meaning* (folded into the project)

There is no separate lab handout. The work you do this week *is* the lab. Commit `floor-10/lab-notes.md` with:

1. A transcript of the demo above (your own hero name). Include `lookup` of three creatures, one of them not in the bestiary (`lookup Drake` works), and at least one `strike`. (Your `benchmark names` microseconds will not match the page; that's fine.)
2. **Set or map?** Each question below is one line of code against one of the Registry's three containers (`byName_`, `weaknesses_`, `weaknessCounts_`). For each, write that line — the way it would appear inside a `Registry` method — for example `weaknesses_.count("fire") > 0`.
   (a) Does McCown know a monster named Wisp? (b) What is Wisp's attack? (c) Does anything fear light? (d) How many monsters fear holy?
   Then one sentence: when do you want a `std::set` instead of a `std::map`?
3. **Sorted for free, and the `const` key.** Run `names`. The monsters went in in *file* order (Goblin, Wraith, Skeleton, …). In one or two sentences: why do they come out alphabetical with no sort in your code, and which earlier floor had you build that same kind of structure by hand? Then: each element of the map is a `std::pair<const std::string, Monster>`, and the name is `const`. Suppose you could rename the `"Bone Spider"` key to `"Zombie"` without moving it. Where in the map would `"Zombie"` be sitting, and why would `find("Zombie")` then miss it?
4. **`recall`, then and now.** Open `hero/BST.h` and find `findFrom`: that recursive descent was Floor 9's `recall`. This week `recall` is one `map::find`. Name one thing you gained by switching and one thing you gave up.
5. **The Phantom Key — try it.** In `countWeakness`, temporarily replace the two-line body with `return weaknessCounts_[w];` and build. Paste the first error line. **Then put the `find` version back and rebuild.** In your own words: (a) what does `[]` do when the key isn't in the map, and (b) why won't the compiler let you use it here?
6. **Three views, one source.** After `strike Goblin`, `names` no longer lists Goblin, but `recall Goblin` (the Floor 9 tree command) still finds it. In one or two sentences: why is that correct, not a bug?
7. **One-paragraph reflection.** The Registry keeps every name in alphabetical order whether you need it or not. Name one command from this week that *used* that order and one that didn't need it at all. If all you ever asked was "is this name here?", would keeping the order be worth paying for? (Floor 11 is about giving it up.)

Your commit history should show at least three commits — Mon (`index`/`knows`), Wed (`recall`/`hasWeakness`/`countWeakness`), Fri (`forget` + lab notes).

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/grix.svg' | relative_url }}" alt="Grix the Opportunist — green-skinned goblin with pointed ears, yellow eyes, gap-toothed grin, patched mismatched tunic, and a stolen brass key on a leather collar."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Grix the Opportunist counts the things nobody fears</span>

Grix loves the new shelf! No more building trees, Grix just *asks*. So Grix is taking inventory. How many beasts fear *thunder?* Grix writes `count = weaknessCounts["thunder"]`. It says zero. Good, none. How many fear *psychic?* `weaknessCounts["psychic"]` — zero again. *Radiant?* Zero. Grix is very thorough; Grix asks about *everything*. ...But now Grix looks at his shelf of weaknesses, the one that should have six kinds on it, and it has — Grix counts — *nine?* Thunder is on it. Psychic is on it. Radiant. With zeros next to them. Grix never *added* those! Grix only *asked!* ...Oh. The bracket. The bracket does not just *look*, it *makes*. Grix asked "is thunder here," and the shelf heard "put thunder here." Grix has been filling his own shelf with ghosts. (Grix needed `find`. Grix always needs the thing he didn't use.)
</div>
</div>

<div class="callout bestiary" markdown="1">
<p class="callout-title">Bestiary · Floor 10</p>

**The Phantom Key** — *HP: zero. Damage: indexes that grow keys no one inserted; lookups that lie by creating the very thing they claim to find.*
Strikes when `operator[]` is used to *read* a `std::map`. On a missing key, `[]` does not return "not found" — it **default-constructs a value and inserts it**, so a query you meant as read-only silently *mutates* the structure. A set of "known weaknesses" accumulates an entry for every weakness ever *asked about*; a word-frequency map sprouts zero-count words; `size()` creeps upward on a container you only ever queried. Nothing looks broken — the value you read back is even *correct* (`0`, "not present") — which is exactly why the Phantom Key is so hard to catch: it answers your question truthfully and corrupts your data in the same breath.

Counter by:

- **Ask with `count()` or `find()`; reserve `[]` and `at()` for keys you mean to set or know exist.** `m.count(k)` and `m.find(k)` never insert. `m[k]` always *might*. That is the whole rule.
- **Make read-only query methods `const`.** On a `const` map, `operator[]` will not compile — so the right design makes the bug *mechanically impossible*. This floor's `countWeakness` is `const` for exactly that reason; reach for `[]` inside it and the compiler stops you.
- **Remember a phantom insert on a balanced tree may also force a phantom *rotation*.** The map is a red-black tree; inserting a key it didn't need can re-balance the tree to make room. You paid O(log n) — and possibly a rotation — to corrupt your own data while *looking*.
- **The Phantom Key completes a family.** Floor 9's False Heir broke *order*, so `find` lied. Floor 9½'s Leaning Tower kept order but lost *balance*, so `find` crawled. The Phantom Key keeps both order and balance and instead **silently grows the container on a read** — the associative-era version of "the structure betrays you while looking perfectly correct."
</div>

<div class="callout check" markdown="1">
<p class="callout-title">The Keeper's Check</p>

You have finished the Trees stretch (Floors 8–9½) and stepped into the associative run (Floors 10–11). This floor ends the way every floor ends: with a short stack of paper questions in class — closed notes, closed laptop, answers in your own hand — drawn from everything this floor taught. If you did the reading, wrote the code, and can say *why* this week's work earns its place in the game, it takes ten minutes.
</div>

---

*McCown speaks a last name to the shelf and the plate answers, instantly, as it has all along — and you understand, now, that "instantly" is a small lie. The shelf is a balanced tree; to find the plate it still **walks**, quietly, log n steps down through order it maintains on every insert. Fast. Honest. Ordered. From the corridor beyond comes a different sound — not the soft settle of a shelf ordering itself, but a hundred names spoken at once into the dark and a hundred answers coming back with no walk at all, no order to them whatsoever, each name landing exactly where it lives because the hall does not **search** for a name — it **computes** where the name is and goes straight there. A whisper, not a walk. The Nameless Bard lets a single open string ring and does not damp it. "They scatter the names on purpose, in the next hall," McCown says, almost to himself. "No order at all — and every answer in one breath. As long as no two names whisper to the same place." He does not explain the last word. It hangs there, ringing with the string: **collisions.** The Hall of Whispers — hash tables — is the next floor down.*
