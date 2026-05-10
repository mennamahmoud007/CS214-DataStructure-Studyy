#include <iostream>
#include <cassert>
using namespace std;

template <class T>
struct Node
{
    T value;              
    Node<T>* next;   // pointer على النود اللي بعدها
};
template <class T>
class llIterator
{
    private:
    Node<T> *current; //pointer to point to the current node 
    public:
    llIterator(){
        current = NULL;
    }
    llIterator(Node<T> *ptr){
        current = ptr;
    }
    T operator*(){
        assert(current != NULL); //iterator should not point to NULL
        return current->value;
    }
    
    llIterator<T> operator++(){
        assert(current != NULL); //iterator should not point to NULL
        current = current->next; 
        return *this;
    }
   
    bool operator==(const llIterator<T>& right) const{
        return (current == right.current);
    }
    bool operator!=(const llIterator<T>& right) const{
        return (current != right.current);
    }
};
template <class T>
class linkedList
{
    private:
    void copyList(const linkedList<T>& other){ //other is object of the original list to be copied
        if (first != NULL) destroy(); //make it empty before copying
        if(other.first == NULL){ 
            first = last = NULL;
            count = 0;
        } else {
            //first node
            Node<T>* current = other.first;  //current points to the original list to be copied
            first = new Node<T>; // create first node at new copy list
            first->value = current->value; 
            first->next = NULL; 
            last = first; 
            current = current->next; // move to next node at original list 
            // rest of the nodes
            while(current != NULL){
                Node<T>* newNode = new Node<T>; 
                newNode->value = current->value; 
                newNode->next = NULL; 
                last->next = newNode; 
                last = newNode;  
                current = current->next; 
            }
            count = other.count;
        }
    }

    protected:
        int count;
        Node<T>* first;
        Node<T>* last;

    public:
        // constructors and destructor
        linkedList(){
            first =last = NULL;  
            count = 0; 
        }

        linkedList(const linkedList<T>& other){
            first = NULL;
            copyList(other);
        }
        ~linkedList(){
            destroy();
        }

        // assignment operator
        const linkedList<T>& operator=(const linkedList<T>& other){
            if(this != &other){
                destroy();
                copyList(other);
            }
            return *this;
        }
        
        void initialize(){
            destroy ();
        }  

        //basic functions  
        bool isEmpty() const{
            return (first == NULL);
            count = 0;
          
        }  
        T front() const{
            assert(first != NULL); 
            return first->value;
        }        
        T back() const{
            assert(last != NULL); 
            return last->value;
        }         
        int length() const{
            return count;
        }

        //traversal functions       
        void print() const{
            Node<T>* current = first; 
            while(current != NULL){
                cout << current->value << " "; 
                current = current->next; 
            }
        }
        void destroy(){
            Node<T>* temp; 
            while(first != NULL){
                temp = first; 
                first = first->next; 
                delete temp; 
            }
            last = NULL; 
            count = 0;
        }       
        
        // abstract functions
        virtual bool search(const T& v) const = 0;
        virtual void insertFirst(const T& v) = 0;
        virtual void insertLast(const T& v) = 0;
        virtual void deleteNode(const T& v) = 0;
        
        // iterators    
        llIterator<T>* begin(){
            return llIterator<T> (first);
        }
        llIterator<T>* end(){
            return llIterator<T> (NULL);
        }
        
    };
