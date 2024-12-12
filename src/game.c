#include <stdio.h>
#include <raylib.h>

#include "../include/game/game.h"

/**
 * InitGame - Initializes the game, setting up the player, NPC, and mediator.
 *
 * This function prepares the game for play by creating a player, an NPC, and
 * a mediator to manage interactions between these entities. The `GameData`
 * structure is used to store the current state of the game.
 *
 * @gameData: A pointer to the GameData structure containing the game state.
 */
void InitGame(GameData *gameData)
{
    printf("Game Initialized!\n");

    InitAudioDevice();      // Initialize audio device

    // Initialize the player and NPC with their respective names
    gameData->player = InitPlayer("Player Hero");
    gameData->npc = InitNPC("Skynet");

    // Create a mediator to facilitate communication between
    // Command and FSM, ultimately updating the playes state
    gameData->mediator = CreateMediator(&gameData->player->base);
}

/**
 * UpdateGame - Updates the game state by handling player input, NPC behavior,
 *              and updating entities based on their current states.
 *
 * This function updates the player’s state, processes AI behavior for the NPC,
 * and triggers appropriate state changes via commands. The NPC's behavior is
 * randomly determined every second.
 *
 * @gameData: A pointer to the GameData structure containing the game state.
 */
void UpdateGame(GameData *gameData)
{
    DrawText("Game Updating...", 190, 260, 20, DARKBLUE);

    // Poll input from the user and execute the corresponding command
    Command command = PollInput();
    ExecuteCommand(command, gameData->mediator); // Execute the command via the mediator

    // Check if player should die
    if (gameData->player->base.health <= 0)
    {
        ChangeState((GameObject *)gameData->player, STATE_DEAD);
    }

    // Update the player's state based on its current configuration
    UpdateState(&gameData->player->base);


    // Simple random behavior for NPC AI (not truly an AI, just random selection)
    // Static variable to track the last AI action time
    // static float lastAITime = 0.0f;

    // Randomly select a command for the NPC
    command = PollAI(&gameData->npc->base, &gameData->player->base);
    switch (command)
    {
    case COMMAND_NONE:
        HandleEvent((GameObject *)gameData->npc, EVENT_NONE);
        printf("COMMAND_NONE");
        break;
    case COMMAND_MOVE_UP:
        HandleEvent((GameObject *)gameData->npc, EVENT_MOVE_UP);
        break;
    case COMMAND_MOVE_DOWN:
        HandleEvent((GameObject *)gameData->npc, EVENT_MOVE_DOWN);
        break;
    case COMMAND_MOVE_LEFT:
        HandleEvent((GameObject *)gameData->npc, EVENT_MOVE_LEFT);
        break;
    case COMMAND_MOVE_RIGHT:
        HandleEvent((GameObject *)gameData->npc, EVENT_MOVE_RIGHT);
        break;
    case COMMAND_ATTACK:
        HandleEvent((GameObject *)gameData->npc, EVENT_ATTACK);
        break;
    case COMMAND_COLLISION_START:
        HandleEvent((GameObject *)gameData->npc, EVENT_DIE);
        break;
    case COMMAND_COLLISION_END:
        HandleEvent((GameObject *)gameData->npc, EVENT_RESPAWN);
        break;
    default:
        break;
    }

    // Update the NPC's state after handling the event
    UpdateState(&gameData->npc->base);

    // Check for collisions between player and NPC
    if (CheckCollision(&gameData->player->base, &gameData->npc->base))
    {
        if (gameData->player->base.currentState != STATE_COLLISION)
        {
            HandleEvent(&gameData->player->base, EVENT_COLLISION_START);
        }

        // Try to push back player
        HandleCollision(&gameData->player->base, &gameData->npc->base);

        // Ensure that we are separated after handling the collision
        if (!CheckCollision(&gameData->player->base, &gameData->npc->base))
        {
            printf("Transitioning back to STATE_IDLE state from STATE_COLLISION\n");
            HandleEvent(&gameData->player->base, EVENT_NONE); // Ideally a EVENT_COLLISION_END
        }
    }
    
    // Check collision with the enemy and the player's attack
    if (gameData->player->attacking)
    {
        if (c2CircletoCircle(gameData->player->attackArea, gameData->npc->base.collider))
        {
            if (gameData->npc->base.currentState != STATE_COLLISION)
            {
                HandleEvent(&gameData->npc->base, EVENT_COLLISION_START);

                gameData->npc->base.health--;
            }
        }
    }
}

/**
 * DrawGame - Draws the game elements to the screen (player, NPC, health bar, etc.).
 *
 * This function handles drawing the player, NPC, health bars, and other UI
 * elements like the game title. It also handles rendering the player’s animation.
 *
 * @gameData: A pointer to the GameData structure containing the game state.
 */
