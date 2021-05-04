#ifndef _INCLINATORE_H_
    #define _INCLINATORE_H_

    #include<iostream>

    /*define di alcuni parametri tenuti costanti*/
    #define lar_cilindri = 40
    #define h_cilindri = 200
    #define l_piano = 500

    /*
    * Definizione dei parametri del componente "pistonesx":
    * @param pos_x_sx = posizione x cilindrosx;
    * @param pos_y_sx = posizione y cilindrosx;
    * @param h_pi_sx = altezza(corsa) pistone sinistro
    * @param lar_pi_sx = larghezza pistone sinistro
    * @param r_sx = raggio coppia rotoidale sinistra 
    */
    struct PSPistonesx{

        float pos_x_sx;
        float pos_y_sx;
        float h_pi_sx;
        float lar_pi_sx;
    };


    /*
    * Definizione dei parametri del componente "piano":
    * @param angolo = angolo di inclinazione del piano
    *  
    */
    struct PSPiano{
    
        float angolo;
        float raggio;
    };


    /*
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


    /*
     * Funzione che permette di creare da terminale il mio device, l'inclinatore
     * @return inclinatore risultante dall'operazione
     */
    PSInclinatore * inclinatore_crea();


    /*
     * Funzione che istanzia e inizializza il pistonesx
     */
    PSPistonesx * pistsx_init(float h_pi_sx, float lar_pi_sx, float pos_x_sx, float pos_y_sx);


    /*
     * Funzione che istanzia e inizializza il piano
     */
    PSPiano * piano_init(float angolo, float raggio); 


    /*
     * Funzione che istanzia e inizializza il pistonedx
     */
    PSPistonedx * pistdx_init(float h_pi_dx, float lar_pi_dx, float pos_x_dx, float pos_y_dx);

    
    /*
     * Di seguito il _set_ di funzioni che permettono di impostare nuovi 
     * parametri rispetto alla strutta PSInclinatore:
     * 
     * pistone_set_h: funzione che permette di impostare altezza(estensione) pistoni
     * pistone_set_lar: funzione che permette di impostare larghezza pistoni
     * pistone_set_pos_x_sx: funzione che permette di impostare posizionex cilindrosx 
     * pistone_set_posy_y_: funzione che permette di impostare posizioney dei due cilindri
     * pistone_set_pos_x_dx: funzione che permette di impostare posizionex cilindrodx 
     * pistone_set_r: funzione che permette di impostare raggi coppie rotoidali
     * pistone_set_rad: funzione che permette di impostare l'angolo di inclinazione del piano
    */
    void pistone_set_h(PSInclinatore * inclinatore, float new_param);
    void pistone_set_lar(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_x_sx(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_y(PSInclinatore * inclinatore, float new_param);
    void pistone_set_pos_x_dx(PSInclinatore * inclinatore, float new_param);
    void pistone_set_r(PSInclinatore * inclinatore, float new_param);
    void pistone_set_rad(PSInclinatore * inclinatore, float new_param);


    /*
     * Funzione che controlla che i parametri inseriti siano coerenti fisicamente,
     * quindi che i parametri inseriti siano positivi e diversi da zero.
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ che permette di modificare il parametro.
     */
    int controllo_dati(PSInclinatore * inclinatore);


    /*
     * Funzione che permette di visualizzare a schermo i dati sul device "inclinatore"
     */    
    void inclinatore_vedi_dati (PSInclinatore * inclinatore);


    /*
     * Funzione che converte l'oggetto "PSInclinatore" in una stringa di codice SVG
     * 
     * @param vedi_misure (opzionale): permette di scegliere 
     * se visualizzare o meno le dimensioni  sul disegno
     */
    std::string inclinatore_to_SVGstring(PSInclinatore * inclinatore, bool vedi_misure = false);  


    /*
     * Dato il nome del file dall'utente, la funzione realizza il file .svg
     * 
     */
    void inclinatore_to_svg (PSInclinatore * inclinatore, std::string fileName, bool vedi_misure = false);


    /*
     * Funzione che permette di implementare le misure all'interno del file svg
     * 
     */
    std::string inclinatore_to_MisureSVG (PSInclinatore * inclinatore);


    /*
     * Funzione che permette di deallocare correttamente struct e istanze
     */
    void inclinatore_cancella (PSInclinatore * inclinatore);

#endif