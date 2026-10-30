// COMP 2450 — Wardens of the Foundations + Middle Gates
// battle/Battle.cpp
//
// This file holds BOTH boss encounters now.
//
//   * runWardenBattle    — Midterm 1 reference (POST-Warden-1 baseline).
//                          Already filled in for you. Do not modify
//                          unless you intend to change the M1 behaviour.
//   * runWaveSurvival    — Midterm 2 work.  THE WORK FOR THIS MIDTERM
//                          IS HERE.  Read the public Warden 2 page
//                          before you start typing.

#include "Battle.h"

#include <algorithm>
#include <iostream>
#include <string>

#include "../bestiary/Search.h"
#include "../hero/Bag.h"
#include "../hero/BagException.h"
#include "../hero/Item.h"
#include "../hero/Queue.h"
#include "../hero/Sort.h"
#include "../hero/Stack.h"
#include "../hero/UndoAction.h"

namespace dungeon {

namespace {

// =====================================================================
// WARDEN 1 — single boss (Floors 0–3). DONE.
// =====================================================================

constexpr int kPlayerStartHP   = 30;
constexpr int kWardenStartHP   = 50;
constexpr int kPlayerAttackDmg = 6;
constexpr int kWardenAttackDmg = 4;

enum class MenuAction { Attack, UseItem, Inspect, Flee };

struct MenuOption {
    int         number;
    std::string label;
    MenuAction  action;
};

void printMenu(const Bag<MenuOption>& menu, int playerHP, int wardenHP) {
    std::cout << "\n  -- Your turn --   you HP " << playerHP
              << "    Warden HP " << wardenHP << "\n";
    for (std::size_t i = 0; i < menu.size(); ++i) {
        std::cout << "    " << menu[i].number << ". " << menu[i].label << "\n";
    }
    std::cout << "  > ";
}

MenuAction readMenuChoice(const Bag<MenuOption>& menu) {
    std::string line;
    if (!std::getline(std::cin, line)) return MenuAction::Flee;
    int n = -1;
    try { n = std::stoi(line); }
    catch (...) {
        throw BagException(
            static_cast<std::size_t>(menu.size() + 1),
            menu.size());
    }
    for (std::size_t i = 0; i < menu.size(); ++i) {
        if (menu[i].number == n) return menu[i].action;
    }
    throw BagException(static_cast<std::size_t>(n), menu.size());
}

// Apply the named item to the player's HP.  Shared between BOTH wardens
// because the inventory + heal mechanic does not change between them —
// only the max-HP cap does.
bool useItem(Hero& hero, int& playerHP, int maxHP) {
    if (hero.inventory.empty()) {
        std::cout << "  Your satchel is empty.\n";
        return false;
    }
    sortInventory(hero, "value desc");
    std::cout << "  Choose an item by name:\n";
    printInventory(hero);
    std::cout << "  > ";
    std::string name;
    if (!std::getline(std::cin, name) || name.empty()) {
        std::cout << "  You hesitate.\n";
        return false;
    }
    const Item* it = findByName<Item>(hero.inventory, name);
    if (!it) throw BagException(0, hero.inventory.size());
    if (it->name.find("otion") != std::string::npos) {
        playerHP = std::min(playerHP + 12, maxHP);
        std::cout << "  You drink " << it->name << ". HP -> " << playerHP << ".\n";
    } else {
        std::cout << "  You ready " << it->name << " — but it is not a consumable.\n";
    }
    return true;
}

}  // anonymous namespace

BattleOutcome runWardenBattle(Hero& hero) {
    int playerHP = kPlayerStartHP;
    int wardenHP = kWardenStartHP;

    Bag<MenuOption> menu;
    menu.push_back({1, "Attack",         MenuAction::Attack});
    menu.push_back({2, "Use item",       MenuAction::UseItem});
    menu.push_back({3, "Inspect Warden", MenuAction::Inspect});
    menu.push_back({4, "Flee",           MenuAction::Flee});

    hero.eventLog.push_front("battle warden — engaged");

    while (playerHP > 0 && wardenHP > 0) {
        try {
            printMenu(menu, playerHP, wardenHP);
            switch (readMenuChoice(menu)) {
                case MenuAction::Attack: {
                    wardenHP -= kPlayerAttackDmg;
                    std::cout << "  You strike for " << kPlayerAttackDmg
                              << ".  Warden HP -> " << std::max(wardenHP, 0) << ".\n";
                    hero.eventLog.push_front(
                        "you struck for " + std::to_string(kPlayerAttackDmg));
                    if (wardenHP > 0) {
                        playerHP -= kWardenAttackDmg;
                        std::cout << "  The Warden retaliates for "
                                  << kWardenAttackDmg
                                  << ".  Your HP -> " << std::max(playerHP, 0) << ".\n";
                        hero.eventLog.push_front(
                            "the Warden struck for " + std::to_string(kWardenAttackDmg));
                    }
                    break;
                }
                case MenuAction::UseItem: {
                    useItem(hero, playerHP, kPlayerStartHP);
                    if (wardenHP > 0 && playerHP > 0) {
                        playerHP -= kWardenAttackDmg;
                        std::cout << "  The Warden strikes while you fumble.  Your HP -> "
                                  << std::max(playerHP, 0) << ".\n";
                        hero.eventLog.push_front(
                            "the Warden struck for " + std::to_string(kWardenAttackDmg));
                    }
                    break;
                }
                case MenuAction::Inspect: {
                    std::cout << "  Warden of the Foundations.  HP " << wardenHP
                              << " / " << kWardenStartHP
                              << ".  No visible weakness.  (free action)\n";
                    break;
                }
                case MenuAction::Flee: {
                    hero.eventLog.push_front("battle warden — fled");
                    return BattleOutcome::Fled;
                }
            }
        }
        catch (const BagException& e) {
            std::cout << "  " << e.what() << " — try again.\n";
        }
    }

    if (wardenHP <= 0) {
        hero.eventLog.push_front("battle warden — outcome: Victory");
        return BattleOutcome::Victory;
    }
    hero.eventLog.push_front("battle warden — outcome: Defeat");
    return BattleOutcome::Defeat;
}

// =====================================================================
// WARDEN 2 — wave survival (Floors 4–7).  YOU BUILD THE BODY.
// =====================================================================
//
// Re-read the public midterm page if anything below is unclear.
//
// REQUIRED MECHANICS
// =====================================================================
// Player starts at 40 HP. Tune as you like; document tunings in
// encounter-notes.md.
//
// For each wave 1..N: build a Queue<Enemy> of enemies (lineup is yours
// to design — wave i with i+1 enemies is a good default).  The wave is
// over when its queue is empty.  Then the next wave begins.
//
// MENU (at minimum, five options):
//   1. Attack front  — damage the FRONT enemy of the current wave;
//                      dequeue it if HP <= 0; otherwise it retaliates
//   2. Use item      — show inventory, pick by name; effect; front
//                      enemy retaliates after
//   3. Inspect log   — print the last few entries of hero.eventLog
//                      via printLog; FREE action — turn does NOT end
//   4. Undo          — pop the most recent action off your undo stack;
//                      restore player HP + inventory.  FREE action.
//                      Limit one per turn (no chained undo-undo).
//                      The wave queue is NOT rewound — see F6 below.
//   5. Flee          — leave; the yard stays open with uncleared waves
//
// END:
//   Victory  when all N waves are cleared
//   Defeat   when playerHP <= 0
//   Fled     when the player chose Flee
//
// FLOOR-TIED REQUIREMENTS — ALL FOUR MUST APPEAR IN YOUR CODE
// =====================================================================
//
//   F4/4½ (linked lists) — every turn appends ONE entry (or one for
//                          your action + one for the retaliation) to
//                          hero.eventLog (a Chain<std::string>).  The
//                          log grows FORWARD; even `undo` appends an
//                          "(undo) reverted: …" entry rather than
//                          rewinding the chain.
//
//   F5 (iterators)       — the Inspect-log branch MUST call printLog
//                          on hero.eventLog with an iterator pair.
//                          begin()/end() walks newest-first (because
//                          eventLog is push_front'd everywhere);
//                          rbegin()/rend() walks oldest-first (a
//                          "battle replay" framing).  Either is fine —
//                          document the choice in a one-line comment.
//                          NO subscripting, NO chain.at(i), NO manual
//                          head()-chase.
//
//   F6 (stacks)          — the undo history MUST be a Stack<UndoAction>
//                          (local to this function, OR hero.undoStack —
//                          your call; the trade-off is in encounter-
//                          notes.md).  Every attack and every use-item
//                          pushes ONE UndoAction (snapshotting player
//                          HP + inventory) BEFORE executing.  `undo`
//                          pops the top and restores both.
//                          ABOVE the stack declaration, in a comment:
//                          why a stack and not a queue.
//                          ABOVE the undo body, in a comment: name
//                          ONE piece of state your undo intentionally
//                          does NOT restore (the wave queue is the
//                          obvious choice — pick that or another, and
//                          defend it).
//
//   F7 (queues)          — the current wave's enemies MUST be held in
//                          a Queue<Enemy>.  front() reads the active
//                          target; dequeue() runs only when that
//                          enemy's HP <= 0.  The Grix anti-pattern —
//                          `vector<Enemy> + erase(begin())` — works
//                          but is NOT the F7 contract.
//
// WHAT THE GRADER WILL DO
// =====================================================================
//   1. cmake --build the project. If it does not compile, the Warden
//      has won by default.
//   2. Type `battle waves 2`. Play through; verify wave 1 drains, wave
//      2 spawns, and FIFO targeting holds (oldest enemy attacked first).
//   3. Type `9` and `abc` at the menu. The game must NOT crash; must
//      re-prompt the same turn.
//   4. Use `Inspect log` (option 3). Turn must NOT advance.
//   5. Attack once, then `Undo` (option 4). HP must rewind.  Front
//      enemy's HP must NOT rewind.  A second consecutive `Undo` must
//      be blocked.
//   6. Open this file and find each of the four Floor ties. They must
//      be REAL — the log grows on every turn, Inspect log walks via
//      iterator, the undo stack is pushed before mutating, the wave
//      really is a Queue<Enemy>.

// =====================================================================
// WARDEN 2 — wave survival (Floors 4–7).
// =====================================================================

BattleOutcome runWaveSurvival(Hero& hero, int waves) {
    if (waves < 1) waves = 1;

	constexpr int maxHP = 40;
    constexpr int attackDamage = 7;
    int playerHP = maxHP;

	struct Enemy {
		std::string name;
		int hp;
		int attack;
	};

	Stack<UndoAction> battleUndo;  // F6: stack, not queue, because we want LIFO undo of the most recent action.  The wave queue is NOT restored by undo.
	bool undoUsedThisTurn = false;  // F6: track if undo was used this turn to prevent multiple undos.

    auto recordUndo = [&](const std::string& description) {
        UndoAction a;
		a.description = description;
		a.inventorySnapshot = hero.inventory;  // snapshot inventory
		a.playerHP = playerHP;  // snapshot HP
        battleUndo.push(a);
    };
	hero.eventLog.push_front("battle waves " + std::to_string(waves) + " -- yard opens");

    for (int w = 1; w <= waves; ++w) {
        Queue<Enemy> line;
        for (int i = 0; i < w + 1; ++i) {
            if (i % 3 == 0) {
                line.enqueue({ "Imp # " + std::to_string(i + 1), 8, 3 });  // Example enemy stats
            }
            else if (i % 3 == 1) {
                line.enqueue({ "Rat # " + std::to_string(i + 1), 5, 2 });
            }
            else {
                line.enqueue({ "Skeleton # " + std::to_string(i + 1), 12, 4 });
            }
        }

        hero.eventLog.push_front("wave " + std::to_string(w) + " enters (" + std::to_string(line.size()) + " enemies)");

        while (!line.empty() && playerHP > 0) {
			const Enemy& frontEnemy = line.front();
			std::cout << "\n -- Wave" << w << " --  Player HP: " << playerHP << "  Front Enemy: " << frontEnemy.name << " (HP: " << frontEnemy.hp << ")\n";
        }
    }
}

}  // namespace dungeon
