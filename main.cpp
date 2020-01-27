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

void orderSelection(string& order);
class FileOrdersNotFound{};

int main() {

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


    try {

        string orders;
        orderSelection(orders);

        BatchProcessor bp;
        bp.load_components("components_info.dat");
        bp.load_models("models.dat");
        bp.load_orders(orders);

        set<Supply> ppp;
        Component c1(12, "pippolo", 3, 1,2,3);
        Component c2(14, "posdlo", 2, 1,2,3);
        BatchPeriod b1(2, 2020);
        BatchPeriod b2(3, 2020);
        BatchPeriod b3(4, 2020);

        ppp.insert(Supply(c1, b3, 4));
        ppp.insert(Supply(c2, b1, 5));
        ppp.insert(Supply(c1, b2, 6));

        cout << ppp.size() << endl;
        for (const Supply &s : ppp) {
            cout << s.get_component().get_id() << " - " << s.get_delivery_period().get_month() << '/' << s.get_delivery_period().get_year() << " q:" << s.get_quantity() << endl;
        }

        bp.start_production();

    } catch (ParsingException pe) {
        cout << "Error: " << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }catch (FileOrdersNotFound){
        cout<<"File order inserito non valido o non trovato,devi inserirne uno tra quelli indicati"<<endl<< "Exiting..."<< endl;
        return 1;
    }

    return 0;

}

void orderSelection(string& order){
    cout<<"Inserire il nome del file di ordine da eseguire nel formato 'orders<1/2/3/4>.dat': "<<endl;
    string oo;
    cin>>oo;
    if(oo!= "orders1.dat" && oo!="orders2.dat" && oo!="orders3.dat" && oo!="orders4.dat") {throw FileOrdersNotFound{};};
    order = oo;
    return;
};

