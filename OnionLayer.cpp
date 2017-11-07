//
// Created by Boris Chen on 05/11/2017.
//

#include "OnionLayer.h"
#include <iostream>

using namespace std;
OnionLayer::OnionLayer(char *filepath) {
    // load file
    ifstream file (filepath);
    if (file.is_open()) {
        string line;
        int cnt = 0;
        while (getline(file, line))
        {
            if (cnt == 0) this->size = stoi(line);
            else if (cnt == 1) this->dim = stoi(line);
            else if (cnt > 1){
                float *record= new float[this->dim]; int j = 0;
                char* _ = new char[line.length() + 1]; strcpy(_, line.c_str());
                char* p = strtok(_, " ");
                while(p){
                    record[j] = stof(p);
                    j++;
                    p = strtok(NULL, " ");
                }
                this->records[cnt - 2] = record;
            }

            cnt++;
        }
    }
    else {
        throw std::invalid_argument("File Not Found!");
    }


    this->build_onion_layers(this->records);
}

void OnionLayer::build_onion_layers(vector<int> index) {
    if (index.size() == 0) return;

    vector<int> index_; //return index


    if (index.size() > 3) {
        this->create_qhull_file(index);
        char *s = this->use_qhull();
        index_  = this->parse_string_to_int_array(s);
        index_  = this->find_dominate_points(index);

    } else{
        index_  = index;
    }


    this->onion_layers[this->current_layer++] = index_;

    for (int i = 0; i < index_.size(); i++) this->remove_from_vector(index_[i], index);

    this->build_onion_layers(index);
}

void OnionLayer::build_onion_layers(map<int, float *> records){
    vector<int> index = this->build_index(records);
    this->build_onion_layers(index);
}


vector<int> OnionLayer::build_index(map<int, float *> records){
    vector<int> v;
    for(map<int,float*>::iterator it = records.begin(); it != records.end(); ++it) {
        v.push_back(it->first);
    }
    return v;
}

char* OnionLayer::use_qhull(){
    FILE *fp = popen("qconvex < tmp.dat Fx", "r");
    char buff[1024];
    char out[2048] = "";

    while (fgets(buff, sizeof(buff), fp) != nullptr){
        strcat(out, buff);
    }
    return out;
}

vector<int> OnionLayer::parse_string_to_int_array(string s) {
    string tmp = s;
    vector<int> out;
    while(tmp.find("\n") != string::npos){
        out.push_back(stoi(tmp.substr(0, tmp.find("\n"))));
        tmp = tmp.substr(tmp.find("\n") + 1);
    }
    return out;
}

vector<int> OnionLayer::find_dominate_points(vector<int> index){
    vector<int> current_layer = index;

    for(int i = 0; i<index.size(); i++) {
        for (int j = 0; j < index.size(); j++)
            if (i != j && this->is_dominate(this->records[index[i]], this->records[index[j]])) {
                this->remove_from_vector(index[j], current_layer);
            }
    }
    return current_layer;
}

bool OnionLayer::is_dominate(float *a, float *b){
    for (int i = 0; i < this->dim; i++){
        if(a[i] < b[i]) return false;
    }
    return true;
}


void OnionLayer::create_qhull_file(vector<int> index) {
    //create
    ofstream file;
    file.open("./tmp.dat");

    //write
    file << index.size() << endl;
    file << this->dim << endl;

    for(int i = 0; i < index.size(); i++)
    {
        for (int j = 0; j < this->dim; j++) {
            file << this->records[index[i]][j] << " ";
        }
        file << endl;
    }
    file.close();
}

vector<int> OnionLayer::get_layer(int layer){
    return this->onion_layers[layer];
}

void OnionLayer::remove_from_vector(int &i, vector<int> &vector){
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++){
        if (*it == i){
            vector.erase(it);
            return;
        }
    }
}

int OnionLayer::get_number_of_layers(){
    return this->current_layer;
}

float * OnionLayer::get_point_by_index(int index){
    return this->records[index];
}

int OnionLayer::get_dim(){
    return this->dim;
}

map<int, float*> OnionLayer::get_all_points(){
    vector<int> index = this->build_index(this->records);
    map<int, float*> return_records;
    for (int i = 0; i < index.size(); i++)
        return_records[i] = this->records[i];
    return return_records;
}

int OnionLayer::get_size(){
    return this->size;
}

void OnionLayer::check_records(){
    this->check_dim();
    this->check_records();
}

void OnionLayer::check_dim(){
    for(std::map<int, float*>::iterator it = this->records.begin(); it != this->records.end(); i++){
        float* tmp = it->second;
        for(int i = 0; i < this->dim; i++)
            if (tmp[i] < 0)
                throw std::invalid_argument("the data is broken or some value is less than 0");
    }
}

void OnionLayer::check_size(){
    if (this->size != this->records.size())
        throw std::invalid_argument("the size of records don't match");
}