//
//  PSLL.h
//  COP3503
//
//  Created by Nicholas Alvarez on 9/8/17.
//  Copyright © 2017 Nick Alvarez. All rights reserved.
//
// Pool-using Singly-Linked List (PSLL)

#ifndef PSLL_h
#define PSLL_h

#include <iostream>
#include <stdexcept>
#include <exception>
#include"List.h"

// Template and Class PSLL

namespace cop3530
{
    
    template <typename L>
    class PSLL_Iter;
    
    template <typename L>
    class PSLL : public List<L> {;
        
    public:
        
        // constructor
        PSLL();
        
        // copy constructor/assignment
        PSLL( const PSLL<L>& src );
        PSLL<L>& operator=( const PSLL<L>& src );
        
        // move constructor/assignment
        PSLL( const PSLL<L>&& src );
        //      PSLL<L>& operator=( const PSLL<L>&& src );
        PSLL<L>& operator=( PSLL<L>&& src );
        
        // destructor
        ~PSLL();
        
        //--------------------------------------------------
        // type aliases
        //--------------------------------------------------
        //using size_t = std::size_t;
        using value_type = L;
        using iterator = PSLL_Iter<L>;
        using const_iterator = PSLL_Iter<L const>;
        
        // iterators over a non-const List
        // dereferenced iterator can be read or written
        iterator begin() { return PSLL_Iter<L>(head); }
        iterator end() { return PSLL_Iter<L>(NULL); }
        
        // iterators over a const List
        // dereferenced iterator can be read but not written
        const_iterator begin() const { return PSLL_Iter<L const>(head); }
        const_iterator end() const { return PSLL_Iter<L const>(NULL); }
        
        
        //------------------------------------------------------------
        //-------------------   METHODS     --------------------------
        //------------------------------------------------------------
        L pop_back() ;
        L pop_front() ;
        bool is_empty() const;
        bool is_full() const;
        size_t length() const;
        L remove( size_t position ) ;
        L item_at( size_t position ) const ;
        void push_back(  const L& element ) ;
        void push_front( const L& element ) ;
        L peek_back() ;
        L peek_front() ;
        void clear() ;
        bool contains(const L& element,bool equals(const L& x, const L& y)) const ;
        void insert( const L element, size_t position ) ;
        L replace(const L& element, size_t position ) ;
        L *contents() ;
        std::ostream& print(std::ostream& out) const ;
        
        // Used for test
        size_t get_pool_size() { return pool_size(); }
        
        //Struct Node
        struct Node {
            L     data;
            Node* next;
        };
        
    private:
        Node* head;
        Node* tail;
        Node* Poolhead;
        
