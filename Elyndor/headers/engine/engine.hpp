#ifndef GAME_ENGINE
#define GAME_ENGINE

#include "../creatures/elf.hpp"
#include "../creatures/goblin.hpp"

#include <random>
#include <iostream>
#include "../kingdom/kingdom.hpp"


class GameEngine {
public:
    GameEngine();
    void start();
private:
    void attack(int kingdomNumber);
    void alias(int kingdomNumber);
    void createKingdom();
    void generateEvent();
    void checkForWin();
    void checkForLoose();
    void displayInfo(int index) const;
    void attackEvent();
    void aliasEvent();
    void artifactEvent();
    double getHealth(int index) const;
    int getForce(int index) const;
    void cleanup();
private:
    std::vector<Kingdom *> m_kingdoms;
    std::vector<bool> m_aliases;
    std::vector<bool> m_destroyed;
    std::string m_main_kingdom_name;
    std::string m_user_name;
};

#endif // GAME_ENGINE