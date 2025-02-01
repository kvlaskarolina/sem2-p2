// Karolina Kulas
#include "branch.hpp"
#include "fruit.hpp"
#include <iostream>
using namespace std;
FRUIT_CLASS::FRUIT_CLASS() {
  prev = NULL;
  next = NULL;
  len = 0;
  weight = 0;
  branch = NULL;
}

FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS &other) {
  prev = NULL;
  next = NULL;
  len = 0;
  weight = other.weight;
  branch = NULL;
}

FRUIT_CLASS::~FRUIT_CLASS() {
  prev = NULL;
  next = NULL;
  len = 0;
  weight = 0;
  branch = NULL;
  delete this;
}

unsigned int FRUIT_CLASS::getLength() { return len; }

unsigned int FRUIT_CLASS::getWeight() { return weight; }

FRUIT_CLASS *FRUIT_CLASS::getNext() { return next; }

FRUIT_CLASS *FRUIT_CLASS::getPrev() { return prev; }

void FRUIT_CLASS::setNext(FRUIT_CLASS *fruit) { next = fruit; }

void FRUIT_CLASS::setPrev(FRUIT_CLASS *fruit) { prev = fruit; }

void FRUIT_CLASS::setLen(unsigned int fruit) { len = fruit; }

void FRUIT_CLASS::setBranch(BRANCH_CLASS *b) { branch = b; }

void FRUIT_CLASS::growthFruit() {
  ++weight;
  if (branch != NULL) {
    branch->increaseFruitWeightTotal(1);
  }
}

void FRUIT_CLASS::fadeFruit() {
  if (weight > 0) {
    --weight;
    if (branch != NULL) {
      branch->decreaseFruitWeightTotal(1);
    }
  }
}

void FRUIT_CLASS::pluckFruit() {
  if (branch != NULL) {
    branch->decreaseFruitWeightTotal(weight);
  }
  weight = 0;
}

BRANCH_CLASS *FRUIT_CLASS::getBranchPointer() { return branch; }
