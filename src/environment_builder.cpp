#include "environment_builder.h"
#include "usable_item.h"
#include "riddle_puzzle.h"
#include "reflection_puzzle.h"
#include "npc.h"
#include <array>

std::unique_ptr<LocationGrid> EnvironmentBuilder::buildEnvironment(EnvironmentType type) {
    switch (type) {
        case EnvironmentType::VILLAGE_OF_LUMINARA:
            return createVillageOfLuminara();
        case EnvironmentType::WHISPERING_WOODS:
            return createWhisperingWoods();
        case EnvironmentType::CRYSTAL_CAVES:
            return createCrystalCaves();
        case EnvironmentType::FORGOTTEN_LIBRARY:
            return createForgottenLibrary();
        case EnvironmentType::ECHOING_MOUNTAINS:
            return createEchoingMountains();
        case EnvironmentType::SHADOW_MARSHES:
            return createShadowMarshes();
        case EnvironmentType::SANCTUM_OF_LIGHT:
            return createSanctumOfLight();
        case EnvironmentType::MALAKARS_LAIR:
            return createMalakarsLair();
        case EnvironmentType::HIDDEN_GROVE:
            return createHiddenGrove();
        default:
            return nullptr;
    }
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createVillageOfLuminara() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row (0,0 to 2,0)
        {{ 
            {"Northern Gate",
             "A sturdy wooden gate marks the northern entrance to the village."},
            {"Village Square",
             "The heart of Luminara, where villagers gather around a stone fountain."},
            {"Eastern Market",
             "Stalls with colorful awnings display various goods and wares."}
        }},
        // Second row (0,1 to 2,1)
        {{
            {"Craftsman's Workshop",
             "The sound of hammering and smell of wood fills this busy workshop."},
            {"Elder's House",
             "A modest but well-kept house where Elder Elda resides."},
            {"Herbalist's Garden",
             "A peaceful garden filled with medicinal plants and herbs."}
        }},
        // Third row (0,2 to 2,2)
        {{
            {"Western Farm",
             "Fields of wheat sway gently in the breeze."},
            {"Southern Road",
             "A well-traveled dirt road leading south from the village."},
            {"Village Shrine",
             "A small shrine dedicated to the ancient protectors of Eldoria."}
        }}
    }};

    // Add NPCs
    // Elder Elda in the Elder's House
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Elda",
        "The wise village elder with kind eyes and silver hair.",
        "Welcome to Luminara, brave adventurer. Dark times have fallen upon our land..."
    ));

    // Add starting quest items
    locations[1][1].items.push_back(std::make_shared<Item>(
        "QUEST_SCROLL",  // ID
        "Quest Scroll",  // Name
        "An ancient scroll detailing your mission to save Eldoria."  // Description
    ));

    return createBasicGrid("Village of Luminara", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createWhisperingWoods() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Ancient Grove",
             "Massive trees tower overhead, their branches forming a natural archway."},
            {"Hidden Path",
             "A narrow trail winds between the ancient trees."},
            {"Mystic Clearing",
             "Moonlight filters through the leaves, illuminating a peaceful clearing."}
        }},
        // Second row
        {{
            {"Twisted Path",
             "The path here winds confusingly between gnarled trees."},
            {"Hermit's Hollow",
             "A small clearing where Gorwin the hermit makes his home."},
            {"Whispering Glade",
             "The leaves here seem to whisper ancient secrets."}
        }},
        // Third row
        {{
            {"Shadowed Vale",
             "Deep shadows gather between the ancient trees."},
            {"Forest Heart",
             "The very heart of the Whispering Woods, where magic runs deep."},
            {"Eastern Trail",
             "A trail leading eastward through the dense forest."}
        }}
    }};

    // Add Gorwin NPC
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Gorwin",
        "A mysterious hermit who knows the woods' secrets.",
        "Seek you the way forward? First answer my riddle..."
    ));

    // Add Gorwin's Riddle puzzle
    locations[1][1].puzzle = std::make_shared<RiddlePuzzle>(
        "Gorwin's Riddle",
        "I speak without a mouth and hear without ears. I have nobody, but I come alive with the wind. What am I?",
        std::vector<std::string>{"echo", "an echo", "the echo"},
        "Think about what carries sound through the forest..."
    );

    // Add the Enchanted Map item (received after solving the riddle)
    locations[1][1].items.push_back(std::make_shared<Item>(
        "ENCHANTED_MAP",
        "Enchanted Map",
        "A magical map that seems to shift and change as you watch."
    ));

    return createBasicGrid("Whispering Woods", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createCrystalCaves() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Cave Entrance",
             "Crystalline formations frame the entrance to the caves."},
            {"Crystal Chamber",
             "The walls are lined with glowing crystals of various colors."},
            {"Reflection Hall",
             "Light bounces between countless crystal surfaces here."}
        }},
        // Second row
        {{
            {"Mineral Pool",
             "A still pool reflects the crystalline ceiling above."},
            {"Central Cavern",
             "A vast chamber where all paths converge."},
            {"Crystal Garden",
             "Crystal formations grow like flowers from the cave floor."}
        }},
        // Third row
        {{
            {"Dark Tunnel",
             "A passage where even the crystals' light seems dim."},
            {"Light Chamber",
             "Beams of light dance through strategically placed crystals."},
            {"Eastern Passage",
             "A tunnel leading deeper into the mountain."}
        }}
    }};

    // Add Crystal Guardian NPC
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Thorin",
        "The Crystal Guardian, his robes embedded with tiny crystals.",
        "The path forward requires understanding of light and reflection..."
    ));

    // Add Light Reflection puzzle
    locations[1][1].puzzle = std::make_shared<ReflectionPuzzle>(
        "Light Reflection",
        "Direct the beam of light to the ancient lock.",
        0, 0,   // Source coordinates
        2, 2,   // Target coordinates
        3       // Max mirrors
    );

    // Add Crystal Lens item
    locations[1][1].items.push_back(std::make_shared<CrystalLens>());

    return createBasicGrid("Crystal Caves", locations);
}

