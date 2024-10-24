#include "npc.h"

NPC::NPC(const std::string& name, const std::string& description, const std::string& dialogue)
    : Entity(name, description) {
    dialogues_.push_back(dialogue);
}

std::string NPC::getDialogue() const {
    return !dialogues_.empty() ? dialogues_[0] : "...";
}

void NPC::addDialogue(const std::string& dialogue) {
    dialogues_.push_back(dialogue);
}