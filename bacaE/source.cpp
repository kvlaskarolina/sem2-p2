// Karolina Kulas
#include <iostream>
#include <string>
using namespace std;
class PLAYER_CLASS;
class CAESAR_CLASS;
class ARENA_CLASS;
class HUMAN_CLASS;
class BEAST_CLASS;
class SQUAD_CLASS;
class BERSERKER_CLASS;
class LIST_OF_SQUAD_PLAYERS;

class PLAYER_CLASS {
  friend class CAESAR_CLASS;
  friend class ARENA_CLASS;
  friend class SQUAD_CLASS;

private:
  virtual void die() = 0;

public:
  unsigned int maxHealth;
  unsigned int currHealth;
  unsigned int damage;
  unsigned int agility;
  bool alive;
  bool judged = false;
  virtual bool wasJudged() { return judged; }
  virtual unsigned int getRemainingHealth() = 0;
  virtual unsigned int getDamage() = 0;
  virtual unsigned int getAgility() = 0;
  virtual unsigned int getMaxHealth() { return maxHealth; }
  virtual unsigned int getCurrHealth() { return currHealth; }
  virtual void takeDamage(unsigned int takenDamage) = 0;
  virtual void applyWinnerReward() = 0;
  virtual void cure() = 0;
  virtual void printParams() = 0;
  virtual string getID() { return "DefaultID"; }
  virtual unsigned int getDefence() { return 0; }
};
class CAESAR_CLASS {
public:
  ARENA_CLASS *arena;
  unsigned int judged;
  CAESAR_CLASS() : arena(NULL), judged(0) {}
  void judgeDeathOrLife(PLAYER_CLASS *toJudge);
};

