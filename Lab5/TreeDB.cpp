#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"

TreeDB::TreeDB(){
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB(){
    clear();
}

bool TreeDB::insert(DBentry* newEntry){
    TreeNode* curr;
    DBentry* from_curr;
    TreeNode* newNode = NULL;
    for (curr = root ; curr != NULL ; ){
        from_curr = curr -> getEntry();
        if (from_curr -> getName() > newEntry -> getName()){
            if ( curr -> getLeft() == NULL){
                newNode = new TreeNode(newEntry);
                curr -> setLeft(newNode);
                return true;
            }
            curr = curr -> getLeft();
        }
        else if (from_curr -> getName() < newEntry -> getName()){
            if ( curr -> getRight() == NULL){
                newNode = new TreeNode(newEntry);
                curr -> setRight(newNode);
                return true;
            }
            curr = curr -> getRight();
        }
        else
            return false;
    }
    if(root == NULL){
        newNode = new TreeNode(newEntry);
        root = newNode;
    }
    return true;
}

DBentry* TreeDB::find(string name){
    TreeNode* curr;
    DBentry* from_curr;
    probesCount = 0;
    for( curr = root ; curr != NULL ; probesCount++){
        from_curr = curr -> getEntry();
        if(from_curr -> getName() > name)
            curr = curr -> getLeft();
        else if(from_curr -> getName() < name)
            curr = curr -> getRight();
        else{
            probesCount++;
            break;
        }
    }
    if(curr == NULL){
        from_curr = NULL;
        probesCount = 0;
    }
    return from_curr;
}

bool TreeDB::remove(string name){
    TreeNode* curr;
    TreeNode* prev = NULL;
    DBentry* from_curr;
    for(curr = root ; curr != NULL ; ){
        from_curr = curr -> getEntry();
        if(from_curr -> getName() > name){
            prev = curr;
            curr = curr -> getLeft();
        }
        else if((from_curr -> getName()) < name){
            prev = curr;
            curr = curr -> getRight();
        }
        else{
            if(curr -> getLeft() == NULL && curr -> getRight() == NULL){
                if(prev != NULL){
                    if(prev -> getLeft() == curr)
                        prev -> setLeft(NULL);
                    else
                        prev -> setRight(NULL);
                }
                else
                    root = NULL;
                delete curr;
            }
            else if(curr -> getLeft() == NULL){
                if( prev != NULL){
                    if(prev -> getLeft() == curr)
                        prev -> setLeft(curr -> getRight());
                    else
                        prev -> setRight(curr -> getRight());
                }
                else
                    root = NULL;
                delete curr;
            }
            else{
                TreeNode* curr_right;
                TreeNode* aux_curr;
                TreeNode* aux_prev = NULL;
                curr_right = curr -> getRight();
                for(aux_curr = curr -> getLeft() ; aux_curr -> getRight() != NULL ; aux_curr = aux_curr -> getRight())
                    aux_prev = aux_curr;
                if(aux_prev != NULL){
                    aux_prev -> setRight( aux_curr -> getLeft());
                    aux_curr -> setLeft(aux_prev);
                }
                aux_curr -> setRight(curr_right);
                if(prev != NULL){
                    if(prev -> getLeft() == curr)
                        prev -> setLeft(aux_curr);
                    else
                        prev -> setRight(aux_curr);
                }
                else
                    root = aux_curr;
                delete curr;
            }
            return true;
        }
    }
    return false;
}

void TreeDB::clear(){
    TreeNode* _right;
    TreeNode* _left;
    TreeNode* curr;
    TreeNode* prev = NULL;
    for(curr = root ; curr != NULL ; ){
        _right = curr -> getRight();
        _left = curr -> getLeft();
        if (_right == NULL && _left == NULL){
            if(prev != NULL){
                if(prev -> getRight() == curr)
                    prev -> setRight(NULL);
                else if(prev -> getLeft() == curr)
                    prev -> setLeft(NULL);
                else
                    prev = NULL;
            }
            else
                root = NULL;
            delete curr;
            curr = root;
            prev = NULL;
        }
        else if(_left == NULL){
            if(prev != NULL ){
                if(curr == prev -> getLeft())
                    prev -> setLeft(curr -> getRight());
                else
                    prev -> setRight(curr -> getRight());
            }
            else
                root = curr -> getRight();
            delete curr;
            prev = NULL;
            curr = root;
        }
        else{
            prev = curr;
            curr = curr -> getLeft();
        }
    }
}

void TreeDB::printProbes() const {
    if(probesCount == 0)
        cout << "Error: entry does not exist\n";
    else
        cout << probesCount << endl;
}

void TreeDB::countActive() const {
    int count = 0;
    TreeNode* min;
    TreeNode* max;
    TreeNode* curr = NULL;
    min = find_min();
    if(min != NULL){        //case root = NULL
        if(min ->getEntry()->getActive() == true)
            count++;
        max = find_max();
        if(min != max){     //case just root
            while(curr != max){
                curr = find_next(min);
                if(curr ->getEntry()->getActive() == true)
                    count++;
                min = curr;
            }
        }
    }
    cout << count << endl;
}
//funciona 1 vez , depois disso sobrescreve a TreeDB.
ostream& operator<< (ostream& out,const TreeDB& rhs){
    TreeNode* min;
    TreeNode* max;
    TreeNode* curr = NULL;
    min = rhs.find_min();
    if(min != NULL){        //case root = NULL
        out << *(min ->getEntry());
        max = rhs.find_max();
        if(min != max){     //case just root
            while(curr != max){
                curr = rhs.find_next(min);
                out << *(curr ->getEntry());
                min = curr;
            }
        }
    }
    return out;
}

TreeNode* TreeDB::find_min() const{
    TreeNode* current;
    TreeNode* previous = NULL;
    for(current = root ; current != NULL ; current = current -> getLeft())
        previous = current;
    return previous;
}

TreeNode* TreeDB::find_max() const{
    TreeNode* curr;
    TreeNode* prev = NULL;
    for(curr = root ; curr != NULL ; curr = curr -> getRight())
        prev = curr;
    return prev;
}

TreeNode* TreeDB::find_next(TreeNode* min) const{
    TreeNode* curr;
    TreeNode* prev = NULL;
    DBentry* from_min;
    DBentry* from_curr;
    for(curr = root ; curr != NULL ; ){
        from_curr = curr -> getEntry();
        from_min = min -> getEntry();
        if(from_curr -> getName() > from_min -> getName()){
            prev = curr;
            curr = curr -> getLeft();
        }
        else if(from_curr -> getName() < from_min -> getName()){
            curr = curr -> getRight();
        }
        else{
            curr = curr -> getRight();
        }

    }
    if(prev == NULL){
        if(curr != NULL){
            prev = curr ->getRight();
            for(curr = prev ; curr != NULL ; curr = curr -> getLeft())
                prev = curr;
        }
    }
    return prev;
}
