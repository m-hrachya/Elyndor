#include "../../headers/engine/engine.hpp"
#include <thread>
#define KINGDOM_COUNT 4
#define CREATURE_COUNT 10

GameEngine::GameEngine() {
    for (int i = 0; i < KINGDOM_COUNT; ++i) {
        createKingdom();
    }
}

void GameEngine::start() {
    std::cout << "Please, enter your name: ";
    std::cin >> m_user_name;
    std::cout << "Hello, " << m_user_name << ". Please, enter your kindom's name: ";
    std::cin >> m_main_kingdom_name;
    std::cout << "\n\n";
    std::cout << "\033[34m////////////////////////////////////////////////////////////////////////////////" << std::endl;
    std::cout << "\n";
    std::cout << "Good! Here is some basic information about your kingdom:" << std::endl;
    displayInfo(0);
    std::cout << "Every 10 seconds a random event will happen. Your task is to choose, what option\nis the best for your kingdom. Remember, every step you make will have an impact\non your win or your loose. You must either destroy all the enemies, or make aliases with\nall the other kingdoms. Good Luck!\n";
    std::cout << "\n";
    std::cout << "////////////////////////////////////////////////////////////////////////////////\033[0m" << std::endl;
    std::cout << "\n\n";
    std::cout << "To start, type \"S\":";
    char dummy;
    std::cin >> dummy;
    while(true) {
        std::cout << "\n\n///////////////////////\n\n";
        std::cout << "Waiting for an event..." << std::endl;
        std::cout << "\n///////////////////////\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));
        generateEvent();
        checkForLoose();
        checkForWin();
        std::cout << "\n///////////////////////\n\n";
        std::cout << "Info about your kingdom:" << std::endl;
        std::cout << "\n";
        displayInfo(0);
        std::cout << "\n";
        std::cout << "Aliases:";
        for (int i = 1; i < KINGDOM_COUNT; ++i) {
            if (m_aliases[i] == true) {
                std::cout << " Kingdom N:" << i;
            }
        }
        std::cout << std::endl;
        std::cout << "\n";
        std::cout << "Remaining kingdoms:";
        for (int i = 1; i < KINGDOM_COUNT; ++i) {
            if (m_destroyed[i] == false) {
                std::cout << " Kingdom N:" << i;
            }
        }
        std::cout << std::endl;
    }
}

void GameEngine::createKingdom() {
    Kingdom* kingdom = new Kingdom;
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 2);
    for (int i = 0; i < CREATURE_COUNT; ++i) {
        int type = dist(engine);
        if (type == 1) {
            kingdom->addCreature(new Elf);
        } else {
            kingdom->addCreature(new Goblin);
        }
    }
    m_kingdoms.push_back(kingdom);
    m_aliases.push_back(false);
    m_destroyed.push_back(false);
}

double GameEngine::getHealth(int index) const {
    if (index < 0 || index >= KINGDOM_COUNT) {
        exit(EXIT_FAILURE);
    }
    double health = 0;
    for (int i = 0; i < CREATURE_COUNT; ++i) {
        health += (((m_kingdoms[index])->m_creatures)[i])->getHealth();
    }
    return health;
}

int GameEngine::getForce(int index) const {
    if (index < 0 || index >= KINGDOM_COUNT) {
        exit(EXIT_FAILURE);
    }
    int force = 0;
    for (int i = 0; i < CREATURE_COUNT; ++i) {
        force += (((m_kingdoms[index])->m_creatures)[i])->getForce();
    }
    return force;
}
 
void GameEngine::displayInfo(int index) const {
    if (index == 0) {
        std::cout << "Kingdom " << m_main_kingdom_name << std::endl;
    } else {
        std::cout << "Kingdom N:" << index << std::endl;
    }
    std::cout << "Overall health: " << getHealth(index) << std::endl;
    std::cout << "Overall force: " << getForce(index) << std::endl;
}

void GameEngine::generateEvent() {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 3);
    int eventNumber = dist(engine);
    switch (eventNumber)
    {
    case 1:
        attackEvent();
        break;
    case 2:
        aliasEvent();
        break;
    case 3:
        artifactEvent();
        break;
    }
}

