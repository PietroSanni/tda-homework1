#include <iostream>
#include "inclinatore.h"

using namespace std;


int main() {

    PSInclinatore * myinclinatore;

    //input dati da console, quello seguente è un test
    myinclinatore = inclinatore_init(100,500,200,40,100,68,20,20,40,500,20,480,500);
    
    //myinclinatore = inclinatore_init(100,500,H_CILINDRI,LAR_CILINDRI,100,68,20,SPESSORE,40,L_PIANO,20,DISTANZA_CILINDRI-LAR_CILINDRI/2,500);
    //controllo dati inseriti da console e comandi set
    /* >=0
       coerenti fisicamente
    */
    stampa_dati (myinclinatore);
    //costruzione svg
    cout<<"Funziona il programma"<<endl;

}