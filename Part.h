//
// Created by mozzicator on 16/01/20.
//

#ifndef INC_PART_H
#define INC_PART_H

#include <string>

class Part {
protected:
    int id;
    std::string name;

    Part() = default;
    Part(const int entity_id, const std::string &entity_name) : id {entity_id}, name {entity_name} {}
    //Part(const Part &) = default;
    //Part(Part &&) = default;

public:
    int get_id() const {
        return id;
    }

    const std::string &get_name() const {
        return name;
    }

    //Part& operator=(const Part &) = default;
};


#endif //INC_PART_H
