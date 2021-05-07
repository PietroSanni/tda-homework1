#include <iostream>
#include "inclinatore.h"
#include <cmath>
using namespace std;

int main() {

    PSInclinatore * myinclinatore;

   
    //input dati da console, quello seguente è un test
    myinclinatore = inclinatore_init(100, 500, 20, 20, 37.5);
    //myinclinatore = inclinatore_init(100,500,H_CILINDRI,LAR_CILINDRI,100,68,20,SPESSORE,40,L_PIANO,20,DISTANZA_CILINDRI-LAR_CILINDRI/2,500);
    
    //myinclinatore = inclinatore_input ();

    //controllo dati inseriti da console e comandi set
    controllo_dati (myinclinatore);
    coerenza_dati (myinclinatore);
    
    stampa_dati (myinclinatore);

    //costruzione svg

    cout<<"Funziona il programma"<<endl;

}