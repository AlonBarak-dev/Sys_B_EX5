#pragma once
#include "Node.hpp"

namespace ariel{

    class OrgChart{

        private:
            ariel::Node _root;
            int _size;
        
        public:

            OrgChart() : _size(0) {}
            ~OrgChart() {}


            OrgChart add_root(const std::string& root_name);
            OrgChart add_sub(const std::string& super, const std::string& sub);
            friend ostream& operator<<(ostream& st, OrgChart& organization);
            


    };

}