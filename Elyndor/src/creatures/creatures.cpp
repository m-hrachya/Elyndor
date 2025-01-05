#include "../../headers/creatures/creatures.hpp"

MagicalCreatures::MagicalCreatures(std::string name, int force, double health) 
                    : m_name{name}, m_force{force}, m_health{health} {}

MagicalCreatures::~MagicalCreatures() {}

void MagicalCreatures::harm(double harmSize) {
    m_health -= harmSize;
    if (m_health < 0) {
        m_health = 0;
    }
}

double MagicalCreatures::getHealth() const {
    return m_health;
}

int MagicalCreatures::getForce() const {
    return m_force;
}

void MagicalCreatures::heal() {
    m_health = 100;
}