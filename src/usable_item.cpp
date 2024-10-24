#include "usable_item.h"

UsableItem::UsableItem(const std::string& id,
                       const std::string& name, 
                       const std::string& description,
                       UseEffect use_effect)
    : Item(id, name, description), use_effect_(use_effect) {}

std::string UsableItem::Use() {
    if (!CanUse()) {
        return "You cannot use " + getName() + " here.";
    }
    return use_effect_();
}

bool UsableItem::CanUse() const {
    return true;
}

std::string UsableItem::GetUseDescription() const {
    return "This item can be used.";
}

CrystalLens::CrystalLens()
    : UsableItem("CRYSTAL_LENS",
                 "Crystal Lens",
                 "A finely crafted lens that can focus and redirect light.",
                 []() { return "You adjust the Crystal Lens, focusing the light."; }) {}

std::string CrystalLens::Use() {
    if (!CanUse()) {
        return "There isn't enough light here to use the Crystal Lens.";
    }
    return UsableItem::Use();
}

bool CrystalLens::CanUse() const {
    return false;  // Placeholder
}

HerbalMixture::HerbalMixture()
    : UsableItem("HERBAL_MIXTURE",
                 "Herbal Mixture",
                 "A mysterious concoction that can reveal what is hidden.",
                 []() { return "You use the Herbal Mixture. The air shimmers and illusions begin to fade."; }) {}

std::string HerbalMixture::Use() {
    if (!CanUse()) {
        return "There are no illusions here to dispel.";
    }
    return UsableItem::Use();
}

bool HerbalMixture::CanUse() const {
    return false;  // Placeholder
}

StaffOfLumos::StaffOfLumos()
    : UsableItem("STAFF_OF_LUMOS",
                 "Staff of Lumos",
                 "An ancient staff radiating with powerful light energy.",
                 []() { return "The Staff of Lumos pulses with brilliant light, its power ready to be unleashed."; }) {}

std::string StaffOfLumos::Use() {
    if (!CanUse()) {
        return "The Staff of Lumos cannot be used here. It seems to respond only to Malakar's presence.";
    }
    return UsableItem::Use();
}

bool StaffOfLumos::CanUse() const {
    return IsInMalakarLair();
}

bool StaffOfLumos::IsInMalakarLair() const {
    return false;  // Placeholder
}

EchoCrystal::EchoCrystal()
    : UsableItem("ECHO_CRYSTAL",
                 "Echo Crystal",
                 "A crystalline structure that can record and replay sounds.",
                 [this]() -> std::string { // Added explicit return type
                     if (HasRecordedSound()) {
                         return "The Echo Crystal resonates, playing back: " + recorded_sound_;
                     }
                     return std::string("The Echo Crystal awaits a sound to record.");
                 }) {}


std::string EchoCrystal::Use() {
    if (!CanUse()) {
        return "The acoustics here aren't suitable for using the Echo Crystal.";
    }
    return UsableItem::Use();
}

bool EchoCrystal::CanUse() const {
    return false;  // Placeholder
}

void EchoCrystal::RecordSound(const std::string& sound) {
    recorded_sound_ = sound;
}

bool EchoCrystal::HasRecordedSound() const {
    return !recorded_sound_.empty();
}

SilverKey::SilverKey()
    : UsableItem("SILVER_KEY",
                 "Silver Key",
                 "An ornate silver key with mysterious markings.",
                 []() { return "You insert the Silver Key into the lock. The door mechanism responds with a click."; }) {}

std::string SilverKey::Use() {
    if (!CanUse()) {
        return "There is no suitable lock here for the Silver Key.";
    }
    return UsableItem::Use();
}

bool SilverKey::CanUse() const {
    return IsAtMalakarDoor();
}

bool SilverKey::IsAtMalakarDoor() const {
    return false;  // Placeholder
}