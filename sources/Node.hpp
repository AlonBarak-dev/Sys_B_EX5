#pragma once
#include <vector>
#include <string>

namespace ariel{
    class Node{

        private:
            std::vector<Node*> _subNodes;
            int _num_of_sub_nodes;
            std::string _name;
            int _size;
            int _level;
        
        public:

            Node(const std::string& name, int level) : _num_of_sub_nodes(0), _name(name), _size(name.length()), _level(level) {}
            Node() :  _num_of_sub_nodes(0), _name(""), _size(0){}
            // ~Node();

            std::string& getName();
            void setName(std::string newName);
            std::vector<Node*> getSubNodes();
            void addSubNode(Node* node);
            void delSubNode(Node* node);
            int getNumOfSubNodes();
            friend std::ostream& operator<<(std::ostream& st, Node& node);
            int size();
            int get_level() const;




    };

}