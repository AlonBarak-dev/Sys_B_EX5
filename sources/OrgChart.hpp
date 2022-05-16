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

            class Iterator{

                private:
                    Node* _ptr;
                    // 0 : Level order, 1 : reverse level order, 2 : preorder
                    int _traverse; 
                    std::queue<Node*> node_queue;   
                    std::stack<Node*> node_stack;     

                public:
                    Iterator(Node* ptr, int traverse) : _ptr(ptr), _traverse(traverse){
                        
                        if(ptr){
                            
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
                                // reverse level order iterator
                            }
                            else if(traverse == 2)
                            {
                                // preorder iterator
                            }
                        }

                    }
                    Iterator(): _ptr(NULL){}
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