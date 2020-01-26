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

using namespace parsers;

using namespace std;

int main() {

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

        BatchProcessor bp;
        bp.load_components("components_info.dat");
        bp.load_models("models.dat");

        double cashAmount;

        // Usiamo un vettore di ordini anziché un set per supportare il caso in cui 2 ordini abbiano lo stesso timestamp
        // Questo ci constringe però ad ordinare gli ordini dopo il caricamento (v. OrderParser::parse())
        vector<Order> orders;
        OrderParser op("orders.dat", cashAmount, orders);
        op.parse();

        if(orders.size() > 0) {
            bp.set_cash_amount(cashAmount);
            cout << "Orders:" << endl;
            for (const Order &order : orders) {
                cout << order << endl;
            }

            queue<Order> orderQueue {};  // coda degli ordini non ancora evasi
            // TODO: migliorare usando una funzione membro di Order tipo get_localtime
            // solo che mi dava leak per l'uso di localtime, quindi ho lasciato stare
            time_t time = orders.begin()->get_timestamp();
            tm minTime = *localtime(&time);
            time = orders.begin()->get_timestamp();
            tm maxTime = *localtime(&time);
            BatchPeriod curPeriod(minTime.tm_mon, minTime.tm_year);
            bp.set_batch_period(curPeriod);
            int orderIndex=0;

            // Cicliamo per tutti i mesi che intercorrono dal mese/anno del primo ordine al mese/anno dell'ultimo
            while(curPeriod.get_month() <= maxTime.tm_mon && curPeriod.get_year() <= maxTime.tm_year) {
                // Aggiungiamo tutti gli ordini del mese corrente
                for (vector<Order>::iterator it = orders.begin(); it != orders.end() && (*it).in_period(curPeriod);  ++it) {
                    bp.append_order(*it);
                }

                bp.process_next_batch();

                ++curPeriod;
            }
        }
    } catch (ParsingException pe) {
        cout << "Error: " << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }
    return 0;
}
