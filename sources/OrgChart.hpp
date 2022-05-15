#pragma once
#include "Node.hpp"

namespace ariel{

    
    class OrgChart{

        private:
            Node _root;
            int _size;
            std::vector<Node> list_of_nodes;

        
        public:

            OrgChart() : _size(0) {}

            class Iterator{

                private:
                    Node* _ptr;
                    // 0 : Level order, 1 : reverse level order, 2 : preorder
                    int _traverse; 

                public:
                    Iterator(Node* ptr) : _ptr(ptr), _traverse(0){}
                    Iterator(): _ptr(NULL){}
                    void operator++();
                    void operator--();
                    Node* operator*() const;
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