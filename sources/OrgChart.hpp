#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>

namespace ariel{

    
    class OrgChart{

        private:
            Node* _root;
            int _size;
            std::vector<Node*> list_of_nodes;

        
        public:

            OrgChart() : _size(0) , _root(nullptr){}
            OrgChart(int size) : _size(size), _root(nullptr){}
            // deep copy ctor
            OrgChart(const OrgChart& other) : _size(other._size), _root(other._root){
                for(Node* n : other.list_of_nodes){
                    this->list_of_nodes.push_back(n);
                }
            }
            // move ctor
            OrgChart(OrgChart&& other){
                this->_root = other._root;
                this->_size = other._size;
                this->list_of_nodes = other.list_of_nodes;

                other._root = nullptr;
                other._size = 0;
                other.list_of_nodes.clear();
            }
            
            class Iterator{

                private:
                    Node* _ptr;
                    const OrgChart& _org_chart;
                    // 0 : Level order, 1 : reverse level order, 2 : preorder
                    int _traverse; 
                    std::queue<Node*> node_queue;   
                    std::stack<Node*> node_stack;     
                    std::vector<Node*> node_vector;

                public:
                    Iterator(Node* ptr, OrgChart& organization, int travers);
                    Iterator(OrgChart& org): _ptr(nullptr), _org_chart(org), _traverse(0){}
                    Iterator& operator++();
                    std::string operator*() const;
                    std::string* operator->() const;
                    bool operator!=(const Iterator&) const;
                    void set_traverse(int travel);
            };

            OrgChart& add_root(const std::string& root_name);
            OrgChart& add_sub(const std::string& super, const std::string& sub);
            friend std::ostream& operator<<(std::ostream& st, OrgChart& organization);
            OrgChart& operator=(const OrgChart& other);
            OrgChart& operator=(OrgChart&& other) noexcept;
            Iterator begin_level_order();
            Iterator end_level_order();
            Iterator begin_reverse_order();
            Iterator reverse_order();
            Iterator begin_preorder();
            Iterator end_preorder();
            Iterator begin();
            Iterator end();


    };

}