        size_t pool_size () {
            if ( Poolhead==NULL ) {
                return 0;
            }
            size_t count=0;
            Node* temp = Poolhead;
            while (temp != NULL ) {
                count++;
                temp=temp->next;
            }
            return count;
        }
        
        
        // This method will manage the free pool nodes
        void deallocate() {
            
            size_t list_size      = this->length();
            size_t list_size_div2 = list_size/2;
            //std::cout <<" Deallocate - List Size = "<<list_size<<std::endl;
            //std::cout <<" Deallocate - Pool Size = "<<pool_size()<<std::endl;
            //std::cout <<" Deallocate - List Size/2  = "<<list_size_div2<<std::endl;
            if ( (list_size >= 100) && (this->pool_size() > list_size_div2) ) {
                
                //std::cout <<" Deallocate - MODIFYING .... = "<<std::endl;
                
                // AND pool contains more notes tha 1/2 List Size
                // reduce pool size by 1/2 list size by deallocating nodes
                Node* temp = Poolhead;
                size_t x=0;
                for ( x=0; x<list_size_div2; x++ ) {
                    temp = temp->next;  // Get Next Mode
                    delete Poolhead;    // Delete Current Node
                    Poolhead = temp;    // Assign Pool Head to next Node
                }
                
                //if ( count>static_cast<float>(size)/2.0f )
            }
            return;
        }
        
    };
    
    
    // Constructor
    template <typename L>
    PSLL<L>::PSLL() {
        head=NULL;
        tail=NULL;
        Poolhead=NULL;
    }
    
    
    // Copy Constructor  Example Usage: PSLL dst(src);
    template <typename L>
    PSLL<L>::PSLL( const PSLL<L>& src )
    {
        
        // Need to do a Deep copy - Make new nodes
        if (src.head == NULL)
        {
            head = NULL;
            tail = NULL;
            Poolhead=NULL;
        }
        else
        {
            Node* SrcPtr;          // will be used to store src Nodes
            Node* newnode;         // will be used for New Nodes
            newnode = new Node();  // Make a new node
            
            // Assign head/tail pointers to new node
            head=newnode;
            tail=newnode;
            
            // copy src head data to New Node head data
            head->data=src.head->data;
            //std::cout<<"Copy Const.. Src->head.data = "<<src.head->data<<std::endl;
            // assign next node to Null for now...
            head->next=NULL;
            
            // assign SrcPtr to the Src Head Node
            SrcPtr = src.head;
            
            // Store New Node in PrevNodePtr
            Node* PrevNodePtr = newnode;
            //std::cout<<"Copy Const.. Src->head = "<<src.head<<std::endl;
            //std::cout<<"Copy Const.. Src->head->next = "<<src.head->next<<std::endl;
            
            // Make a Copy of all the Source Nodes
            while ( SrcPtr->next != NULL )
            {
                
                // Proceed to next Node
                SrcPtr = SrcPtr->next;
                
                // Make a new Node
                newnode = new Node();
                //std::cout<<"Copy Const.. making new node"<<newnode<<std::endl;
                PrevNodePtr->next = newnode;   // Link Previous Node to New Node
                newnode->data = SrcPtr->data;  // Get Data from Src for NewNode
                //std::cout<<"Copy Const.. SrcPtr->data = "<<SrcPtr->data<<std::endl;
                newnode->next = NULL;          // Set Next Node to Null
                PrevNodePtr = newnode;
            }
            // Set Tail to the last node created
            tail     = newnode;
            Poolhead = NULL;
            //std::cout<<"Copy Const.. head = "<<head<<std::endl;
            //std::cout<<"Copy Const.. head->next = "<<head->next<<std::endl;
            //std::cout<<"Copy Const.. tail = "<<tail<<std::endl;
            //std::cout<<"Copy Const.. tail->next = "<<tail->next<<std::endl;
            
        }
    }
    
    
    // Copy Assignment Example Usage: PSLL dst;
    //                                ....do a bunch of stuff with dst...
    //                                ....now I don't need dst anymore, so reuse it...
    //                                dst= src;
    // NOTE: The Pool List remains the same
    //       The Destination Nodes are removed first before new nodes created
    template <typename L>
    PSLL<L>& PSLL<L>::operator=( const PSLL<L>& src )
    {
        // Need to deallocate all of the current Nodes
        // NOTE: Pool Nodes are not deallocated .. keep intact
        Node* current = head;
        Node* next;
        if ( head != NULL ) {
            // Remove all Nodes in List
            while ( current != NULL ) {
                next=current->next; // Store next node
                delete current;     // Delete current
                current=next;       // Make current Node the current
            }
        }
        
        // Perform a deep-copy of all the Source List Nodes
        if (src.head == NULL)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            Node* SrcPtr;          // will be used to store src Nodes
            Node* newnode;         // will be used for New Nodes
            newnode = new Node();  // Make a new node
            
            // Assign head/tail pointers to new node
            head=newnode;
            tail=newnode;
            
            // copy src head data to New Node head data
            head->data=src.head->data;
            // assign next node to Null for now...
            head->next=NULL;
            
            // assign SrcPtr to the Src Head Node
            SrcPtr = src.head;
            
            // Store New Node in PrevNodePtr
            Node* PrevNodePtr = newnode;
            
            // Make a Copy of all the Source Nodes
            while ( SrcPtr->next != NULL )
            {
                // Proceed to next Node
                SrcPtr = SrcPtr->next;
                
                // Make a new Node
                newnode = new Node();
                PrevNodePtr->next = newnode;   // Link Previous Node to New Node
                newnode->data = SrcPtr->data;  // Get Data from Src for NewNode
                newnode->next = NULL;          // Set Next Node to Null
                PrevNodePtr = newnode;
            }
            // Set Tail to the last node created
            tail = newnode;
        }
        // Return Reference to destination
        return *this;
    }
    
    
    // Move constructor
    template <typename L>
    PSLL<L>::PSLL( const PSLL<L>&& src )
    {
        head = src.head;
        tail = src.tail;
        Poolhead = src.Poolhead;
    }
    
    // Move Assignment
    template <typename L>
    PSLL<L>& PSLL<L>::operator=( PSLL<L>&& src )
    {
        // Need to deaallocate all Nodes First...
        clear ();
        // assign to source list
        head = src.head;
        tail = src.tail;
        Poolhead = src.Poolhead;
        // Set member variables to Null since move
        // has taken ownership
        src.head      = nullptr;
        src.tail      = nullptr;
        src.Poolhead  = nullptr;
        return *this;
    }
    
    // destructor
    template <typename L>
    PSLL<L>::~PSLL() {
        clear();
    }
    
    
    //------------ IS_FULL() --------------------------
    template<typename L>
    bool PSLL<L>::is_full() const {
        return false;
    }
    
    
    // ----------- IS_EMPTY() -----------------------
    template<typename L>
    bool PSLL<L>::is_empty() const {
        // Is_Empty when head isnt pointing to something
        if ( head==NULL ){
            return true;
        }
        return false;
        
    }
    
    
    //------------- LENGTH() -----------------------
    template<typename L>
    size_t PSLL<L>::length() const {
        
        if ( head==NULL ) {
            return 0;
        }
        size_t count=0;
        Node* temp = head;
        while ( temp != NULL ) {
            count++;
            temp=temp->next;
        }
        return count;
        
    }
    
    
    //------------- POP_BACK() ------------------------
    template<typename L>
    L PSLL<L>::pop_back() {
        
        if ( head==NULL ) {
            throw std::runtime_error("PSLL<E>.pop_back(): Can not pop and empty list");
        }
        
        bool FreeNodesLT50 = false;
        // Check to see if Free Pool Nodes are less
        // than 50.. If yes, then  set Boolean Variable
        // Doing this only once so do not have to call the pool_size
        // method while messing with the free pool pointers.
        if ( this->pool_size() < 50 )
        {
            FreeNodesLT50 = true;
        }
        
        Node* cur_free = Poolhead;
        if ( length()==1 ) {
            
            // Set data at head of list since length=1
            L data = head->data;
            
            if ( FreeNodesLT50 )
            {
                // Set Free pool to node being removed
                Poolhead  = head;
                // Now link node being removed to free list
                Poolhead->next = cur_free;
            }
            else
            {
                // Delete Head Node
                delete head;
            }
            
            // Set Head and Tail to Null
            head=NULL;
            tail=NULL;
            deallocate();
            return data;
        }
        
        size_t x;
        // Set data at tail of list
        L data = tail->data;
        
        Node* temp     = head;
        Node* cur_tail = tail;
        // Advance to node before last node
        for ( x=0; x<length()-2; x++ )  {
            temp = temp->next;
        }
        // now temp pointer points to Prev Node before tail
        
        // Check that PoolNodes are less than 50 NODES
        if ( FreeNodesLT50 )
        {
            // <50 Nodes So Set Free pool head pointer to node being removed
            Poolhead = tail;  // equivalent to temp->next and cur_tail
        }
        else
        {
            // >= 50 Pool Nodes delete Tail Node
            delete tail;
        }
        
        // Set Prev Node to Null since now new tail node
        temp->next = NULL;
        
        // Set tail to the Prev Node (since tail being removed)
        tail = temp;
        
        // Check if Pool Nodes < 50
        if ( FreeNodesLT50 )
        {
            // Now set the Tail Node to point to Prev head PoolNode
            cur_tail->next = cur_free;
        }
        
        // Need to call deallocate to manage free pool nodes
        deallocate();
        return data;
        
    }
    
    
    
    // -------------------- POP_FRONT() --------------------------
    template<typename L>
    L PSLL<L>::pop_front(){
        
        if ( head==NULL ) {
            throw std::runtime_error("PSLL<E>.pop_front(): Can not pop and empty list");
        }
        
        bool FreeNodesLT50 = false;
        // Check to see if Free Pool Nodes are less
        // than 50.. If yes, then  set Boolean Variable
        // Doing this only once so do not have to call the pool_size
        // method while messing with the free pool pointers.
        if ( this->pool_size() < 50 )
        {
            FreeNodesLT50 = true;
        }
        
        Node* cur_free = Poolhead;
        Node* cur_head = head;
        // Set data to Node at Head of list
        L data = head->data;
        if ( length()==1 ) {
            
            if ( FreeNodesLT50 )
            {
                // Set Free pool to node being removed
                Poolhead  = head;
                // Now link node being removed to free list
                Poolhead->next = cur_free;
            }
            else
            {
                // Delete Head Node >50 Free Nodes all ready
                delete head;
            }
            
            // Set Head and Tail to Null
            head=NULL;
            tail=NULL;
            return data;
        }
        
        // Set Free pool head pointer to node being removed
        // if less than 50 Free Nodes
        if ( FreeNodesLT50 )
        {
            // Add Head node to Free Pool since <50 Nodes
            Poolhead = head;
        }
        
        // Proceed to next Head Node
        head = head->next;
        
        // Check that <50 Nodes in Free Pool
        if ( FreeNodesLT50 )
        {
            // Set next Pool node to point previous Pool Head Node
            Poolhead->next = cur_free;
        }
        else
        {
            // Head Node not being added to Free Pool so delete
            // Note: Need to use cur_head cause head pointer is
            //       now pointing to latest node.
            delete cur_head;
        }
        
        // Need to call deallocate to manage free pool nodes
        deallocate();
        return data;
        
    }
    
    
    //--------------------- REMOVE(size_t position) --------------------------
    template<typename L>
    L PSLL<L>::remove( size_t position) {
        
        
        if ( head==NULL ) {
            throw std::runtime_error("PSLL<E>.remove(): Empty list");
        }
        
        if ( (position<0) || (position > length() ) ) {
            throw std::runtime_error("PSLL<E>.remove(): position out of range");
        }
        
        bool FreeNodesLT50 = false;
        // Check to see if Free Pool Nodes are less
        // than 50.. If yes, then  set Boolean Variable
        // Doing this only once so do not have to call the pool_size
        // method while messing with the free pool pointers.
        if ( this->pool_size() < 50 )
        {
            FreeNodesLT50 = true;
        }
        
        Node* cur_free = Poolhead;
        Node* cur_head = head;
        if ( length()==1 ) {
            
            // Set data to Node at Head of list
            L data = head->data;
            
            // Check that Free Nodes <50
            if ( FreeNodesLT50 )
            {
                // Set Free pool to node being removed
                Poolhead  = head;
                // Now link node being removed to free list
                Poolhead->next = cur_free;
            }
            else
            {
                // >50 Nodes So remove the Head Node
                delete head;
            }
            
            // Set Head and Tail to Null
            head=NULL;
            tail=NULL;
            // Manage Free Pool
            deallocate();
            // Return
            return data;
        }
        
        
        // Removing Head node
        if ( position==0 ) {
            
            // Set data to Node at Head of list
            L data = head->data;
            
            // Check that <50 Node in Free Pool
            if ( FreeNodesLT50 )
            {
                // Set Free pool to node being removed
                Poolhead = head;
            }
            
            // Set head Node to Next Node
            head = head->next;
            
            // Check that <50 Node in Free Pool
            if ( FreeNodesLT50 )
            {
                // Now link node being removed to free list
                Poolhead->next = cur_free;
            }
            else
            {
                // Delete Head Node since Free Node contains >= 50 Nodes
                delete cur_head;
            }
            
            // Note: this line incorrect needs to be moved before
            //        this line executes Poolhead->next = cur_free;
            //        because it overwrites the head->next location
            //head = head->next;
            
            // Manage Free Pool - check if any Nodes need to be deallocated
            deallocate();
            
            // Return Data
            return data;
        }
        
        
        // Else.. not removing Head Node
        // Find the Prev Node before the position
        size_t x= 1;
        Node* temp = head;
        for( x=1; x<position; x++ ) {
            temp=temp->next;
        }
        
        // temp now points to Node before position
        // Get data from Node at position
        L data = temp->next->data;
        Node* FreeNode = temp->next;     // This node needs to be added to free pool
        temp->next = temp->next->next;   // Store the next pointer before deleting Node
        
        // Now Check if Node removed was the Tail Node
        if ( position == length()-1 ) {
            // Node removed is the Tail Node
            tail=temp;  // Update Tail pointer
            temp->next = NULL;  // make next pointer Null
        }
        
        // Check if less than 50 Nodes in Free  Pool
        if ( FreeNodesLT50 )
        {
            // Update Free Pool
            // Set Free pool to node being removed
            Poolhead  = FreeNode;
            // Now link node being removed to free list
            Poolhead->next = cur_free;
        }
        else
        {
            // Delete the Node at position since Free Pool
            // all ready contains >= 50 Nodes
            delete FreeNode;
        }
        
        // manage free pool
        deallocate();
        return data;
        
    }
    
    
    
    //----------------- ITEM_AT(size_t position) --------------------------
    template<typename L>
    L PSLL<L>::item_at( size_t position ) const {
        
        if ( position<0 || position>= length() ) {
            throw std::runtime_error("PSLL<E>.item_at(): Position is out of range");
        }
        
        if ( head==NULL ) {
            throw std::runtime_error("PSLL<E>.item_at(): List is empty");
        }
        
        Node* temp=head;
        size_t i=0;
        for( i=0; i<position; i++){
            temp=temp->next;
        }
        
        // temp now points to Node requested (position)
        return temp->data;
        
    }
    
    
    
    //-----------------------PEEK_BACK( ) -----------------------------------------
    template<typename L>
    L PSLL<L>::peek_back() {
        
        if ( tail == NULL ) {
            throw std::runtime_error("PSLL<E>.peek_back(): Empty List");
        }
        return tail->data; //return item at tail node
        
    }
    
    
    //----------------------- PEEK_FRONT () --------------------------------------
    template<typename L>
    L PSLL<L>::peek_front() {
        
        if ( head== NULL ) {
            throw std::runtime_error("PSLL<E>.peek_front(): Empty List");
        }
        return head->data; //Return data at head
        
    }
    
    
    
    //-------------------- CLEAR() --------------------------------
    template<typename L>
    void PSLL<L>::clear() {
        
        // NOTE: Do not return if Head==Null cause need to check PoolHead
        Node* current = head;
        Node* next;
        // Remove all Nodes in List
        while ( current != NULL ) {
            next=current->next; // Store next node
            delete current;     // Delete current
            current=next;       // Make current Node the current
        }
        
        // Remove all Nodes in Free Pool
        current = Poolhead;
        while ( current != NULL ) {
            next=current->next; // Store next node
            delete current;     // Delete current
            current=next;       // Make current Node the current
        }
        
        // make head, tail, and poolhead NULL
        head=NULL;
        tail=NULL;
        Poolhead=NULL;
        return;
        
    }
    
    
    
    //------------- push_back( const L& element ) -----------------------------
    template<typename L>
    void PSLL<L>::push_back( const L& element ) {
        
        Node* newnode;
        // Need to check Free Pool to see if Nodes avail
        if ( Poolhead == NULL ) {
            // Free Pool Null so make new Node
            newnode = new Node();
        } else {
            // Get node from Free Pool
            newnode=Poolhead;       // Set Node to Head Node in FreePool
            Poolhead=Poolhead->next; // Remove Node from Pool
            newnode->next=NULL;     // New Node next pointer is NULL is Tail node
        }
        
        newnode->data =element;  // Store new element in new node
        newnode->next =NULL;     // New Node next pointer is NULL since Tail node
        
        if ( head == NULL ) {
            // if Head Null then this node is First node in List
            head=newnode;
            tail=newnode;
        } else {
            tail->next=newnode;
            tail=newnode;
        }
        
        // Manage Free Pool List
        deallocate();
        return;
        
    }
    
    
    //-------------------- push_front( const L& element ) ---------------------------
    template<typename L>
    void PSLL<L>::push_front( const L& element ) {
        
        Node* newnode;
        // Need to check Free Pool to see if Nodes avail
        
        if ( Poolhead == NULL ) {
            // Free Pool Null so make new Node
            newnode = new Node();
        } else {
            // Get node from Free Pool
            newnode=Poolhead;        // Set Node to Head Node in FreePool
            Poolhead=Poolhead->next; // Remove Node from Pool
        }
        
        // Store element in new node
        newnode->data = element;
        
        if ( head == NULL ){
            head=newnode;
            tail=newnode;
            newnode->next=NULL;
        } else {
            // Push new node to front of the list
            newnode->next=head;  // New Node next point points to existing head
            head=newnode;        // Head now points to new node
        }
        
        // Manage Free Pool List
        deallocate();
        return;
        
    }
    
    
    //------------- INSERT(const L& Element, sie_t position) ---------------------
    template<typename L>
    void PSLL<L>:: insert( L element, size_t position ) {
        
        if ( position<0 || position > length() ) {
            throw std::runtime_error("PSLL<E>.insert(): position is out of range");
        }
        
        if ( position == length() )
        {
            // then inserting at the back of the list
            this->push_back( element );
            return;
        }
        
        Node* newnode;
        // Need to check Free Pool to see if Nodes available
        if ( Poolhead == NULL ) {
            // Free Pool Null so make new Node
            newnode = new Node();
        } else {
            // Get node from Free Pool
            newnode=Poolhead;        // Set Node to Head Node in FreePool
            Poolhead=Poolhead->next; // Remove Node from Pool
        }
        
        // Store new element in new node
        newnode->data = element;
        
        if (position==0) {
            // New node will be at head of the list
            newnode->next = head;
            head          = newnode;
            // Manage Free Pool
            deallocate();
            return;
        }
        
        Node* temp=head;
        // Find the Previous Node before the insert Position
        for ( size_t x=1; x<position; x++){
            temp=temp->next;
        }
        
        // Now temp is pointing to the previous Node before the Insert position
        // Set the pointer of the new node to be equal to the previous node
        newnode->next = temp->next;
        
        // modify the previous node to point to the new node
        temp->next = newnode;
        
        // Manage Free Pool
        deallocate();
        return;
        
    }
    
    
    //-----------------------replace(const L& element, size_t position ) --------------------------
    template<typename L>
    L PSLL<L>:: replace(const L& element, size_t position ) {
        
        // Replaces the existing element at the specified position with
        // the specified element and return the original element.
        if ( position<0 || position >= length() || length()==0 ){
            throw std::runtime_error("PSLL<E>.replace(): position out of range or empty list.");
        }
        
        size_t x=0;
        Node* temp = head;
        while( x != position ) {
            temp=temp->next;
            x++;
        }
        
        L data = temp->data;
        temp->data=element;
        
        return data;
        
    }
    
    
    
    //------------- contains(const L& element,bool equals(const L& a, const L& b)) const ------------
    template<typename L>
    bool PSLL<L>:: contains(const L& element,bool equals(const L& x, const L& y)) const {
        
        if ( length()==0 ) {
            throw std::runtime_error("PSLL<E>.contains(): List is empty ");
        }
        
        Node* temp=head;
        while( temp != NULL  ){
            if ( equals(element, temp->data) ) {
                return true;
            }
            temp=temp->next;
        }
        return false;
        
    }
    
    
    //------------- std::ostream& PSLL<L>::print(std::ostream &out) ------------------
    template<typename L>
    std::ostream&  PSLL<L>::print(std::ostream& out) const
    {
        if ( length()==0 ) {
            out<<"<empty list>"<<std::endl;
            return out;
        }
        
        Node* temp = head;
        out<< "[";
        while( temp != NULL ) {
            out<< temp->data;
            
            if ( temp->next != NULL ) {
                out<<",";
            }
            temp=temp->next;
            
        }
        out<<"]"<< std::endl;
        return out;
        
    }
    
    
    //----------------------- contents() ------------------------------------
    template<typename L>
    L *PSLL<L>::contents() {
        
        if ( length()==0 ) {
            throw std::runtime_error("PSLL<E>.contents(): List is empty ");
        }
        
        size_t x=0;
        size_t cur_length;
        cur_length = length();  // get current length of array
        L *array = new L[length()];
        
        Node* temp = head;    // Temp pointer to head
        for ( x=0; x<cur_length; x++ ) {  
            array[x]= temp->data; // get data from node
            temp=temp->next;      // increment pointer
        }
        
        //while ( temp->next != NULL ) {  
        // While next is not null insert data into array 
        //   array[x]= temp->data;
        //   temp=temp->next;
        //   x++;
        //}
        return array;
        
    }
    
}


