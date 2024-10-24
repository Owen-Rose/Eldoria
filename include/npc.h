#ifndef NPC_H_
#define NPC_H_

#include "entity.h"
#include <string>
#include <vector>
#include <unordered_map>

/**
 * @enum NPCType
 * @brief Defines the different types of NPCs in the game
 */
enum class NPCType {
    QUEST_GIVER,    ///< NPCs who give quests (e.g., Elda)
    MERCHANT,       ///< NPCs who trade items
    PUZZLE_MASTER,  ///< NPCs who present puzzles (e.g., Gorwin)
    GUIDE,          ///< NPCs who provide information
    ANTAGONIST      ///< Antagonistic NPCs (e.g., Shadow Figure)
};

/**
 * @enum DialogueState
 * @brief Represents different states of NPC dialogue
 */
enum class DialogueState {
    INITIAL,          ///< First meeting
    QUEST_AVAILABLE,  ///< When NPC has a quest to give
    QUEST_ACTIVE,     ///< While quest is ongoing
    QUEST_COMPLETE,   ///< After quest completion
    PUZZLE_HINT,      ///< When providing puzzle hints
    MERCHANT_TRADE,   ///< During trading
    ANTAGONIST        ///< Special dialogue for antagonists
};

/**
 * @class NPC
 * @brief Represents a non-player character in the game
 * 
 * This class handles all NPC-specific functionality including dialogue,
 * quest management, hints, and item interactions. It supports the various
 * NPC types described in the game design document.
 */
class NPC : public Entity {
public:
    /**
     * @brief Constructor for NPC
     * @param name The NPC's name
     * @param description The NPC's description
     * @param initial_dialogue The NPC's initial dialogue
     * @param type The type of NPC
     */
    NPC(const std::string& name, 
        const std::string& description,
        const std::string& initial_dialogue,
        NPCType type = NPCType::GUIDE);

    /**
     * @brief Add dialogue for a specific state
     * @param state The dialogue state
     * @param dialogue The dialogue text
     */
    void addDialogue(DialogueState state, const std::string& dialogue);

    /**
     * @brief Get dialogue for a specific state
     * @param state The dialogue state
     * @return The dialogue text
     */
    std::string getDialogue(DialogueState state = DialogueState::INITIAL) const;

    /**
     * @brief Set up a quest for this NPC
     * @param quest_description Description of the quest
     * @param completion_dialogue Dialogue when quest is completed
     * @param reward_item_id ID of the reward item (if any)
     */
    void setQuest(const std::string& quest_description, 
                  const std::string& completion_dialogue,
                  const std::string& reward_item_id = "");

    /**
     * @brief Check if NPC has a quest
     * @return true if NPC has a quest
     */
    bool hasQuest() const;

    /**
     * @brief Check if quest is completed
     * @return true if quest is completed
     */
    bool isQuestCompleted() const;

    /**
     * @brief Mark the quest as completed
     */
    void completeQuest();

    /**
     * @brief Get the quest description
     * @return Quest description string
     */
    std::string getQuestDescription() const;

    /**
     * @brief Get the reward item ID
     * @return Reward item ID string
     */
    std::string getRewardItemId() const;

    /**
     * @brief Set the current dialogue state
     * @param state The new state
     */
    void setState(DialogueState state);

    /**
     * @brief Get the current dialogue state
     * @return Current dialogue state
     */
    DialogueState getState() const;

    /**
     * @brief Get the NPC type
     * @return NPC type
     */
    NPCType getType() const;

    /**
     * @brief Add a hint to the NPC's hint collection
     * @param hint The hint text
     */
    void addHint(const std::string& hint);

    /**
     * @brief Get a random hint
     * @return A hint string
     */
    std::string getRandomHint() const;

    /**
     * @brief Override of Entity's Examine function
     * @return Detailed description of the NPC
     */
    std::string Examine() const override;

    /**
     * @brief Add a keyword response
     * @param keyword The trigger keyword
     * @param response The response text
     */
    void addResponse(const std::string& keyword, const std::string& response);

    /**
     * @brief Get response for a keyword
     * @param keyword The trigger keyword
     * @return The response text
     */
    std::string getResponse(const std::string& keyword) const;

    /**
     * @brief Check if NPC can interact with an item
     * @param itemId The item ID
     * @return true if interaction is possible
     */
    bool canInteractWith(const std::string& itemId) const;

    /**
     * @brief Add an item interaction
     * @param itemId The item ID
     * @param response The interaction response
     */
    void addItemInteraction(const std::string& itemId, const std::string& response);

    /**
     * @brief Get the interaction response for an item
     * @param itemId The item ID
     * @return The interaction response
     */
    std::string getItemInteraction(const std::string& itemId) const;

private:
    NPCType type_;                    ///< Type of NPC
    DialogueState current_state_;     ///< Current dialogue state
    bool has_quest_;                  ///< Whether NPC has a quest
    bool quest_completed_;            ///< Whether quest is completed
    std::string quest_description_;   ///< Description of the quest
    std::string reward_item_id_;      ///< ID of quest reward item

    std::unordered_map<DialogueState, std::string> dialogues_;  ///< State-specific dialogues
    std::vector<std::string> hints_;                            ///< Collection of hints
    std::unordered_map<std::string, std::string> keyword_responses_;  ///< Keyword-triggered responses
    std::unordered_map<std::string, std::string> interaction_items_;  ///< Item interaction responses
};

#endif  // NPC_H_