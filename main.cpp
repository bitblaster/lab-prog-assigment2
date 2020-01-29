/**
 * Classe main.cpp del progetto
 *
 * @author Giacomo Vettoretti, 1187540
 * @version 1.0 29/01/20
 */


#include <iostream>
#include "parsers/ComponentParser.h"
#include "BatchProcessor.h"
using namespace parsers;

using namespace std;


// TODO mettere namespace alle classi!
int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "È necessario specificare il file degli ordini\nUso: produzione <file-ordine.dat>" << endl;
        return 1;
    }

    string ordersFile {argv[1]};

    string option;
    if(argc > 2)
        option = argv[2];

    try {
        BatchProcessor bp;
        if (option == "-v")
            bp.set_verbose(true);
        bp.load_components("components_info.dat");
        bp.load_models("models.dat");
        bp.load_orders(argv[1]);
        bp.start_production();
    } catch (ParsingException pe) {
        cout << "Error: " << pe.what() << endl << "Exiting..." << endl;
        return 1;
    }

    return 0;
}