void DrawGame(GameData *gameData)
{
    DrawText("Raylib Animated FSM Starter Kit!", 190, 180, 20, DARKBLUE);

    // Begin drawing to the screen
    BeginDrawing();

    // Clear the screen with a white background
    ClearBackground(DARKGREEN);

    // Draw some basic UI text (game title and description)
    DrawText("Welcome to Raylib Animated FSM Starter", 190, 200, 20, LIGHTGRAY);
    DrawText("Gameplay Programming I", 190, 220, 20, LIGHTGRAY);

    // Drawing Player and Position Data
    const char *infoPosition = TextFormat("(%.f, %.f)", gameData->player->base.position.x, gameData->player->base.position.y);

    // Draw a circle representing the player at their position
    DrawCircleLines(gameData->player->base.position.x, gameData->player->base.position.y, 20, gameData->player->base.color);

    if (gameData->player->attacking)
    {
        // Draw the attack area of the player
        DrawCircle(gameData->player->attackArea.p.x, gameData->player->attackArea.p.y, gameData->player->attackArea.r, gameData->player->base.color);
    }

    // Draw text showing player position below the player
    DrawText(infoPosition,
             gameData->player->base.position.x - (MeasureText(infoPosition, 20) / 2),
             gameData->player->base.position.y + 30,
             20, DARKBLUE);

    // Drawing Health Bar for the player
    const int healthBarWidth = 100;
    const int healthBarHeight = 10;
    const int healthBarX = gameData->player->base.position.x - (healthBarWidth / 2); // Position health bar above the player
    const int healthBarY = gameData->player->base.position.y - 40;

    // Calculate health percentage (for drawing the health bar)
    float healthPercentage = (float)gameData->player->base.health / 100;

    // Draw the background of the health bar (gray)
    DrawRectangle(healthBarX, healthBarY, healthBarWidth, healthBarHeight, GRAY);

    // Draw the health bar foreground (green based on current health)
    DrawRectangle(healthBarX, healthBarY, healthBarWidth * healthPercentage, healthBarHeight, GREEN);

    // Enemy health bar
    const int healthBarXNPC = gameData->npc->base.position.x - (healthBarWidth / 2); // Position health bar above the player
    const int healthBarYNPC = gameData->npc->base.position.y - 40;
    // Calculate health percentage (for drawing the health bar)
    float healthPercentageNPC = (float)gameData->npc->base.health / 100;
    // Draw the background of the health bar (gray)
    DrawRectangle(healthBarXNPC, healthBarYNPC, healthBarWidth, healthBarHeight, GRAY);
    // Draw the health bar foreground (green based on current health)
    DrawRectangle(healthBarXNPC, healthBarYNPC, healthBarWidth * healthPercentageNPC, healthBarHeight, GREEN);

    // Drawing NPC and Position Data
    infoPosition = TextFormat("(%.f, %.f)", gameData->npc->base.position.x, gameData->npc->base.position.y);

    // Draw the NPC circle at their position
    DrawCircle(gameData->npc->base.position.x, gameData->npc->base.position.y, 20, gameData->npc->base.color);
    // Render the npc's animation at their current position
    RenderAnimation(&gameData->npc->base.animation, gameData->npc->base.position, RAYWHITE);

    // Draw text showing NPC position below the NPC
    DrawText(infoPosition,
             gameData->npc->base.position.x - (MeasureText(infoPosition, 20) / 2),
             gameData->npc->base.position.y + 30,
             20, DARKBLUE);

    // Render the player's animation at their current position
    RenderAnimation(&gameData->player->base.animation, gameData->player->base.position, WHITE);

    // End drawing to the screen
    EndDrawing();
}

/**
 * CloseGame - Closes the game and frees any allocated resources.
 *
 * This function cleans up any memory and resources allocated during the game’s
 * initialization (such as deleting the player, NPC, and mediator objects).
 *
 * @gameData: A pointer to the GameData structure containing the game state.
 */
void CloseGame(GameData *gameData)
{
    printf("Game Closed!\n");

    CloseAudioDevice();     // Close audio device

    // If the game data is not null, delete all objects associated with the game
    if (gameData != NULL)
    {
        DeleteGameData(gameData);
    }
}

/**
 * DeleteGameData - Deletes all objects within the game data structure to free memory.
 *
 * This function deletes the player, NPC, and mediator objects, and then frees the
 * memory used by the GameData structure itself.
 *
 * @gameData: A pointer to the GameData structure containing the game state.
 */
void DeleteGameData(GameData *gameData)
{
    if (gameData != NULL)
    {
        // Delete the player and NPC objects if they are not null
        if (gameData->player != NULL)
        {
            DeletePlayer(&gameData->player->base);
        }

        if (gameData->npc != NULL)
        {
            DeleteNPC(&gameData->npc->base);
        }

        if (gameData->mediator != NULL)
        {
            DeleteMediator(gameData->mediator);
        }
    }
}
