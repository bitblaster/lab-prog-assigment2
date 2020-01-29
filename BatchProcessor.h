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
#include "Stock.h"

typedef std::pair<int, std::shared_ptr<const Component>> supply_key;

class BatchProcessor {
    std::map<int, std::shared_ptr<const Component>> component_map;
    std::map<int, std::shared_ptr<const Model>> model_map;

    /** Lista completa degli ordini da elaborare, da cui gli ordini vengono estratti
     * per essere accodati in order_queue nel mese di competenza */
    std::list<std::shared_ptr<Order>> order_list;

    /** Coda degli ordini non ancora evasi, da cui gli ordini vengono estratti
     * per essere accodati in processed_orders quando vengono evasi */
    std::list<std::shared_ptr<Order>> order_queue;

    /** Lista degli ordini evasi */
    std::list<std::shared_ptr<Order>> processed_orders;
    double cash_amount;
    unsigned int batch_month;

    /** Mappa delle forniture di componenti richieste (e pagate) ma non ancora arrivate */
    std::map<supply_key, std::unique_ptr<Supply>> supplies;

    /** Magazzino dei componenti */
    Stock stock;

    bool can_produce() const;            //controllare se è possibile produrre
    void verify_supplies();        //controlla le componenti ordinate se sono arrivate
    void enqueue_new_orders();     //aggiunge in coda gli ordini arrivati questo mese
    void process_batch();         // esegue la produzione vera e propria del lotto per gli ordini evadibili
    double process_missing_components(const std::shared_ptr<Order> order, bool processSupplies);          // verifica quanto costano i componenti mancanti di un ordine
    void process_order(const std::shared_ptr<Order> order);          // processa l'ordine e lo evade
    void print_current_status() const;        //stampa dopo ogni ordine lo stato

public:
    BatchProcessor() : cash_amount {0}, batch_month{0}, stock{} {}

    void load_components(const std::string &componentsFile);
    void load_models(const std::string &modelsFile);
    void load_orders(const std::string &ordersFile);

    void start_production();
};


#endif //INC_BATCHPROCESSOR_H
