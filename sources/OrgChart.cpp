#include "OrgChart.hpp"
#include <iostream>

using namespace std;


namespace ariel{

    // iterator methods
    OrgChart::Iterator& OrgChart::Iterator::operator++(){

        if (this->_traverse == 0)
        {
            // level order iterator

            this->_ptr = this->node_queue.front();       // next in the queue
            if (this->_ptr)
            {
                for(Node* sub : this->_ptr->getSubNodes()){
                    this->node_queue.push(sub);
                }
            }
            this->node_queue.pop();     // pop the first element in the queue
            return *this;
        }

        if (this->_traverse == 1)
        {
            // reverse level order iterator
            return *this;
        }

        if (this->_traverse == 2)
        {
            // pre order iterator 
            return *this;
        }
        
        return *this;
    }
    
    
    Node& OrgChart::Iterator::operator*() const{
        return *this->_ptr;
    }
    
    Node* OrgChart::Iterator::operator->() const{
        return this->_ptr;
    }
    
    bool OrgChart::Iterator::operator!=(const Iterator& it) const{
        return this->_ptr != it._ptr;
    }

    void OrgChart::Iterator::set_traverse(int travel){
        this->_traverse = travel;
    }

    // OrgChart methods --------------------------------------

    OrgChart& OrgChart::add_root(const std::string& root_name){
        // change the name of the root
        if (!this->_root)
        {
            this->_root = new Node(root_name);
        }
        else{
            this->_root->setName(root_name);
        }
        this->list_of_nodes.push_back(this->_root);
        return *this;
    }

    OrgChart& OrgChart::add_sub(const std::string& super, const std::string& sub){
        
        // a boolean variable indicating that super is part of the organization
        bool found = false;
        // loop over the members and search for super
        for (size_t i = 0; i < this->list_of_nodes.size(); i++)
        {
            if (this->list_of_nodes.at(i)->getName() == super)
            {
                // add the new sub to the super node
                Node* new_sub = new Node{sub};
                this->list_of_nodes.at(i)->addSubNode(new_sub);
                this->list_of_nodes.push_back(new_sub);
                found = true;
                break;
            }
        }
        if(!found){
            // throw error in case super is not in the otganization
            throw runtime_error("The Desired person/class isn't part of this organization!");
        }
        return *this;
    }

    ostream& operator<<(ostream& st, OrgChart& organization){

        for (size_t i = 0; i < organization.list_of_nodes.size(); i++)
        {
            st << " -- " << organization.list_of_nodes.at(i)->getName() << " " << endl;
        }
        return st;
    }

    OrgChart::Iterator OrgChart::begin_level_order(){
        
        Iterator it{this->_root, 0};
        return it;
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