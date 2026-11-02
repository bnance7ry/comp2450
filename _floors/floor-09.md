---
title: The Halving Hall
floor_number: Floor 9
order: 130
flavor_quote: "Ask the tree a name. It will not search everywhere — only left, or only right, and the half it does not choose it never thinks of again."
week: 11
zybook: "Chapter 8 (Trees) — full chapter; class focus §8.3–8.8 (binary search trees)"
---

## The briefing

The stair out of the scriptorium climbs to a smaller room, and a colder one. Where the Hall of Lineages sprawled — one great chart fanning into hundreds of twigs — this chamber holds a single tall chart, narrow, and *orderly* in a way the last one never was: every node on it has at most **two** lines coming down, one bearing left and one bearing right, and the names are not scattered. They are *sorted*. McCown is already here, though you did not see him pass you on the stair. He is holding a name-card and looking at the chart the way a man looks at a tool he trusts.

"Last floor you asked me a question," he says, without turning. "You asked why my lineage tree was no faster to search than the flat list I kept on the first floor. You were right to ask. It wasn't. To find a beast on that chart I had to read *every branch* — the tree remembered where things *belonged*, but it did not remember where things *were*. " He sets the card against the chart, at the root. "This chart is different. This chart has a *rule*."

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/mccown.svg' | relative_url }}" alt="Scrivener McCown, Keeper of the Bestiary — an aging scholar-monk in grey robes with ink-stained fingers and spectacles, holding a single name-card against a tall, narrow classification chart where every node forks into exactly two sorted branches."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Scrivener McCown, Keeper of the Bestiary</span>

One rule, and it is the whole floor. At *every* node on this chart: everything to the **left** is smaller, everything to the **right** is larger. That is all. But watch what it buys me. I want *Skeleton*. I stand at the root — *Goblin*. Does Skeleton come before Goblin or after? After. So I go **right**, to *Wraith* — and every beast whose name falls before Goblin, an entire branch of this chart, I have set aside in one step, unconsidered. Now: *Wraith*. Before or after? Before. **Left** — and there is Skeleton. Two questions, and the branches I never walked I never had to. A thousand beasts, and I would have my answer in ten such questions, not a thousand. I am not *reading* the chart. I am *halving* it. — You will build me this. And you will build the one piece I did not have to lend you on the last floor: the tree must own its nodes, and clean up after itself. The destructor you *read* in the Hall of Lineages, you *write* here.
</div>
</div>

Last week a node had a whole `Bag` of children and no order among them, so finding a thing meant asking *every* child — a scan, dressed up as a tree. This week a node has at most **two** children, `left` and `right`, and an iron rule binds them: *left is smaller, right is larger.* That single constraint is the difference between a tree you read and a tree that **reads itself**. It is called a **binary search tree**, and it is the structure that has quietly been under half the fast lookups you have ever used.

<figure class="diagram">
  <img src="{{ '/assets/diagrams/bst-invariant.svg' | relative_url }}" alt="A binary search tree rooted at 8, with 3 on the left and 10 on the right; 3 has children 1 and 6; 6 has children 4 and 7; 10 has a right child 14 with a left child 13. A search for 7 is traced: at 8 go left (7<8), at 3 go right (7>3), at 6 go right (7>6), arrive at 7. The discarded subtrees at each step are shaded out, showing roughly half the tree falling away per comparison."/>
  <figcaption>The invariant, and what it buys. <strong>Left &lt; node &lt; right</strong> at every node. To find <code>7</code> you compare once and go <em>one way</em>: each step throws away an entire subtree — about half of what was left. A scan of <code>n</code> nodes becomes a descent of about <code>log₂ n</code>.</figcaption>
</figure>

You will learn three things this week, and the third is a debt from last floor coming due:

