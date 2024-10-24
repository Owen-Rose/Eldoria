#include "npc.h"
#include <sstream>

NPC::NPC(const std::string& name, 
         const std::string& description,
         const std::string& initial_dialogue,
         NPCType type)
    : Entity(name, description),
      type_(type),
      has_quest_(false),
      quest_completed_(false) {
    
    if (!initial_dialogue.empty()) {
        addDialogue(DialogueState::INITIAL, initial_dialogue);
    }
}

void NPC::addDialogue(DialogueState state, const std::string& dialogue) {
    dialogues_[state] = dialogue;
}

std::string NPC::getDialogue(DialogueState state) const {
    auto it = dialogues_.find(state);
    if (it != dialogues_.end()) {
        return it->second;
    }
    
    // Fallback to initial dialogue if requested state not found
    it = dialogues_.find(DialogueState::INITIAL);
    return it != dialogues_.end() ? it->second : "...";
}

void NPC::setQuest(const std::string& quest_description, 
                   const std::string& completion_dialogue,
                   const std::string& reward_item_id) {
    quest_description_ = quest_description;
    has_quest_ = true;
    quest_completed_ = false;
    reward_item_id_ = reward_item_id;
    addDialogue(DialogueState::QUEST_COMPLETE, completion_dialogue);
}

bool NPC::hasQuest() const {
    return has_quest_;
}

bool NPC::isQuestCompleted() const {
    return quest_completed_;
}

void NPC::completeQuest() {
    if (has_quest_) {
        quest_completed_ = true;
    }
}

std::string NPC::getQuestDescription() const {
    return quest_description_;
}

std::string NPC::getRewardItemId() const {
    return reward_item_id_;
}

void NPC::setState(DialogueState state) {
    current_state_ = state;
}

DialogueState NPC::getState() const {
    return current_state_;
}

NPCType NPC::getType() const {
    return type_;
}

void NPC::addHint(const std::string& hint) {
    hints_.push_back(hint);
}

std::string NPC::getRandomHint() const {
    if (hints_.empty()) {
        return "";
    }
    // Simple way to get a "random" hint - can be enhanced with better randomization
    return hints_[hints_.size() % hints_.size()];
}

std::string NPC::Examine() const {
    std::ostringstream oss;
    oss << Entity::Examine() << "\n";
    
    // Add role-specific description
    switch (type_) {
        case NPCType::QUEST_GIVER:
            oss << "This person seems to have something important to tell you.";
            break;
        case NPCType::MERCHANT:
            oss << "A merchant who might trade with you.";
            break;
        case NPCType::PUZZLE_MASTER:
            oss << "Someone who appears to know the secrets of this place.";
            break;
        case NPCType::GUIDE:
            oss << "A helpful guide who can provide information.";
            break;
        case NPCType::ANTAGONIST:
            oss << "Something about them seems untrustworthy...";
            break;
    }

    return oss.str();
}

void NPC::addResponse(const std::string& keyword, const std::string& response) {
    keyword_responses_[keyword] = response;
}

std::string NPC::getResponse(const std::string& keyword) const {
    auto it = keyword_responses_.find(keyword);
    return (it != keyword_responses_.end()) ? it->second : "";
}

bool NPC::canInteractWith(const std::string& itemId) const {
    return interaction_items_.find(itemId) != interaction_items_.end();
}

void NPC::addItemInteraction(const std::string& itemId, const std::string& response) {
    interaction_items_[itemId] = response;
}

std::string NPC::getItemInteraction(const std::string& itemId) const {
    auto it = interaction_items_.find(itemId);
    return (it != interaction_items_.end()) ? it->second : "";
}