#ifndef EVENTS_H
#define EVENTS_H

// Define an enumeration for different event types
typedef enum
{
    EVENT_NONE, // Represents no event or an idle state where nothing happens.

    // Movement Events:
    EVENT_MOVE_UP, // Represents moving the player character up (e.g., in a platformer, upwards movement).
    // EVENT_MOVE_UP_RIGHT,   // Represents moving the player character diagonally up-right (e.g., in a platformer, jumping at an angle).
    // EVENT_MOVE_UP_LEFT,    // Represents moving the player character diagonally up-left (e.g., in a platformer, jumping at an angle).
    EVENT_MOVE_DOWN,       // Represents moving the player character down (e.g., in a platformer, downward movement).
    // EVENT_MOVE_DOWN_RIGHT, // Represents moving the player character diagonally down-right (e.g., running at an angle).
    // EVENT_MOVE_DOWN_LEFT,  // Represents moving the player character diagonally down-left (e.g., running at an angle).
    EVENT_MOVE_LEFT,       // Represents moving the player character to the left (e.g., in a platformer, leftward movement).
    EVENT_MOVE_RIGHT,      // Represents moving the player character to the right (e.g., in a platformer, rightward movement).
    EVENT_MOVE, // A general move event for when the player is moving in any direction, used as a catch-all for movement.
    EVENT_ROLL,

    // Environmental/State Events:
    // EVENT_FLOOR_LAND, // Represents the player landing on the floor after a jump or fall (e.g., gravity pulling the player down).

    // Combat Events:
    EVENT_ATTACK, // Represents a basic attack event (e.g., player character performing a melee or ranged attack).
    // EVENT_ATTACK_SPECIAL, // Represents performing a special or charged attack (e.g., a powerful or combo attack).
    EVENT_DEFEND, // Represents the player character activating a defense action (e.g., blocking, shielding).

    // Life Cycle Events:
    EVENT_DIE,     // Represents the player character dying (e.g., health reaching zero or being defeated by an enemy).
    EVENT_RESPAWN, // Represents the player respawning after death (e.g., after a timeout, or at a checkpoint).
    // EVENT_HURT,    // Represents the player character taking damage (e.g., from enemies, traps, or environmental hazards).
    // EVENT_HEAL,    // Represents the player character receiving healing (e.g., health items or regenerative effects).

    // Collision Events:
    EVENT_COLLISION_START, // Represents the start of a collision (e.g., player colliding with a wall, enemy, or object).
    EVENT_COLLISION_END,   // Represents the end of a collision (e.g., player moving away from a colliding object or enemy).

    // Player Actions:
    // EVENT_PICKUP, // Represents the player picking up an item (e.g., collecting weapons, coins, health potions, etc.).

    // Game State Events:
    // EVENT_WIN,   // Represents the player winning the game or level (e.g., completing a mission, reaching the end goal).
    // EVENT_LOSE,  // Represents the player losing the game or level (e.g., failing objectives or losing all lives).
    // EVENT_PAUSE, // Represents the player pausing the game (e.g., opening the pause menu).

    // Miscellaneous Events:
    // EVENT_FALL,     // Represents the player character falling (e.g., falling off platforms or dropping into a pit).
    // EVENT_WIN_BOSS, // Represents the player defeating a boss (e.g., completing a major challenge in the game).

    EVENT_COUNT // Represents the total number of events (for counting purposes, typically used for array size).
} Event;        // Define 'Event' as the type of the enum

#endif