1. **One rule turns a scan into a descent.** On a general tree, search recursed into *every* child. Here, the ordering lets you compare once and recurse into *one* child — left if you want something smaller, right if larger. Every step discards half the tree. That is the entire reason binary search trees exist, and it is why `recall <name>` this week is not just correct but *fast*.
2. **An in-order walk is a free sort.** Visit the left subtree, then the node, then the right subtree, and because left holds everything smaller and right everything larger, the values come out **in ascending order** — with no sort step anywhere. The tree does not just *store* your data; it keeps it *sorted*, continuously, through every insert and remove. `catalogue` is one four-line traversal and the bestiary prints alphabetical.
3. **You now write the Rule of Three.** On Floor 8 the recursive destructor and deep-copy ctor were *handed* to you, to read. This week they are yours to write — because a BST owns its nodes exactly the way that `Tree` did, and a structure that `new`s its nodes must `delete` them, deep-copy them, and not leak them. The recursion is the same shape you have written four times now. The stakes are just higher: get the destructor wrong and you leak half a tree.

There is a fourth thing, and it is the hard one: **removing** a node. Adding is easy — a new value always lands in an empty slot at the bottom. But removing a node that has *two children* means something has to take its place without breaking the rule, and choosing that something correctly is the single trickiest method you will write all semester. We save it for Friday, on purpose.

<figure class="diagram">
  <img src="{{ '/assets/diagrams/bst-remove-cases.svg' | relative_url }}" alt="Three panels showing BST node removal. Panel 1, 'leaf': removing a childless node just detaches it. Panel 2, 'one child': removing a node with a single child splices that child up into its place. Panel 3, 'two children': removing a node with two children replaces its value with its in-order successor (the smallest value in its right subtree), then deletes that successor — which is itself a leaf-or-one-child case."/>
  <figcaption>Removing a node is three cases. A <strong>leaf</strong> just detaches. A node with <strong>one child</strong> hands its place to that child. A node with <strong>two children</strong> can't simply vanish — so you copy its <em>in-order successor</em> (the smallest value on its right) up into it, then delete that successor, which is always an easier case. The trick is that the hard case reduces to a case you already solved.</figcaption>
</figure>

## Objectives

By the end of Floor 9 you will be able to:

- State the **binary-search-tree invariant** in one sentence (*left subtree smaller, right subtree larger, at every node*) and explain why it lets search discard half the tree at each step.
- Implement a recursive `insert` that places a value in its sorted slot, and explain why a value inserted into an empty subtree is always a new leaf.
- Implement a recursive `find` that descends one side per comparison, and articulate why this is O(log n) on a balanced tree and O(n) on a degenerate one.
- Implement an **in-order traversal** and explain why "left, node, right" yields ascending order — the tree's "free sort."
- Write the recursive **destructor** and **deep-copy constructor** for a node-owning tree (the Rule of Three you *read* on Floor 8), and say what leaks or aliases if either is wrong.
- Implement `remove` for all three cases — leaf, one child, two children — and explain why the two-child case copies the **in-order successor** up and why that successor is always a leaf-or-one-child node.
- Read a benchmark of linear scan vs. BST lookup and explain the diverging curves, *and* explain why inserting already-sorted data destroys the advantage.
- Name the single property a BST needs to *guarantee* O(log n) — **balance** — and identify it as the problem the next floor solves.

## Pre-class

### Reading (ZyBook Ch. 8, *Trees* — §8.3–8.8 this week)

You already read all of Chapter 8 on Floor 8. This week we **live inside §8.3–8.8** — the binary-search-tree sections you previewed then and were promised you'd return to. Re-read them; they are the week, not background.