// ... Similar implementations for other environments ...

// Add these implementations to your existing environment_builder.cpp file

std::unique_ptr<LocationGrid> EnvironmentBuilder::createForgottenLibrary() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Ancient Archives",
             "Towering shelves filled with ancient tomes and scrolls."},
            {"Reading Hall",
             "A grand hall with reading tables and magical floating lights."},
            {"Restricted Section",
             "A roped-off area containing rare and powerful books."}
        }},
        // Second row
        {{
            {"West Wing",
             "A quiet section with comfortable reading nooks."},
            {"Central Chamber",
             "The heart of the library, where the Book Sorting Puzzle awaits."},
            {"East Wing",
             "Shelves containing historical records and maps."}
        }},
        // Third row
        {{
            {"Scholar's Corner",
             "A cozy area where scholars gather to discuss their findings."},
            {"Library Entrance",
             "The grand entrance to the Forgotten Library."},
            {"Curator's Office",
             "A well-organized office filled with catalogues and notes."}
        }}
    }};

    // Add Lyra NPC to Central Chamber
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Lyra",
        "A wise scholar with keen eyes and a patient demeanor.",
        "The ancient knowledge held here must be properly ordered..."
    ));

    return createBasicGrid("Forgotten Library", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createEchoingMountains() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Rocky Outcrop",
             "A windswept ledge overlooking distant peaks."},
            {"Mountain Peak",
             "The highest point, where the wind carries strange echoes."},
            {"Crystal View",
             "A ledge offering a view of crystalline formations below."}
        }},
        // Second row
        {{
            {"Echo Chamber",
             "A natural cave where sounds reflect in mysterious ways."},
            {"Resonance Chamber",
             "The heart of the Echo Puzzle, where sounds converge."},
            {"Wind Tunnel",
             "A natural passage where the wind creates musical notes."}
        }},
        // Third row
        {{
            {"Mountain Path",
             "A treacherous path winding through the mountains."},
            {"Base Camp",
             "A relatively safe area to rest and prepare."},
            {"Eastern Trail",
             "A path leading down towards the Shadow Marshes."}
        }}
    }};

    return createBasicGrid("Echoing Mountains", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createShadowMarshes() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Misty Shore",
             "A foggy shoreline where shadows dance on the water."},
            {"Shadow Pool",
             "A dark pool reflecting distorted images."},
            {"Twisted Grove",
             "A grove of trees bent into unnatural shapes."}
        }},
        // Second row
        {{
            {"Illusion Path",
             "A path that seems to shift and change."},
            {"Heart of Shadows",
             "The center of the marshes where reality seems most unstable."},
            {"Phantom Clearing",
             "A clearing where ghostly shapes flit between trees."}
        }},
        // Third row
        {{
            {"Western Edge",
             "The border between the marshes and firmer ground."},
            {"Sunken Path",
             "A partially flooded trail through the marsh."},
            {"Eastern Gateway",
             "A path leading toward the Sanctum of Light."}
        }}
    }};

    return createBasicGrid("Shadow Marshes", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createSanctumOfLight() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Western Courtyard",
             "An open courtyard bathed in golden light."},
            {"Grand Entrance",
             "Massive doors marked with symbols of light."},
            {"Eastern Courtyard",
             "A peaceful garden with light-catching crystals."}
        }},
        // Second row
        {{
            {"Hall of Trials",
             "A chamber where wisdom is tested."},
            {"Central Sanctum",
             "The sacred heart of the Sanctum where Mira resides."},
            {"Meditation Chamber",
             "A quiet room for contemplation and preparation."}
        }},
        // Third row
        {{
            {"Ancient Archives",
             "Records of the Sanctum's history and prophecies."},
            {"Path to Malakar",
             "A heavily guarded passage leading to Malakar's domain."},
            {"Artifact Chamber",
             "A secure room housing powerful relics."}
        }}
    }};

    // Add Mira NPC
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Mira",
        "The Priestess of Light, radiating wisdom and power.",
        "To wield the Staff of Lumos, one must first prove their worth..."
    ));

    return createBasicGrid("Sanctum of Light", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createMalakarsLair() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Dark Antechamber",
             "A foreboding entrance hall shrouded in darkness."},
            {"Corrupted Hall",
             "A once-grand hall now tainted by dark energy."},
            {"Shadow Throne",
             "An imposing throne room radiating dark power."}
        }},
        // Second row
        {{
            {"Torture Chamber",
             "A grim chamber filled with evil implements."},
            {"Central Chamber",
             "The heart of Malakar's power."},
            {"Ritual Room",
             "A chamber where dark rituals are performed."}
        }},
        // Third row
        {{
            {"Prison Cells",
             "Dark cells holding Malakar's prisoners."},
            {"Guard Room",
             "A chamber where Malakar's minions gather."},
            {"Exit Portal",
             "A mysterious portal pulsing with energy."}
        }}
    }};

    return createBasicGrid("Malakar's Lair", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createHiddenGrove() {
    std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
               LocationGrid::GRID_SIZE> locations = {{
        // First row
        {{ 
            {"Ancient Tree",
             "A massive tree radiating ancient magic."},
            {"Sacred Pool",
             "A pool of crystal-clear water with healing properties."},
            {"Mystic Circle",
             "A circle of standing stones humming with power."}
        }},
        // Second row
        {{
            {"Meditation Spot",
             "A peaceful clearing perfect for contemplation."},
            {"Grove Heart",
             "The magical center of the Hidden Grove."},
            {"Fairy Ring",
             "A ring of mushrooms where magical creatures gather."}
        }},
        // Third row
        {{
            {"Overgrown Path",
             "A barely visible path leading to the grove."},
            {"Flower Garden",
             "A garden of magical flowering plants."},
            {"Crystal Cave",
             "A small cave filled with glowing crystals."}
        }}
    }};

    // Add Elyndor NPC
    locations[1][1].npcs.push_back(std::make_shared<NPC>(
        "Elyndor",
        "A mysterious mystic with deep knowledge of the grove.",
        "The grove reveals its secrets only to those who are worthy..."
    ));

    return createBasicGrid("Hidden Grove", locations);
}

std::unique_ptr<LocationGrid> EnvironmentBuilder::createBasicGrid(
    const std::string& name,
    const std::array<std::array<LocationData, LocationGrid::GRID_SIZE>,
                    LocationGrid::GRID_SIZE>& locations) {
    
    auto grid = std::make_unique<LocationGrid>(name);

    // Create and populate locations
    for (int y = 0; y < LocationGrid::GRID_SIZE; ++y) {
        for (int x = 0; x < LocationGrid::GRID_SIZE; ++x) {
            const auto& data = locations[y][x];
            auto location = std::make_shared<Location>(data.name, data.description);

            // Add items
            for (const auto& item : data.items) {
                location->addItem(item);
            }

            // Add NPCs
            for (const auto& npc : data.npcs) {
                location->addNPC(npc);
            }

            // Set puzzle if exists
            if (data.puzzle) {
                location->setPuzzle(data.puzzle);
            }

            grid->setLocation(x, y, location);
        }
    }

    // Connect adjacent locations within the grid
    grid->connectGridLocations();

    return grid;
}