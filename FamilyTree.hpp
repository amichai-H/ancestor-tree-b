#pragma once
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
namespace family
{
    class Node{
        public:
            string name;
            string relation = "me";
            Node *father;
            Node *mother;
            void set_name(string s);
            string get_name();
            void set_mother(string s);
            void set_father(string s);
            bool myNameIs(string s);
            Node* get_mother();
            Node* get_father();
            Node* get_by_name(string name);
            Node* get_by_name_son(string name,Node* son);
            Node* get_by_relation(string relation);
            bool addRecorsiveF(string name, string father,string relation);
            bool addRecorsiveM(string name, string mother,string relation);
            void print2DUtil(Node *root, int space);
            ~Node(){
                    if (this->father == NULL && this->mother == NULL)
                    {
                        
                    }
                    else if(this->father == NULL){
                        delete(this->mother);
                        this->mother=NULL;
                     }
                    else if (this->mother == NULL)
                    {
                       delete(father);
                       this->father=NULL;
                    }else
                    {
                        delete(mother);
                        delete(father);
                        this->mother=NULL;
                        this->father=NULL;
                    }
                    cout << "delete: "+name << endl;

            }
            
        };
    class Tree{
        public:
        Node* root = new Node();

            Tree(string s){
                root->set_name(s);
                cout<< root->get_name()<<endl;
                printf("new Tree\n");
            }
            string to_string();
            Tree& addFather(string child, string father);
            Tree& addMother(string child, string mother);
            string relation(string name);
            string find(string motherORfather);
            void display();
            void remove(string s);
            ~Tree(){
                delete(root);
            }
        
    };
    bool addRecorsiveF(string name, string father,Node &current);
    bool addRecorsiveM(string name, string mother,Node &current);
}; // namespace family