template <class T>
class unordered : public linkedList<T>
{ //this -> to access the protected members of the base class better than using linkedList<T>::first directly
public:
    bool search(const T& searchItem) const{ //o(n) in worst case
        bool found = false; 
        Node<T>* current = first;
        while(current != NULL && !found){
            if(current->value == searchItem) {
                found = true;
            }
            else current = current->next; 
        }
        return found;
    }
    void reverse(){
        Node<T>* prev = NULL; //last node after reverse will point to NULL
        Node<T>* current = first; 
        Node<T>* next = NULL; //store the next node before changing the link
        // prev  current  next
        // NULL   80      30     60     50     NULL
        while(current != NULL){
            next = current->next; //store the next node before changing the link
            current->next = prev; //reverse the link
            prev = current; //move prev to current
            current = next; //move to next node
        }
        swap(first, last); //swap first and last pointers
        first = prev; //update first pointer to the new first node after reverse
    }
    void insertFirst(const T& newItem){ //o(1)
        Node<T>* newNode = new Node<T>;
        newNode->value = newItem;
        if (count == 0) { // if the list is empty before insertion
           first = last = newNode;
           newNode->next = NULL;
        }
        else{
            newNode->next =first;
            first = newNode;
        } 
        count++;

        if(last == NULL) last = newNode;
    }
    void insertLast(const T& newItem){ //o(1)
        Node<T>* newNode = new Node<T>;
        newNode->value = newItem;
        newNode->next = NULL;
        if (count ==0){ // if the list is empty before insertion{
            first = last = newNode;
            newNode->next = NULL;
        }
        else {
            last->next = newNode;
            newNode->next = NULL;
            last = newNode;
        }
        count++;
    }
    void insertAtPos(int pos, const T& newItem){ //o(n) in worst case
        if(pos < 0 || pos > count) cout << "Invalid position." << endl;
        else if(pos == 0) insertFirst(newItem);
        else if(pos == count) insertLast(newItem);
        else{
            Node<T>* newNode = new Node<T>;
            newNode->value = newItem;
            Node<T>* current = first;
            for(int i=0; i<pos-1; i++){ // or for(int i=1; i<pos; i++) 
                current = current->next; // move to the node just before the position of insertion
            }
            newNode->next = current->next;
            current->next = newNode;
            count++;
        }

    }
    void deleteNode(const T& deleteItem){ //o(n) in worst case
        if(first == NULL) cout << "Cannot delete from an empty list."<< endl;; // empty list
        //if has only one node and that node is the one to be deleted
        else if(first->value == deleteItem && first == last && count == 1){ 
            delete first;
            first = last = NULL;
            count--;
        }
        if(first->value == deleteItem){ // if the deleted node is the first node
            Node<T> *current = first;
            first = first->next;
            count--;  
            if(first == NULL) last = NULL; // if list becomes empty
            delete current;
        }
        else{
            bool found = false;
            Node<T> *current = first; //before the deleted node
            Node<T> *temp = first-> next; // the deleted node
            while(temp != NULL && !found){
                if(temp->value != deleteItem){
                    current = temp;
                    temp = temp->next;
                }
                else{
                    found = true;
                }
            }
            if (found){
                current->next = temp->next; 
                count--;
                if(temp == last){
                    last = current; // if last node is deleted
                    last->next = NULL;
                } 
                delete temp;
            }
            else {
            cout << "Item to be deleted is not in the list." << endl;
            }   
        }
         
    }
}; 
template <class T>
class ordered : public linkedList<T>
{ //this -> to access the protected members of the base class better than using linkedList<T>::first directly
public:
    bool search(const T& searchItem) const{ //o(n) in worst case
        bool found = false; 
        Node<T>* current = first;
        while(current != NULL && !found){
            if(current->value >= searchItem) found = true; 
            else current = current->next; 
        }
        if (found)
        found = (current->value == searchItem);//test for equality
        return found;
    }
    void insert(const Type& newItem){ //o(n) in worst case
        Node<T> *current; //pointer to traverse the list 
        Node<T> *trailCurrent; //pointer just before current
        Node<T> *newNode; //pointer to create a node
        bool found;
        newNode = new Node<T>; //create the node
        newNode->value = newItem; //store newItem in the node
        newNode->next = NULL; //set the link field of the nodeto NULL
        if (first == NULL) //Case 1 : list is empty
        {
            first = newNode;
            last = newNode;
            count++;
        }
        else
        {
            current = first;
            found = false;
            while (current != NULL && !found) {//search the list to find the position to insert newItem
                if (current->value >= newItem)  found = true;
                else
                {
                    trailCurrent = current;
                    current = current->next;
                }
            }
            if (current == first) //Case 2 : newItem should be inserted before all the nodes in the list
            {
                newNode->next = first;
                first = newNode;
                count++;
            }
           
            else  //Case 3 : newItem should be inserted after the first node in the list (trail+new+current)
            {
                trailCurrent->next = newNode;
                newNode->next = current;
                if (current == NULL)
                last = newNode;
                count++;
            }
        }
    }
//in reality, the functions insertFirst and insertLast do not apply to an ordered
//linked list because the new item must be inserted at the proper place in the list. However, you
//must provide its definition as these functions are declared as abstract in the parent class.
    void insertFirst(const T& newItem){ //o(n)
        insert (newItem);
    }
    void insertLast(const T& newItem){ //o(n)
       insert (newItem);
    }
    void deleteNode(const T& deleteItem){ //o(n) in worst case
        Node<T> *current; //pointer to traverse the list
        Node<T> *trailCurrent; //pointer just before current
         bool found;
         if (first == NULL) cout << "Cannot delete from an empty list."<< endl;; // empty list
         else
         {
             current = first;
             found = false;
             while (current != NULL && !found) //search the list to find the node to delete
             {
                 if (current->value >= deleteItem) found = true;
                 else
                 {
                     trailCurrent = current;
                     current = current->next;
                 }
             }
             if (current == NULL || current->value != deleteItem) cout << "Item to be deleted is not in the list." << endl; //item not found
             else if (current->value == deleteItem) //item is in the list
             {
                if (current == first) //item is in the first node
                {
                    first = first->next;
                    if (first == NULL) last = NULL; //if list becomes empty after deletion
                    delete current;
                }
                else //item is in a node other than the first
                {
                    trailCurrent->next = current->next;
                    if (current == last) last = trailCurrent; //if item to be deleted is in the last node
                    delete current;
                }
                count--;
            }
         }  
    } 
}; 
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// doubly linked list

