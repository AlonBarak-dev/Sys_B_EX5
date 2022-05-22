#include "Node.hpp"
using namespace std;

namespace ariel{

    // Node::~Node(){
    //     for(Node* sub : this->_subNodes){
    //         delete sub;
    //     }
    // };

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

    int Node::get_level() const{
        return this->_level;
    }


}