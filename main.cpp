#include <iostream>
#include "inclinatore.h"
#include <cmath>
using namespace std;

int main() {

    PSInclinatore * myInclinatore;

   
    //input dati da console, quello seguente è un test
    //myinclinatore = inclinatore_init(100, 450, 20, 20, 40);
    //myinclinatore = inclinatore_init(100,500,H_CILINDRI,LAR_CILINDRI,100,68,20,SPESSORE,40,L_PIANO,20,DISTANZA_CILINDRI-LAR_CILINDRI/2,500);
    
    myInclinatore = inclinatore_input ();

    //controllo dati inseriti da console e comandi set
    controllo_dati (myInclinatore);
    coerenza_dati (myInclinatore);

    stampa_dati (myInclinatore);

    //costruzione svg
    inclinatore_to_svg (myInclinatore);

    inclinatore_destroy (myInclinatore);

    return EXIT_SUCCESS;
}
