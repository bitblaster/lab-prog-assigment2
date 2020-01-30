/**
 * BatchProcessor.h
 * Scopo: Definire la classe BatchProcessor che si occupa della produzione dei lotti
 * @author Roberto Mozzicato, 1236209
 * @version 1.0 29/01/20
 */

#ifndef INC_BATCHPROCESSOR_H
#define INC_BATCHPROCESSOR_H

#include <map>
#include <list>
#include <queue>
#include "Component.h"
#include "Model.h"
#include "Order.h"
#include "Supply.h"
#include "Stock.h"

typedef std::pair<int, std::shared_ptr<const Component>> supply_key;

/**
 * Classe che rappresenta il gestore dei lotti di produzione.
 * Fa riferimento ai componenti, ai modelli e agli ordini caricati per il processo di produzione.
 * Dato che molti oggetti, seppur piccoli, sono condivisi fra diversi contenitori, si è preferito
 * allocarlo nel free store e usare smart pointers (nello specifico shared_pointers) per ridurre l'occupazione
 * nello stack, per evitare operazioni di copia e per semplificare la gestione della memoria
 *
 * L'algoritmo di produzione è il seguente:
 *   - Viene eseguita la produzione di un lotto per ogni mese nell'intervallo [mese_primo_ordine, mese_ultimo_ordine]
 *     (ad es. se sono presenti 3 ordini con date 12/03/20, 15/06/20, 08/02/21, elabora tutti i 12 lotti mensili fra marzo 2020 e febbraio 2021)
 *   - Per ogni lotto:
 *     - si effettua la produzione degli ordini per i quali ci sono sufficienti componenti a magazzino (questi includono gli ordini non evasi
 *       in precedenza fino agli ordini del mese corrente incluso, con priorità in ordine di data)
 *     - si acquistano i componenti necessari per gli ordini che non è stato possibile evadere, previa disponibilità di cassa, inclusi
 *       i componenti richiesti (ma che non era stato possibile acquistare) da ordini non evasi nei lotti precedenti
 *   - Gli ordini contribuiscono (in positivo) alla cassa, ovvero la cassa viene incrementata istantaneamente del valore dell'ordine per ogni ordine evaso
 *   - La richiesta di forniture avviene raggruppando tutte le necessità degli ordini in coda nel mese corrente, e acquistando
 *     più componenti del necessario se il numero richiesto vicino ad una delle 2 soglie di acquisto (11 o 51 componenti). v. Component::get_suggested_quantity
 */
class BatchProcessor {
    /** Mappa dei componenti */
    std::map<int, std::shared_ptr<const Component>> component_map;
    /** Mappa dei modelli */
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

    /** Modalità verbosa */
    bool verbose;

    /**
     * Verifica se è possibile produrre, ovvero se sono rimasti ordini in attesa o in coda e se questi non sono inevadibili
     * per mancanza di cassa
     * @return true se si può effettuare la produzione, false altrimenti
     */
    bool can_produce() const;            //

    /**
     * Verifica se sono arrivate delle forniture richieste e le aggiunge a magazzino
     */
    void verify_supplies();        //controlla le componenti ordinate se sono arrivate

    /**
     * Accoda agli ordini in elaborazione gli ordini del mese corrente
     */
    void enqueue_new_orders();     //aggiunge in coda gli ordini arrivati questo mese

    /**
     * Esegue la produzione vera e propria del lotto per gli ordini evadibili
     */
    void process_batch();

    /**
     * Verifica se i componenti di un ordine sono disponibili in magazzino e, se non già fatto in un lotto precedente,
     * li richiede come fornitura o integra un'eventuale fornitura esistente per il mese corrente.
     * Chiamato col parametro processSupplies a false effettua solo il calcolo di quanto costerebbe acquistare i componenti mancanti
     *
     * @param order ordine in elaboazione
     * @param processSupplies se true effettua richieste di fornitura e blocca le disponibilità in magazzino, se false effettua solo un calcolo dei costi
     * @return il costo previsto per i componenti mancanti, -1 se tutti i componenti sono disponibili in magazzino
     */
    double process_missing_components(const std::shared_ptr<Order> order, bool processSupplies);

    /** Processa l'ordine e lo evade, aggiungendo il ricavato in cassa
     * @param order ordine da evadere
     */
    void process_order(const std::shared_ptr<Order> order);

    /**
     * Stampa lo stato corrente
     */
    void print_current_status() const;

public:
    BatchProcessor();

    /**
     * Carica le componenti effettuando il parsing del file specificato
     * @param componentsFile file da leggere
     */
    void load_components(const std::string &componentsFile);

    /**
     * Carica i modelli effettuando il parsing del file specificato
     * @param modelsFile file da leggere
     */
    void load_models(const std::string &modelsFile);

    /**
     * Carica gli ordini e la cassa iniziale effettuando il parsing del file specificato
     * @param ordersFile file da leggere
     */
    void load_orders(const std::string &ordersFile);

    /** Avvia la produzione, a condizione che componenti, modelli e ordini siano stati caricati */
    void start_production();

    void set_verbose(bool v) {
        verbose = v;
    }
};


#endif //INC_BATCHPROCESSOR_H
