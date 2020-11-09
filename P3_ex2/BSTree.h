/* 
 * File:   BSTree.h
 * Author: JORGEC
 *
 * Created on 17 de mayo de 2020, 12:25
 */

#ifndef BSTREE_H
#define BSTREE_H
#include <vector>
#include "Position.h"
#include <iostream>

using namespace std;

template <class K, class V>
class BSTree {
    public:
        BSTree() {
            root = nullptr; // Set root a nullptr
            cout << "Arbre binari buit creat." << endl;
        }
        
        BSTree(const BSTree<K, V>& orig) {
            root = new Position<K,V>(*orig.root); // Set root al node copiat
            cout << "Arbre binari copiat." << endl; 
        }
        
        virtual ~BSTree() {
            delete root; // Trucada al destructor de root
            cout << "Arbre binari eliminat!" << endl;
        }

        bool isEmpty() const {
            return (root == nullptr); // Comprova si el node root és nullptr
        }
        
        Position<K, V>* getRoot() const {
            return root;
        }
        
        // Mètode per calcular el size del BSTree
        int size() const {
            if (root != nullptr)
                return 1 + sizeRec(root->left()) + sizeRec(root->right());
            else
                return 0;
        }
        
        // Mètode per calcular la height del BSTree
        int height() const {
            if (root == nullptr) return 0;
        
            int leftheight = height(root->left());
            int rightheight = height(root->right());

            return 1 + max(leftheight, rightheight);
        }

        
        // Insertar un element al BSTree
        virtual Position<K, V>* insert(const K& key, const V& value) {
            Position<K,V>* nt = new Position<K,V>(key,value);    
            
            if (isEmpty())
                root = nt;
            else if (contains(key)){
                nt = _search(key);
                nt->addValue(value);
            }
            else {
                Position<K,V>* temp = root;
                while (temp->hasLeft() && temp->hasRight()
                        || (temp->hasLeft() && !temp->hasRight() && key < temp->getKey())
                        || (!temp->hasLeft() && temp->hasRight() && key > temp->getKey()))
                {
                    if (key < temp->getKey())
                        temp = temp->left();
                    else
                        temp = temp->right();
                } 
                if (key < temp->getKey())
                    temp->setLeft(nt);
                else
                    temp->setRight(nt);

                nt->setParent(temp);
                nt->addValue(value);
            }
            return nt;
        }
        
        // Comprovar si el BSTree conté la key especificada
        bool contains(const K& key) const {
            Position<K,V>* temp = root;
        
            if (temp->getKey() == key) return true;

            while (temp->hasLeft() || temp->hasRight()) {
                if (temp->getKey() == key)
                    return true;
                if (key < temp->getKey()) {
                    if (!temp->hasLeft()) return false;
                    else temp = temp->left();
                }
                else {
                    if (!temp->hasRight()) return false;
                    else temp = temp->right();
                }
            }
            if (temp->getKey() == key) return true;
            return false;
        }
        
        // Retorna un vector de values de la key especificada
        vector<V> getValues(const K& key) const {
            if (!contains(key)) {
                throw out_of_range("La key de la qual volem extreure el vector no existeix.");
            } else {
                Position<K,V>* pos;
                pos = _search(key);
                return pos->getValues();
            }
        }

        // Printeja el BSTree en preordre
        void printPreOrder(const Position<K, V> *node = nullptr) const {
            cout << "Preordre = {" << root->getKey() << ",";
                
            if (root->hasLeft())
                showPreorder(root->left());

            if (root->hasRight())
                showPreorder(root->right());
            
            cout << "}" << endl;
        }
        
        // Printeja el BSTree en postordre
        void printPostOrder(const Position<K, V> *node = nullptr) const {
            cout << "Postordre = {";
            if (root != nullptr) {
                showPostorder(root->left());
                showPostorder(root->right());
                cout << root->getKey() << "}" << endl;
            }
        }
        
        // Printeja el BSTree en postordre
        void printInorder() {
            int cnt = 0;
            if (root != nullptr) {
                cout << "Inordre = { ";
                showInorder(root->left(),cnt);
                cout << root->getKey() << "," << endl;
                showInorder(root->right(),cnt);
                cout << " }" << endl;
            }
        }

        // Comprova si dos BSTree són iguals
        bool identicalTree(const BSTree<K, V>& other) const {
            if (size() != other.size())
                return false;
            else {
                return aux_identicalTree(getRoot(), other.getRoot());
            }
        }
        
