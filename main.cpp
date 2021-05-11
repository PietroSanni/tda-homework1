#include <iostream>
#include "inclinatore.h"
#include <cmath>
using namespace std;

int main() {

    PSInclinatore * myInclinatore;

    myInclinatore = inclinatore_init(50, 500, 15, 20, 45);
    
    //myInclinatore = inclinatore_input ();

    controllo_dati (myInclinatore);
    coerenza_dati (myInclinatore);
    stampa_dati (myInclinatore);

    inclinatore_to_svg (myInclinatore);

    inclinatore_destroy (myInclinatore);
    cout << "PROVA";

    return EXIT_SUCCESS;
}