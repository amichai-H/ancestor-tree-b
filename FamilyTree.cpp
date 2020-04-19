#include "FamilyTree.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
#define COUNT 10  
namespace family
{
    bool equals(string s1,string s2){
        return s1.compare(s2)==0;
    }
    void Node::set_name(string s){
        name = s;
    }
    Node* Node::get_by_name(string name){
        Node* returnThis1=NULL;
        Node* returnThis2=NULL;

        if (myNameIs(name))
        {
            return this;
        }
        if (father!=NULL)
        {
            returnThis1 = father->get_by_name(name);
        }
        if (mother!=NULL)
        {
            returnThis2 = mother->get_by_name(name);
        }
        if (returnThis1!=NULL)
        {
            return returnThis1;
        }
            return returnThis2;
    }Node* Node::get_by_name_son(string name,Node* son){
        Node* returnThis1=NULL;
        Node* returnThis2=NULL;

        if (myNameIs(name))
        {
            return son;
        }
        if (father!=NULL)
        {
            returnThis1 = father->get_by_name_son(name,this);
        }
        if (mother!=NULL)
        {
            returnThis2 = mother->get_by_name_son(name,this);
        }
        if (returnThis1!=NULL)
        {
            return returnThis1;
        }
            return returnThis2;
    }
    Node* Node::get_by_relation(string relation){
        Node* returnThis1=NULL;
        Node* returnThis2=NULL;

        if (equals(relation,this->relation))
        {
            return this;
        }
        if (father!=NULL)
        {
            returnThis1 = father->get_by_relation(relation);
        }
        if (mother!=NULL)
        {
            returnThis2 = mother->get_by_relation(relation);
        }
        if (returnThis1!=NULL)
        {
            return returnThis1;
        }
            return returnThis2;
        }

    string Node::get_name(){
        return name;
    }
    void Node::set_mother(string s){
        this->mother = new Node();
        this->mother->name = s;
    }
    void Node::set_father(string s){
        this->father = new Node();
        this->father->name=s;
    }
    bool Node::myNameIs(string s){
        return get_name().compare(s)==0;
    }
    Node* Node::get_mother(){
        return this->mother;
    }
    Node* Node::get_father(){
        return this->father;
    }
    void Node::print2DUtil(Node *root, int space){   //take from https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
    // Base case  
    if (root == NULL)  
        return;  
  
    // Increase distance between levels  
    space += COUNT;  
  
    // Process right child first  
    print2DUtil(root->father, space);  
  
    // Print current node after space  
    // count  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->name<<"\n";  
  
    // Process left child  
    print2DUtil(root->mother, space);  
}  



    
    bool Node::addRecorsiveF(string name, string father,string relation){
         //cout << get_name() << endl;
        if (this->myNameIs(name))
        {
            if (this->father!=NULL)
            {
                throw std::invalid_argument( "duplicate father" );            
            }
              
            this->set_father(father);
            this->father->relation = relation;
            return true;
        }
        else
        {
            if (equals(relation,"father"))
            {
                relation = "grandfather";
            }
            else if(equals(relation,"grandfather"))
            {
                relation = "great-grandfather";
            }
            else
            {
                relation = "great-"+relation;
            }
            if (this->get_father()==NULL && this->get_mother()==NULL)
            {
                return false;
            }
            else if (this->get_father() == NULL )
            {
                return this->get_mother()->addRecorsiveF(name,father,relation);
            }
            else if(this->get_mother() == NULL)
            {
            return this->get_father()->addRecorsiveF(name,father,relation);

            }else
            {
                return this->get_father()->addRecorsiveF(name,father,relation) || this->get_mother()->addRecorsiveF(name,father,relation);
            }

            }
        }
    bool Node::addRecorsiveM(string name, string mother, string relation){
        if (this->myNameIs(name))
        {
            if (this->mother!=NULL)
            {
                throw std::invalid_argument( "duplicate father" );            
            }
           
            this->set_mother(mother);
            this->mother->relation = relation;
            return true;
        }
        else
        {
            if (equals(relation,"mother"))
            {
                relation = "grandmother";
            }
            else if(equals(relation,"grandmother"))
            {
                relation = "great-grandmother";
            }
            else
            {
                relation = "great-"+relation;
            }
            if (this->get_father()==NULL && this->get_mother()==NULL)
            {
                return false;
            }
            else if (this->get_father()==NULL )
            {
                return this->get_mother()->addRecorsiveM(name,mother,relation);
            }
            else if(this->get_mother()==NULL)
            {
            return this->get_father()->addRecorsiveM(name,mother,relation);

            }else
            {
                return this->get_father()->addRecorsiveM(name,mother,relation) || this->get_mother()->addRecorsiveM(name,mother,relation);
            }

            }
    }
    Tree& Tree::addFather(string name,string father){
        if(!this->root->addRecorsiveF(name,father,"father")){
            throw std::invalid_argument( "wrong " );
        }

        return *this;
    }
    Tree& Tree::addMother(string name,string mother){
        if(!this->root->addRecorsiveM(name,mother,"mother")){
            throw std::invalid_argument( "wrong" );
        }
        return *this;
    }
    string Tree::relation(string name){
        if (equals(name,root->name))
        {
            return "me";
        }
        Node* temp = root->get_by_name(name);
         if (temp==NULL)
        {
            return "unrelated";
        }
            return temp->relation;
       
        
    }
    string Tree::find(string motherORfather){
        if(equals(motherORfather,"me")){
            return this->root->name;
        }
        Node* temp = root->get_by_relation(motherORfather);
        if (temp==NULL)
        {
            throw std::invalid_argument( "The tree cannot handle the '"+motherORfather+"' relation" );
        }
        return temp->name;
        
    }
    void Tree::display(){
        root->print2DUtil(root, 0);  
        
        return;
    }
    void Tree::remove(string name){
        if (equals(name,root->name))
        {
            throw std::invalid_argument( "remove root" );

        }
        Node* temp = root->get_by_name_son(name,root);
        if (temp==NULL)
        {
            throw std::invalid_argument( "remove nothing" );
        }
        if (temp->father!=NULL&&temp->father->myNameIs(name))
        {
            delete temp->father;
            temp->father = NULL;
        }
        if (temp->mother!=NULL&&temp->mother->myNameIs(name))
        {
            delete temp->mother;
            temp->mother = NULL;
        }
    }

    

}; // namespace family