/*
* Author: Jeffrey Lim
* main.cpp
 11-23-2022

 This program models a game of the medieval times in a world filled with protectors and nobles.
 There are two types of Nobles, one that hires an army to battle for him and one that battles for himself.
 Nobles have the ability to fire warriors as well.
 Protectors have the ability to runaway from their army.
 When two Nobles battle, the winner is determined by the overall strengths of each hired warrior OR each Noble itself if he is fighting. The Noble with the greater overall "army strength" is the winner
 After a battle, each individual protector in the Noble's army is reduced using a calculated ratio depending on the characteristics of the opponent's strength.

 SEPARATED COMPILATION

 */

#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace WarriorCraft;

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);

}