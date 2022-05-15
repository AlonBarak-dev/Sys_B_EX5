#pragma once
#include "Node.hpp"

namespace ariel{

    
    class OrgChart{

        private:
            Node _root;
            int _size;
        
        public:

            OrgChart() : _size(0) {}
            // ~OrgChart();


            class Iterator{

                private:
                    Node* _ptr;
                public:
                    Iterator(Node* ptr) : _ptr(ptr){}
                    Iterator(): _ptr(NULL){}
                    // ~Iterator();
                    // Iterator& operator=(const Iterator&);
                    void operator++();
                    void operator--();
                    Node* operator*() const;
                    Node* operator->() const;
                    bool operator!=(const Iterator&) const;
            };




            OrgChart add_root(const std::string& root_name);
            OrgChart add_sub(const std::string& super, const std::string& sub);
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