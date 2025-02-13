#include <iostream> 

class RuleOfThree {
public:
    int* int_ptr;
    RuleOfThree(int i) {
      int_ptr = new int{i};
    }
    ~RuleOfThree() { delete int_ptr; }
};


void f(RuleOfThree s) {
  std::cout << *(s.int_ptr) << std::endl;
  // s is destroyed at the end of the function f
}

int main() {
  RuleOfThree r{42};
  
  f(r); // Calling f copies r
        // the copy is destroyed at the end of the call
  
  // To uncomment
  // RuleOfThree t{9001};
  // r = t;
}
