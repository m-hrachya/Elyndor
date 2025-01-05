#ifndef KINGDOM
#define KINGDOM

#include <iostream>
#include "../creatures/elf.hpp"
#include "../creatures/goblin.hpp"



class Kingdom {
private:
    friend class GameEngine;
    void addCreature(MagicalCreatures* creature);
    void healKingdom();
    void harmKingdom(double harmSize);
    int m_creatures_count = 0;
    std::vector<MagicalCreatures* > m_creatures;
};

#endif // KINGDOM