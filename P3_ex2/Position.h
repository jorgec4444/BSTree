/* 
 * File:   Position.h
 * Author: JORGEC
 *
 * Created on 17 de mayo de 2020, 12:27
 */

#ifndef POSITION_H
#define POSITION_H
#include <vector>
#include <iostream>

using namespace std;

template <class K, class V>
class Position {
    public:
        // Constructor position
        Position(const K key, const V tuple) {
            pKey = key;
            pParent = nullptr;
            pLeft = nullptr;
            pRight = nullptr;
            values.push_back(tuple);
        }
        
        // Constructor còpia position
        Position(const Position<K, V>& orig) {
            pKey = orig.pKey;
            values = orig.getValues();
            
            if (orig.hasLeft()) {
                pLeft = orig.left();
            } else pLeft = nullptr;
        
            if (orig.hasRight()) {
                pRight = orig.right();
            } else pRight = nullptr;
        
            //cout << "Node copiat!" << endl;
        }
        
        // Destructor position
        virtual ~Position() {
            if (hasLeft() && hasRight()) {
                delete pLeft;
                delete pRight;
            }else if (hasLeft() && !hasRight())
                delete pLeft;
            else if (!hasLeft() && hasRight())
                delete pRight;
            //cout << "Node " << pKey << " eliminat." << endl;
        }
        
        // Retorna el depth (num ancestres)
        int depth() const {
            int depth ;
            if (isRoot())
                return 0;
            else {
                depth = pParent->depth() + 1;
            }
            return depth;
        }
        
        // Retorna l'alçada del node
        int height() const {
            if (isLeaf()) return 1;
            else {
                Position<K,V>* left = pLeft;
                Position<K,V>* right = pRight;
                int leftheight = height(pLeft);
                int rightheight = height(pRight);
                
                return 1 + max(leftheight, rightheight);
            }
        }
        
        // Mètode auxiliar per retornar l'alçada del node
        int height(Position<K,V>* p) const {
            if (p == nullptr) return 0;
            else {
                int leftheight = height(p->left());
                int rightheight = height(p->right());

                return 1 + max(leftheight, rightheight);
            }
        }

        // Retorna la key del position
        const K& getKey() const {
            return pKey;
        }
        
        // Retorna el vector values del position actual (no és const per poder
        // modificar-lo i accedir als seus valors.
        vector<V> getValues() const {
            return values;
        }
        
        // Afegir un value al vector values del position actual
        void addValue(const V& value) {
            values.push_back(value);
        } 
        
        // Comprova si dos positions són iguals
        bool operator==(const Position<K, V>& other) const {
            if (other.getKey() == pKey) {
                if (values.size() == other.getValues().size()) {
                    if (values == other.getValues()) return true;
                    else return false;
                }
                else return false;
            }
            else return false;
        }
        
        /*Setters*/
        
        // Set nou element
        void setElement(const K& data) {
            pKey = data;
        }
        
        // Set nou parent
        void setParent(Position<K, V>* parent) {
            pParent = parent;
        }
        
        // Set nou left
        void setLeft(Position<K, V>* left) {
            pLeft = left;
            pLeft->setParent(pParent);
        }
        
        // Set nou right
        void setRight(Position<K, V>* right) {
            pRight = right;
            pRight->setParent(pParent);
        }
        
        /*Consultors*/
        
        // Retorna el node pare
        Position<K, V>* parent() const {
            return pParent;
        }
        
       // Retorna el node left
        Position<K, V>* left() const {
            return pLeft;
        }
        
        // Retorna el node right
        Position<K, V>* right() const {
            return pRight;
        }
        
        // Retorna si el node té parent 
        bool isRoot() const {
            return (pParent == nullptr);
        }
        
        // Retorna si el node no té left o right
        bool isLeaf() const {
            return ((!hasRight()) && (!hasLeft()));
        }
        
        // Retorna si el node té pare
        bool hasParent() const {
            return (pParent != nullptr);
        }
        
        // Retorna si el node té right
        bool hasRight() const {
            return (pRight != nullptr);
        }
    
        // Retorna si el node té left
        bool hasLeft() const {
            return (pLeft != nullptr);
        }
    
    private:
        K pKey;
        vector<V> values;
        Position<K,V>* pParent;
        Position<K,V>* pLeft;
        Position<K,V>* pRight;
};

#endif /* POSITION_H */

