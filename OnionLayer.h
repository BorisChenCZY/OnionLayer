//
// Created by Boris Chen on 05/11/2017.
//

#ifndef ONIONLAYER_ONIONLAYER_H
#define ONIONLAYER_ONIONLAYER_H

#include <map>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdexcept>

class OnionLayer {

private:
    int dim, size;
    std::map<int, float*> records;
    std::map<int, std::vector<int>> onion_layers;
    int current_layer = 1;

    void build_onion_layers(std::map<int, float *> records);

    void build_onion_layers(std::vector<int> index);

    void create_qhull_file(std::vector<int> index);

    char* use_qhull();

    bool is_dominate(float *a, float *b);

    std::vector<int> find_dominate_points(std::vector<int> index);

    std::vector<int> parse_string_to_int_array(std::string tmp);

    void remove_from_vector(int &i, std::vector<int> &vector);

    std::vector<int> build_index(std::map<int, float *> records);

    void check_records();

    void check_dim();

    void check_size();

public:
    OnionLayer(char* filepath);
    OnionLayer(int dim, std::map<int, float*> records): dim(dim), records(records){
            this->build_onion_layers(this->records);};
    OnionLayer(float * records[], int dim, int size):size(size), dim(dim) { for (int i = 0; i < size; i++) this->records[i] = records[i];
            this->build_onion_layers(this->records);};



    std::vector<int> get_layer(int layer = 1);

    int get_number_of_layers();

    float * get_point_by_index(int index);

    int get_dim();

    std::map<int, float *> get_all_points();

    int get_size();

};


#endif //ONIONLAYER_ONIONLAYER_H
