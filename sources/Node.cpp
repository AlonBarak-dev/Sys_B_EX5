#include "Node.hpp"
using namespace std;

namespace ariel{


    string& Node::getName(){
        return this->_name;
    }

    void Node::setName(string newName){
        this->_name = std::move(newName);
    }

    vector<Node*> Node::getSubNodes(){
        return this->_subNodes;
    }

    void Node::addSubNode(Node* node){
        this->_subNodes.push_back(node);
    }

    void Node::delSubNode(Node* node){
        
        for (size_t i = 0; i < this->_subNodes.size(); i++)
        {
            if (this->_subNodes.at(i)->getName() == node->getName())
            {
                this->_subNodes.erase(this->_subNodes.begin()+(int)i);
                break;
            }
        }
    }

    int Node::getNumOfSubNodes(){
        return this->_subNodes.size();
    }

    int Node::size(){
        return this->_name.length();
    }

    ostream& operator<<(ostream& st, Node& node){return st << node.getName();}

    Node& Node::operator=(const Node& other){
        // operator = preform a deep copy

        // in case this = other
        if (this == &other)
        {
            return *this;
        }
        // deep copy the attributes
        for(Node* sub: other._subNodes){
            this->_subNodes.push_back(sub);
        }
        this->_num_of_sub_nodes = other._num_of_sub_nodes;
        this->_name = other._name;
        this->_size = other._size;
        this->_level = other._level;   

        return *this;
    }

    Node& Node::operator=(Node&& other) noexcept{
        // operator = preform a shallow copy

        if (this != &other)
        {
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
        return *this;
        
    }

    int Node::get_level() const{
        return this->_level;
    }


}