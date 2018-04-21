//
//  SSLL.h
//  COP3503
//
//  Created by Nicholas Alvarez on 9/8/17.
//  Copyright © 2017 Nick Alvarez. All rights reserved.
//
// SIMPLE SINGLY LINKED LIST

#ifndef _SSLL_H_
#define _SSLL_H_

#include<iostream>
#include <stdexcept>
#include <exception>
#include <stdlib.h>
#include"List.h"


// Template and Class SSLL
namespace cop3530
{
    
    template <typename DataT>
    class SSLL_Iter;
    
    template <typename L>
    class SSLL : public List<L>{
        
        
    public:
        // constructor
        SSLL();
        
        // copy constructor/assignment
        SSLL( const SSLL<L>& src );
        SSLL<L>& operator=( const SSLL<L>& src );
        
        // move constructor/assignment
        SSLL( const SSLL<L>&& src );
        SSLL<L>& operator=( SSLL<L>&& src );
        
        // destructor
        ~SSLL();
        
        //--------------------------------------------------
        // type aliases
        //--------------------------------------------------
        //using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = L;
        using iterator = SSLL_Iter<L>;
        using const_iterator = SSLL_Iter<L const>;
        
        // iterators over a non-const List
        iterator begin() { return SSLL_Iter<L>(head); }
        iterator end() { return SSLL_Iter<L>(NULL); }
        
        // iterators over a const List
        const_iterator begin() const { return SSLL_Iter<L>(head); }
        const_iterator end() const { return SSLL_Iter<L>(NULL); }
        
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
        std::ostream& print(std::ostream& out) const;
        
        
        struct Node {
            L data;
            Node* next;
        };
        