- Before **Monday** — §8.3 *Binary search trees* (the ordering property) and §8.4 *BST search algorithm*. Say the rule out loud each step: *less than? go left. greater than? go right.* Then §8.7 *BST insert algorithm* — insert is the same downward walk as search, right up until it falls off the bottom into an empty spot. If you read one more, make it §8.6 *BST height and insertion order*: it shows, in the book's own words, why inserting in *sorted* order is the worst thing you can do to a tree — our phase-5 stick.
- Before **Wednesday** — §8.5 *BST inorder traversal*. The key sentence to internalize: *an inorder traversal visits a BST from smallest to largest.* Ask yourself **why** before class — it is the whole reason BSTs are everywhere. (§8.10 *BST: Recursion* is the recursive shape your `destroy` and `clone` will share.)
- Before **Friday** — §8.8 *BST remove algorithm*. The hard reading of the chapter: §8.8.1 is the leaf / single-child case, §8.8.2 the two-children case. Watch for the word **successor**. We will write it together, but arrive having seen the shape of the problem.

> **A note on "balanced."** The chapter shows you BSTs at their best — bushy, shallow, fast. It is honest about the catch, and so are we: a BST is only fast if it is *balanced*, and nothing in this floor's code forces it to be. Insert your data already sorted and the tree degenerates into a glorified linked list. Floor 9½ adds the rule that keeps it balanced. This floor earns that floor.

There are no pre-class videos beyond the chapter's own animations. Class is live coding, all three days.

## In-class (MWF)

| Day | Focus | Activity |
|-----|-------|----------|
| **M** | The invariant: insert + find | Open `hero/BST.h`. Read the provided `Node` (just `data`, `left`, `right`) and the public methods that delegate to the six helpers you'll write. Write `insertInto` together — *null slot ⇒ new leaf; else go left if smaller, right if larger.* Then `findFrom` — the same walk, but you **stop** at a match and return `nullptr` if you fall off. Run `selftest bst` (phases 2, 3, and 5 go green) and `recall Lich` — it descends to the beast in a handful of comparisons. (`catalogue` still waits on Wednesday's in-order walk — the tree is built, but nothing yet knows how to read it out in order.) |
| **W** | The free sort + the Rule of Three | Write `inOrderInto` — *left, node, right* — and run `catalogue`: alphabetical, from a four-line traversal. Then the debt from Floor 8: write the recursive `destroy` (free both children, then the node) and `clone` (copy the node, then deep-copy each side). Put Floor 8's `Tree` destructor on the projector beside it — *identical shape, two children instead of a bag.* `selftest bst` phases 4 and 6 (the deep-copy/leak check) go green. |
| **F** | Remove — the hard one | Do the three cases on the board *before* typing: leaf, one child, two children. Write `removeFrom`. The two-child case is the whole lesson: copy the **in-order successor** (leftmost node of the right subtree) up, then delete *it* — which is now an easy case. Run `forget Goblin`, then `catalogue` to see it gone and still sorted. Phase 7 goes green. Close with `benchmark bst`: watch linear climb while BST stays flat — then watch the closing note warn you what a *sorted* insert would have done. |

## The project — Floor 9

This week's increment is **a `BST<T>` and the fast, self-sorting bestiary it powers**: McCown's catalogue, rebuilt as a binary search tree you can list in order, look up in O(log n), and remove from — all while it keeps itself sorted.

You will receive (in your starter drop):

