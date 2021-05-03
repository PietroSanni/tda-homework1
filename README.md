# tpa-homework1
## First Homework: Incredible Machines by Pietro Sannicolò
### Pistone regolatore dell'inclinazione di un piano 
L'obiettivo del mio progetto è quello di realizzare un meccansimo meccanico composto da un pistone fisso a telaio, che tramite il variare della sua altezza, varia l'angolo di inclinazione di un piano. Quest'ultimo ha un estremo vincolato al pistone e l'altro a telaio, tramite coppie rotoidali.

Schema del meccanismo prototipo `pistone.svg`
![](pistone.svg)

**Come lavora il programma:**
1. Si inseriscono i valori delle dimensioni
2. Second item
3. Third item
    1. Indented item
    2. Indented item
4. Viene creato il file .svg con i parametri scelti 

**Parametri variabili:**
- Lunghezza del pistone a sx (mentre il valore del cilindro sx è fisso);
- Lunghezza del pistone a dx (mentre il valore del cilindro dx è fisso);
- Spessore circonferenze;
- Spessore del piano.

**Parametri fissi:**
- Lunghezza dei cilindri = 200;
- Lunghezza piano = 500.

**Vincoli dimensionali:**
- I parametri negativi (o nulli) non sono ammissibili;
- Larghezza del pistone (sx/dx) non deve essere superiore (o uguale) a quella del cilindro (valore del cilindro (sx/dx) è fissa);
- Lunghezza del pistone (sx/dx) non deve essere superiore (o uguale) a quella del cilindro (valore del cilindro (sx/dx) è fissa);
- Il raggio della circonferenza (che simula una coppia rotoidale) non deve essere maggiore del pistone sx/dx;
- Lo spessore del piano non deve essere maggiore dell'altezza dei pistoni.
