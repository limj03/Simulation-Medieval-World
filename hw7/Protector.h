#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>

namespace WarriorCraft {
    class Lord;

    class Protector {

        friend std::ostream& operator<<(std::ostream& os, const Protector& protector);

    public:

        Protector(const std::string& theName, double theStrength);

        //getter methods

        const std::string& getName() const;

        double getProtectorStrength() const;

        //setter methods

        void setProtectorStrength(double theStrength);

        void setProtectorBoss(Lord* Lordptr);

        bool runaway();

        virtual void defend() const = 0;

        Lord* getBoss() const;
    private:
        std::string name;
        double strength;
        Lord* boss;

    };

    class Wizard : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };

    class Warrior : public Protector {
    public:
        using Protector::Protector;
        void defend() const override;
    };
    
    class Swordsman : public Warrior {
    public:
        using Warrior::Warrior;
        void defend() const override;
    };

    class Archer : public Warrior {
        using Warrior::Warrior;
        void defend() const override;
    };
}


#endif