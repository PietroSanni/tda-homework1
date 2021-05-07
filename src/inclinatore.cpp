#include "inclinatore.h"
#include <iostream>
#include <string.h> 
#include <cmath>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

using namespace std;


PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float lar_pi, float r, float rad){
    float e;

    //istanza del nuovo inclinatore
    PSInclinatore * new_inclinatore = new PSInclinatore; 

    new_inclinatore -> cilindrosx = cilindro_init(posx_sx, posy_sx, H_CILINDRI, LAR_CILINDRI);
    new_inclinatore -> cilindrodx = cilindro_init(posx_sx + LAR_CILINDRI + DISTANZA_CILINDRI, posx_sx, LAR_CILINDRI, H_CILINDRI);
    
    e = sin(rad) - H_CILINDRI - r;
    new_inclinatore -> pistonesx = pistone_init(lar_pi, r, e);
    e = DISTANZA_CILINDRI - cos(rad);
    new_inclinatore -> pistonedx = pistone_init(lar_pi, r, e);

    new_inclinatore -> piano = piano_init(rad, L_PIANO, SPESSORE);
 
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
    //NB: per il cilindro dx: h e lar sono inverite, essendo ruotato di 90gradi
return new_cilindro;
}


// Inizializzazione dei parametri dei pistoni
PSPistone * pistone_init(float lar_pi, float raggio, float pippo) {

    PSPistone * new_pistone = new PSPistone;

    //Definizione Pistone (estensione del pistone inserita con _set_)  
    new_pistone-> lar = lar_pi;
    //Dimensioni raggio coppia 
    new_pistone-> r = raggio; 
    new_pistone-> est = pippo;   
   
return new_pistone;
}


// Inizializzazione dei parametri del piano
PSPiano * piano_init(float rad, float spessore, float lunghezza) { 

    PSPiano * new_piano = new PSPiano;

    new_piano-> angolo = rad;
    new_piano-> spes = spessore;
    new_piano-> l = lunghezza;

    return new_piano;
}

//Funzione per inserire i parametri dell'inclinatore da console e creare il device
PSInclinatore * inclinatore_input(){

    float posx_sx, posy_sx, h_ci, lar_ci, lar_pi, r, rad, l, spes, posx_dx, posy_dx;
    
    cout << "Crea l'inclinatore inserendo i vari parametri richiesti:" << endl;
    cout << "Inserire posizione (x,y) del cilindro sx:"; cin >> posx_sx >> posy_sx;
    cout << "Inserire larghezza dei pistoni sx e dx:"; cin >> lar_pi;
    cout << "Inserire raggio delle coppie rotoidali:"; cin >> r;
    cout << "Inserire l'angolo di inclinazione:"; cin >> rad;

    return inclinatore_init(posx_sx, posy_sx, lar_pi, r, rad);
}



/*
* SET di funzioni che calcolano i valori dei parametri restanti:
*/
//Larghezza Pistone generico 
void set_larghezza_pistone (PSPistone * pistone, float new_param){
    pistone-> lar = new_param;
 // pistone-> pistonesx-> posx_sx = pistsx-> pistonesx-> pos_x1 + ((pistsx-> pistonesx-> larg_1 - pistsx-> pistonesx-> larg_2)/2);
 // pistsx-> pistonesx-> pos_cx = pistsx-> pistonesx-> pos_x1 + ((pistsx-> pistonesx-> larg_1 - pistsx-> pistonesx-> larg_2)/2) + (mylivella->mypiston1->larg_2)/2;
    }

//Larghezza Pistoni
void set_larghezza_pistoni (PSInclinatore * inclinatore, float new_param){
        set_larghezza_pistone (inclinatore-> pistonesx, new_param);
        set_larghezza_pistone (inclinatore-> pistonedx, new_param);
} 

//Raggio coppie rotoidali generico
void set_raggio (PSPistone * pistone, float new_param){
    pistone-> r = new_param;
}

//Modifico il valore del raggio dei due pistoni
void set_raggi (PSInclinatore * inclinatore, float new_param){
        set_raggio (inclinatore-> pistonesx, new_param);
        set_raggio (inclinatore-> pistonedx, new_param);
}

//modifico posizioney del cilindro
void set_posizioney_cilindro(PSCilindro * cilindro, float new_param){
    cilindro-> pos_y = new_param;
}

