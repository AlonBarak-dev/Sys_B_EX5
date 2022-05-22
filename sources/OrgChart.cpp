#include "OrgChart.hpp"
#include <iostream>

using namespace std;


namespace ariel{

    // iterator methods --------------------------------
    OrgChart::Iterator& OrgChart::Iterator::operator++(){

        if (this->_traverse == 0)
        {
            // level order iterator
            if (this->node_queue.empty())
            {
                this->_ptr = nullptr;
                return *this;
            }
            this->_ptr = this->node_queue.front();       // next in the queue
            if (this->_ptr != nullptr)
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

            if (this->node_stack.empty())
            {
                this->_ptr = nullptr;
                return *this;
            }
            this->_ptr = (this->node_stack.top());    // next in the stack
            this->node_stack.pop();     // remove the prev one
            return *this;   
        }
        if (this->_traverse == 2)
        {
            // pre order iterator 
            if (this->node_vector.empty())
            {
                this->_ptr = nullptr;
                return *this;
            }
            this->_ptr = this->node_vector.front();   // next node
            this->node_vector.erase(this->node_vector.begin());
            if ((this->_ptr != nullptr) && !this->_ptr->getSubNodes().empty())
            {
                int idx = 0;
                for(Node* sub : this->_ptr->getSubNodes()){
                    this->node_vector.insert(this->node_vector.begin()+idx, sub);
                    idx++;
                }
            }
            return *this;
        }
        return *this;
    }
    
    
    string OrgChart::Iterator::operator*() const{
        return this->_ptr->getName();
    }
    
    string* OrgChart::Iterator::operator->() const{
        return &(this->_ptr->getName());
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
        if (this->_root == nullptr)
        {
            this->_root = new Node(root_name, 0);
            this->list_of_nodes.push_back(this->_root);
        }
        else{
            this->_root->setName(root_name);
        }
        
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
                int level = 1 + this->list_of_nodes.at(i)->get_level();
                Node* new_sub = new Node{sub, level};
                this->list_of_nodes.at(i)->addSubNode(new_sub);
                auto idx = this->list_of_nodes.begin() + (int)i;
                this->list_of_nodes.insert(idx, new_sub);
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

        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        Iterator it{this->_root,*this ,0};
        return it;
    }
    
    OrgChart::Iterator OrgChart::end_level_order(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{*this};
    }
    
    OrgChart::Iterator OrgChart::begin_reverse_order(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{this->_root, *this, 1};
    }
    
    OrgChart::Iterator OrgChart::reverse_order(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{*this};
    }
    
    OrgChart::Iterator OrgChart::begin_preorder(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{this->_root, *this, 2};
    }
    
    OrgChart::Iterator OrgChart::end_preorder(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{*this};
    }
    
    OrgChart::Iterator OrgChart::begin(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{this->_root, *this, 0};
    }
    
    OrgChart::Iterator OrgChart::end(){
        if (this->list_of_nodes.empty())
        {
            throw runtime_error("EMPTY!");
        }
        return Iterator{*this};
    }




}