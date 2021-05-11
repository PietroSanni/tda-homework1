#ifndef _INCLINATORE_H_
    #define _INCLINATORE_H_

    #include<iostream>


    /*define di alcuni parametri tenuti costanti*/
    #define LAR_CILINDRI  40
    #define H_CILINDRI  200
    #define L_PIANO  500
    #define SPESSORE  20
    #define DISTANZA_CILINDRI 500
    #define LAYOUT_WIDTH 800
    #define LAYOUT_HEIGHT 600
    

    /*
    * Definizione dei parametri del componente "cilindro":
    * @param pos_x = posizione x cilindro;
    * @param pos_y = posizione y cilindro;
    * @param h = altezza cilindro;
    * @param lar = larghezza cilindro;
    */
    struct PSCilindro{
 
        float pos_x;
        float pos_y;
        float h;
        float lar;
    };


    /*
    * Definizione dei parametri del componente "pistone":
    * @param est = estensione del pistone;
    * @param lar = larghezza del pistone;
    * @param r = raggio coppia rotoidale;
    */
       struct PSPistone{

        float est;
        float lar;
        float r;
    };


    /*
    * Definizione dei parametri del componente "piano":
    * @param angolo = angolo di inclinazione del piano;
    * @param spes = spessore del piano;
    * @param l = lunghezza del piano;
    * @param posx = coordinatax del piano inclinato dello spigolo in alto a sx;
    * @param posy = coordinatay del piano inclinato dello spigolo in alto a sx;
    */
    struct PSPiano{
    
        float angolo;
        float spes;
        float l;
        float posx;
        float posy;
    };


    /*
    * Definizione della struttura complessiva "PSInclinatore"
    */
    struct PSInclinatore{

        PSCilindro * cilindrosx;
        PSCilindro * cilindrodx;
        PSPistone * pistonesx;
        PSPistone * pistonedx;
        PSPiano * piano;
    };


    /*
     * Funzione di inserimento dei parametri
     */
    PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float lar_pi, float r, float rad);


    /*
     * Funzione che istanzia e inizializza i componenti "cilindro"
     */
    PSCilindro * cilindro_init(float posx, float posy, float h_ci, float lar_ci);


    /*
     * Funzione che istanzia e inizializza i componenti "pistone"
     */
    PSPistone * pistone_init(float lar_pi, float raggio);


    /*
     * Funzione che istanzia e inizializza il componente "piano"
     */
    PSPiano * piano_init(float rad, float spessore, float lunghezza); 


    /*
     * Funzione che permette di creare da terminale il mio device, l'inclinatore
     * @return inclinatore risultante dall'operazione
     */
    PSInclinatore * inclinatore_input();

 
    /*
     * Di seguito il _set_ di funzioni che permettono di impostare nuovi 
     * parametri rispetto alla struttura PSInclinatore:
     * 
     * set_larghezza_pistone: Larghezza Pistone generico
     * set_larghezza_pistoni: Modifica il valore della larghezza dei due pistoni
     * set_raggio: Raggio coppie rotoidali generico
     * set_raggi: Modifico il valore del raggio delle due coppie rotoidali
     * set_posizioney_cilindro: Modifico posizioney del cilindro
     * set_posizionex_cilindro: Modifico posizionex del cilindro
     * set_angolo: Angolo di inclinazione piano
     */
    void set_larghezza_pistone (PSPistone * pistone, float new_param);
    void set_larghezza_pistoni (PSInclinatore * inclinatore, float new_param);
    void set_raggio (PSPistone * pistone, float new_param);
    void set_raggi (PSInclinatore * inclinatore, float new_param);
    void set_posizioney_cilindro(PSCilindro * cilindro, float new_param);
    void set_posizionex_cilindro(PSCilindro * cilindro, float new_param);
    void set_angolo (PSPiano * pian, float new_param);
    void set_estensione(PSPistone * pist, float new_param);


    /*
     * Funzione che controlla che i parametri inseriti siano positivi e diversi da zero.
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ che permette di modificare il parametro.
     */
    int controllo_dati (PSInclinatore * inclinatore);


    /*
     * Funzione che controlla che i parametri inseriti siano coerenti fisicamente:
     * - larghezza pistone < larghezza cilindro
     * - controlla che il device sia contenuto nel layout in direzione y
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ che permette di modificare il parametro.
     */
    int coerenza_dati (PSInclinatore * inclinatore);


    /*
     * Funzione che permette di visualizzare a schermo i dati dei parametri
     */    
    void stampa_dati (PSInclinatore * inclinatore);


    /*
     * Dato il nome del file dall'utente, la funzione realizza la stringa svg
     */ 
    std::string inclinatore_to_stringasvg (PSInclinatore * inc);


    /*
     * Dato il nome del file dall'utente, la funzione realizza la stringa svg
     */ 
    void inclinatore_to_svg (PSInclinatore * inc);


    /*
     * Posizione x,y del vertice alto a sinistra del piano inclinato
     * calcolata all'inerno di inclinatore_to_stringasvg.
     * Necessaria, per comodità per stampare le misure del device
     */
    void set_piano_posx(PSPiano * piano, float x);
    void set_piano_posy(PSPiano * piano, float y);


    /*
     * Funzione che se chiamata, implementare all'interno del file svg
     * le misure dei componenti del device
     */
    std::string inclinatore_to_misureSVG (PSInclinatore * inc);


    /*
     * Funzione che permette di deallocare correttamente struct e istanze
     */
    void inclinatore_destroy (PSInclinatore * inclinatore);
    

#endif