        // Mètode auxiliar per comprovar si dos BSTree són iguals
        bool aux_identicalTree(Position<K,V>* a, Position<K,V>* b) const {
            if (a == nullptr && b == nullptr) return true;
            else if (a == nullptr && b != nullptr) return false;
            else if (a != nullptr && b == nullptr) return false;
            else {
                if (a->operator ==(*b) && aux_identicalTree(a->left(),b->left()) 
                    && aux_identicalTree(a->right(), b->right()))
                    return true;
                else
                    return false;
            }
        }
        
        // Mètode per trobar una key que pot estar al BSTree
        Position<K, V>* _search(const K& key) const {
            Position<K,V>* temp = root;
            
            if (temp->getKey() == key){
                return temp;
            } 
            else {
                while (temp->hasLeft() || temp->hasRight()) {
                    if (temp->getKey() == key){
                        return temp;
                    }
                    else if (key < temp->getKey()){
                        if (!temp->hasLeft()){
                            cout << "Node not found" << endl;
                            return nullptr;
                        }
                        else {
                            temp = temp->left();
                            return aux_search(temp,key);
                        }
                    }
                    else {
                        if (!temp->hasRight()){
                            cout << "Node not found" << endl;
                            return nullptr;
                        }
                        else {
                            temp = temp->right();
                            return aux_search(temp,key);
                        }
                    }
                }
            }
            if (temp->getKey() == key) return temp;
            return nullptr;
        }
        
        // Mètode auxiliar per trobar la key al BSTree
        Position<K, V>* aux_search(Position<K,V>* pos, const K& key) const {
            if (pos->getKey() == key){
                return pos;
            }
            else {
                while (pos->hasLeft() || pos->hasRight()) {
                    if (pos->getKey() == key){
                        return pos;
                    }
                    else if (key < pos->getKey()){
                        if (!pos->hasLeft()){
                            cout << "Node not found" << endl;
                            return nullptr;
                        }
                        else {
                            pos = pos->left();
                            return aux_search(pos,key);
                        }
                    }
                    else {
                        if (!pos->hasRight()){
                            cout << "Node not found" << endl;
                            return nullptr;
                        }
                        else {
                            pos = pos->right();
                            return aux_search(pos,key);
                        }
                    }
                }
            }
            if (pos->getKey() == key) return pos;
            return nullptr;
        }
        
    protected:
        Position<K, V>* root;

    private:
        int _size;
        
        // Mètode auxiliar per retornar el size
        int sizeRec(Position<K,V>* p) const {
            if (p != nullptr)
                return 1 + sizeRec(p->left()) + sizeRec(p->right());
            else return 0;
        }
        
        // Mètode auxiliar per printejar el BSTree en preordre
        void showPreorder(Position<K,V>* p) const {
            cout << p->getKey() << ",";

            if (p->hasLeft())
                showPreorder(p->left());

            if (p->hasRight())
                showPreorder(p->right());
        }

        // Mètode auxiliar per printejar el BSTree en postordre
            void showPostorder(Position<K,V>* p) const {
                if (p != nullptr) {
                    showPostorder(p->left());
                    showPostorder(p->right());
                    cout << p->getKey() << ",";
                }
        }
            
        // Mètode auxiliar per printejar el BSTree en inordre
        void showInorder(Position<K,V>* p, int &cnt) const {
            if (cnt < 40) {
                if (p != nullptr) {
                    showInorder(p->left(),cnt);
                    cout << p->getKey() << ",";
                    cnt++;
                    showInorder(p->right(),cnt);
                }
            }
            else {
                char opt;
                cout << "\nVols contiunuar mostrant l'arbre?(S/N)" << endl;
                cin >> opt;
                if (opt == 's' || opt == 'S') {
                    cnt = 0;
                    showInorder(p,cnt);
                }
                else if (opt == 'n' || opt == 'N') {
                    cout << "Sortint del Inorder..." << endl;
                    exit(0);
                }
            }
        }
            
        // Mètode auxiliar per retornar l'alçada del BSTree
        int height(Position<K,V>* p) const {
            if (p == nullptr) return 0;
            else {
                int leftheight = height(p->left());
                int rightheight = height(p->right());

                return 1 + max(leftheight, rightheight);
            }
        }
};
#endif /* BSTREE_H */

