#ifndef _INCLINATORE_H_
    #define _INCLINATORE_H_

    #include<iostream>

    /*define di alcuni parametri tenuti costanti*/
    #define LAR_CILINDRI  40
    #define H_CILINDRI  200
    #define L_PIANO  500
    #define SPESSORE  20
    #define DISTANZA_CILINDRI 480
    #define LAYOUT_WIDTH 800
    #define LAYOUT_HEIGHT 600
    
    /*
<<<<<<< HEAD
    * Definizione dei parametri del componente "pistonesx":
    * @param pos_x_sx = posizione x cilindrosx;
    * @param pos_y_sx = posizione y cilindrosx;
    * @param h_pi_sx = altezza(corsa) pistone sinistro
    * @param lar_pi_sx = larghezza pistone sinistro
    * @param r_sx = raggio coppia rotoidale sinistra 
=======
    * Definizione della struttura complessiva "PSInclinatore"
>>>>>>> test
    */
    struct PSInclinatore{

<<<<<<< HEAD
        float pos_x_sx;
        float pos_y_sx;
        float h_pi_sx;
        float lar_pi_sx;
=======
        PSCilindro * cilindrosx;
        PSCilindro * cilindrodx;
        PSPistone * pistonesx;
        PSPistone * pistonedx;
        PSPiano * piano;
>>>>>>> test
    };

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

<<<<<<< HEAD
=======
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

>>>>>>> test
    /*
    * Definizione dei parametri del componente "piano":
    * @param angolo = angolo di inclinazione del piano;
    * @param spes = spessore del piano;
    * @param l = lunghezza del piano;
    */
    struct PSPiano{
    
        float angolo;
<<<<<<< HEAD
        float raggio;
=======
        float spes;
        float l;
>>>>>>> test
    };


    /*
<<<<<<< HEAD
    * Definizione dei parametri del componente "pistonedx":
    * @param pos_x_dx = posizione x cilindrodx;
    * @param pos_y_dx = posizione y cilindrodx;
    * @param h_pi_dx = altezza(corsa) pistone destra
    * @param lar_pi_dx = larghezza pistone destra
    * @param r_dx = raggio coppia rotoidale destra 
* POSIZIONE???
    *
    */
    struct PSPistonedx{

        float pos_x_dx;
        float pos_y_dx;
        float h_pi_dx;
        float lar_pi_dx;
    };


    struct PSInclinatore{

        PSPistonesx * pistonesx;
        PSPiano * piano;
        PSPistonedx * pistonedx;
    };
=======
     * Funzione di inserimento dei parametri
     */
    PSInclinatore * inclinatore_init(float posx_sx, float posy_sx, float lar_pi, float r, float rad){
>>>>>>> test


    /*
     * Funzione che istanzia e inizializza i componenti "cilindro"
     */
    PSCilindro * cilindro_init(float posx, float posy, float h_ci, float lar_ci);


    /*
     * Funzione che istanzia e inizializza i componenti "pistone"
     */
<<<<<<< HEAD
    PSPistonesx * pistsx_init(float h_pi_sx, float lar_pi_sx, float pos_x_sx, float pos_y_sx);
=======
    PSPistone * pistone_init(float lar_pi, float raggio);
>>>>>>> test


    /*
     * Funzione che istanzia e inizializza il componente "piano"
     */
<<<<<<< HEAD
    PSPiano * piano_init(float angolo, float raggio); 

=======
    PSPiano * piano_init(float rad, float spessore, float lunghezza); 
>>>>>>> test

    /*
     * Funzione che permette di creare da terminale il mio device, l'inclinatore
     * @return inclinatore risultante dall'operazione
     */
<<<<<<< HEAD
    PSPistonedx * pistdx_init(float h_pi_dx, float lar_pi_dx, float pos_x_dx, float pos_y_dx);
=======
    PSInclinatore * inclinatore_input();
>>>>>>> test

 
    /*
     * Di seguito il _set_ di funzioni che permettono di impostare nuovi 
     * parametri rispetto alla strutta PSInclinatore:
     * 
     * pistone_set_h: funzione che permette di impostare altezza(estensione) pistoni
     * pistone_set_lar: funzione che permette di impostare larghezza pistoni
     * pistone_set_pos_x_sx: funzione che permette di impostare posizionex cilindrosx 
<<<<<<< HEAD
     * pistone_set_posy_y_: funzione che permette di impostare posizioney dei due cilindri
=======
     * pistone_set_posy_y: funzione che permette di impostare posizioney dei due cilindri
>>>>>>> test
     * pistone_set_pos_x_dx: funzione che permette di impostare posizionex cilindrodx 
     * pistone_set_r: funzione che permette di impostare raggi coppie rotoidali
     * pistone_set_rad: funzione che permette di impostare l'angolo di inclinazione del piano
    * /
    void pistone_set_h(PSInclinatore * inclinatore, float new_param);
    void pistone_set_lar(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_x_sx(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_y(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_x_dx(PSInclinatore * inclinatore, float new_param);
    void pistone_set_r(PSInclinatore * inclinatore, float new_param);
    void pistone_set_rad(PSInclinatore * inclinatore, float new_param);
*/

    /*
     * Di seguito il _set_ di funzioni che permettono di impostare nuovi 
     * parametri rispetto alla struttura PSInclinatore:
     * 
     * set_estensione_pistonesx: funzione che permette di regolare l'estensione del pistone (in funz. dell'angolo)
     *
     * 
     */
    void set_estensione_pistonesx (PSInclinatore * pistsx, float new_param);
    void set_estensione_pistonedx (PSInclinatore * pistdx, float new_param);


    /*
     * Funzione che controlla che i parametri inseriti siano coerenti fisicamente,
     * quindi che i parametri inseriti siano positivi e diversi da zero.
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ che permette di modificare il parametro.
     */
    int controllo_dati(PSInclinatore * inclinatore);


    /*
     * Funzione che controlla che i parametri inseriti siano coerenti fisicamente.
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ che permette di modificare il parametro.
     */
    int coerenza_dati(PSInclinatore * inclinatore);


    /*
     * Funzione che permette di visualizzare a schermo i dati dei parametri
     */    
    void stampa_dati (PSInclinatore * inclinatore);


    /*
     * Funzione che converte l'oggetto "PSInclinatore" in una stringa di codice SVG
     * 
     * @param vedi_misure (opzionale): permette di scegliere 
     * se visualizzare o meno le dimensioni  sul disegno
     * /
    std::string inclinatore_to_SVGstring(PSInclinatore * inclinatore, bool vedi_misure = false);  


    /*
     * Dato il nome del file dall'utente, la funzione realizza il file .svg
     * 
     * 
    void inclinatore_to_svg (PSInclinatore * inclinatore, std::string fileName, bool vedi_misure = false);


    /*
     * Funzione che permette di implementare le misure all'interno del file svg
     * 
     * /
    std::string inclinatore_to_MisureSVG (PSInclinatore * inclinatore);


    /*
     * Funzione che permette di deallocare correttamente struct e istanze
     * /
    void inclinatore_cancella (PSInclinatore * inclinatore);
    */

#endif