template <class T>
struct DNode
{
    T value;              
    DNode<T>* next;   // pointer على النود اللي بعدها
    DNode<T>* back;   // pointer على النود اللي قبلها
};
template <class T>
class doublyLinkedList{
    private:
    void copyList(const doublyLinkedList<Type>& other){ //other is object of the original list to be copied
        if (first!=NULL) destroy(); //make it empty before copying
        if(other.first == NULL){
            first=last = NULL;
            count = 0;
        }
        else{
            //first node
            DNode<T>* current = other.first;  //current points to the original list to be copied
            first = new DNode<T>; // create first node at new copy list
            first->value = current->value;
            first->next = NULL;
            first->back = NULL;
            last = first;
            current = current->next; // move to next node at original list
            // rest of the nodes
            while(current != NULL){
                DNode<T>* newNode = new DNode<T>;
                newNode->value = current->value;
                newNode->next = NULL;
                newNode->back = last;
                last->next = newNode;
                last = newNode;
                current = current->next; 
            }
            count = other.count;
        }
    }
    protected:
        int count;
        DNode<T>* first;
        DNode<T>* last;
    public:
    // constructors and destructor
    doublyLinkedList(){
        first = last = NULL;
        count = 0;
    }
    doublyLinkedList(const doublyLinkedList<Type>& other){
        first = NULL;
        copyList(other);
    }
    ~doublyLinkedList(){
        destroy();
    }
    // assignment operator
    const doublyLinkedList<Type>& operator=(const doublyLinkedList<Type> & other){
        if(this != &other){
            destroy();
            copyList(other);
        }
        return *this;
    }
    void initializeList(){
        destroy();
    }
    bool isEmptyList() const{
        return (first == NULL);
    }
    
    void destroy(){
        DNode <T>* temp; ;
        while(first !=Null){
            temp = first;
            first = first->next;
            delete temp;
        }
        last =Null;
        count = 0;
    }
    int length() const{
        return count;
    }
    void print() const;{
        DNode<T>* current() = first;
        while(current != NULL){
            cout << current->value << " ";
            current = current->next;
            }
    }
    Type front() const{
        assert(first != NULL);
        return first->value;
    }
    Type back() const{
        assert(last != NULL);
        return last->value;
    }
    void search(const Type& searchItem) const{
        bool found = false;
        DNode<T>* current = first;
        while(current != NULL && !found){
            if(current->value >= searchItem) found = true;
            else current = current->next;
        }
        if (found) found = (current->value == searchItem); //test for equality
        return found;
    }
    // void insert(const Type& insertItem){
        //     DNode <T>* current; //pointer to traverse the list
        //     DNode <T>* trailCurrent; //pointer just before current
    //     DNode <T>* newNode; //pointer to create a node
    //     bool found;
    //     newNode = new DNode<T>;
    //     newNode->value = insertItem;
    //     newNode->next = NULL;
    //     newNode->back = NULL;
    //     if(first==Null && count == 0){ //if the list is empty before insertion
    //         first=newNode;
    //         last = newNode;
    //         newNode->next = NULL;
    //         newNode->back = NULL;
    //         count++;
    //     }
    //     else{
        //         current = first;
        //         found = false;
        //         while(current != NULL && !found){
    //             if(current->value >= insertItem) found = true;
    //             else{
        //                 trailCurrent = current;
        //                 current = current->next;
        //             }
        //         }
        //         if(current == first){ //insert before the first node
        //             newNode->next = first;
        //             newNode->back = NULL;
        //             first->back = newNode;
        //             first = newNode;
        //             count++;
        //         }
        //         else{
            //             //if the new node is not inserted at the end of the list
            //             if(current != NULL){
                //                 trailCurrent->next = newNode;
                //                 newNode->back = trailCurrent;
    //                 newNode->next = current;
    //                 current->back = newNode; 
    //             } 
    //             else{ //if the new node is inserted at the end of the list
    //                 trailCurrent->next = newNode;
    //                 newNode->back = trailCurrent;
    //                 newNode->next = NULL;
    //                 last = newNode;
    //             }  
    //             count++;
    //         }
    