- Everything through Floor 8, fully working — `Bag`, `Chain` with iterators, `Stack`, `Queue`, `hotPotato`, `simulate`, `lint`, `undo`, the whole `Tree<T>` and its `taxonomy`/`lineage` commands, every benchmark and self-test. Floor 8's stubs are now reference code — including the `Tree` destructor and deep-copy you are about to write the BST versions of.
- A new `hero/BST.h` with **six helper bodies stubbed**: `insertInto`, `findFrom` (Monday); `inOrderInto`, `destroy`, `clone` (Wednesday); `removeFrom` (Friday). The `Node`, the access methods, `size`/`height` (the recursive shapes you wrote on Floor 8, handed back), and the public delegators are **provided**.
- A new `hero/BSTTests.cpp` — `selftest bst` runs `BST<int>` through **seven phases** against one fixed sample tree. Phase 5 is the one to watch: it inserts `{1,2,3,4,5,6}` *already sorted* and asserts the height is **5, not 2** — degeneration, made into a green test.
- The bestiary, now also built as a `BST<Monster>` keyed by name (the `Bag<Monster>` you've always had still works too — the BST sits *alongside* it). New commands: `catalogue`, `recall <name>`, `forget <name>`, and `benchmark bst [N]`.

You will write:

1. **Monday:** `insertInto`, `findFrom`. After this, `selftest bst` passes phases 2, 3, and 5 (phase 5 only needs `insert`), and `recall <name>` works. The tree is built — `catalogue` lists it once you add Wednesday's in-order walk.
2. **Wednesday:** `inOrderInto`, `destroy`, `clone`. After this, `catalogue` prints **alphabetical**, and self-test phases 4 and 6 (the deep-copy/no-leak check) pass.
3. **Friday:** `removeFrom`. After this, `forget <name>` works and phase 7 passes.

Demo target (Friday):

```
> selftest bst
  empty BST<int>: empty() && size==0 && height==0: OK
  insert: root==5 and size==7 over the sample: OK
  contains: 7 and 2 present, 6 and 404 absent: OK
  inOrder == {2,3,4,5,7,8,9} (ascending): OK
  degenerate: sorted inserts give height==5, not balanced: OK
  deep copy: mutating the original leaves the copy unchanged: OK
  remove: leaf(2), one-child(3), two-children(5) all correct: OK
  all phases OK

> catalogue
Bone Spider   HP 6   ATK 2   weakness: fire
Cave Troll   HP 28   ATK 7   weakness: fire
... (alphabetical) ...
Wraith   HP 14   ATK 4   weakness: holy
  (15 creatures, alphabetical; tree height 6)

> recall Lich
Lich   HP 35   ATK 6   weakness: holy
  (recalled from the tree)
> recall Drake
  'Drake' is not in McCown's catalogue.

> forget Goblin
  McCown strikes 'Goblin' from the tree. (14 remain.)

> benchmark bst
  N= 100000  query=last    linear=  1813.323 us  BST=     0.456 us  (tree height 40)
  ... your microseconds vary by machine, but the shape never does: BST flat, linear climbing ...
> quit
McCown notes your departure. "You leave in order."
```

### Lab 9 — *A Tree That Sorts Itself* (folded into the project)

There is no separate lab handout. The work you do this week *is* the lab. Commit `floor-09/lab-notes.md` with:

1. A transcript of the demo above (your own hero name; `recall` at least three creatures, one of them absent).
2. **The invariant, by hand.** On paper, insert `8, 3, 10, 1, 6, 14, 4, 7, 13` into an empty BST, one at a time, drawing the tree after each. Then trace `find(7)`: write down which way you go at each node, how many nodes you look at, and how many you *never look at*. One sentence: how does the number you looked at compare to the tree's height?
3. **In-order is sorted.** Write out the in-order traversal of your tree from step 2. Confirm it's ascending. In two sentences: *why* does "left, node, right" produce sorted order — what does the invariant guarantee about everything in the left subtree?
4. **The three removals.** From your tree, remove `4`, then `10`, then `8` (the root). Draw the tree after each and name which case fired: leaf, one child, or two children. For the root: which node moved up, and why does *that* value keep the tree in order, being bigger than everything on its left and smaller than everything else on its right?
5. **The degeneracy experiment.** Run `benchmark bst`. Paste the table. Then, in two sentences, explain the closing note: if you had inserted the monsters in *alphabetical* order instead of shuffled, what would the tree's height have been, and what would have happened to `recall`'s speed? (You are describing the problem Floor 9½ exists to solve.)
6. **One-paragraph reflection.** You have now built five containers on pointers — `Chain`, `Stack`, `Queue`, `Tree`, and `BST`. This is the first one that is *fast because of its shape*. What did the ordering rule buy you that the general `Tree` couldn't, and what did it cost you (think about `remove`)? And: the destructor you *read* on Floor 8, you *wrote* this week. Did it feel different to write than to read?

Your commit history should show at least three commits — Mon (`insert`/`find` + `catalogue`/`recall`), Wed (in-order + Rule of Three), Fri (`remove` + `forget` + lab notes).

<div class="character-card" markdown="1">
<div class="character-portrait">
  <img src="{{ '/assets/portraits/grix.svg' | relative_url }}" alt="Grix the Opportunist — green-skinned goblin with pointed ears, yellow eyes, gap-toothed grin, patched mismatched tunic, and a stolen brass key on a leather collar."/>
</div>
<div class="character-quote" markdown="1">
<span class="speaker">Grix the Opportunist has also built a binary search tree</span>

Grix learned the rule! Smaller left, bigger right. *Very* good rule. So Grix built his tree very carefully: he added his treasures *in order*, smallest first, so it would come out perfectly sorted. Aardvark-tooth, then Bone-button, then Copper-bit, then... and look! Every single one went to the **right**. Every time. Grix's tree is one long line leaning right, all the way down. ...It *is* a binary search tree, Grix checked the rule, the rule holds! Why does finding the Zinc-whistle take Grix exactly as long as reading his old list did. The rule is *correct*. The rule is just not... *helping*. (It is a list wearing a hat. Grix has been told this before.)
</div>
</div>

<div class="callout bestiary" markdown="1">
<p class="callout-title">Bestiary · Floor 9</p>

**The False Heir** — *HP: zero. Damage: corrupted order, vanished subtrees, lookups that lie.*
Strikes when `remove` mishandles a node with two children. The node has to be replaced by *exactly one* value — the in-order successor (smallest on the right) or predecessor (largest on the left) — and any other choice silently breaks the invariant. Pick a wrong replacement and the tree still *looks* like a tree, but `find` now walks past nodes that are really there and reports them missing. Worse: delete the two-child node outright and **both** its subtrees float free — half your catalogue, leaked and unreachable, gone until the program ends.

Counter by:

- **Reduce the hard case to an easy one.** Don't try to delete a two-child node in place. Copy its in-order successor's *value* up into it, then go `remove` that successor from the right subtree. The successor is the leftmost node of that subtree, so it has **no left child** — its removal is always the leaf or one-child case. The hard problem becomes one you already solved.
- **Return the new subtree root, and re-link it.** Every recursive `removeFrom` returns what should now sit in that slot, and the caller assigns it: `n->left = removeFrom(n->left, ...)`. Forget the assignment and you keep a pointer to a node you just deleted — a dangling reference, the Severed Branch's cousin from last floor.
- **The destructor is the same monster as Floor 4's leak, grown a second head.** A `Chain` leaked a *line*. A `BST` with a wrong `destroy` leaks a *subtree* — and if you delete a node before recursing into its children, you lose the only pointers to half your tree in one statement. Free the children first. Always.
- **The invariant is yours to keep; nothing enforces it.** Insert on the wrong side once and the node is filed where search will never look for it — present, but permanently invisible. The rule is only true because *your code* makes it true on every insert and every remove.
</div>

<div class="callout check" markdown="1">
<p class="callout-title">The Keeper's Check</p>

You are deep in the Trees stretch now (Floors 8–9½). This floor ends the way every floor ends: with a short stack of paper questions in class — closed notes, closed laptop, answers in your own hand — drawn from everything this floor taught. If you did the reading, wrote the code, and can say *why* this week's work earns its place in the game, it takes ten minutes.
</div>

---

*McCown takes your name-card — the one he has been carrying since the Hall of Lineages — and slots it into the chart, comparing as he goes: before this name, after that one, left, right, down to an empty branch where it fits and nowhere else. "Filed," he says, satisfied, "and findable." But the chart he files you into is leaning. From up here you can see what you could not from the floor: this tree, for all its rules, has grown lopsided — long on one side, stunted on the other — and somewhere above, a draft moves through a room where the branches are being bent back toward level by a hand you cannot see. The Nameless Bard tunes a string a half-step and does not yet play. The next room knows how to keep its balance. This one only hoped to.*
