//
// Created by mozzicator on 26/01/20.
//

#ifndef INC_BATCHPROCESSOR_H
#define INC_BATCHPROCESSOR_H

#include <map>
#include <list>
#include <queue>
#include "Component.h"
#include "Model.h"
#include "Order.h"
#include "BatchPeriod.h"
#include "Fund.h"
#include "Supply.h"
#include "Warehouse.h"

class BatchProcessor {
    std::map<int, Component> component_map;
    std::map<int, Model> model_map;

    // Usiamo un vettore di ordini anziché un set per supportare il caso in cui 2 ordini abbiano lo stesso timestamp
    // Questo ci constringe però a fare il sort degli ordini dopo il caricamento (v. OrderParser::parse())
    std::vector<Order> order_list;
    Fund fund;  //per la cassa utilizzo la classe cassa
    double cash_amount;
    std::queue<Order> order_queue;  // coda degli ordini non ancora evasi
    std::vector<Order> processed_orders; //ordini evasi;

    BatchPeriod *batch_period;
    std::set<Supply> supplies;    //set delle componenti in consegna
    Warehouse warehouse;

    bool can_produce();            //controllare se è possibile produrre
    void verify_supplies();        //controlla le componenti ordinate se sono arrivate
    void enqueue_new_orders();     //aggiunge in coda gli ordini arrivati questo mese
    void process_batch();         //avanza mese
    void verify_orders();         //controlla se gli ordini in coda sono realizzabili
    void process_order();          //processa l'ordine e lo evade
    void current_status();        //stampa dopo ogni ordine lo stato
    void warehouse_status();      //stampa lo stato del magazzino;
    void add_processed_order(Order order);
public:
    BatchProcessor() : cash_amount {0}, batch_period{nullptr}, warehouse{} {}

    void load_components(const std::string &componentsFile);
    void load_models(const std::string &modelsFile);
    void load_orders(const std::string &ordersFile);

    void set_cash_amount(double cashAmount){
        fund = Fund(cashAmount);
    }

    double get_cash_amount() {
        return fund.get_cash();
    }

    void start_production();


};


#endif //INC_BATCHPROCESSOR_H
