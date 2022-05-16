#pragma once
#include "Node.hpp"
#include <stack>
#include <queue>
#include <algorithm>

namespace ariel{

    
    class OrgChart{

        private:
            Node* _root;
            int _size;
            std::vector<Node*> list_of_nodes;

        
        public:

            OrgChart() : _size(0) , _root(nullptr){}
            OrgChart(int size) : _size(size), _root(nullptr){}

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
                    Iterator(Node* ptr, OrgChart& organization ,int traverse) : _ptr(ptr), _traverse(traverse), _org_chart(organization){
                        
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
                                // iterate over the elements in a level order and push into a stack
                                // this will give us the reverse implementation
                                for (auto i = organization.begin_level_order(); i != organization.end_level_order(); ++i)
                                {
                                    this->node_stack.push(&(*i));
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

                    Iterator(OrgChart& org): _ptr(nullptr), _org_chart(org), _traverse(0){}
                    Iterator& operator++();
                    Node& operator*() const;
                    Node* operator->() const;
                    bool operator!=(const Iterator&) const;
                    void set_traverse(int travel);
            };

            OrgChart& add_root(const std::string& root_name);
            OrgChart& add_sub(const std::string& super, const std::string& sub);
            friend std::ostream& operator<<(std::ostream& st, OrgChart& organization);
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