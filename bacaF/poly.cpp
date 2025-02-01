POLYNOMIAL operator/(const POLYNOMIAL &other) const {
  POLYNOMIAL nominative;
  POLYNOMIAL divisor;
  POLYNOMIAL pom;
  POLYNOMIAL result;
  Node *current = head;
  while (current != NULL) {
    nominative.addElementBackwards(current);
    current = current->next;
  }
  current = other.head;
  while (current != NULL) {
    divisor.addElementBackwards(current);
    current = current->next;
  }
  if (head->power < other.head->power) {
    return pom;
  }
  result = nominative;
  int power, value, divider;
  Node *top = nominative.head;
  Node *bottom = divisor.head;
  if (bottom->power == 0 && bottom->value == 0) {
    return pom;
  }
  while (top->power >= other.head->power) {
    bottom = divisor.head;
    if (top->value == 0) {
      if (top->next == NULL) {
        break;
      }
      top = top->next;
    } else {
      while (bottom != NULL) {
        if (bottom->value != 0) {
          if (bottom == divisor.head) {
            power = top->power - bottom->power;
            if (power < 0) {
              result.deleteNodes();
              current = pom.head;
              while (current != NULL) {
                result.addElementToList(current->power, current->value,
                                        current->divider);
                current = current->next;
              }
              result.removeZerosAtFront();
              result.lowerDividersAndMultiply();
              result.lowerValues();
              result.addZerosInside();
              return result;
            }
            //								cout << "top: " << top->value << " " <<
            //bottom->divider << endl;
            value = top->value * bottom->divider;
            divider = top->divider * bottom->value;
            int divek = result.NWD3(value, divider);
            value /= divek;
            divider /= divek;
            if (value < 0 && divider < 0) {
              value = -value;
              divider = -divider;
            } else if (value > 0 && divider < 0) {
              value = -value;
              divider = -divider;
            }
            pom.addElementToList(power, value, divider);
            ;
            result.remover(bottom->power + power, bottom->value * value,
                           bottom->divider * divider);
            bottom = bottom->next;
          } else {
            result.remover(bottom->power + power, bottom->value * value,
                           bottom->divider * divider);
            bottom = bottom->next;
          };
          //							cout << bottom->value << " " << value <<
          //" " << bottom->value*value << endl;
        } else {
          bottom = bottom->next;
        }
      }
      //					cout << "result: " << result <<
      //endl;
      nominative = result;
      top = nominative.head;
    }
  }
  result.deleteNodes();
  current = pom.head;
  while (current != NULL) {
    result.addElementToList(current->power, current->value, current->divider);
    current = current->next;
  }
  result.removeZerosAtFront();
  result.lowerDividersAndMultiply();
  result.lowerValues();
  result.addZerosInside();
  return result;
}