void GameEngine::attackEvent() {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 3);
    int kingdomNumber = 0;
    do {
        kingdomNumber = dist(engine);
    } while (m_aliases[kingdomNumber] != false);
    std::cout << "\033[31mOh no, it seams that Kingdom N:" << kingdomNumber << " wants to attack you!\033[0m" << std::endl;
    std::cout << "\033[31mHis characteristics:\033[0m" << std::endl;
    displayInfo(kingdomNumber);
    std::cout << "\033[32mYour charactersistics:\033[0m" << std::endl;
    displayInfo(0);
    char user_choice = 0;
    std::cout << "\033[31mTo attack, type \"A\", and to try to alias, type \"F\": \033[0m" << std::endl;
    std::cin >> user_choice;
    if (user_choice == 'F') {
        std::uniform_int_distribution<int> dist1(1, 2);
        std::cout << "\nWaiting for them to respond...\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (dist(engine) == 1) {
            std::cout << "\033[32mNice, they agreed to become aliases! Your kingdom grows!\n\033[0m" << std::endl;
            alias(kingdomNumber);
            return;
        } else {
            std::cout << "\033[31mUnfortunately, they are attacking... To the battle!\033[0m" << std::endl;
        }
    }
    attack(kingdomNumber);
}

void GameEngine::aliasEvent() {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 3);
    int kingdomNumber = 0;
    do {
        kingdomNumber = dist(engine);
    } while (m_aliases[kingdomNumber] != false);
    std::cout << "\033[32mWow, a good chance to make new friends! Kingdom N:" << kingdomNumber << " want to make alias with you!\033[0m" << std::endl;
    char user_choice = 0;
    std::cout << "\033[32mTo accept, type \"A\", to reject, type \"R\": \033[0m";
    std::cin >> user_choice;
    if (user_choice == 'R') {
        std::cout << "\033[31mHmm.. Ok, maybe you better know what you are doing)))\033[0m" << std::endl;
    } else {
        std::cout << "\033[32mNice! You made new alias wiht this kingdom!\033[0m" << std::endl;
        alias(kingdomNumber);
    }
}

void GameEngine::artifactEvent() {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 2);
    int artifactType = dist(engine);
    if (artifactType == 1) {
        std::cout << "\033[32mWow, you found an artifact that is healing you!\033[0m" << std::endl;
        m_kingdoms[0]->healKingdom();
    } else {
        std::cout << "\033[31mOops... You found an artifact that harmed your kingdom and took 50\% avay of your health...\nGood Luck next time...\033[0m" << std::endl;
        m_kingdoms[0]->harmKingdom(getHealth(0) / 2);
    }
}

void GameEngine::attack(int kingdomNumber) {
    m_kingdoms[0]->harmKingdom(getForce(kingdomNumber));
    m_kingdoms[kingdomNumber] ->harmKingdom(getForce(0));
    if (getHealth(kingdomNumber) == 0) {
        m_destroyed[kingdomNumber] = true;
    }
    if (getHealth(0) == 0) {
        m_destroyed[0] = true;
    }
}
void GameEngine::alias(int kingdomNumber) {
    m_aliases[kingdomNumber] = true;
    m_kingdoms[0]->healKingdom();
    m_kingdoms[kingdomNumber]->healKingdom();
}

void GameEngine::checkForLoose() {
    if (m_destroyed[0]) {
        std::cout << "\033[31mAhh.. Your kingdom is destroyed... Game Over!\033[0m" << std::endl;
        cleanup();
        exit(EXIT_SUCCESS);
    }
}

void GameEngine::checkForWin() {
    for (int i = 1; i < KINGDOM_COUNT; ++i) {
        if (m_aliases[i] == false && m_destroyed[i] == false) {
            return;
        }
    }
    std::cout << "\033[32mCongratulations!!! You won!\033[0m" << std::endl;
    cleanup();
    exit(EXIT_SUCCESS);
}

void GameEngine::cleanup() {
    for (int i = 0; i < KINGDOM_COUNT; ++i) {
        for (int j = 0; j < CREATURE_COUNT; ++j) {
            delete m_kingdoms[i]->m_creatures[j];
        }
        delete m_kingdoms[i];
    }
}