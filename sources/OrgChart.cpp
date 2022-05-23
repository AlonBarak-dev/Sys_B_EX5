#include "OrgChart.hpp"
#include <iostream>

using namespace std;


namespace ariel{

    // ------------------------------------------ iterator methods --------------------------------

    // ctor
    OrgChart::Iterator::Iterator(Node* ptr, OrgChart& organization ,int traverse) : _ptr(ptr), _traverse(traverse), _org_chart(organization){
                        
        if(ptr != nullptr){
            
            if (traverse == 0)
            {
                // level order iterator
                // noitce that ptr is the root of the organization
                for (Node* sub : this->_ptr->getSubNodes())
                {
                    // push the sub of the root to the queue
                    this->node_queue.push(sub);
                }
            }
            else if(traverse == 1)
            {
                // reverse level order iterato
                this->node_stack.push(nullptr);
                int curr_level = 0;
                while (this->node_stack.size() <= this->_org_chart.list_of_nodes.size())
                {
                    std::vector<Node*> level_vector;
                    for (Node* sub : this->_org_chart.list_of_nodes)
                    {
                        if (sub->get_level() == curr_level)
                        {
                            level_vector.push_back(sub);
                        }
                    }
                    std::reverse(level_vector.begin(), level_vector.end());
                    for (size_t i = 0; i < level_vector.size(); i++)
                    {
                        this->node_stack.push(level_vector.at(i));
                    }
                    curr_level++;
                }
                this->_ptr = this->node_stack.top();
                this->node_stack.pop();
            }
            else if(traverse == 2)
            {
                // preorder iterator
                for (Node* sub : this->_ptr->getSubNodes())
                {
                    this->node_vector.push_back(sub);
                }
                this->node_vector.push_back(nullptr);
            }
        }
    }

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

    // -------------------------------------OrgChart methods --------------------------------------

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

        // print the organization's layers
        stack<Node*> node_stack;
        node_stack.push(nullptr);
        int curr_level = 0;
        while (node_stack.size() <= organization.list_of_nodes.size())
        {
            std::vector<Node*> level_vector;
            for (Node* sub : organization.list_of_nodes)
            {
                if (sub->get_level() == curr_level)
                {
                    level_vector.push_back(sub);
                }
            }
            std::reverse(level_vector.begin(), level_vector.end());
            for (size_t i = 0; i < level_vector.size(); i++)
            {
                node_stack.push(level_vector.at(i));
                st << level_vector.at(i)->getName() << "       ";
            }
            st << "\n";
            curr_level++;
        }
        return st;
    }

    OrgChart& OrgChart::operator=(const OrgChart& other){
        // operator = preform deep copy

        // in case both are the same
        if (this == &other)
        {
            return *this;
        }
        // else
        this->list_of_nodes.clear();
        for(Node* n : other.list_of_nodes){
            this->list_of_nodes.push_back(n);
        }
        this->_size = other._size;
        return *this;

    }

    OrgChart& OrgChart::operator=(OrgChart&& other) noexcept{
        // operator = preform shallow copy

        if (this != &other)
        {
            this->_root = other._root;
            this->_size = other._size;
            this->list_of_nodes = other.list_of_nodes;

            other._root = nullptr;
            other._size = 0;
            other.list_of_nodes.clear();
        }
        return *this;
        
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