/**
 * Classe main.cpp del progetto
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */



#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "parsers/ComponentParser.h"
#include "parsers/ModelListParser.h"
#include "parsers/OrderParser.h"
#include "parsers/ModelParser.h"
#include "Order.h"
#include "BatchProcessor.h"
#include "BatchPeriod.h"
#include "Supply.h"
#include <string>

using namespace parsers;

using namespace std;


// TODO verificare inizializzazione di tutti i membri e rimuovere costruttori di default
// TODO rinominare BatchProcessor in Production
// TODO mettere namespace alle classi!
// todo aggiungere commenti throws nelle funzioni che possono lanciare eccezioni
//TODO verificare che funziona ordinamento ordini
int main(int argc, char *argv[]) {
//    shared_ptr<Component> c1 { make_shared<Component>(12, "pippolo", 3, 1,2,3)};
//    shared_ptr<Component> c2 { make_shared<Component>(14, "posdlo", 2, 1,2,3)};
//
//    map<supply_key, int> m;
//    m[supply_key(12,c1)]=2;
//    m[supply_key(3,c2)]=76;
//
//    for (auto it = m.begin(); it != m.end();  ++it) {
//        cout << it->first.first << ',' << it->first.second << ',' << it->second << endl;
//    }
//    cout << endl;
    // TODO forse in tutti gli oggetti a parte quelli che hanno caricato gli oggetti possiamo usare reference_wrapper!!!

    // TODO controllare tutti i costruttori e le funzioni messi a "default" nei vari oggetti, vedere se default è standard su tutti i compilatori
     // NON VA BENE IL MODO CON CUI HO CREATO I PARSER, CON GLI OGGETTI MEMBRI RESTITUITI PER REFERENCE!!!
     // SE ESCONO FUORI SCOPE GLI OGGETTIPRINCIPALI PERDO ANCHE QUELLI FIGLI SE LI HO UTILIZZATI ESTERNAMENTE!!!
     // VEDERE SE RESTITUIRE SENZA REFERENCE (FORSE OTTIMIZZA CON NRVO) O SE USARE SMART POINTERS
    // parsing components
    // parsing models, ordinando componenti per mesi necessari <-----------------
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


    if(argc < 2) {
        cout << "È necessario specificare il file degli ordini\nUso: produzione <file-ordine.dat>" << endl;
        return 1;
    }

    try {
        BatchProcessor bp;
        bp.load_components("components_info.dat");
        bp.load_models("models.dat");
        bp.load_orders(argv[1]);
        bp.start_production();

//        set<Supply> ppp;
//        Component c1(12, "pippolo", 3, 1,2,3);
//        Component c2(14, "posdlo", 2, 1,2,3);
//
//        cout << ppp.size() << endl;
//        for (const Supply &s : ppp) {
//            cout << s.get_component()->get_id() << " - " << s.get_delivery_period() << " q:" << s.get_quantity() << endl;
//        }

    } catch (ParsingException pe) {
        cout << "Error: " << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }

    return 0;
}

