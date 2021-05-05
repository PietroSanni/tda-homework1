
#include "inclinatore.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;


PSInclinatore * inclinatore_init(float posxsx, float posxdx, float posy, float hsx, float larsx, float hdx, float lardx, float r, float rad){
    
    //istanza del nuovo inclinatore
    PSInclinatore * new_inclinatore = new PSInclinatore; 

    new_inclinatore -> pistonesx = pistsx_init(posxsx, posy, hsx, larsx);
    new_inclinatore -> piano = piano_init(r, rad);
    new_inclinatore -> pistonedx = pistdx_init(posxdx, hdx, lardx);
 
return new_inclinatore;
}


// Inizializzazione dei parametri del pistone sx
PSPistonesx * pistsx_init(float h_pi_sx, float lar_pi_sx, float pos_x_sx, float pos_y_sx) {

    PSPistonesx * new_pistonesx = new PSPistonesx;

    //Dimensioni e posizione del pistone sinistro
    new_pistonesx-> h_pi_sx = hsx;
    new_pistonesx-> lar_pi_sx = larsx;
    new_pistonesx-> pos_x_sx = posxsx;
    new_pistonesx-> pos_y_sx = posy;

return new_pistonesx;
}


// Inizializzazione dei parametri del piano
PSPiano * piano_init(float angolo, float raggio) { 

    PSPiano * new_piano = new PSPiano;

    //Inclinazione piano e raggio coppie rotoidali
    new_piano-> angolo = rad;
    new_piano-> raggio = r;

return new_piano;
}


// Inizializzazione dei parametri del pistone dx
PSPistonedx * pistdx_init(float h_pi_dx, float lar_pi_dx, float pos_x_dx, float pos_y_dx) {

    PSPistonedx * new_pistonedx = new PSPistonedx;

    //Dimensioni e posizione del pistone destro
    new_pistonedx-> h_pi_dx = hdx;
    new_pistonedx-> lar_pi_dx = lardx;
    new_pistonedx-> pos_x_dx =  posxdx;
    new_pistonedx-> pos_y_dx = posy;

return new_pistonedx;
}


//Funzione per inserire i parametri dell'inclinatore da console e creare il device
PSInclinatore * inclinatore_crea(){

    float posxsx, posxdx, posy, hsx, larsx, hdx, lardx, r, rad;

    cout << "Inserire posizione x del cilindro a sinistra:"; cin >> posxsx;
    cout << "Inserire posizione x del cilindro a destra:";   cin >> posxdx;
    cout << "Inserire posizione y dei due pistoni";          cin >> posy;

    cout << "Inserire altezza(estensione) del pistone sinistro:";  cin >> hsx;
    cout << "Inserire larghezza del pistone sinistro:";            cin >> larsx;
   
    cout << "Inserire altezza(estensione) del pistone destro:";    cin >> hdx;
    cout << "Inserire larghezza del pistone destro:";              cin >> lardx;

    cout << "Inserire raggio delle due coppie rotoidali";    cin >> r;
    cout << "Inserire inclinazione(angolo) del piano";       cin >> rad;

    return inclinatore_init;
}

//Funzione che permette di impostare altezza(estensione) pistoni
void pistone_set_h(PSInclinatore * inclinatore, float new_param);{ 
    mylivella-> pistonesx-> h_pi_sx = new_param;
    mylivella-> pistonedx-> h_pi_dx = new_param;
}





























