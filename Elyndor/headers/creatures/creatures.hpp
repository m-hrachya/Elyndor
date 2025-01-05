#ifndef CREATURES
#define CREATURES

#include <iostream>

class MagicalCreatures {
public:
    MagicalCreatures(std::string name, int force, double health = 100);
    virtual void heal();
    virtual void harm(double harmSize);
    virtual double getHealth() const;
    virtual int getForce() const;
    virtual ~MagicalCreatures() = 0;
private:
    std::string m_name;
    int m_force;
    double m_health;
};

#endif // CREATURES