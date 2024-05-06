//Testing by Juvraj Shergill
//file addded and changed by Juvraj Shergill
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>
#include <algorithm>

#include <gtest/gtest.h>
// testing is at the end of file 

using namespace std;

class Actor {
public:
    int x;
    int y;
    int health = 100;
    int speed;
    int defense;

    Actor(int x, int y, int health, int speed) : x(x), y(y), health(health), speed(speed), defense(0) {}
    virtual ~Actor() {}

    virtual void move(int newX, int newY) = 0;
    virtual void attack(Actor& target) = 0;
    virtual void takeDamage(int damage) {
        int finalDamage = max(0, damage - defense);
        health -= finalDamage;
        if (health <= 0) {
            cout << getType() << " has been defeated!\n";
        }
    }
	virtual void specialAbility(vector<Actor*>& actors) = 0;
    virtual string getType() const = 0;
    virtual string getClass() const = 0;
	virtual void chooseAction(vector<Actor*>& actors) = 0;

    int getHealth() const {
        return health;
    }

    int getSpeed() const {
        return speed;
    }

    int getDefense() const {
        return defense;
    }

    void setDefense(int def) {
        defense = def;
    }
};

class Hero : public Actor {

public:
    Hero(int x, int y, int health, int speed) : Actor(x, y, health, speed) {}
    virtual ~Hero() {}
    // testing 
    virtual void move(int newX, int newY) {
        x = newX;
        y = newY;
    }
    // added this part - using for testig 
     void attack(Actor& target) override {
        int attackPower = 10;  
        target.takeDamage(attackPower);
        cout << "Hero attacks " << target.getType() << " with power " << attackPower << endl;
    }
    // added this part - using for testing 
     void specialAbility(vector<Actor*>& actors) override {
        cout << "Hero uses a special ability!" << endl;
        for (auto* actor : actors) {
            if (actor->getType() == "Hero") {
                actor->setDefense(actor->getDefense() + 5);
            }
        }
    }
    // useing for testing 
    string getClass() const override {
        return "Warrior";  
    }
    // useing for testing
    void chooseAction(vector<Actor*>& actors) override {
        if (!actors.empty()) attack(*actors.front());
    }

    string getType() const override { return "Hero"; }

    void displayHealth(vector<Actor*> actors) {
        cout << "Remaining health:\n";
        for (Actor* actor : actors) {
            cout << actor->getClass() << ": " << actor->getHealth() << " HP\n";
        }
    }
};

