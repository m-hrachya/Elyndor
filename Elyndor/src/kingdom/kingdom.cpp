#include "../../headers/kingdom/kingdom.hpp"

void Kingdom::addCreature(MagicalCreatures* creature) {
    m_creatures.push_back(creature);
    ++m_creatures_count;
}

void Kingdom::healKingdom() {
    for (int i = 0; i < m_creatures_count; ++i) {
        m_creatures[i]->heal();
    }
}

void Kingdom::harmKingdom(double harmSize) {
    double eachHarmSize = harmSize / m_creatures_count;
    for (int i = 0; i < m_creatures_count; ++i) {
        m_creatures[i]->harm(eachHarmSize);
    }
}