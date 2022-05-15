#include "OrgChart.hpp"
#include <iostream>

using namespace std;


namespace ariel{

    // OrgChart::~OrgChart(){};
    // OrgChart::Iterator::~Iterator(){};
    // OrgChart::Iterator& OrgChart::Iterator::operator=(const OrgChart::Iterator& it){}
    void OrgChart::Iterator::operator++(){}
    void OrgChart::Iterator::operator--(){}
    Node* OrgChart::Iterator::operator*() const{
        return this->_ptr;
    }
    Node* OrgChart::Iterator::operator->() const{
        return this->_ptr;
    }
    bool OrgChart::Iterator::operator!=(const Iterator&) const{
        return false;
    }


    OrgChart OrgChart::add_root(const std::string& root_name){
        return *this;
    }

    OrgChart OrgChart::add_sub(const std::string& super, const std::string& sub){
        return *this;
    }

    ostream& operator<<(ostream& st, OrgChart& organization){
        return st;
    }

    OrgChart::Iterator OrgChart::begin_level_order(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::end_level_order(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::begin_reverse_order(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::reverse_order(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::begin_preorder(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::end_preorder(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::begin(){
        return Iterator{};
    }
    OrgChart::Iterator OrgChart::end(){
        return Iterator{};
    }




}