class Fighter : public Hero {
public:
    Fighter(int x, int y, int health) : Hero(x, y, health, 20) {
        setDefense(3); // Medium armor
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Fighter"; }

    void specialAbility(vector<Actor*>& actors) override {
        cout << "The Fighter Lunges at the Enemy!\n";
        if (!actors.empty()) {
            int targetIndex;
            cout << "Choose target for special ability: ";
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size()) {
                Actor* target = actors[targetIndex];
                target->takeDamage(30); //Special Move damage
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
        else {
            cout << "No target available for special ability!\n";
        }
    }

    void attack(Actor& target) override {
        cout << "The Fighter attacks using Double Slash!\n";
        target.takeDamage(20); // Fighter deals more base damage - class feature
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for " << getClass() << ":\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack:\n";
            int targetIndex = -1;
            for (size_t i = 0; i < actors.size(); ++i) {
                if (actors[i]->getType() != "Hero" && actors[i]->getHealth() > 0) {
                    cout << i << ". " << actors[i]->getClass() << " - Health: " << actors[i]->getHealth() << " HP\n";
                }
            }
            cin >> targetIndex;
            targetIndex += 4;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex]->getType() != "Hero" && actors[targetIndex]->getHealth() > 0) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

};

class Ranger : public Hero {
public:
    Ranger(int x, int y, int health) : Hero(x, y, health, 28) {
        setDefense(2); // Light armor 
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Ranger"; }

    void specialAbility(vector<Actor*>& actors) override {
        cout << "The Ranger uses Volley to hit two enemies!\n"; //allows to spread dmg among multiple targets
        int targetIndex1, targetIndex2;
        cout << "Choose first target to hit: ";
        cin >> targetIndex1;
        cout << "Choose second target to hit: ";
        cin >> targetIndex2;
        if (targetIndex1 >= 0 && targetIndex1 < actors.size() && targetIndex2 >= 0 && targetIndex2 < actors.size()) {
            Actor* target1 = actors[targetIndex1];
            Actor* target2 = actors[targetIndex2];
            target1->takeDamage(15); //damage from ability
            target2->takeDamage(15);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    void attack(Actor& target) override {
        cout << "The Ranger attacks using Rapid Shot!\n";
        target.takeDamage(18);
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for " << getClass() << ":\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack:\n";
            int targetIndex = -1;
            for (size_t i = 0; i < actors.size(); ++i) {
                if (actors[i]->getClass() != "Hero" && actors[i]->getHealth() > 0) {
                    cout << i << ". " << actors[i]->getType() << " - Health: " << actors[i]->getHealth() << " HP\n";
                }
            }
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex]->getClass() != "Hero" && actors[targetIndex]->getHealth() > 0) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

class Rogue : public Hero {
public:
    Rogue(int x, int y, int health) : Hero(x, y, health, 30) {
        setDefense(2); // Light armor
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Rogue"; }

    void specialAbility(vector<Actor*>& actors) override {
        cout << "The Rogue performs a sneak attack!\n"; //special ability
        int targetIndex;
        cout << "Choose target: ";
        cin >> targetIndex;
        if (targetIndex >= 0 && targetIndex < actors.size()) {
            actors[targetIndex]->takeDamage(20);
        }
        else {
            cout << "Invalid target!\n";
        }
    }

    void attack(Actor& target) override {
        cout << "The Rogue strikes with their daggers!\n"; //two slashes but low dmg
        target.takeDamage(5);
        target.takeDamage(5);
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for Rogue:\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack: ";
            int targetIndex;
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex] != this) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

class Paladin : public Hero {
public:
    Paladin(int x, int y, int health) : Hero(x, y, health, 12) {
        setDefense(5); // Heavy armor
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Paladin"; }

    void specialAbility(vector<Actor*>& actors) override {
        cout << "The Paladin uses Lay on Hands to heal!\n"; //self-heal
        int targetIndex;
        cout << "Choose target to heal: ";
        cin >> targetIndex;
        if (targetIndex >= 0 && targetIndex < actors.size()) {
            actors[targetIndex]->takeDamage(-15); // Heals 15 health
        }
        else {
            cout << "Invalid target!\n";
        }
    }

    void attack(Actor& target) override {
        cout << "The Paladin swings their longsword!\n";
        target.takeDamage(15);
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for Paladin:\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack: ";
            int targetIndex;
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex] != this) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

class Wizard : public Hero {
private:
    bool fireballCharged;
public:
    Wizard(int x, int y, int health) : Hero(x, y, health, 14), fireballCharged(false) {
        setDefense(1); // Robe
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Wizard"; }

    void specialAbility(vector<Actor*>& actors) override {
        if (!fireballCharged) {
            cout << "The Wizard charges up Fireball!\n"; //Takes one turn to cast
            fireballCharged = true;
        }
        else {
            cout << "The Wizard unleashes Fireball!\n";
            for (Actor* actor : actors) {
                actor->takeDamage(30);
            }
            fireballCharged = false;
        }
    }

    void attack(Actor& target) override {
        cout << "The Wizard casts Lightning Beam!\n";
        target.takeDamage(15);
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for Wizard:\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack: ";
            int targetIndex;
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex] != this) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

class Cleric : public Hero {
private:
    bool divineAidCharged;
public:
    Cleric(int x, int y, int health) : Hero(x, y, health, 10), divineAidCharged(false) {
        setDefense(5); // Heavy armor
    }

    void move(int newX, int newY) override {}
    string getClass() const override { return "Cleric"; }

    void specialAbility(vector<Actor*>& actors) override { //Cleric feature
        if (!divineAidCharged) {
            cout << "The Cleric starts charging Divine Aid!\n";
            divineAidCharged = true;
        }
        else {
            cout << "The Cleric casts Divine Aid!\n";
            for (Actor* actor : actors) {
                actor->takeDamage(-20); // Heal 20 health
            }
            divineAidCharged = false;
        }
    }

    void attack(Actor& target) override {
        cout << "The Cleric strikes with their mace!\n";
        target.takeDamage(10);
    }

    void chooseAction(vector<Actor*>& actors) override {
        displayHealth(actors);
        cout << "Choose action for Cleric:\n";
        cout << "1. Attack\n";
        cout << "2. Use Special Ability\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Choose target to attack: ";
            int targetIndex;
            cin >> targetIndex;
            if (targetIndex >= 0 && targetIndex < actors.size() && actors[targetIndex] != this) {
                attack(*actors[targetIndex]);
            }
            else {
                cout << "Invalid target!\n";
            }
        }
        else if (choice == 2) {
            specialAbility(actors);
        }
        else {
            cout << "Invalid choice!\n";
        }
    }
};

class Monster : public Actor {
protected:
    
public:
    Monster(int x, int y, int health, int speed) : Actor(x, y, health, speed) { }

    // Added functions - Move, attack, special attack, getclass, choose action,
    // testing    
    void move(int newX, int newY) override {
        x = newX;
        y = newY;
        cout << "Monster moves to (" << x << ", " << y << ")." << endl;
    }

    void attack(Actor& target) override {
        int attackPower = 15;  
        target.takeDamage(attackPower);
        cout << "Monster attacks " << target.getType() << " with power " << attackPower << endl;
    }

     void specialAbility(vector<Actor*>& actors) override {
        cout << "Monster uses a roar!" << endl;
        for (auto* actor : actors) {
            if (actor->getType() == "Hero") {
                cout << "Hero is stunned by the Monster's roar!" << endl;
            }
        }
    }

    string getType() const override { return "Monster"; }

    string getClass() const override {
        return "GiantRat";  
    }

    void chooseAction(vector<Actor*>& actors) override {
        for (auto* actor : actors) {
            if (actor->getType() == "Hero") {
                attack(*actor);
                break;  
            }
        }
    }

    void displayHealth(vector<Actor*>& actors) {
        cout << "Remaining health:\n";
        for (Actor* actor : actors) {
            cout << actor->getType() << ": " << actor->getHealth() << " HP\n";
        }
    }
};

class GiantRat : public Monster {
public:
    GiantRat(int x, int y, int health) : Monster(x, y, health, 17) { setDefense(0); } 

    void move(int newX, int newY) override {}
    string getClass() const override { return "Giant Rat"; }

    void specialAbility(vector<Actor*>& actors) override {}

    void attack(Actor& target) override {
        cout << "The Giant Rat snaps its teeth!\n";
        target.takeDamage(8);
    }

    void chooseAction(vector<Actor*>& actors) override {
        int targetIndex = rand() % actors.size();
        attack(*actors[targetIndex]);
    }
};

class Bandit : public Monster {
public:
    Bandit(int x, int y, int health) : Monster(x, y, health, 15) {setDefense(0);}

    void move(int newX, int newY) override {}
    string getClass() const override { return "Bandit"; }

    void specialAbility(vector<Actor*>& actors) override {}

    void attack(Actor& target) override {
        cout << "The Bandit slashes with his dagger!\n";
        target.takeDamage(12);
    }

    void chooseAction(vector<Actor*>& actors) override {
        int targetIndex = rand() % actors.size();
        attack(*actors[targetIndex]);
    }
};

class Orc : public Monster {
public:
    Orc(int x, int y, int health) : Monster(x, y, health, 11) {setDefense(0);}

    void move(int newX, int newY) override {}
    string getClass() const override { return "Orc"; }

    void specialAbility(vector<Actor*>& actors) override {}

    void attack(Actor& target) override {
        cout << "The Orc swings its greataxe!\n";
        target.takeDamage(20);
    }

    void chooseAction(vector<Actor*>& actors) override {
        int targetIndex = rand() % actors.size();
        attack(*actors[targetIndex]);
    }
};

class Skeleton : public Monster {
public:
    Skeleton(int x, int y, int health) : Monster(x, y, health, 13) {setDefense(0);}

    void move(int newX, int newY) override {}
    string getClass() const override { return "Skeleton"; }

    void specialAbility(vector<Actor*>& actors) override {}

    void attack(Actor& target) override {
        cout << "The Skeleton swings its sword!\n";
        target.takeDamage(10);
    }

    void chooseAction(vector<Actor*>& actors) override {
        int targetIndex = rand() % actors.size();
        attack(*actors[targetIndex]);
    }
};

class Necromancer : public Monster {
public:
    Necromancer(int x, int y, int health) : Monster(x, y, health, 40) {setDefense(0);}

    void move(int newX, int newY) override {}
    string getClass() const override { return "Necromancer"; }

    void specialAbility(vector<Actor*>& actors) override {
        cout << "The Necromancer unleashes Unholy Rancor!\n";
        for (Actor* actor : actors) {
            if (actor->getType() != "Necromancer") {
                actor->takeDamage(10); // Assuming 10 damage for Unholy Rancor
            }
        }
    }

    void attack(Actor& target) override {
        cout << "The Necromancer attacks with his mace!\n";
        target.takeDamage(15);
    }

    void chooseAction(vector<Actor*>& actors) override {
        int actionChoice = rand() % 2; // Randomly choose between normal attack and special ability
        if (actionChoice == 0) {
            specialAbility(actors);
        }
        else {
            int targetIndex = rand() % actors.size();
            attack(*actors[targetIndex]);
        }
    }
};

// Testing here 
class ActorTest : public ::testing::Test {
protected:
    Hero *hero;
    Monster *monster;

    void SetUp() override {
        hero = new Hero(0, 0, 100, 5);
        monster = new Monster(0, 0, 50, 3);
    }

    void TearDown() override {
        delete hero;
        delete monster;
    }
};

// Hero test
TEST_F(ActorTest, MoveHero) {
    hero->move(10,10);
    EXPECT_EQ(hero->x, 10);
    EXPECT_EQ(hero->y, 10);
}
TEST_F(ActorTest, HeroStats) {
    EXPECT_EQ(hero->getHealth(), 100);
    EXPECT_EQ(hero->getSpeed(), 5);
    EXPECT_EQ(hero->getClass(), "Warrior");
}

// Monster test
TEST_F(ActorTest, MoveMonster) {
    monster->move(10,10);
    EXPECT_EQ(monster->x, 10);
    EXPECT_EQ(monster->y, 10);
}
TEST_F(ActorTest, MonsterStats) {
    EXPECT_EQ(monster->getHealth(), 50);
    EXPECT_EQ(monster->getSpeed(), 3);
    EXPECT_EQ(monster->getType(), "Monster");
}

