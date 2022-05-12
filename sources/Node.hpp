#pragma once
#include <vector>
#include <string>

namespace ariel{
    class Node{

        private:
            std::vector<Node> _subNodes;
            int _num_of_sub_nodes;
            std::string _name;
        
        public:

            Node(std::string name) : _num_of_sub_nodes(0), _name(name) {}
            Node(){}
            ~Node() {}

            std::string getName();
            void setNmae();
            std::vector<Node> getSubNodes();
            void addSubNode(Node);
            void delSubNode(Node);
            int getNumOfSubNodes();




    };

}