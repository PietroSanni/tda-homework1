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
#include <iomanip>

using namespace std;


PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float lar_pi, float r, float rad){

    //istanza del nuovo inclinatore
    PSInclinatore * new_inclinatore = new PSInclinatore; 

    new_inclinatore -> cilindrosx = cilindro_init(posx_sx, posy_sx, H_CILINDRI, LAR_CILINDRI);
    new_inclinatore -> cilindrodx = cilindro_init(posx_sx + DISTANZA_CILINDRI, posy_sx, LAR_CILINDRI, H_CILINDRI);
    
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
PSPiano * piano_init(float rad, float lunghezza, float spessore) { 

    PSPiano * new_piano = new PSPiano;

    new_piano-> angolo = rad;
    new_piano-> spes = spessore;
    new_piano-> l = lunghezza;

    return new_piano;
}

//Funzione per inserire i parametri dell'inclinatore da console e creare il device
PSInclinatore * inclinatore_input(){

    float posx_sx, posy_sx, h_ci, lar_ci, lar_pi, r, rad, l, spes, posx_dx, posy_dx;
    
    cout << endl;
    cout << "CREA L'INCLINATORE" << endl;
    cout << "  Inserire posizione x del cilindro sx:   "; cin >> posx_sx;
    cout << "  Inserire posizione y del cilindro sx:   "; cin >> posy_sx;
    cout << "  Inserire larghezza dei pistoni sx e dx: "; cin >> lar_pi;
    cout << "  Inserire raggio delle coppie rotoidali: "; cin >> r;
    cout << "  Inserire l'angolo di inclinazione:      "; cin >> rad;

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

    while (inclinatore-> cilindrosx-> pos_x < 0 ||
            inclinatore-> cilindrosx-> pos_x > LAYOUT_WIDTH) {
        cout << "Posizione x del device esterna al layout (" << LAYOUT_WIDTH <<"), inserire nuovo dato: ";
        cin >> new_param;
        set_posizionex_cilindro(inclinatore-> cilindrosx, new_param);
    }

    while (inclinatore-> cilindrosx-> pos_y < 0 ||
            inclinatore-> cilindrosx-> pos_y > LAYOUT_HEIGHT) {
        cout << "Posizione y del device esterna al layout (" << LAYOUT_HEIGHT <<"), inserire nuovo dato: ";
        cin >> new_param;
        set_posizioney_cilindro(inclinatore-> cilindrosx, new_param);
    }

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



// Controllo della coerenza tra i parametri inseriti in ordine di priorità e calcolo
int coerenza_dati(PSInclinatore * inclinatore){

    float new_param;
    float altezza_device;
    float larghezza_device;
    float esx, edx;
      
    //Controlla che il raggio delle coppie rotoidali sia minore o uguale allo spessore del piano
    while (inclinatore-> pistonesx-> r > inclinatore-> piano -> spes) {
        cout << "ERRORE: raggio delle coppie rotoidali pari a: " << inclinatore-> pistonesx-> r
                << ", eccede lo spessore del piano (" << inclinatore-> piano -> spes << "), reinserire valore: ";
        cin >> new_param;
        set_raggi(inclinatore, new_param);
        controllo_dati(inclinatore);
    }


    //Controlla che la larghezza del pistone sia minore di quella del cilindro 
    //vale per entrambi i pistoni sx e dx
    while (inclinatore->pistonesx->lar >= inclinatore->cilindrosx->lar) {
        cout << "ERRORE: larghezza pistone " << inclinatore->pistonesx->lar 
                << ", eccede larghezza cilindro pari a: " << inclinatore->cilindrosx->lar << ", reinserire dato: ";
        cin >> new_param;

        set_larghezza_pistoni(inclinatore, new_param);
        controllo_dati(inclinatore);
    }


    //Controllo che l'angolo non sia minore, prima del calcolo delle estensioni pistoni
    controllo_dati(inclinatore);
    //calcolo estensione per pistone sx
    esx = (inclinatore->piano->l + inclinatore->pistonesx-> r + inclinatore-> pistonedx-> r) * sin(inclinatore-> piano-> angolo * M_PI / 180) 
                - inclinatore->cilindrosx->h - inclinatore-> pistonesx-> r + (inclinatore-> cilindrodx-> h / 2);
    //calcolo estensione per pistone dx
    edx = DISTANZA_CILINDRI - (inclinatore->cilindrosx->lar / 2) - inclinatore-> pistonedx-> r - 
                ((inclinatore-> piano-> l + inclinatore-> pistonesx-> r + inclinatore-> pistonedx-> r)) * cos(inclinatore-> piano-> angolo * M_PI / 180);
    
    while (esx < 0 || edx < 0
            || esx >= inclinatore->cilindrosx->h
            || edx >= inclinatore->cilindrodx->lar) {
        cout << "ERRORE: estensione pistoni non valida (sx = " << esx
             << ", dx = " << edx << "), inserire un nuovo angolo: ";
        cin >> new_param;

        set_angolo(inclinatore->piano, new_param); 
        controllo_dati(inclinatore);
        esx = (inclinatore->piano->l + inclinatore->pistonesx->r + inclinatore->pistonedx->r) * sin(inclinatore-> piano-> angolo * M_PI / 180) 
                - inclinatore->cilindrosx->h - inclinatore->pistonesx->r + (inclinatore->cilindrodx->h / 2);
        edx = DISTANZA_CILINDRI - (inclinatore->cilindrosx->lar / 2) - inclinatore->pistonedx->r - 
                ((inclinatore->piano->l + inclinatore->pistonesx->r + inclinatore->pistonedx->r)) * cos(inclinatore->piano->angolo * M_PI / 180);
    }
    set_estensione(inclinatore->pistonesx, esx);
    set_estensione(inclinatore->pistonedx, edx);


    //Controlla che il device sia contenuto nel layout in direzione y
    altezza_device = inclinatore-> pistonesx -> r * 2 +
                     inclinatore-> pistonesx -> est + 
                     inclinatore-> cilindrosx -> h;
    //Se sconfina il layout, mi chiede di rinserire pos_y
    while (inclinatore-> cilindrosx-> pos_y < altezza_device 
            || inclinatore-> cilindrosx-> pos_y > LAYOUT_HEIGHT) {

        cout << "ERRORE: device posizionato in y = " << inclinatore-> cilindrosx-> pos_y 
                << ", supera layout_height (" << LAYOUT_HEIGHT<< ") reinserire dato: ";
        cin >> new_param;

        set_posizioney_cilindro(inclinatore-> cilindrosx, new_param);
        set_posizioney_cilindro(inclinatore-> cilindrodx, new_param);
        controllo_dati(inclinatore);
    }

    //Controlla che il device sia contenuto nel layout in direzione x
    larghezza_device = inclinatore-> cilindrosx-> lar + DISTANZA_CILINDRI + inclinatore-> cilindrodx -> lar;

    //Se sconfina il layout, mi chiede di rinserire pos_x
    while (inclinatore-> cilindrosx-> pos_x + larghezza_device > LAYOUT_WIDTH) {

        cout << "ERRORE: device posizionato in x = " << inclinatore-> cilindrosx-> pos_x
                << ", supera layout_width (" << LAYOUT_WIDTH << "), reinserire dato: ";
        cin >> new_param;

        set_posizionex_cilindro(inclinatore-> cilindrosx, new_param);
        set_posizionex_cilindro(inclinatore-> cilindrodx, new_param + DISTANZA_CILINDRI);
        controllo_dati(inclinatore);
    }
}


void stampa_dati (PSInclinatore * inc){
    
    cout << endl;
    cout << "DATI DELL'INCLINATORE"<< endl;

    cout << "Cilindri: "<< endl;
    cout << "  Cilindro sx:\t\t"<< "posizionex: "<< inc-> cilindrosx-> pos_x <<  ",  posizioney: " << inc-> cilindrosx-> pos_y <<  endl;
    cout << "  Cilindro sx:\t\t"<< "larghezza:  "<< inc-> cilindrosx-> lar << ",  altezza: " << inc-> cilindrosx-> h << endl;
    cout << "  Cilindro dx:\t\t"<< "posizionex: "<< inc-> cilindrodx-> pos_x <<  ", posizioney: " << inc-> cilindrodx-> pos_y <<  endl;
    cout << "  Cilindro dx:\t\t"<< "larghezza:  "<< inc-> cilindrodx-> lar << ", altezza: " << inc-> cilindrodx-> h << endl;

    cout << "Pistoni: \t\t " << endl;
    cout << "  Pistone sx:\t\t"<< "larghezza: "<< inc-> pistonesx-> lar << ", estensione: " << inc-> pistonesx -> est << endl;
    cout << "  Pistone dx:\t\t"<< "larghezza: "<< inc-> pistonedx-> lar << ", estensione: " << inc-> pistonedx -> est << endl;
    cout << "  Coppie rotoidali:\t"<< "raggiosx:  "<< inc-> pistonesx-> r << ", raggiodx: " << inc-> pistonedx-> r << endl;
    
    cout << "Piano: \t\t " << endl;
    cout << "  Angolo inclinazione:\t" << inc-> piano -> angolo <<  endl;
    cout << "  Spessore piano:\t" << inc-> piano-> spes << endl;
    cout << "  Lunghezza piano:\t" << inc-> piano-> l << endl;

    cout << endl;
}

// Funzione di inizializzazione e implementazione del file svg
void inclinatore_to_svg (PSInclinatore * myInc){

    string fileName = "";
    char misure;

    cout << "Inserire il nome del file .svg che verrà creato: "; 
    cin >> fileName;
    cout << endl << "Visualizzare le misure dei parametri del device? (Y/N): ";
    cin >> misure;
    cout << endl;

    ofstream mySVG(fileName + ".svg");
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << LAYOUT_WIDTH << "\" height=\"" << LAYOUT_HEIGHT << "\">" << endl;
    mySVG << inclinatore_to_stringasvg (myInc);

    if (misure == 'Y') {

        mySVG << inclinatore_to_misureSVG (myInc);
    }
    
    mySVG << "</svg>";
    mySVG.close();
}


string inclinatore_to_stringasvg (PSInclinatore * inc){

    string str = "";
    float x, y;
    float ipo, alpha, gamma;

    //Cilindro di sinistra
    x = inc-> cilindrosx-> pos_x;
    y = inc-> cilindrosx-> pos_y - inc-> cilindrosx-> h;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> cilindrosx-> lar) + "\" height=\"" + to_string(inc-> cilindrosx-> h) +  "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    //Pistone di sinistra
    x = x + (inc-> cilindrosx-> lar - inc-> pistonesx-> lar) / 2;
    y = y - inc-> pistonesx-> est;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonesx-> lar) + "\" height=\"" + to_string(inc-> pistonesx-> est) +  "\" style=\"fill:rgb(255, 238, 204);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    
    // Coppia rotoidale sx
    x = x + inc-> pistonesx-> lar / 2;
    y = y - inc-> pistonesx-> r;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonesx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"#ffaa80\" /> \n";
    
    // Piano:
    ipo = sqrt(pow (inc->pistonesx->r , 2) + pow(inc->piano->spes/2, 2));
    alpha = asin(inc->pistonesx->r / ipo) * 180 / M_PI;
    gamma = 90 - alpha - inc-> piano-> angolo;

    x = x + (ipo * cos (gamma * M_PI / 180));
    y = y - (ipo * sin (gamma * M_PI / 180));
    set_piano_posx(inc->piano, x);
    set_piano_posy(inc->piano, y);

    str += "<g transform=\"rotate(" + to_string(inc-> piano-> angolo) + "," + to_string(x) + "," + to_string(y) + ")\"> \n";
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> piano -> l) + "\" height=\"" + to_string(inc-> piano -> spes) + "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    str += "</g> \n";

    //Cilindro di destra
    x = inc-> cilindrodx-> pos_x;
    y = inc-> cilindrodx-> pos_y - inc-> cilindrodx-> h;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> cilindrodx-> lar) + "\" height=\"" + to_string(inc-> cilindrodx-> h) +  "\" style=\"fill:rgb(204,0,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
   
    //Pistone di destra
    x = x - inc-> pistonedx-> est;
    y = y + (inc-> cilindrodx-> h - inc-> pistonedx-> lar) / 2;
    str += "<rect  x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc-> pistonedx-> est) + "\" height=\"" + to_string(inc-> pistonedx-> lar) +  "\" style=\"fill:rgb(255, 238, 204);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";

    // Coppia rotoidale dx
    x = x - inc-> pistonedx-> r;
    y = y + inc-> pistonedx-> lar / 2;
    str += "<circle cx=\"" + to_string(x) + "\" cy=\"" + to_string(y) + "\" r=\"" + to_string(inc-> pistonedx-> r) + "\" stroke=\"black\" stroke-width=\"3\" fill=\"#ffaa80\" /> \n";
       
    return str;
}


