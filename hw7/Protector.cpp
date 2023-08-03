#include "Protector.h"
#include "Noble.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    // output operator for Protector. Returns the name of the protector and its strength
    ostream& operator<<(ostream& os, const Protector& protector) {
        os << protector.name << ": " << protector.strength;
        return os;
    }

    //Protector:
    // 
    // constructor
    Protector::Protector(const string& theName, double theStrength) : name(theName), strength(theStrength), boss(nullptr) {}


    //returns the name of protector
    const string& Protector::getName() const {
        return name;
    }

    //returns the strength of Protector
    double Protector::getProtectorStrength() const {
        return strength;
    }

    //takes in a new strength and replaces the Protector's original strength with the new strength
    void Protector::setProtectorStrength(double theStrength) {
        strength = theStrength;
    }

    //takes in a Lord pointer and sets the Protector's boss to it
    void Protector::setProtectorBoss(Lord* Lordptr) {
        boss = Lordptr;
    }

    // lets the Protector decide to runaway from his noble
    // does not fail silently so returns true if successful or false if not.
    bool Protector::runaway() {
        // Test Case: if the Protector has no boss
        if (boss == nullptr) {
            cout << name << " is not hired to anyone." << endl;
            return false;
        }
        // Test Case: if the Protector is dead
        else if (strength == 0) {
            cout << name << " is already dead." << endl;
            return false;
        }
        //Test Case: if the Protector can be removed from the army meaning he is in the army.
        if (boss->remove_protector(*this) == true) {
            cout << name << " flees in terror, abandoning his lord, " << boss->getName() << endl;
            boss = nullptr; //update boss to nullptr because he is no long employed
            return true;
        }
        else {
            return false;
        }

    }
    // returns the Protector's boss
    Lord* Protector::getBoss() const {
        return boss;
    }

    //Wizard:
    // prints the dialog of a wizard in battle
    void Wizard::defend() const {
        cout << "POOF" << endl;
    }

    //Warrior:
    // prints the dialog of a Warrior in battle
    void Warrior::defend() const {
        cout << getName() << " says: Take that in the name of my lord, " << getBoss()->getName() << endl;
    }

    //Swordsman:
    // prints the dialog of a Swordsman in battle
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();
    }

    //Archer:
    // prints the dialog of an Archer in battle
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }

}
