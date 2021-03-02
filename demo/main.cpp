#include "libchess/board.h"

#include <iostream>

int main() {
    libchess::Board b;

    std::cout << b.GetPrintableString() << std::endl;

    return 0;
}