void set_piano_posx(PSPiano * piano, float x) {
    piano-> posx = x;
}
void set_piano_posy(PSPiano * piano, float y) {
    piano-> posy = y;
}


//Funzione per rimuovere le cifre decimali
string myValue (float f){
    stringstream ss;
    ss << fixed << setprecision(0) <<  f;
    
    return ss.str();
}


/* Funzione che sviluppa la stringa di misure 
 * i valori di x y per il piano possono essere richiamati 
 * tramite set_piano_sx e set_piano_dx
*/
string inclinatore_to_misureSVG (PSInclinatore * inc){

    string str = "";

    float x, y;
    
    //MISURA: altezza cilindro sx
    x = inc->cilindrosx->pos_x;
    y = inc->cilindrosx->pos_y - inc->cilindrosx->h;
    str += "<rect x=\"" + to_string(x - 10) + "\" y=\"" + to_string(y) + "\" width=\"0.1\" height=\"" + to_string(inc->cilindrosx->h) + "\" style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x - 32) + "\" y=\"" + to_string(y + inc->cilindrosx->h / 2) + "\" fill=\"black\">" + myValue(inc->cilindrosx->h) + "</text>\n";

    //MISURA: larghezza cilindro sx
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(inc->cilindrosx->pos_y + 10) + "\" width=\"" + to_string(inc->cilindrosx->lar) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + (inc->cilindrosx->lar)/3) + "\" y=\"" + to_string(inc->cilindrosx->pos_y + 25) + "\" fill=\"black\">" + myValue(inc->cilindrosx->lar) + "</text>";
    
    //MISURA: distanza cilindri
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(inc->cilindrosx->pos_y + 5) + "\" width=\"" + to_string(DISTANZA_CILINDRI) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + DISTANZA_CILINDRI / 2) + "\" y=\"" + to_string(inc->cilindrosx->pos_y + 20) + "\" fill=\"black\">" + myValue(DISTANZA_CILINDRI) + "</text>";
    
    //MISURA: estensione pistone sx
    y = y - inc->pistonesx->est;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"0.1\" height=\"" + to_string(inc->pistonesx->est) + "\" style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x - 20) + "\" y=\"" + to_string(y + inc->pistonesx->est / 2) + "\" fill=\"black\">" + myValue(inc->pistonesx->est) + "</text>";
 
    //MISURA: larghezza pistone sx
    x = x + (inc->cilindrosx->lar - inc->pistonesx->lar) / 2;
    y = inc->cilindrosx->pos_y - inc->cilindrosx->h;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y + 10) + "\" width=\"" + to_string(inc->pistonesx->lar) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x) + "\" y=\"" + to_string(y + 25) + "\" fill=\"black\">" + myValue(inc->pistonesx->lar) + "</text>";
    
    //MISURA: raggio coppia rotoidale sx
    x = inc->cilindrosx->pos_x + inc->cilindrosx->lar / 2;
    y = y - inc->pistonesx->est - inc->pistonesx->r * 2;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y - 10) + "\" width=\"" + to_string(inc->pistonesx->r) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + 2) + "\" y=\"" + to_string(y - 15) + "\" fill=\"black\">" + myValue(inc->pistonesx->r) + "</text>";
    
    //MISURA: larghezza cilindro dx
    x = inc->cilindrosx->pos_x + DISTANZA_CILINDRI;
    y = inc->cilindrosx->pos_y;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y + 20) + "\" width=\"" + to_string(inc->cilindrodx->lar) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + (inc->cilindrodx->lar)/2 - 10) + "\" y=\"" + to_string(y + 35) + "\" fill=\"black\">" + myValue(inc->cilindrodx->lar) + "</text>";
    
    //MISURA: estensione pistone dx
    x = x - inc->pistonedx->est;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y + 15) + "\" width=\"" + to_string(inc->pistonedx->est) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + (inc->pistonedx->est)/2 - 5) + "\" y=\"" + to_string(y + 30) + "\" fill=\"black\">" + myValue(inc->pistonedx->est) + "</text>";
    
    //MISURA: raggio coppia rotoidale dx
    x = x - inc->pistonedx->r;
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y + 10) + "\" width=\"" + to_string(inc->pistonedx->r) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0);stroke-width:1;stroke:rgb(0, 0, 0)\" /> \n";
    str += "<text x=\"" + to_string(x + 2) + "\" y=\"" + to_string(y + 25) + "\" fill=\"black\">" + myValue(inc->pistonedx->r) + "</text>";

    //MISURA: piano inclinato
    x = inc->piano->posx + 10;
    y = inc->piano->posy - 10;
    str += "<g transform=\"rotate(" + to_string(inc->piano->angolo) + "," + to_string(x) + "," + to_string(y) + ")\"> \n";
    str += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(inc->piano->l) + "\" height=\"0.1\"" + " style=\"fill:rgb(0, 0, 0));stroke-width:1;stroke:rgb(0,0,0)\" /> \n";
    str += "<text x=\"" + to_string(x + (inc->piano->l / 2)) + "\" y=\"" + to_string(y - 10) + "\" fill=\"black\">" + myValue(inc->piano->l) + "</text>\n";
    str += "</g> \n";

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