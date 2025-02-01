#include <iostream>
using namespace std;
class FRUIT_CLASS;
class BRANCH_CLASS;
class WOOD_CLASS;
class GARDEN_CLASS;

class FRUIT_CLASS {
private:
  FRUIT_CLASS *prev;
  FRUIT_CLASS *next;
  unsigned int len;
  unsigned int weight;
  BRANCH_CLASS *branch;
  unsigned int idx;

public:
  FRUIT_CLASS() {
    prev = NULL;
    next = NULL;
    len = 0;
    weight = 0;
    branch = NULL;
  }
  FRUIT_CLASS(const FRUIT_CLASS &other)
      : prev(NULL), next(NULL), len(0), weight(other.weight),
        branch(other.branch) {
    branch->increaseFruitTotal(1);
    branch->increaseFruitWeightTotal(weight);
  }
  ~FRUIT_CLASS() {
    branch->decreaseFruitTotal(1);
    branch->decreaseFruitWeightTotal(weight);
    delete this;
  }
  unsigned int getLength() { return len; }
  unsigned int getWeight() { return weight; }
  FRUIT_CLASS *getNext() { return next; }
  FRUIT_CLASS *getPrev() { return prev; }
  void setNext(FRUIT_CLASS *fruit) { (*this).next = fruit; }
  void setPrev(FRUIT_CLASS *fruit) { (*this).prev = fruit; }
  void setLen(unsigned int fruit) { (*this).len = fruit; }
  void setBranch(BRANCH_CLASS *b) { branch = b; }
  void growthFruit() {
    ++weight;
    branch->increaseFruitWeightTotal(1);
  }
  void fadeFruit() {
    if (weight > 0) {
      --weight;
      branch->decreaseFruitWeightTotal(1);
    }
  }
  void pluckFruit() {
    branch->decreaseFruitWeightTotal(weight);
    weight = 0;
  }
  BRANCH_CLASS *getBranchPointer() { return branch; }
};
class BRANCH_CLASS {
private:
  unsigned int len;
  unsigned int fruitsTotal;
  unsigned int fruitsWeightTotal;
  unsigned int height;
  BRANCH_CLASS *prev;
  BRANCH_CLASS *next;
  FRUIT_CLASS *firstFruit;
  FRUIT_CLASS *lastFruit;
  TREE_CLASS *tree;

public:
  BRANCH_CLASS() {
    prev = NULL;
    next = NULL;
    firstFruit = NULL;
    lastFruit = NULL;
    len = 0;
    fruitsTotal = 0;
    fruitsWeightTotal = 0;
    height = 0;
    tree = NULL;
    tree->increaseBranchTotal(1);
  }
  BRANCH_CLASS(BRANCH_CLASS &other)
      : prev(NULL), next(NULL), height(0), tree(other.tree),
        fruitsTotal(other.fruitsTotal),
        fruitsWeightTotal(other.fruitsWeightTotal) {
    len = other.len;
    FRUIT_CLASS *temp = new FRUIT_CLASS();
    temp = other.getFirst();
    while (temp != NULL) {
      // przepisac owoce
    }
    tree->increaseBranchTotal(1);
  }
  ~BRANCH_CLASS() {
    if (firstFruit != NULL) {
      FRUIT_CLASS *currFruit = new FRUIT_CLASS();
      currFruit = firstFruit;
      while (currFruit != lastFruit) {
        currFruit = currFruit->getNext();
        delete currFruit->getPrev();
      }
      delete currFruit;
    }
    tree->decreaseBranchTotal(1);
    delete this;
  }
  unsigned int getLength() { return len; }
  unsigned int getFruitsTotal() { return fruitsTotal; }
  unsigned int getWeightsTotal() { return fruitsWeightTotal; }
  unsigned int getHeight() { return height; }
  FRUIT_CLASS *getFirst() { return firstFruit; }
  FRUIT_CLASS *getLast() { return lastFruit; }
  void setFirst(FRUIT_CLASS *b) { firstFruit = b; }
  void setLast(FRUIT_CLASS *b) { lastFruit = b; }
  BRANCH_CLASS *getNext() { return next; }
  BRANCH_CLASS *getPrev() { return prev; }
  void setNext(BRANCH_CLASS *b) { next = b; }
  void setPrev(BRANCH_CLASS *b) { prev = b; }
  void decreaseFruitWeightTotal(unsigned int x) {
    fruitsWeightTotal -= x;
    tree->decreaseFruitWeightTotal(x);
  }
  void increaseFruitWeightTotal(unsigned int x) {
    fruitsWeightTotal += x;
    tree->increaseFruitWeightTotal(x);
  }
  void decreaseFruitTotal(unsigned int x) {
    fruitsTotal -= x;
    tree->decreaseFruitTotal(x);
  }
  void increaseFruitTotal(unsigned int x) {
    fruitsTotal += x;
    tree->increaseFruitTotal(x);
  }
  void growthBranch() {
    ++len;
    FRUIT_CLASS *currFruit = new FRUIT_CLASS();
    if (firstFruit != NULL) {
      *currFruit = *firstFruit;
      while (currFruit != lastFruit) {
        currFruit->growthFruit();
        currFruit = currFruit->getNext();
      }
      currFruit->growthFruit();
      if (len % 2 == 0) {
        FRUIT_CLASS *newFruit = new FRUIT_CLASS();
        currFruit->setNext(newFruit);
        newFruit->setPrev(currFruit);
        newFruit->setLen(len);
        lastFruit = newFruit;
        newFruit->setBranch(this); // nie jestem pewna czy to dziala
      }
    } else {
      if (len == 2) {
        FRUIT_CLASS *newFruit = new FRUIT_CLASS();
        newFruit->setLen(len);
        firstFruit = newFruit;
        lastFruit = newFruit;
        ++fruitsTotal;
      }
    }
  }
  void fadeBranch() {
    if (len != 0) {
      --len;
      FRUIT_CLASS *currFruit = new FRUIT_CLASS();
      if (len == 1) {
        --fruitsTotal;
        decreaseFruitWeightTotal(firstFruit->getWeight());
        firstFruit = NULL;
        lastFruit = NULL;
      }
      if (firstFruit != NULL) {
        *currFruit = *firstFruit;
        while (currFruit != lastFruit) {
          currFruit->fadeFruit();
          currFruit = currFruit->getNext();
        }
        currFruit->fadeFruit();
        if (len % 2 == 1) {
          --fruitsTotal;
          decreaseFruitWeightTotal(currFruit->getWeight());
          currFruit = currFruit->getPrev();
          lastFruit = currFruit;
        }
      } else {
        if (len == 2) {
          FRUIT_CLASS *newFruit = new FRUIT_CLASS();
          firstFruit = newFruit;
          lastFruit = newFruit;
        }
      }
    }
  }
  void harvestBranch(unsigned int x) {
    FRUIT_CLASS *currFruit = new FRUIT_CLASS();
    currFruit = firstFruit;
    while (currFruit->getLength() < x && currFruit != lastFruit) {
      currFruit = currFruit->getNext();
    }
    while (currFruit != lastFruit) {
      currFruit->pluckFruit();
      currFruit = currFruit->getNext();
    }
    if (currFruit->getLength() >= x) {
      currFruit->pluckFruit();
    }
  }
  void cutBranch(unsigned int x) {
    FRUIT_CLASS *curr = new FRUIT_CLASS;
    curr = firstFruit;
    while (curr != NULL && curr->getLength() <= x) {
      curr = curr->getNext();
    }
    while (curr != NULL && curr->getLength() > x) {
      curr = curr->getNext();
      delete curr->getPrev();
    }
    len = x;
  }
  FRUIT_CLASS *getFruitPointer(unsigned int x) {
    if (x % 2 == 1 || x == 0)
      return NULL;
    FRUIT_CLASS *currFruit = new FRUIT_CLASS();
    currFruit = firstFruit;
    while (currFruit->getLength() != x && currFruit != lastFruit) {
      currFruit = currFruit->getNext();
    }
    if (currFruit->getLength() == x) {
      return currFruit;
    } else
      return NULL;
  }
  TREE_CLASS *getTreePointer() { return tree; }
};
class TREE_CLASS {
private:
  unsigned int len;
  unsigned int fruitsTotal;
  unsigned int fruitsWeightTotal;
  unsigned int branchesTotal;
  unsigned int height;
  unsigned int id;
  BRANCH_CLASS *first;
  BRANCH_CLASS *last;
  TREE_CLASS *prev;
  TREE_CLASS *next;
  GARDEN_CLASS *garden;

public:
  TREE_CLASS() {
    len = 0;
    fruitsTotal = 0;
    fruitsWeightTotal = 0;
    branchesTotal = 0;
    height = 0;
    id = 0;
    first = NULL;
    last = NULL;
    prev = NULL;
    next = NULL;
    garden = NULL;
  }
  TREE_CLASS(TREE_CLASS &other) {
    len = other.len;
    fruitsTotal = other.fruitsTotal;
    fruitsWeightTotal = other.fruitsWeightTotal;
    branchesTotal = other.branchesTotal;
    height = other.height;
    id = 0;
    first = NULL;
    last = NULL;
    prev = NULL;
    next = NULL;
    garden = other.garden;
  }
  ~TREE_CLASS() {}
  unsigned int getBranchesTotal() { return branchesTotal; }
  unsigned int getFruitsTotal() { return fruitsTotal; }
  unsigned int getWeightsTotal() { return fruitsWeightTotal; }
  unsigned int getHeight() { return height; }
  unsigned int getNumber() { return id; }
  TREE_CLASS *getPrev() { return prev; }
  TREE_CLASS *getNext() { return next; }
  void decreaseFruitWeightTotal(unsigned int x) {
    fruitsWeightTotal -= x;
    garden->decreaseFruitWeightTotal(x);
  }
  void increaseFruitWeightTotal(unsigned int x) {
    fruitsWeightTotal += x;
    garden->increaseFruitWeightTotal(x);
  }
  void decreaseFruitTotal(unsigned int x) {
    fruitsTotal -= x;
    garden->decreaseFruitTotal(x);
  }
  void increaseFruitTotal(unsigned int x) {
    fruitsTotal += x;
    garden->increaseFruitTotal(x);
  }
  void decreaseBranchTotal(unsigned int x) {
    branchesTotal -= x;
    garden->decreaseBranchTotal(x);
  }
  void increaseBranchTotal(unsigned int x) {
    branchesTotal += x;
    garden->increaseBranchTotal(x);
  }
  void growthTree() {
    ++height;
    BRANCH_CLASS *currBranch = new BRANCH_CLASS();
    currBranch = first;
    while (currBranch != last && currBranch != NULL) {
      currBranch->growthBranch();
    }
    if (currBranch != NULL) {
      currBranch->growthBranch();
    }
    if (height % 3 == 0) {
      if (last != NULL) {
        BRANCH_CLASS *newBranch = new BRANCH_CLASS();
        last->setNext(newBranch);
        newBranch->setPrev(last);
        last = newBranch;
      } else {
        BRANCH_CLASS *newBranch = new BRANCH_CLASS();
        first = newBranch;
        last = newBranch;
      }
    }
  }
  void fadeTree() {
    if (height != 0) {
      --height;
      BRANCH_CLASS *currBranch = new BRANCH_CLASS();
      currBranch = first;
      while (currBranch != last && currBranch != NULL) {
        currBranch->fadeBranch();
      }
      if (currBranch != NULL) {
        currBranch->fadeBranch();
      }
      if (height % 3 == 2) {
        currBranch = last->getPrev();
        last = currBranch;
        currBranch = currBranch->getNext();
        delete currBranch;
      }
    }
  }
  void harvestTree(unsigned int x) {
    BRANCH_CLASS *currBranch = new BRANCH_CLASS();
    currBranch = first;
    while (currBranch != NULL) {
      currBranch->harvestBranch(x);
      currBranch = currBranch->getNext();
    }
  }
  void cutTree(unsigned int x) {}
  void cloneBranch(BRANCH_CLASS &toClone) {
    BRANCH_CLASS *temp = new BRANCH_CLASS();
    temp = first;
    while (temp != NULL && temp->getLength() != 0) {
      temp->getNext();
    }
    if (temp->getLength() == 0) {
      BRANCH_CLASS *pom = new BRANCH_CLASS(toClone);
      temp = pom;
      delete pom;
    }
  }
  GARDEN_CLASS *getGardenPointer() { return garden; }
  BRANCH_CLASS *getBranchPointer(unsigned int idx) { return NULL; }
};
class GARDEN_CLASS {
private:
  unsigned int treesTotal;
  unsigned int branchesTotal;
  unsigned int fruitsTotal;
  unsigned int weightsTotal;
  TREE_CLASS *firstTree;
  TREE_CLASS *lastTree;

public:
  GARDEN_CLASS() {
    treesTotal = 0;
    branchesTotal = 0;
    fruitsTotal = 0;
    weightsTotal = 0;
    firstTree = NULL;
    lastTree = NULL;
  }
  ~GARDEN_CLASS() {
    TREE_CLASS *currTree = new TREE_CLASS();
    currTree = firstTree;
    while (currTree->getNext() != NULL) {
      currTree = currTree->getNext();
      delete currTree->getPrev();
    }
    delete currTree;
  }
  unsigned int getTressTotal() { return treesTotal; }
  unsigned int getBranchesTotal() { return branchesTotal; }
  unsigned int getFriutsTotal() { return fruitsTotal; }
  unsigned int getWeightsTotal() { return weightsTotal; }
  void decreaseFruitWeightTotal(unsigned int x) { weightsTotal -= x; }
  void increaseFruitWeightTotal(unsigned int x) { weightsTotal += x; }
  void decreaseFruitTotal(unsigned int x) { fruitsTotal -= x; }
  void increaseFruitTotal(unsigned int x) { fruitsTotal += x; }
  void decreaseBranchTotal(unsigned int x) { branchesTotal -= x; }
  void increaseBranchTotal(unsigned int x) { branchesTotal += x; }
  void decreaseTreesTotal(unsigned int x) { treesTotal -= x; }
  void increaseTreesTotal(unsigned int x) { treesTotal += x; }
  void plantTree() {}
  void extractTree(unsigned int x) {}
  void growthGarden() {}
  void fadeGarden() {}
  void harvestGarden() {}
  void cloneTree(unsigned int x) {}
  TREE_CLASS *getTreePointer(unsigned int x) {}
};