//Angolo di inclinazione piano
void set_angolo (PSPiano * pian, float new_param){
    pian-> angolo = new_param;
}



// Funzione controllo dei segni dei parametri inseriti
int controllo_dati(PSInclinatore * inclinatore){
  
    float new_param;

    while (inclinatore-> pistonesx-> lar <= 0) {
        cout << "Larghezza dei pistoni non valida, inserire un valore positivo: ";
        cin >> new_param;
        set_larghezza_pistoni(inclinatore, new_param);
    }
    while (inclinatore-> pistonesx-> r <= 0) {
        cout << "Raggio delle coppie rotoidali non valido, inserire un valore positivo: ";
        cin >> new_param;
        set_raggi(inclinatore, new_param);
    }
    while (inclinatore-> piano-> angolo <= 0) {
        cout << "Angolo di inclinazione piano non valido, inserire un valore positivo: ";
        cin >> new_param;
        set_angolo(inclinatore-> piano, new_param);  
    }
}



// Controllo della coerenza tra i parametri inseriti

int coerenza_dati(PSInclinatore * inclinatore){

    float new_param;
    float altezza_device;

    //Controlla che la larghezza del pistonesx sia minore di quella del cilindrosx
    while (inclinatore-> pistonesx-> lar < inclinatore-> cilindrosx-> lar) {
        cout << "Larghezza pistone deve essere minore della larghezza cilindro, reinserire larghezza del pistone: ";
        cin >> new_param;
        set_larghezza_pistoni(inclinatore, new_param);
        controllo_dati(inclinatore);
    }
    //Controlla che la ci stia nel piano in y
    altezza_device = inclinatore-> pistonesx -> r * 2 +
                     inclinatore-> pistonesx -> est + 
                     inclinatore-> cilindrosx -> h;

    //Se è sballato, mi chiede di rinserire pos_y, h_pi, r (h_ci no, essendo define)
    while (inclinatore-> cilindrosx-> pos_y < altezza_device 
            || inclinatore-> cilindrosx-> pos_y > LAYOUT_HEIGHT) {

        cout << "ERRORE: device posizionato in y supera layout_height, reinserire pos_y cilindro: ";
        cin >> new_param;

        set_posizioney_cilindro(inclinatore-> cilindrosx, new_param);
        controllo_dati(inclinatore);
    }

    //??//Estensione del pistonesx non deve superare altezza cilindrosx
    while (inclinatore-> pistonesx -> est < inclinatore-> cilindrosx-> h) {
        cout << "Estensione pistone deve essere minore dell'altezza del cilindro, problema strutturale";
        cin >> new_param;
        controllo_dati(inclinatore);
    }
    //??//Estensione del pistonesx non deve superare altezza cilindrodx
    while (inclinatore-> pistonedx -> est < inclinatore-> cilindrodx-> h) {
        cout << "Estensione pistone deve essere minore dell'altezza del cilindro, problema strutturale";
        cin >> new_param;
        controllo_dati(inclinatore);
    }
    /*
    //Controlla che il raggio delle coppie rotoidali non sia più grande del ??estensione o spess piano
    while (inclinatore-> pistonesx-> r <= inclinatore-> ?????piano o pist?-> alt_1) {
        cout << "Il raggio delle coppie rotoidali non deve eccedere lo spessore del piano o dell'estensione del pistone: ";
        cin >> new_param;
        set_raggi(inclinatore, new_param);
        controllo_dati(inclinatore);
    }
   
}



void stampa_dati (PSInclinatore * inclinatore){
    
    cout << "Dati dell'inclinatore da stampare: "<< endl;
    cout << "Cilindri: \t\t "<< endl;
    cout << "Posizione cilindro sx:  \t\t"<< "x: "<< inclinatore-> cilindrosx-> pos_x <<  ", y: " << inclinatore-> cilindrosx-> pos_y <<  endl;
    cout << "Cilindro sx: \t\t"<< "larghezza: "<< inclinatore-> cilindrosx-> lar << ", altezza: " << inclinatore-> cilindrosx-> h << endl;
    cout << "Cilindro dx: \t\t" << "larghezza: "<< inclinatore-> cilindrodx-> h << ", altezza: " << inclinatore-> cilindrodx-> lar << endl;

    cout << "Pistoni: \t\t " << endl;
    cout << "Pistone sx: \t\t"<< "larghezza: "<< inclinatore-> pistonesx-> lar << endl;
    cout << "Pistone dx: \t\t" << "larghezza: "<< inclinatore-> pistonedx-> lar << endl;
    cout << "Coppie rotoidali: \t\t"<< "raggiosx: "<< inclinatore-> pistonesx-> r << ", raggiodx: " << inclinatore-> pistonedx-> r << endl;
    /*
    cout << "Coordinate coppia rotoidale: \t\t" << "x: " << inclinatore->mypiston1->pos_cx <<  ", y: " << mylivella->mypiston1->pos_cy <<  endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mylivella->mypiston2->pos_x1 <<  ", y: " << mylivella->mypiston2->pos_y1 <<  endl;
    */
    cout << "Piano: \t\t " << endl;
    cout << "Angolo inclinazione: \t\t " << inclinatore-> piano -> angolo <<  endl;
    cout << "Spessore piano: \t\t " << inclinatore-> piano-> spes << endl;
    cout << "Lunghezza piano: \t\t" << inclinatore-> piano-> l << endl;
}


