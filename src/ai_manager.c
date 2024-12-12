#include <stdlib.h>
#include <time.h>

#include "../include/command/command.h"
#include "../include/utils/ai_manager.h"

#include "../include/gameobjects/npc.h"
#include "../include/gameobjects/player.h"

/**
 * InitAIManager - Initializes the AI manager and sets up any required resources.
 *
 * This function is responsible for preparing the AI system for use. In this case, the
 * implementation is a placeholder and does not perform any specific initialization
 * tasks. Additional initialization steps can be added if needed in the future.
 */
void InitAIManager()
{
    // Initialize AI
}

Command NPCFollowPlayer(NPC *obj, Player player)
{
    if (obj->base.position.x <= player.base.position.x)
    {
        return COMMAND_MOVE_RIGHT;
    }
    else if (obj->base.position.x >= player.base.position.x)
    {
        return COMMAND_MOVE_LEFT;
    }
    else if (obj->base.position.y <= player.base.position.y)
    {
        return COMMAND_MOVE_DOWN;
    }
    else if (obj->base.position.y >= player.base.position.y)
    {
        return COMMAND_MOVE_UP;
    }

    return COMMAND_NONE;
}

/**
 * PollAI - Retrieves a random command from the AI.
 *
 * This function simulates AI behavior by returning a random command. It uses the
 * `rand()` function to select a command from the available pool of commands, with
 * the total number of commands being defined by `COMMAND_COUNT`.
 *
 * @return: A randomly chosen Command value from the range [0, COMMAND_COUNT-1].
 */
Command PollAI(GameObject *obj, GameObject* player)
{
    if (obj->health <= 0)
    {
        obj->position.x = 450;
        obj->position.y = 450;

        obj->health = 100;
    }
    // If the player is in range
    else if (Vector2Distance(obj->position, player->position) < 300.0f)
    {
        if (obj->position.y > player->position.y)
        {
            return COMMAND_MOVE_UP;
        }
        else if (obj->position.y < player->position.y)
        {
            return COMMAND_MOVE_DOWN;
        }
        else if (obj->position.x > player->position.x)
        {
            return COMMAND_MOVE_LEFT;
        }
        else if (obj->position.x < player->position.x)
        {
            return COMMAND_MOVE_RIGHT;
        }
    }
    

    return COMMAND_NONE;
}

/**
 * ExitAIManager - Cleans up any resources allocated by the AI manager.
 *
 * This function is responsible for deallocating or cleaning up any resources used
 * by the AI manager. Currently, it is a placeholder since there are no resources
 * to clean up, but it can be expanded in the future if necessary.
 */
void ExitAIManager()
{
    // Cleanup resources if needed - Currently a placeholder.
    // Add any necessary cleanup logic here (e.g., freeing memory, closing files).
}
