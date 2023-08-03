#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>

namespace WarriorCraft {
    class Protector;

    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:

        Noble(const std::string& theName);

        //getter methods

        const std::string& getName() const;

        void battle(Noble& player2);

        virtual void protector_dies();

        virtual double calc_ratio(const double strength1, const double strength2) = 0;

        virtual void modifyStrengths(double ratio) = 0;

        virtual void defend() const = 0;

        virtual double getStrength() const = 0;

    protected:
        bool isAlive() const;
        void setLife(bool life);

    private:
        std::string name;
        bool life;
    };

    class Lord : public Noble {
        friend std::ostream& operator<<(std::ostream& os, const Lord& lord);
    public:
        Lord(const std::string& theName);

        double getStrength() const override;

        bool hires(Protector& protector);

        bool fire(Protector& protector);

        bool remove_protector(Protector& protector);

        void modifyStrengths(double ratio) override;

        void defend() const override;

        double calc_ratio(const double strength1, const double strength2) override;



    private:
        std::vector<Protector*> protector_lst;
    };

    class PersonWithStrengthToFight : public Noble {
        friend std::ostream& operator<<(std::ostream& os, const PersonWithStrengthToFight& PersonWithStrengthToFight);
    public:
        PersonWithStrengthToFight(const std::string& theName, double theStrength);

        void modifyStrengths(double ratio) override;

        void defend() const override;

        double getStrength() const override;

        double calc_ratio(const double strength1, const double strength2) override;

        void protector_dies() override;
    private:
        double strength;
    };

}

#endif