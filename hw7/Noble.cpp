

#include "Noble.h"
#include "Protector.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {


    // constructor
    Noble::Noble(const string& theName) :name(theName), life(true) {}

    //returns the name of the Noble
    const string& Noble::getName() const {
        return name;
    }

    //Method deems the protector as dead and sets its strength and status to 0 and false.
    void Noble::protector_dies() {
        life = false;
        modifyStrengths(0);
    }


    //battle is a method for nobles
    //takes in a second noble that is to be battled.
    //method determines and prints out the outcomes of each battle, and calculates the ratio needed to be applied for individual protector's strengths
    void Noble::battle(Noble& player2) {
        cout << name << " battles " << player2.name << endl;
        //Test Case: if both nobles are dead
        if (life == false && player2.life == false) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        //Test Case: if the second noble is dead
        else if (life == true && player2.life == false) {
            defend();
            cout << "He's dead, " << name << endl;
        }
        //Test Case: if the first noble is dead
        else if (life == false && player2.life == true) {
            player2.defend();
            cout << "He's dead, " << player2.name << endl;
        }
        //Test Case: if both nobles have the same strength
        else if (getStrength() == player2.getStrength()) {
            defend();
            player2.defend();
            cout << "Mutual Annihilation: " << name << " and " << player2.name << " die at each other's hands" << endl;
            protector_dies();
            player2.protector_dies();

        }
        //Test Case: if the first noble's army is stronger than the second noble's army
        else if (getStrength() > player2.getStrength()) {
            defend();
            player2.defend();

            cout << name << " defeats " << player2.name << endl;

            //calculating the ratio that needs to be applied in the calculation of each individual protector's strength
            modifyStrengths(calc_ratio(getStrength(), player2.getStrength()));
            player2.protector_dies();

        }
        //Test Case: if the second noble's army is stronger than the first noble's army
        else {
            defend();
            player2.defend();

            cout << player2.name << " defeats " << name << endl;
            //calculating the ratio that needs to be applied in the calculation of each individual protector's strength
            player2.modifyStrengths(player2.calc_ratio(player2.getStrength(), getStrength()));
            protector_dies();
        }

    }
    // sets the life of the Noble, either dead or alive
    void Noble::setLife(bool newlife) {
        life = newlife;
    }
    // checks to see if noble is alive
    bool Noble::isAlive() const {
        return life;
    }

    //Lord:

    // output operator for the Lord Noble. Utilizes the output from Warrior as well.
    ostream& operator<<(ostream& os, const Lord& lord) {
        os << lord.getName() << " has an army of " << lord.protector_lst.size();
        // iteratre through the army
        for (size_t index = 0; index < lord.protector_lst.size(); ++index) {
            os << endl << "\t" << *(lord.protector_lst[index]);
        }
        os << endl;
        return os;
    }

    Lord::Lord(const string& theName) : Noble(theName) {}

    //takes in the ratio to be applied to each warrior after a battle and modifies the strengths of the protectors
    void Lord::modifyStrengths(double ratio) {

        //iterate through the army
        for (size_t index = 0; index < protector_lst.size(); ++index) {
            double newStrength = ratio * protector_lst[index]->getProtectorStrength();
            protector_lst[index]->setProtectorStrength(newStrength);
        }
    }

    //takes in a reference of a protector and attempts to hire the protector. Method returns true of the protector is successfully hired and false if not
    bool Lord::hires(Protector& protector) {
        // Test Case: if the protector is not hired to anyone and the Noble is alive.
        if (protector.getBoss() == nullptr && isAlive() == true) {
            protector.setProtectorBoss(this);  //set the boss
            protector_lst.push_back(&protector);
            return true;
        }
        else {
            return false; // if protector was already hired or if the noble isnt alive
        }
    }

    //takes in a reference of a protector and attempts to fire the protector. Method returns true of the protector is successfully fired and false if not
    bool Lord::fire(Protector& protector) {
        //Test Case: if the noble is dead and protector is hired...
        if (isAlive() == false && protector.getBoss() != nullptr) {
            cerr << "Attempt to fire " << protector.getName() << " by " << getName() << " failed!" << endl;
            return false; //the noble isnt alive 
        }
        //Test Case: if the protector is found in the army and can be removed
        if (remove_protector(protector) == true) {
            cout << "You don't work for me anymore " << protector.getName() << "! -- " << getName() << "." << endl;
            protector.setProtectorBoss(nullptr); //update boss to nullptr because he is no longer employed
            return true;
        }
        return false;

    }

    //takes in a reference of a protector and attempts to remove the protector from the Noble's army. Is used when a protector is either fired or runs away to eliminate redundancy.
    //Method returns true if successful, and false if not
    //Method removes the protector from the army and keeps the order of the orignal lineup the same.
    bool Lord::remove_protector(Protector& protector) {
        bool found = false;
        // iterate through the army
        for (size_t index = 0; index < protector_lst.size(); ++index) {
            //Test Case: if we HAVE FOUND the protector to remove...
            if (found == false) {
                //Test Case: if the address of the protector in the vector is equal to the address of the protector we are trying to fire
                if (protector_lst[index] == &protector) {
                    found = true;

                }
            }
            // after removal, the elements after the element removed gets shifted one spot to the right
            else {
                protector_lst[index - 1] = protector_lst[index];
            }

        }
        // if the protector is found, the last "slot" in the vector needs to be removed. If it was not found, nothing needs to be removed.
        if (found == true) {
            protector_lst.pop_back(); //remove the last "slot"
        }
        else { //if protector was never found, error message prints out that the warrior was never even hired to the Noble
            cerr << protector.getName() << " is not hired by " << getName() << "!" << endl;
        }
        return found;

    }
    // adds up the strength of each protector and returns the total strength of the army
    double Lord::getStrength() const {
        double strength = 0;
        for (size_t index = 0; index < protector_lst.size(); ++index) {
            strength += protector_lst[index]->getProtectorStrength();
        }
        return strength;
    }
    // calls the defend() from each protector
    void Lord::defend() const {
        for (size_t index = 0; index < protector_lst.size(); ++index) {
            protector_lst[index]->defend();
        }
    }

    //method calculates the ratio needed to be accounted for in the strengths of the protectors after battle
    double Lord::calc_ratio(const double strength1, const double strength2) {
        return (strength1 - strength2) / strength1; //same as 1 - (player2.strength / strength)....
    }


    // PersonWithStrengthToFight

    // output operator for PersonWithStrengthToFight Noble. Returns the name of the warrior and its strength
    ostream& operator<<(ostream& os, const PersonWithStrengthToFight& PersonWithStrengthToFight) {
        os << PersonWithStrengthToFight.getName() << ": " << PersonWithStrengthToFight.getStrength();
        return os;
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double theStrength) : strength(theStrength), Noble(name) {}

    //modify the strength of the specific noble that has no ARMY
    void PersonWithStrengthToFight::modifyStrengths(double ratio) {
        strength -= ratio;
    }

    // Noble defend() method. prints out what he says in battle
    void PersonWithStrengthToFight::defend() const {
        cout << "Ugh!" << endl;
    }

    //returns the strength of the specific noble
    double PersonWithStrengthToFight::getStrength() const {
        return strength;
    }

    //method returns the losers strength in this case.
    double PersonWithStrengthToFight::calc_ratio(const double strength1, const double strength2) {
        return strength2;
    }

    //sets the specific noble to be dead and strength goes to zero
    void PersonWithStrengthToFight::protector_dies() {
        Noble::setLife(false);
        strength = 0;
    }
}