class ARENA_CLASS {
  friend class PLAYER_CLASS;
  friend class SQUAD_CLASS;
  friend class CAESAR_CLASS;

private:
  CAESAR_CLASS *caesar;

public:
  unsigned int attackCounter;
  ARENA_CLASS(CAESAR_CLASS *thisCaesar) : caesar(thisCaesar) {
    caesar->arena = this;
  }
  void fight(PLAYER_CLASS *player1, PLAYER_CLASS *player2) {
    if (player1->getRemainingHealth() == 0 ||
        player2->getRemainingHealth() == 0) {
      return;
    }
    if (player2->getAgility() > player1->getAgility()) {
      PLAYER_CLASS *pom = player1;
      player1 = player2;
      player2 = pom;
    }
    player1->printParams();
    player2->printParams();
    attackCounter = 0;
    bool flag = true;
    while (attackCounter < 40 && flag) {
      if (player1->getRemainingHealth() > 0) {
        ++attackCounter;
        player2->takeDamage(player1->getDamage());
        player2->printParams();
        if (player2->getRemainingHealth() == 0) {
          player2->die();
          flag = false;
        }
        if (player2->getRemainingHealth() < 10) {
          flag = false;
        }
      } else
        break;

      if (player2->getRemainingHealth() > 0 && flag) {
        ++attackCounter;
        player1->takeDamage(player2->getDamage());
        player1->printParams();
        if (player1->getRemainingHealth() == 0) {
          player1->die();
          flag = false;
        }
        if (player1->getRemainingHealth() < 10) {

          flag = false;
        }
      } else
        break;
    }
    if (player1->getRemainingHealth() > 0) {
      caesar->judgeDeathOrLife(player1);
      player1->printParams();
    }
    if (player2->getRemainingHealth() > 0) {
      caesar->judgeDeathOrLife(player2);
      player2->printParams();
    }
    if (player1->getRemainingHealth() > 0) {
      player1->applyWinnerReward();
      player1->cure();
    }
    if (player2->getRemainingHealth() > 0) {
      player2->applyWinnerReward();
      player2->cure();
    }
    player1->printParams();
    player2->printParams();
  }
};
void CAESAR_CLASS::judgeDeathOrLife(PLAYER_CLASS *toJudge) {
  judged++;
  if (arena->attackCounter % 2 == 0 && judged % 3 == 0) {
    toJudge->die();
    judged = 0;
    toJudge->judged = true;
  }
}
class HUMAN_CLASS : virtual public PLAYER_CLASS {
private:
  string ID;
  virtual void die() {
    alive = false;
    currHealth = 0;
  }

public:
  unsigned int defence;
  HUMAN_CLASS(string id) {
    ID = id;
    maxHealth = 200;
    currHealth = 200;
    damage = 30;
    agility = 10;
    defence = 10;
    alive = true;
  }
  virtual void printParams() {
    if (getRemainingHealth() > 0) {
      cout << getID() << ":" << getMaxHealth() << ":" << getCurrHealth() << ":"
           << getRemainingHealth() << "%:" << getDamage() << ":" << getAgility()
           << ":" << getDefence() << endl;
    } else
      cout << getID() << ":R.I.P." << endl;
  }
  virtual unsigned int getDamage() { return damage; }
  virtual unsigned int getRemainingHealth() {
    return (currHealth * 100) / maxHealth;
  }
  virtual unsigned int getAgility() { return agility; }
  virtual unsigned int getDefence() { return defence; }
  virtual string getID() { return ID; }
  virtual void setID(string newID) { ID = newID; }
  virtual void takeDamage(unsigned int takenDamage) {
    if (takenDamage < getAgility() + getDefence())
      return;
    if (currHealth > (takenDamage - getAgility() - getDefence())) {
      currHealth -= (takenDamage - getAgility() - getDefence());
    } else {
      die();
    }
  }
  virtual void applyWinnerReward() {
    damage += 2;
    agility += 2;
  }
  virtual void cure() { currHealth = maxHealth; }
};
class BEAST_CLASS : virtual public PLAYER_CLASS {
private:
  string ID;
  virtual void die() {
    alive = false;
    currHealth = 0;
  }

public:
  BEAST_CLASS(string id) {
    ID = id;
    maxHealth = 150;
    currHealth = 150;
    damage = 40;
    agility = 20;
    alive = true;
  }
  virtual void printParams() {
    if (getRemainingHealth() > 0) {
      cout << getID() << ":" << getMaxHealth() << ":" << getCurrHealth() << ":"
           << getRemainingHealth() << "%:" << getDamage() << ":" << getAgility()
           << endl;
    } else
      cout << getID() << ":R.I.P." << endl;
  }
  virtual void setID(string newID) { ID = newID; }
  virtual string getID() { return ID; }
  virtual unsigned int getDamage() {
    if (getRemainingHealth() < 25)
      return 2 * damage;
    return damage;
  }
  virtual unsigned int getRemainingHealth() {
    return (currHealth * 100) / maxHealth;
  }
  virtual unsigned int getAgility() { return agility; }
  virtual void takeDamage(unsigned int takenDamage) {
    if (takenDamage < (getAgility() / 2))
      return;
    if (currHealth > (takenDamage - getAgility() / 2)) {
      currHealth -= (takenDamage - getAgility() / 2);
    } else {
      die();
    }
  }
  virtual void applyWinnerReward() {
    damage += 2;
    agility += 2;
  }
  virtual void cure() { currHealth = maxHealth; }
  virtual unsigned int getDefence() { return 0; }
};
class BERSERKER_CLASS : public HUMAN_CLASS, public BEAST_CLASS {
private:
  string ID;
  unsigned int defence;
  virtual void die() {
    alive = false;
    currHealth = 0;
  }

public:
  BERSERKER_CLASS(string idH, string idB) : HUMAN_CLASS(idH), BEAST_CLASS(idB) {
    maxHealth = 200;
    currHealth = 200;
    HUMAN_CLASS::setID(idH);
    BEAST_CLASS::setID(idB);
    HUMAN_CLASS::damage = 35;
    HUMAN_CLASS::agility = 5;
    HUMAN_CLASS::defence = 15;
    BEAST_CLASS::damage = 35;
    BEAST_CLASS::agility = 5;
    alive = true;
  }
  virtual void printParams() {
    if (getRemainingHealth() > 0) {
      if (asHuman()) {
        cout << HUMAN_CLASS::getID() << ":" << getMaxHealth() << ":"
             << getCurrHealth() << ":" << getRemainingHealth()
             << "%:" << getDamage() << ":" << getAgility() << ":"
             << getDefence() << endl;
      } else {
        cout << BEAST_CLASS::getID() << ":" << getMaxHealth() << ":"
             << getCurrHealth() << ":" << getRemainingHealth()
             << "%:" << getDamage() << ":" << getAgility() << endl;
      }
    } else
      cout << HUMAN_CLASS::getID() << ":R.I.P." << endl;
  }
  bool asHuman() { return getRemainingHealth() >= 25; }
  virtual string getID() {
    if (asHuman())
      return HUMAN_CLASS::getID();
    return BEAST_CLASS::getID();
  }
  virtual unsigned int getDamage() {
    if (asHuman())
      return BEAST_CLASS::damage;
    return BEAST_CLASS::damage * 2;
  }
  virtual unsigned int getDefence() {
    if (asHuman())
      return HUMAN_CLASS::defence;
    return 0;
  }
  virtual unsigned int getRemainingHealth() {
    return (currHealth * 100) / maxHealth;
  }
  virtual unsigned int getAgility() { return BEAST_CLASS::agility; }
  virtual void takeDamage(unsigned int takenDamage) {
    if (!asHuman()) {
      if (takenDamage < HUMAN_CLASS::agility / 2)
        return;
      if (currHealth > (takenDamage - HUMAN_CLASS::agility / 2)) {
        currHealth -= (takenDamage - HUMAN_CLASS::agility / 2);
      } else {
        die();
      }
    } else {
      if (takenDamage < HUMAN_CLASS::agility + HUMAN_CLASS::defence)
        return;
      if (currHealth >
          (takenDamage - BEAST_CLASS::agility - HUMAN_CLASS::defence)) {
        currHealth -=
            (takenDamage - BEAST_CLASS::agility - HUMAN_CLASS::defence);
      } else {
        die();
      }
    }
  }
  virtual void applyWinnerReward() {
    damage += 2;
    agility += 2;
  }
  virtual void cure() { currHealth = maxHealth; }
};
class MEMBER_OF_SQUAD {
  friend SQUAD_CLASS;

public:
  MEMBER_OF_SQUAD *prev;
  MEMBER_OF_SQUAD *next;
  PLAYER_CLASS *thisPlayer;
  MEMBER_OF_SQUAD(MEMBER_OF_SQUAD *thisNext, PLAYER_CLASS *newPlayer,
                  MEMBER_OF_SQUAD *thisPrev) {
    next = NULL;
    prev = thisPrev;
    thisPlayer = newPlayer;
  }
};
class SQUAD_CLASS : virtual public PLAYER_CLASS {
  friend MEMBER_OF_SQUAD;

private:
  virtual void die() {
    if (firstMember == NULL)
      return;
    firstMember = NULL;
    numberOfMembers = 0;
    return;
  }

public:
  string squadID;
  MEMBER_OF_SQUAD *firstMember;
  unsigned int numberOfMembers;
  SQUAD_CLASS(string ID) {
    firstMember = NULL;
    squadID = ID;
    numberOfMembers = 0;
  }
  virtual string getID() { return squadID; }
  void addPlayer(PLAYER_CLASS *newPlayer) {
    if (!(newPlayer->getRemainingHealth() > 0))
      return;
    if (firstMember == NULL) {
      ++numberOfMembers;
      MEMBER_OF_SQUAD *newMember = new MEMBER_OF_SQUAD(NULL, newPlayer, NULL);
      firstMember = newMember;
      return;
    }
    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr->next != NULL) {
      if (curr->thisPlayer == newPlayer)
        return;
      curr = curr->next;
    }
    if (curr->thisPlayer == newPlayer)
      return;
    MEMBER_OF_SQUAD *newMember = new MEMBER_OF_SQUAD(NULL, newPlayer, curr);
    curr->next = newMember;
    ++numberOfMembers;
  }
  virtual unsigned int getAgility() {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return 0;
    MEMBER_OF_SQUAD *curr = firstMember;
    unsigned int minAgility = 4294967294;
    while (curr != NULL) {
      if (minAgility > curr->thisPlayer->getAgility()) {
        minAgility = curr->thisPlayer->getAgility();
      }
      curr = curr->next;
    }
    return minAgility;
  }
  virtual unsigned int getDamage() {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return 0;
    MEMBER_OF_SQUAD *curr = firstMember;
    unsigned int sumOfDamage = 0;
    while (curr != NULL) {
      sumOfDamage += curr->thisPlayer->getDamage();
      curr = curr->next;
    }
    return sumOfDamage;
  }
  virtual void applyWinnerReward() {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return;
    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr != NULL) {
      if (curr->thisPlayer->getRemainingHealth() > 0) {
        curr->thisPlayer->agility += 2;
        curr->thisPlayer->damage += 2;
      }
      curr = curr->next;
    }
  }
  virtual void cure() {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return;
    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr != NULL) {
      if (curr->thisPlayer->getRemainingHealth() > 0) {
        curr->thisPlayer->currHealth = curr->thisPlayer->getMaxHealth();
      }
      curr = curr->next;
    }
  }
  virtual unsigned int getRemainingHealth() {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return 0;
    MEMBER_OF_SQUAD *curr = firstMember;
    unsigned int max = 0;
    while (curr != NULL) {
      if (max < curr->thisPlayer->getRemainingHealth()) {
        max = curr->thisPlayer->getRemainingHealth();
      }
      curr = curr->next;
    }
    return max;
  }
  virtual void takeDamage(unsigned int takenDamage) {
    eliminateDeadOnes();
    if (firstMember == NULL)
      return;
    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr != NULL) {
      curr->thisPlayer->takeDamage(takenDamage / numberOfMembers);
      curr = curr->next;
    }
    eliminateDeadOnes();
  }
  bool playersCMP(MEMBER_OF_SQUAD *player1, MEMBER_OF_SQUAD *player2) {
    if (player1->thisPlayer->getID() < player2->thisPlayer->getID())
      return true;
    if (player1->thisPlayer->getID() > player2->thisPlayer->getID())
      return false;
    if (player1->thisPlayer->getMaxHealth() <
        player2->thisPlayer->getMaxHealth())
      return true;
    if (player1->thisPlayer->getMaxHealth() >
        player2->thisPlayer->getMaxHealth())
      return false;
    if (player1->thisPlayer->getCurrHealth() <
        player2->thisPlayer->getCurrHealth())
      return true;
    if (player1->thisPlayer->getCurrHealth() >
        player2->thisPlayer->getCurrHealth())
      return false;
    if (player1->thisPlayer->getRemainingHealth() <
        player2->thisPlayer->getRemainingHealth())
      return true;
    if (player1->thisPlayer->getRemainingHealth() >
        player2->thisPlayer->getRemainingHealth())
      return false;
    if (player1->thisPlayer->getDamage() < player2->thisPlayer->getDamage())
      return true;
    if (player1->thisPlayer->getDamage() > player2->thisPlayer->getDamage())
      return false;
    if (player1->thisPlayer->getAgility() < player2->thisPlayer->getAgility())
      return true;
    if (player1->thisPlayer->getAgility() > player2->thisPlayer->getAgility())
      return false;
    if (player1->thisPlayer->getDefence() < player2->thisPlayer->getDefence())
      return true;
    if (player1->thisPlayer->getDefence() > player2->thisPlayer->getDefence())
      return false;
    return true;
  }
  void eliminateDeadOnes() { // dziala
    while (firstMember != NULL &&
           firstMember->thisPlayer->getRemainingHealth() == 0) {
      if (firstMember->thisPlayer->wasJudged()) {
        firstMember = NULL;
        numberOfMembers = 0;
        return;
      }
      MEMBER_OF_SQUAD *toDelete = firstMember;
      firstMember = firstMember->next;
      if (firstMember != NULL) {
        firstMember->prev = NULL;
      }
      delete toDelete;
      --numberOfMembers;
    }

    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr != NULL) {
      if (curr->thisPlayer->getRemainingHealth() == 0) {
        if (firstMember->thisPlayer->wasJudged()) {
          firstMember = NULL;
          numberOfMembers = 0;
          return;
        }
        if (curr->prev != NULL) {
          curr->prev->next = curr->next;
        }
        if (curr->next != NULL) {
          curr->next->prev = curr->prev;
        }
        curr = curr->next;
        --numberOfMembers;
      } else {
        curr = curr->next;
      }
    }
    if (numberOfMembers == 0)
      firstMember = NULL;
  }
  void swapPlayers(MEMBER_OF_SQUAD *A, MEMBER_OF_SQUAD *B) {
    MEMBER_OF_SQUAD *helper1;
    MEMBER_OF_SQUAD *helper2;
    MEMBER_OF_SQUAD *helper3;
    MEMBER_OF_SQUAD *helper4;
    MEMBER_OF_SQUAD *temp;

    if (A == B)
      return;

    if (B->next == A) {
      temp = A;
      A = B;
      B = temp;
    }
    if (firstMember == A)
      firstMember = B;
    helper1 = A->prev;
    helper2 = B->prev;
    helper3 = A->next;
    helper4 = B->next;

    A->prev = helper3;
    B->prev = helper1;
    A->next = helper4;
    B->next = helper2;

    if (A->prev != NULL)
      A->prev->next = A;

    if (A->next != NULL)
      A->next->prev = A;
    if (B->prev != NULL)
      B->prev->next = B;

    if (B->next != NULL)
      B->next->prev = B;
  }

  void sortSquad() {
    if (firstMember == NULL)
      return;

    bool swapped;
    do {
      swapped = false;
      MEMBER_OF_SQUAD *curr = firstMember;
      while (curr->next != NULL) {
        if (!playersCMP(curr, curr->next)) {
          swapPlayers(curr, curr->next);
          swapped = true;
        } else {
          curr = curr->next;
        }
      }
    } while (swapped);
  }

  virtual void printParams() {
    eliminateDeadOnes();
    if (numberOfMembers == 0) {
      cout << getID() << ":nemo" << endl;
      return;
    }
    cout << getID() << ":" << numberOfMembers << ":" << getRemainingHealth()
         << "%:" << getDamage() << ":" << getAgility() << endl;
    sortSquad();
    MEMBER_OF_SQUAD *curr = firstMember;
    while (curr != NULL) {
      curr->thisPlayer->printParams();
      curr = curr->next;
    }
  }
};
