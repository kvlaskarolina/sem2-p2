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