#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include "parsers/ComponentParser.h"
#include "parsers/ModelListParser.h"
#include "parsers/OrderParser.h"
#include "parsers/ModelParser.h"

using namespace parsers;

using namespace std;

void
process_production(int month, int year, double &cashAmount, queue<Order> &orderQueue, const vector<Model> &modelMap,
                   const unordered_map<int, Component> &componentMap);

const Model& test();

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

        const Model &mm=test();
        cout << mm.get_components()[0].get_name();

        //ComponentParser cp("/home/mozzicator/sviluppo/cpp/assignments/02-approvvigionamento/test-data/components_info.dat");
        ComponentParser cp("components_info.dat");
        cp.parse();

        cout << "Components:" << endl;
        for(const pair<int, Component> &p : cp.get_parsed_components()) {
            cout << p.second << endl;
        }

        cout << "Prova Component:" << cp.get_parsed_components().at(2) << endl;

        //ModelListParser mlp("models.dat", cp.get_parsed_components());
        ModelListParser mlp("models.dat");
        mlp.parse();

        cout << "Models:" << endl;
        for (const Model &model : mlp.get_parsed_models()) {
            cout << model << endl;
        }

        OrderParser op("orders.dat");
        op.parse();

        const vector<Order> &orders = op.get_parsed_orders();

        if(orders.size() > 0) {
            cout << "Orders:" << endl;
            for (const Order &order : orders) {
                cout << order << endl;
            }

            double cashAmount = op.get_cash_amount();
            queue<Order> orderQueue {};  // coda degli ordini non ancora evasi
            tm minTime = orders.begin()->get_localtime();
            tm maxTime = orders.end()->get_localtime();
            int curMonth = minTime.tm_mon;
            int curYear = minTime.tm_year;
            int orderIndex=0;

            // Cicliamo per tutti i mesi che intercorrono dal mese/anno del primo ordine al mese/anno dell'ultimo
            while(curMonth <= maxTime.tm_mon && curYear <= maxTime.tm_year) {
                // Aggiungiamo tutti gli ordini del mese corrente
                while (orderIndex < orders.size() && orders[orderIndex].in_month(curMonth, curYear)) {
                    orderQueue.push(orders[orderIndex]);
                    ++orderIndex;
                }

                process_production(curMonth, curYear, cashAmount, orderQueue, mlp.get_parsed_models(), cp.get_parsed_components());

                // Passiamo al prossimo mese, tenendo naturalmente conto anche dell'anno
                ++curMonth;
                if(curMonth > 12) {
                    curMonth = 1;
                    ++curYear;
                }
            }
        }

    } catch (ParsingException pe) {
        cout << "Error: " << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }
    return 0;
}

void
process_production(int month, int year, double &cashAmount, queue<Order> &orderQueue, const vector<Model> &modelMap,
                   const unordered_map<int, Component> &componentMap) {

}

const Model& test() {
    ModelParser mp("05-asciugacapelli.dat");
    mp.parse();
    return mp.get_parsed_model();
}