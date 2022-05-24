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
            Node() :  _num_of_sub_nodes(0), _name(""), _size(0), _level(0){}
            Node(const Node& other){
                // deep copy ctor
                for(Node* sub: other._subNodes){
                    this->_subNodes.push_back(sub);
                }
                this->_num_of_sub_nodes = other._num_of_sub_nodes;
                this->_name = other._name;
                this->_size = other._size;
                this->_level = other._level;
            }
            Node(Node&& other) noexcept{
                // Move ctor
                this->_subNodes = other._subNodes;
                this->_num_of_sub_nodes = other._num_of_sub_nodes;
                this->_name = other._name;
                this->_size = other._size;
                this->_level = other._level;

                other._subNodes.clear();
                other._size = 0;
                other._level = 0;
                other._num_of_sub_nodes = 0;
                other._name.clear();
            }

            ~Node() = default;

            std::string& getName();
            void setName(std::string newName);
            std::vector<Node*> getSubNodes();
            void addSubNode(Node* node);
            void delSubNode(Node* node);
            int getNumOfSubNodes();
            friend std::ostream& operator<<(std::ostream& st, Node& node);
            Node& operator=(const Node& other);
            Node& operator=(Node&& other) noexcept;
            int size();
            int get_level() const;




    };

}