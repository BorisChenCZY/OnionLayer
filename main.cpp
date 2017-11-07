#include <iostream>
#include "OnionLayer.h"

using namespace std;
int main() {
    // import from a file
    OnionLayer onionLayer = OnionLayer("./test.dat");

    // get number of layers
    cout<<"the number of layers is: \n";
    cout<<onionLayer.get_number_of_layers()<<endl;

    // get index of a layer
    int TEST_LAYER = 3;
    cout<<"the indexes of "<< TEST_LAYER << " is:\n";
    vector<int> layer= onionLayer.get_layer(TEST_LAYER);
    for (int i = 0; i < layer.size(); i++) cout<<layer[i]<<endl;

    // get corresponding point of a certain index
    int TEST_INDEX = 2;
    cout<<"the corresponding point of "<< TEST_INDEX<< " is:\n";
    float* point = onionLayer.get_point_by_index(layer[TEST_INDEX]);
    for (int i = 0; i < onionLayer.get_dim(); i++) cout<<point[i]<<' '; cout<<endl;

}