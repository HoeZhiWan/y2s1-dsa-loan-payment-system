#include "loanSystem.h"
#include <iostream>

using namespace std;

int main() {
    LoanSystem::initialize();
    
    LoanSystem loanSystem;
    loanSystem.menuLoop();
    
    LoanSystem::shutdown();
    
    return 0;
}