    //     }
    // }
    void insertFirst(const Type& newItem){
        DNode <T>* newNode = new DNode<T>;
        newNode->value = newItem;
        if (count ==0){ //if the list is empty before insertion
            first = last  = newNode;
            newNode->next = newNode->back = NULL;
        }
        else{
            newNode->next = first;
            newNode->back = NULL;
            first->back = newNode;
            first = newNode;
        };
        count++;
    }
    void insertLast(const Type& newItem){
        DNode <T>* newNode = new DNode<T>;
        newNode->value = newItem;
        if (count ==0){ //if the list is empty before insertion
            first = last = newNode;
            newNode->next =newNode->back == NULL;
        }
        else{
            last->next = newNode;
            newNode->back = last;
            newNode->next = NULL;
            last = newNode;
        };
        count++;
    }
    void insertAtPos(int pos, const Type& newItem){
        if(pos < 0 || pos > count) cout << "out of bounds" << endl;
        else if(pos == 0) insertFirst(newItem);
        else if(pos == count) insertLast(newItem);
        else{
            DNode<T>* newNode = new DNode<T>;
            newNode->value = newItem;
            DNode<T>* current = first;
            for(int i=0; i<pos-1; i++){ // or for(int i=1; i<pos; i++) 
                current = current->next; // move to the node just before the position of insertion
            }
            newNode->next = current->next;
            newNode->back = current;
            current->next->back = newNode;
            current->next = newNode;
            count++;
        }
        
    }
    void deleteNode(const Type& deleteItem){
        DNode <T>* current; //pointer to traverse the list
        if (count == 0) cout<<"List is empty, cannot delete an item"<<endl;
        else if (count ==1 && first->value == deleteItem){ //if the list has only one node and that node is the one to be deleted
            delete first;
            first = last = NULL;
            count--;
        }
        //remove first node
        else if(first->value == deleteItem){
            current = first;
            first = first->next;
            if(first != NULL) first->back = NULL; //if list is not empty after deletion
            else last = NULL; //if list becomes empty after deletion
            delete current;
            count--;
        }
        //remove last node
        else if(last->value == deleteItem){
            current = last;
            last = last->back;
            if(last != NULL) last->next = NULL; //if list is not empty after deletion
            else first = NULL; //if list becomes empty after deletion
            delete current;
            count--;
        }
        //remove a node other than the first and last nodes
        else{
            current = first->next; //start from the second node
            while(current != NULL){
                if(current->value == deleteItem)
                break;
                current = current->next; //move to the next node before deleting the current node to avoid dangling pointer     
            }
            current -> back->next = current->next; //link the previous node to the next node
            current -> next->back = current->back; //link the next node to the previous node
            delete current;
            count--;
            if(current==NULL) cout<<"The item to be deleted is not in the list."<<endl;
            else{
                cout<<"The item to be deleted is not in the list."<<endl;
           }
        }
        
    } 
    void display() const{
        DNode<T>* current = first;
        cout << "List elements: ";
        while(current != NULL){
            cout << current->value << " ";
            current = current->next;
        }
        cout << endl;
    }    
    void reverse() const{
        DNode<T>* current = last;
        cout << "List reversed elements: ";
        while(current != NULL){
            cout << current->value << " ";
            current = current->back;
        }
        cout << endl;
    } 

};