//
//  PSLL_Iter.h
//  COP3530
//
//  Created by Nicholas Alvarez on 11/7/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//
namespace cop3530
{
    
    
    template <typename DataT>
    class PSLL_Iter
    {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = PSLL_Iter;
        using self_reference = PSLL_Iter&;
        
    private:
        typename PSLL<DataT>::Node* here;
        
    public:
        explicit PSLL_Iter( typename PSLL<DataT>::Node* start = nullptr ) : here( start ) {}
        PSLL_Iter( const PSLL_Iter& src ) : here( src.here ) {}
        
        reference operator*() const { return here->data; }
        pointer operator->() const { return &here->data; }
        
        self_reference operator=( PSLL_Iter<DataT> const& src ) {
            here = src.here;
            return *this;
        }
        
        self_reference operator++() {
            here = here->next;
            return *this;
        } // preincrement
        
        self_type operator++(int) {
            PSLL_Iter<DataT> temp(*this);
            here = here->next;
            return temp;
        } // postincrement
        
        bool operator==( PSLL_Iter<DataT> const& rhs ) const { return (here == rhs.here); }
        bool operator!=( PSLL_Iter<DataT> const& rhs) const { return (here != rhs.here); }
    }; // end PSSL_Iter
    
}
#endif /* _PSLL_H_ */

