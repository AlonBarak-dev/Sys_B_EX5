#include "OrgChart.hpp"
#include <iostream>

using namespace std;
using namespace ariel;

int main(){

    OrgChart organization{0};

    organization.add_root("Boaz Ben Moshe")
        .add_sub("Boaz Ben Moshe", "Elad Horev")
        .add_sub("Boaz Ben Moshe", "Amit Dvir")
        .add_sub("Elad Horev", "Yossi")
        .add_sub("Elad Horev", "Anat")
        .add_sub("Elad Horev", "Ben")
        .add_sub("Amit Dvir", "Haim")
        .add_sub("Amit Dvir", "Yuval")
        .add_sub("Yossi", "sub-Yossi");
    
    cout << organization << endl;


    return 0;
}
