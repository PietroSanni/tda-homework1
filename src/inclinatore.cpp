#include "inclinatore.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float h_ci, float lar_ci, float lar_pi, float r, float rad, float l, float spes, float posx_dx, float posy_dx){
    
    //istanza del nuovo inclinatore
    PSInclinatore * new_inclinatore = new PSInclinatore; 

    new_inclinatore -> cilindrosx = cilindro_init(posx_sx, posy_sx, h_ci, lar_ci);
    new_inclinatore -> cilindrodx = cilindro_init(posx_dx, posy_dx, lar_ci, h_ci);
    new_inclinatore -> pistonesx = pistone_init(lar_pi, r);
    new_inclinatore -> pistonedx = pistone_init(lar_pi, r);
    new_inclinatore -> piano = piano_init(rad, l, spes);
 
return new_inclinatore;
}


// Inizializzazione dei parametri dei cilindri
PSCilindro * cilindro_init(float posx, float posy, float h_ci, float lar_ci) {

    PSCilindro * new_cilindro = new PSCilindro;

    //Posizione cilindro
    new_cilindro-> pos_x = posx;        
    new_cilindro-> pos_y = posy;
    //Dimensioni cilindro
    new_cilindro-> h = h_ci;    
    new_cilindro-> lar = lar_ci;
   
return new_cilindro;
}


// Inizializzazione dei parametri dei pistoni
PSPistone * pistone_init(float lar_pi, float raggio) {

    PSPistone * new_pistone = new PSPistone;

    //Definizione Pistone (estensione del pistone inserita con _set_)  
    new_pistone-> lar = lar_pi;
    //Dimensioni raggio coppia 
    new_pistone-> r = raggio;    
   
return new_pistone;
}


void set_estensione_pistonesx(PSInclinatore * pippo, float new_param){

    pippo-> pistonesx -> est = new_param;

}

// Inizializzazione dei parametri del piano
PSPiano * piano_init(float rad, float spessore, float lunghezza) { 

    PSPiano * new_piano = new PSPiano;

    new_piano-> angolo = rad;
    new_piano-> spes = spessore;
    new_piano-> l = lunghezza;

    return new_piano;
}


void stampa_dati (PSInclinatore * inclinatore){
    
    cout << "Dati dell'inclinatore da stampare: " << endl;
    cout << "Posizione cilindro sx:  \t\t" << "x: " << inclinatore-> cilindrosx-> pos_x <<  ", y: " << inclinatore-> cilindrosx-> pos_y <<  endl;
    /*
    cout << "Cilindro esterno: \t\t" << "diametro: " << mylivella->mypiston1->larg_1 << ", altezza: " << mylivella->mypiston1->alt_1 << endl;
    cout << "Cilindro Interno: \t\t" << "diametro: " << mylivella->mypiston1->larg_2 << ", altezza: " << mylivella->mypiston1->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t\t" << "x: " << mylivella->mypiston1->pos_cx <<  ", y: " << mylivella->mypiston1->pos_cy <<  endl;
    cout << "Pistone di Destra: \t\t " << endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mylivella->mypiston2->pos_x1 <<  ", y: " << mylivella->mypiston2->pos_y1 <<  endl;
    cout << "Cilindro esterno: \t\t" << "diametro: " << mylivella->mypiston2->larg_1 << ", altezza: " << mylivella->mypiston2->alt_1 << endl;
    cout << "Cilindro interno: \t\t" << "diametro: " << mylivella->mypiston2->larg_2 << ", altezza: " << mylivella->mypiston2->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t" << "x: " << mylivella->mypiston2->pos_cx <<  ", y: " << mylivella->mypiston2->pos_cy <<  endl;
    cout << "Piastra: \t\t " << endl;
    cout << "Spessore piastra: \t 30" <<  endl;
    cout << "Lunghezza piastra: \t\t 500" << endl;
    cout << "Angolo di inclinazione: \t\t" << mylivella->myplate->angle << endl;
*/
}








/*Funzione per inserire i parametri dell'inclinatore da console e creare il device
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

    return inclinatore_init(posxsx, posxdx, posy, hsx, larsx, hdx, lardx, r, rad);
}
*/

/*Funzione che permette di impostare altezza(estensione) pistoni 
void pistone_set_h(PSInclinatore * inclinatore, float new_param) { 
    inclinatore-> pistonesx-> h_pi_sx = new_param;
    inclinatore-> pistonesx-> (pos_y - h_cilindri) = new_param;

    mylivella->mypiston1->pos_y2 = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->mypiston1->pos_cy = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->myplate->pos_cyS = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->myplate->pos_y = mylivella->myplate->pos_cyS - (mylivella->myplate->spessore / 2);
    mylivella->myplate->angle = atan((mylivella->myplate->pos_cyD - mylivella->myplate->pos_cyS)/(mylivella->myplate->pos_cxD - mylivella->myplate->pos_cxS))*180/M_PI;  
}
*/









