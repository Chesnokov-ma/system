#include <string>

#include "ising.h"
#include "cairo.h"

int main() {
    std::string folder = "Temp";

    Ising::Create(5, 10, folder);

    Cairo::Create(4, 2, folder);

    return 0;
}