string inclinatore_to_svg (PSInclinatore * inc){

    string str = "";
    float x, y;
    float ipo, alpha, gamma;

    //Cilindro di sinistra
    str += "<rect  x=\"" + to_string(inc-> cilindrosx-> pos_x) + "\" y=\"" + to_string(inc-> cilindrosx-> pos_y) + "\" width=\"" + to_string(inc-> cilindrosx-> lar) + "\" height=\"" + to_string(inc-> cilindrosx-> h) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    //Pistone di sinistra
    x = inc-> cilindrosx-> pos_x + (inc-> cilindrosx-> lar - inc-> pistonesx-> lar) / 2;
    y = inc-> cilindrosx-> pos_y - inc-> cilindrosx-> h;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonesx-> lar) + "\" height=\"" + to_string(inc-> pistonesx-> est) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    // Coppia rotoidale sx
    x = x + inc-> pistonesx-> lar / 2;
    y = y - inc-> pistonesx-> est - inc-> pistonesx-> r;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonesx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";
    

    // Piano:
    ipo = sqrt(inc-> pistonesx-> r * inc-> pistonesx-> r+((SPESSORE/2)*(SPESSORE/2)));
    alpha = acos(inc-> pistonesx-> r / ipo)*180/3.14;
    gamma = 90 - alpha - inc-> pistonesx-> r;
    x = x + ipo * sin (gamma);
    y = y - ipo * cos (gamma);
    str += "<g transform=\"rotate(" + to_string(inc-> piano-> angolo) + "," + to_string(mylivella->mypiston1->pos_cx) + "," + to_string(mylivella->mypiston1->pos_cy) + ")\"> \n";
    str += "<rect  x=\"" + to_string(mylivella->myplate->pos_x) + "\" y=\"" + to_string(mylivella->myplate->pos_y) + "\" width=\"" + to_string(mylivella->myplate->lunghezza) + "\" height=\"" + to_string(mylivella->myplate->spessore) + "\" style=\"fill:rgb(0,120,0);stroke-width:3;stroke:rgb(200,200,200)\" /> \n";
    str += "</g> \n";


    //Cilindro di destra
    str += "<rect  x=\"" + to_string(inc-> cilindrodx-> pos_x) + "\" y=\"" + to_string(inc-> cilindrodx-> pos_y) + "\" width=\"" + to_string(inc-> cilindrodx-> lar) + "\" height=\"" + to_string(inc-> cilindrodx-> h) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    //Pistone di destra
    x = inc-> cilindrodx-> pos_x - inc-> pistonedx-> est;
    y = inc-> cilindrodx-> pos_y - (inc-> cilindrodx-> h - inc-> pistonedx-> lar) / 2;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonedx-> est) + "\" height=\"" + to_string(inc-> pistonedx-> lar) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";

    // Coppia rotoidale dx
    x = x - inc-> pistonedx-> r;
    y = y - inc-> pistonedx-> lar / 2;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonedx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";
    


 
    
    return str;
}




/*
//Funzione che permette di deallocare correttamente struct e istanze
void inclinatore_cancella (PSInclinatore * inclinatore) {

    delete inclinatore-> cilindrosx;
    delete inclinatore-> cilindrodx;
    delete inclinatore-> pistonesx;
    delete inclinatore-> pistonedx;
    delete inclinatore-> piano;
}
*/