#ifndef NPC_H_
#define NPC_H_

#include "entity.h"
#include <string>
#include <vector>

class NPC : public Entity {
public:
    NPC(const std::string& name, const std::string& description, const std::string& dialogue);
    std::string getDialogue() const;
    void addDialogue(const std::string& dialogue);

private:
    std::vector<std::string> dialogues_;
};

#endif // NPC_H_