    private:
        Node* head;
        Node* tail;
        
    };
    
    
    // Constructor
    template <typename L>
    SSLL<L>::SSLL() {
        head=NULL;
        tail=NULL;
        
    }
    
    
    // Copy Constructor  Example Usage: PSLL dst(src);
    template <typename L>
    SSLL<L>::SSLL( const SSLL<L>& src )
    {
        
        // Need to do a Deep copy - Make new nodes
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
    SSLL<L>& SSLL<L>::operator=( const SSLL<L>& src )
    {
        // Need to deallocate all of the current Nodes
        // NOTE: Pool Nodes are not deallocated .. keep intact
        Node* current = head;
        Node* next;
        // Remove all Nodes in List
        while ( current != NULL ) {
            next=current->next; // Store next node
            delete current;     // Delete current
            current=next;       // Make current Node the current
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
    SSLL<L>::SSLL( const SSLL<L>&& src )
    {
        head = src.head;
        tail = src.tail;
        
    }
    
    // Move Assignment
    template <typename L>
    SSLL<L>& SSLL<L>::operator=( SSLL<L>&& src )
    {
        // Need to deaallocate Nodes First...
        clear ();
        head = src.head;
        tail = src.tail;
        // Set source variables to NULL since move
        // now has taken ownership of them
        src.head = nullptr;
        src.tail = nullptr;
        return *this;
    }
    
    // destructor
    template <typename L>
    SSLL<L>::~SSLL() {
        clear();
    }
    
    //------------ IS_FULL()-----------------------
    template<typename L>
    bool SSLL<L>::is_full() const
    {
        
       
            return false;
    
        
    }
    
    
    // ------------IS_EMPTY()---------------------
    template<typename L>
    bool SSLL<L>::is_empty() const
    {
        // List is empty when head is Null
        if ( head==NULL ) {
            return true;
        } else {
            return false;
        }
        
    }
    
    //----------------LENGTH()---------------------
    template<typename L>
    size_t SSLL<L>::length() const
    {
        
        if ( head == NULL ) {
            return 0;
        }
        size_t size=0;
        Node* temp = head;
        
        while ( temp !=NULL ) {
            size++;
            temp=temp->next;
        }
        return size;
        
    }
    
    //------------------POP_BACK()----------------
    template<typename L>
    L SSLL<L>::pop_back()
    {
        
        
        if ( length()==0 ) {
            throw std::runtime_error("SSLL<E>.pop_back(): Can not pop and empty list");
        }
        
        // only one element in list
        if ( length()==1 ) {
            L data = head->data;
            delete head;
            head=NULL;
            tail= NULL;
            return data;
        }
        
        size_t x;
        L data=tail->data; //store data at tail node
        Node* temp = head;
        // Find the Node before the Tail Node by iterating through
        // each element.  Note: length()-1 is Tail Location
        for ( x=0; x<length()-2; x++ ) {
            temp = temp->next;
        }
        
        // temp is pointing to Prev Node before Tail
        delete temp->next; // remove tail node
        temp->next=NULL;   //set pointer of tail-1 node to NULL
        tail=temp;         //set new tail pointer
        return data;
        
    }
    
    
    // --------------------POP_FRONT()--------------------------
    template<typename L>
    L SSLL<L>::pop_front() {
        
        // Remove and returns the element at list's head
        if ( head==NULL ) {
            throw std::runtime_error("SSLL<E>.pop_front(): Empty list ");
        }
        if ( length()==1 ) {
            L data= head->data;
            delete head;
            head=NULL;
            tail=NULL;
            return data;
        }
        
        // Return Head Data
        Node* deleting = head;
        L data= head->data;
        head  = head->next;
        delete deleting;
        return data;
        
    }
    
    
    
    //-------------------REMOVE(size_t position)------------------
    template<typename L>
    L SSLL<L>::remove( size_t position) {
        
        if ( head==NULL || position< 0 || position >= length() ) {
            throw std::runtime_error("SSLL<E>.remove( position ): Empty list OR position not in range");
        }
        
        if ( length()==1 ) {
            // Removing the Head Node and only One Node
            L data = head->data;
            delete head;
            head=NULL;
            tail=NULL;
            return data;
        }
        
        if ( position==0 ) {
            // removing the Head Node and more than one Node
            L data = head->data;
            Node* deleting = head;
            head = head->next;  // Update Head pointer
            delete deleting;    // Delete Head node
            return data;
        }
        
        // Find the Prev Node before the position
        size_t x= 1;
        Node* temp = head;
        for( x=1; x<position; x++ ) {
            temp=temp->next;
        }
        
        // temp now points to Node before position
        // Get data from Node at position
        L data = temp->next->data;
        Node* deleting = temp->next;
        temp->next = temp->next->next;   // Store the next pointer before deleting Node
        delete deleting;  // Deleting Node requested at position
        
        // Now Check if Node removed was the Tail Node
        if ( position == length()-1 ) {
            // Node removed is the Tail Node
            tail=temp;  // Update Tail pointer
            temp->next = NULL;  // make next pointer Null
        }
        return data;
        
    }
    
    
    
    //---------------------------ITEM_AT(size_t position)--------------------------
    template<typename L>
    L SSLL<L>::item_at( size_t position ) const {
        
        if ( position<0 || position>= length() ) {
            throw std::runtime_error("SSLL<E>.item_at(): Position is out of range");
        }
        
        if ( head==NULL ) {
            throw std::runtime_error("SSLL<E>.item_at(): List is empty");
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
    L SSLL<L>::peek_back() {
        
        if ( tail == NULL ) {
            throw std::runtime_error("SSLL<E>.peek_back(): Empty List");
        }
        return tail->data; //return item at tail node
        
    }
    
    
    //----------------------- PEEK_FRONT () --------------------------------------
    template<typename L>
    L SSLL<L>::peek_front() {
        
        if ( head== NULL ) {
            throw std::runtime_error("SSLL<E>.peek_front(): Empty List");
        }
        
        return head->data; //Return data at head
        
    }
    
    
    //-------------------- CLEAR() --------------------------------------------
    template<typename L>
    void SSLL<L>::clear() {
        
        Node* current = head;
        Node* next;
        while ( current != NULL ) {
            next=current->next; // Store next node
            delete current;     // Delete currrent
            current=next;       // Make current Node the current
        }
        
        // make head and tail NULL
        head=NULL;
        tail= NULL;
        return;
        
    }
    
    
    //-----------------------push_back( const L&  element )) ------------------------
    template<typename L>
    void SSLL<L>::push_back(  const L&  element ) {
        
        Node* newnode= new Node();
        newnode->data = element;
        newnode->next = NULL;
        if ( head==NULL ) {
            head = newnode;
            tail = newnode;
        } else {
            tail->next = newnode;
            tail = newnode;
        }
        
    }
    
    
    
    //----------------------- push_front( const L& element ) --------------------
    template<typename L>
    void SSLL<L>::push_front( const L& element ) {
        
        Node* newnode = new Node();
        newnode->data=element;
        
        if(head==NULL){
            head= newnode;
            tail=newnode;
            newnode->next= NULL;
        } else {
            newnode->next=head;
            head=newnode;
            
        }
        
    }
    
    
    
    //-----------------------INSERT(const L& Element, size_t position)------------------
    template<typename L>
    void SSLL<L>:: insert( const L element, size_t position ) {
        
        if( position<0 || position > length() ) {
            throw std::runtime_error("SSLL<E>.insert(): position is out of range");
        }
        
        if ( position == length() )
        {
            // then inserting at the back of the list
            this->push_back( element );
            return;
        }
        
        // Create New Node and store the data
        Node* newnode = new Node();
        
        newnode->data = element;
        if (position==0) {
            // Inserting before head so make New Node the current head
            newnode->next = head;
            head          = newnode;
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
        return;
        
    }
    
    
    //-----------------------replace(const L& element, size_t position ) --------------------------
    template<typename L>
    L SSLL<L>:: replace(const L& element, size_t position ) {
        
        // Replaces the existing element at the specified position with
        // the specified element and return the original element.
        if ( position<0 || position >= length() || length()==0 ){
            throw std::runtime_error("SSLL<E>.replace(): position out of range or empty list.");
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
    
    
    //---------------contains(const L& element,bool equals(const L& a, const L& b)) const--------------------
    template<typename L>
    bool SSLL<L>:: contains(const L& element,bool equals(const L& x, const L& y)) const {
        
        if ( head==NULL ) {
            throw std::runtime_error("SSLL<E>.contains(): Empty List ");
        }
        
        Node* temp = head;
        while ( temp != NULL ) {
            
            if ( equals(element,temp->data) ){
                return true;
            }
            
            temp=temp->next;
            
        }
        return false;
        
    }
    
    
    
    //------------- std::ostream& SSLL<L>::print(std::ostream &out) ------------------
    template<typename L>
    std::ostream&  SSLL<L>::print(std::ostream& out) const
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
    L *SSLL<L>::contents() {
        
        if ( length()==0 ) {
            throw std::runtime_error("SSLL<E>.contents(): List is empty ");
        }
        
        size_t x=0;
        size_t cur_length=length();
        
        L *array = new L[length()];
        Node* temp = head;    // Temp pointer to head
        
        for ( x=0; x<cur_length; x++ ) {
            array[x]= temp->data;
            temp=temp->next;
        }
        
        //while ( temp->next != NULL ) {
        // While next is not null insert data into array
        //    array[x]= temp->data;
        //    temp=temp->next;
        //    x++;
        // }
        return array;
        
    }
    
}


//
//  SSLL_Iter.h
//  COP3530
//
//  Created by Nicholas Alvarez on 11/7/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//

namespace cop3530
{
    
    
    template <typename DataT>
    class SSLL_Iter
    {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = SSLL_Iter;
        using self_reference = SSLL_Iter&;
        
    private:
        typename SSLL<DataT>::Node* here;
        
    public:
        explicit SSLL_Iter( typename SSLL<DataT>::Node* start = nullptr ) : here( start ) {}
        SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}
        
        reference operator*() const { return here->data; }
        pointer operator->() const { return &here->data; }
        
        self_reference operator=( SSLL_Iter<DataT> const& src ) {
            here = src.here;
            return *this;
        }
        
        self_reference operator++() {
            here = here->next;
            return *this;
        } // preincrement
        
        self_type operator++(int) {
            SSLL_Iter<DataT> temp(*this);
            here = here->next;
            return temp;
        } // postincrement
        
        bool operator==( SSLL_Iter<DataT> const& rhs ) const { return (here == rhs.here); }
        bool operator!=( SSLL_Iter<DataT> const& rhs) const { return (here != rhs.here); }
    }; // end SSLL_Iter
    
    template <typename DataT>
    class SSLL_Const_Iter //: public std::iterator<std::forward_iterator_tag, T>
    {
    public:
        // inheriting from std::iterator<std::forward_iterator_tag, T>
        // automatically sets up these typedefs...
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = SSLL_Const_Iter;
        using self_reference = SSLL_Const_Iter;
        
        
    private:
        typename SSLL<DataT>::Node* here;
        
    public:
        explicit SSLL_Const_Iter(typename SSLL<DataT>::Node* start = nullptr) :
        here(start) {
        }
        SSLL_Const_Iter(const SSLL_Const_Iter& src) :
        here(src.here) {
        }
        
        reference operator*() const {
            if (!here) {
                throw std::logic_error("Can't use operator with a null node");
            }
            return here->data;
        }
        pointer operator->() const {
            if (!here) {
                throw std::logic_error("Can't use operator with a null node");
            }
            return &here->data;
        }
        
        self_reference operator=(const SSLL_Const_Iter& src) {
            if (*this == src) {
                return *this;
            }
            here = src.here;
            return *this;
        }
        
        self_reference operator++() {
            if (!here) {
                throw std::logic_error("Can't use operator with a null node");
            }
            here = here->next;
            return *this;
        } // preincrement
        
        self_type operator++(int) {
            if (!here) {
                throw std::logic_error("Can't use operator with a null node");
            }
            SSLL_Const_Iter results(*this);
            here = here->next;
            return results;
        } // postincrement
        
        bool operator==(const SSLL_Const_Iter& rhs) const {
            return here == rhs.here;
        }
        
        bool operator!=(const SSLL_Const_Iter& rhs) const {
            return here != rhs.here;
        }
    }; // end SSLL_Iter
}
#endif /* _SSLL_H_ */

