#include "inclinatore.h"
#include <iostream>
#include <string.h> 
#include <string>
#include <math.h>
#include <cmath>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;


PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float lar_pi, float r, float rad){

    //istanza del nuovo inclinatore
    PSInclinatore * new_inclinatore = new PSInclinatore; 

    new_inclinatore -> cilindrosx = cilindro_init(posx_sx, posy_sx, H_CILINDRI, LAR_CILINDRI);
    new_inclinatore -> cilindrodx = cilindro_init(posx_sx + LAR_CILINDRI + DISTANZA_CILINDRI, posy_sx, LAR_CILINDRI, H_CILINDRI);
    
    new_inclinatore -> pistonesx = pistone_init(lar_pi, r);
    new_inclinatore -> pistonedx = pistone_init(lar_pi, r);

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
PSPistone * pistone_init(float lar_pi, float raggio) {

    PSPistone * new_pistone = new PSPistone;

    //Definizione Pistone (estensione del pistone inserita con _set_)  
    new_pistone-> lar = lar_pi;
    //Dimensioni raggio coppia 
    new_pistone-> r = raggio; 
    
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
    
    cout << endl << endl;
    cout << "CREA L'INCLINATORE" << endl;
    cout << "Inserire posizione x del cilindro sx:   "; cin >> posx_sx;
    cout << "Inserire posizione y del cilindro sx:   "; cin >> posy_sx;
    cout << "Inserire larghezza dei pistoni sx e dx: "; cin >> lar_pi;
    cout << "Inserire raggio delle coppie rotoidali: "; cin >> r;
    cout << "Inserire l'angolo di inclinazione:      "; cin >> rad;

    cout << endl;

    return inclinatore_init(posx_sx, posy_sx, lar_pi, r, rad);
}



/*
* SET di funzioni che permettono di impostare nuovi parametri:
*/
//Larghezza Pistone generico 
void set_larghezza_pistone (PSPistone * pistone, float new_param){

    pistone-> lar = new_param;
    }

//Modifico il valore della larghezza dei due pistoni
void set_larghezza_pistoni (PSInclinatore * inclinatore, float new_param){

        set_larghezza_pistone (inclinatore-> pistonesx, new_param);
        set_larghezza_pistone (inclinatore-> pistonedx, new_param);
} 

//Raggio coppie rotoidali generico
void set_raggio (PSPistone * pistone, float new_param){
    pistone-> r = new_param;
}

//Modifico il valore del raggio delle due coppie rotoidali
void set_raggi (PSInclinatore * inclinatore, float new_param){

        set_raggio (inclinatore-> pistonesx, new_param);
        set_raggio (inclinatore-> pistonedx, new_param);
}

//Modifico il valore dell'estensione del pistone
void set_estensione(PSPistone * pist, float new_param){
    pist -> est = new_param;
} 

//Modifico posizioney del cilindro
void set_posizioney_cilindro(PSCilindro * cilindro, float new_param){
    cilindro-> pos_y = new_param;
}

//Modifico posizionex del cilindro
void set_posizionex_cilindro(PSCilindro * cilindro, float new_param){
    cilindro-> pos_x = new_param;
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

    float esx, edx;
    //calcolo estensione per pistone sx
    esx = L_PIANO * sin(inclinatore-> piano-> angolo) - H_CILINDRI - inclinatore-> pistonesx-> r;
    //calcolo estensione per pistone dx
    edx = DISTANZA_CILINDRI - (LAR_CILINDRI / 2) - inclinatore-> pistonedx-> r - (L_PIANO * cos(inclinatore-> piano-> angolo));
    set_estensione(inclinatore-> pistonesx, esx);
    set_estensione(inclinatore-> pistonedx, edx);
}



// Controllo della coerenza tra i parametri inseriti
int coerenza_dati(PSInclinatore * inclinatore){

    float new_param;
    float altezza_device;
    float larghezza_device;

    //Controlla che la larghezza del pistone sia minore di quella del cilindro 
    //vale per entrambi i pistoni sx e dx
    while (inclinatore-> pistonesx-> lar >= inclinatore-> cilindrosx-> lar) {
        cout << "ERRORE: larghezza pistone " << inclinatore-> pistonesx-> lar 
            << " eccede larghezza cilindro pari a: " << inclinatore-> cilindrosx-> lar 
            << ", reinserire dato: ";
        cin >> new_param;

        set_larghezza_pistoni(inclinatore, new_param);
        controllo_dati(inclinatore);
    }

    //Controlla che il device sia contenuto nel layout in direzione y
    altezza_device = inclinatore-> pistonesx -> r * 2 +
                     inclinatore-> pistonesx -> est + 
                     inclinatore-> cilindrosx -> h;

    //Se sconfina il layout, mi chiede di rinserire pos_y
    while (inclinatore-> cilindrosx-> pos_y < altezza_device 
            || inclinatore-> cilindrosx-> pos_y < LAYOUT_HEIGHT) {

        cout << "ERRORE: device posizionato in y supera layout_height, reinserire dato: ";
        cin >> new_param;

        set_posizioney_cilindro(inclinatore-> cilindrosx, new_param);
        set_posizioney_cilindro(inclinatore-> cilindrodx, new_param);
        controllo_dati(inclinatore);
    }

    //Controlla che il device sia contenuto nel layout in direzione x
    larghezza_device = DISTANZA_CILINDRI + inclinatore-> cilindrodx -> lar;

    //Se sconfina il layout, mi chiede di rinserire pos_x
    while (inclinatore-> cilindrosx-> pos_x >= larghezza_device 
            || inclinatore-> cilindrosx-> pos_x > LAYOUT_WIDTH) {

        cout << "ERRORE: device posizionato in x supera layout_width, reinserire dato: ";
        cin >> new_param;

        set_posizionex_cilindro(inclinatore-> cilindrosx, new_param);
        set_posizionex_cilindro(inclinatore-> cilindrodx, new_param + inclinatore-> cilindrosx-> lar + DISTANZA_CILINDRI);
        controllo_dati(inclinatore);
    }

    //Estensione del pistonesx non deve superare altezza cilindrosx
    while (inclinatore-> pistonesx -> est >= inclinatore-> cilindrosx-> h) {
        cout << "ERRORE: estensione pistonesx non deve eccedere altezza del cilindrosx, problema strutturale, reinserire angolo";
        cin >> new_param;

        set_angolo(inclinatore-> piano, new_param);
        controllo_dati(inclinatore);
    }

    //Estensione del pistonedx non deve superare altezza (larghezza) cilindrodx
    while (inclinatore-> pistonedx -> est >= inclinatore-> cilindrodx-> h) {
        cout << "ERRORE: Estensione pistonedx non deve eccedere larghezza del cilindrodx, problema strutturale, reinserire angolo: ";
        cin >> new_param;

        set_angolo(inclinatore-> piano, new_param);
        controllo_dati(inclinatore);
    }
    
    //Controlla che il raggio delle coppie rotoidali sia minore o uguale allo spessore del piano
    while (inclinatore-> pistonesx-> r > inclinatore-> piano -> spes) {
        cout << "ERRORE: raggio delle coppie rotoidali eccede lo spessore del piano, reinserire un altro valore: ";
        cin >> new_param;
        set_raggi(inclinatore, new_param);
        controllo_dati(inclinatore);
    }
}



void stampa_dati (PSInclinatore * inc){
    
    cout << endl << endl;
    cout << "DATI DELL'INCLINATORE"<< endl;

    cout << "Cilindri: "<< endl;
    cout << "Posizione cilindro sx:  "<< "x: "<< inc-> cilindrosx-> pos_x <<  ", y: " << inc-> cilindrosx-> pos_y <<  endl;
    cout << "Cilindro sx: \t\t"<< "larghezza: "<< inc-> cilindrosx-> lar << ", altezza: " << inc-> cilindrosx-> h << endl;
    cout << "Posizione cilindro dx:  "<< "x: "<< inc-> cilindrodx-> pos_x <<  ", y: " << inc-> cilindrodx-> pos_y <<  endl;
    cout << "Cilindro dx: \t\t" << "larghezza: "<< inc-> cilindrodx-> lar << ", altezza: " << inc-> cilindrodx-> h << endl;

    cout << "Pistoni: \t\t " << endl;
    cout << "Pistone sx: \t\t"<< "larghezza: "<< inc-> pistonesx-> lar << ", estensione: " << inc-> pistonesx -> est << endl;
    cout << "Pistone dx: \t\t" << "larghezza: "<< inc-> pistonedx-> lar << ", estensione: " << inc-> pistonedx -> est << endl;
    cout << "Coppie rotoidali: \t"<< "raggiosx:  "<< inc-> pistonesx-> r << ", raggiodx: " << inc-> pistonedx-> r << endl;
    
    cout << "Piano: \t\t " << endl;
    cout << "Angolo inclinazione: \t" << inc-> piano -> angolo <<  endl;
    cout << "Spessore piano: \t" << inc-> piano-> spes << endl;
    cout << "Lunghezza piano: \t" << inc-> piano-> l << endl;

}

// Funzione di inizializzazione e implementazione del file svg
void inclinatore_to_svg (PSInclinatore * myInc){

    string fileName = "";
    cout << "Inserire il nome del file .svg che verrà creato: "; cin >> fileName;

    ofstream mySVG(fileName + ".svg");
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;
    mySVG << inclinatore_to_stringasvg (myInc);
    mySVG << "</svg>";
    mySVG.close();

}


string inclinatore_to_stringasvg (PSInclinatore * inc){

    string str = "";
    float x, y;
    float ipo, alpha, gamma;

    //Cilindro di sinistra
    str += "<rect  x=\"" + to_string(inc-> cilindrosx-> pos_x) + "\" y=\"" + to_string(inc-> cilindrosx-> pos_y - inc-> cilindrosx-> h) + "\" width=\"" + to_string(inc-> cilindrosx-> lar) + "\" height=\"" + to_string(inc-> cilindrosx-> h) +  "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    //Pistone di sinistra
    x = inc-> cilindrosx-> pos_x + (inc-> cilindrosx-> lar - inc-> pistonesx-> lar) / 2;
    y = inc-> cilindrosx-> pos_y - inc-> cilindrosx-> h - inc-> pistonesx-> est;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonesx-> lar) + "\" height=\"" + to_string(inc-> pistonesx-> est) +  "\" style=\"fill:rgb(255, 238, 204);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    // Coppia rotoidale sx
    x = x + inc-> pistonesx-> lar / 2;
    y = y - inc-> pistonesx-> r;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonesx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"ffaa80\" /> \n";
    
    // Piano:
    ipo = sqrt(inc-> pistonesx-> r * inc-> pistonesx-> r+((SPESSORE/2)*(SPESSORE/2)));
    alpha = acos(inc-> pistonesx-> r / ipo)*180/3.14;
    gamma = 90 - alpha - inc-> pistonesx-> r;
    x = x + ipo * sin (gamma);
    y = y - ipo * cos (gamma);
    str += "<g transform=\"rotate(" + to_string(inc-> piano-> angolo) + ")\"> \n";
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> piano -> l) + "\" height=\"" + to_string(inc-> piano -> spes) + "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(204,0,0)\" /> \n";
    str += "</g> \n";

    //Cilindro di destra
    str += "<rect  x=\"" + to_string(inc-> cilindrodx-> pos_x) + "\" y=\"" + to_string(inc-> cilindrodx-> pos_y - inc-> cilindrodx-> h) + "\" width=\"" + to_string(inc-> cilindrodx-> lar) + "\" height=\"" + to_string(inc-> cilindrodx-> h) +  "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    //Pistone di destra
    x = inc-> cilindrodx-> pos_x - inc-> pistonedx-> est;
    y = inc-> cilindrodx-> pos_y - inc-> pistonedx-> lar - (inc-> cilindrodx-> h - inc-> pistonedx-> lar) / 2;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonedx-> est) + "\" height=\"" + to_string(inc-> pistonedx-> lar) +  "\" style=\"fill:rgb(255, 238, 204);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";

    // Coppia rotoidale dx
    x = x - inc-> pistonedx-> r;
    y = y + inc-> pistonedx-> lar / 2;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonedx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"ffaa80\" /> \n";
       
    return str;
}




//Funzione che permette di deallocare correttamente struct e istanze
void inclinatore_destroy (PSInclinatore * inclinatore) {

    delete inclinatore-> cilindrosx;
    delete inclinatore-> cilindrodx;
    delete inclinatore-> pistonesx;
    delete inclinatore-> pistonedx;
    delete inclinatore-> piano;
}