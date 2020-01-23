#include <iostream>
#include <vector>
#include "parsers/ComponentParser.h"

using namespace parsers;
using namespace std;

int main() {
    // parsing components
    // parsing models, ordinando componenti per mesi necessari
    // parsing orders ordinati per data

    // prendere primo e ultimo mese ordini
    // produzione eseguita per ogni mese di questo intervallo

    // operazioni preliminari:
        //aggiunta in magazzino di componenti acquistati e arrivati in questo mese
        //aggiunta alla coda ordini di questo mese

    // avvio produzione mese, per ogni ordine:
        // verifica componenti con quantità (funzione check_component(quantity) in storage)
            // se ok:
                // togliamo componenti da storage
                // aggiungiamo soldi in cassa
                // marchiamo ordine come processato
                // togliamo ordine dalla coda
                // stampare stato
            // se non ok:
                // ordinare componenti mancanti con numero mesi maggiore se ci sono i soldi
                // (la classe che gestisce l'acquisto eventualmente aggiunge a un acquisto dello stesso componente nello mese la nuova quantità
    try {
        //ComponentParser cp("/home/mozzicator/sviluppo/cpp/assignments/02-approvvigionamento/test-data/components_info.dat");
        ComponentParser cp("components_info.dat");
        cp.parse();

        cout << "Components:" << endl;
        for (const Component &comp : cp.get_parsed_components()) {
            cout << comp << endl;
        }
        cout << "Hello, World!" << endl;
    } catch (ParsingException pe) {
        cout << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }
    return 0;
}
