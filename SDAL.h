//
//  SDAL.h
//  COP3503
//
//  Created by Nicholas Alvarez on 9/8/17.
//  Copyright © 2017 Nick Alvarez. All rights reserved.
//

#ifndef SDAL_h
#define SDAL_h
#include<iostream>
#include <stdexcept>
#include <exception>
#include"List.h"

// Template and Class SDAL

namespace cop3530
{
    
    template <typename DataT>
    class SDAL_Iter;
    
    template <typename L>
    class SDAL : public List<L>{
    public:
        // type aliases for prettier code
        using self_type = SDAL;
        using self_reference = SDAL&;
        
    public:
        
        // constructors
        SDAL(size_t size);
        SDAL();
        
        // copy constructor/assignment
        SDAL( const SDAL<L>& src );
        SDAL<L>& operator=( const SDAL<L>& src );
        
        // move constructor/assignment
        SDAL( const SDAL<L>&& src );
        //     SDAL<L>& operator=( const SDAL<L>&& src );
        SDAL<L>& operator=( SDAL<L>&& src );
        
        // destructor
        ~SDAL();
        
        //--------------------------------------------------
        // type aliases
        //--------------------------------------------------
        //using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = L;
        using iterator = SDAL_Iter<L>;
        using const_iterator = SDAL_Iter<L const>;
        
        // iterators over a non-const List
        // derefereced iterator can be read or written
        iterator begin() { return SDAL_Iter<L>(&state); }
        iterator end() { return SDAL_Iter<L>(NULL); }
        
        // iterators over a const List
        // dereferenced valued can be read but not written
        const_iterator begin() const { return SDAL_Iter<L>(&state); }
        const_iterator end()   const { return SDAL_Iter<L>(NULL); }
        
        // ---------------------------------------------------
        // -----------------  METHODS ------------------------
        // ---------------------------------------------------
        L pop_back()  override;
        L pop_front()  override;
        bool is_empty() const override;
        bool is_full() const override;
        size_t length() const override;
        L remove( size_t position )  override;
        L item_at( size_t position ) const  override;
        void push_back(  const L& element )  override;
        void push_front( const L& element )  override;
        L peek_back()  override;
        L peek_front()  override;
        void clear()  override;
        bool contains(const L& element,bool equals(const L& x, const L& y)) const  override;
        void insert( const L element, size_t position )  override;
        L replace(const L& element, size_t position )  override;
        L *contents()  override;
        std::ostream& print(std::ostream& out) const  override;
        
        struct Node {
            L*     array;      // Pointer to Array of Type L
            size_t arraysize;  // current depth of array
            size_t tail;       // Tail - number of entries in array
        };
        
    private:
        //------------------- Variables -------------------------
        // Container for array and state; packaging this way enables iterator functionality
        Node   state;
        size_t strt_arraysize;
        
        //----- Have to create a expand array and decrease array ----------
        
        // Whenever an item is added and the backing array is full,
        // allocate a new array 150% the size of the original,
        // copy the items over to the new array, and deallocate the original one.
        L*  expandarray(L array[]){
            
            // Compute the size of the new array
            size_t biggersize = state.arraysize * 1.5;
            
            // Create new Array where expanded is pointer to New Array
            L* expanded = new L[biggersize];
            
            // Get Current length of array (number of Entries)
            size_t cur_length = length();
            
            // Copy the current array to new Expanded Array
            // Note: Only copy the current elements
            for (size_t i=0; i<cur_length; i++ ) {
                expanded[i] = array[i];
            }
            
            // Copy the current array to new Expanded Array
            //for(size_t i=0; i<biggersize; i++ ){
            //
            // if ( i < state.arraysize )
            //    expanded[i] = array[i];
            // else
            //    expanded[i] = 0;
            //
            //}
            
            // Delete Current Array
            delete[] array;
            state.arraysize=biggersize;
            
            // Return pointer to the new Expanded Array
            return expanded;
            
        }
        
        
        // Because we don't want the list to waste too much memory,
        // whenever the array's size is ≥ 100 slots and fewer than half the slots are used,
        // allocate a new array 75% the size of the original, copy the items over to the
        // new array, and deallocate the original one.
        L* decrease(L array[]){
            
            // Compute the size of the new array
            size_t smallersize = state.arraysize * .75;
            
            // Create new Array where decreaed is pointer to New Array
            L* decreased= new L[smallersize];
            
            for(size_t i =0; i< smallersize; i++){
                decreased[i]=array[i];
            }
            
            // Delete current Array
            delete[] array;
            state.arraysize=smallersize;
            
            // Return pointer to Decresed Array
            return decreased;
            
        }
        
    };
    
    
    
    // constructor
    template <typename L>
    SDAL<L>::SDAL(size_t size) {
        // Create array of Type L[Size]
        // NOTE: array = pointer to the first addres &L[0]
        state.array = new L[size];
        state.arraysize=size;
        state.tail=0;
        strt_arraysize = size;
    }
    
    template <typename L>
    SDAL<L>::SDAL() {
        // Create array of Type L[50]
        // NOTE: array = pointer to the first addres &L[0]
        state.array = new L[50];
        state.arraysize=50;
        state.tail=0;
        strt_arraysize = 50;
    }
    
    // Copy Constructor  Example Usage: SDAL dst(src);
    template <typename L>
    SDAL<L>::SDAL( const SDAL<L>& src )
    {
        state.array = new L[src.state.arraysize];
        state.arraysize=src.state.arraysize;
        state.tail=src.state.tail;
        // Copy contents of array
        for ( size_t i=0; i<src.state.tail; i++)
            state.array[i]=src.state.array[i];
    }
    
    // Copy Assignment Example Usage: SSLL dst;
    //                                ....do a bunch of stuff with dst...
    //                                ....now I don't need dst anymore, so reuse it...
    //                                dst= src;
    template <typename L>
    SDAL<L>& SDAL<L>::operator=( const SDAL<L>& src )
    {
        if (state.arraysize != src.state.arraysize) {
            delete [] state.array;
            state.array = new L[src.state.arraysize];
            state.arraysize=src.state.arraysize;
        }
        state.tail=src.state.tail;
        // Copy contents of array
        for ( size_t i=0; i<src.state.tail; i++)
        {
            state.array[i]=src.state.array[i];
        }
        return *this;
    }
    
    // Move constructor
    template <typename L>
    SDAL<L>::SDAL( const SDAL<L>&& src )
    {
        state.array = src.state.array;
        state.arraysize=src.state.arraysize;
        state.tail=src.state.tail;
    }
    
    // Move Assignment
    template <typename L>
    //  SDAL<L>& SDAL<L>::operator=( const SDAL<L>&& src )
    SDAL<L>& SDAL<L>::operator=( SDAL<L>&& src )
    {
        if ( state.array != nullptr ) {
            delete [] state.array;
        }
        state.array = src.state.array;
        state.arraysize=src.state.arraysize;
        state.tail=src.state.tail;
        // set source variables to NULL since
        // move has taken ownership
        src.state.array = nullptr;
        return *this;
    }
    
    
    // Destructor
    template <typename L>
    SDAL<L>::~SDAL() {
        if ( state.array != nullptr ) {
            delete[] state.array;
        }
    }
    
    
    //--------------------------------------------------------------
    //-----------------------METHODS--------------------------------
    //--------------------------------------------------------------
    
    //------------ IS_FULL()-----------------------
    template<typename L>
    bool SDAL<L>::is_full() const{
        return false; //Never full
    }
    
    
    // -----------IS_EMPTY()---------------------
    template<typename L>
    bool SDAL<L>::is_empty() const {
        
        if(state.tail==0){
            return true;
        }
        return false;
        
    }
    
    
    //----------------LENGTH()------------------
    template<typename L>
    size_t SDAL<L>::length() const {
        size_t size= state.tail;
        return size;
        
    }
    
    
    
    //------------------POP_BACK()-----------------
    template<typename L>
    L SDAL<L>:: pop_back() {
        if(length()==0){
            throw std::runtime_error("SDAL<E>.pop_back(): No elements to pop");
        }
        L data = state.array[state.tail-1];
        state.tail--;
        
        // Need to check if the array needs to be decreased
        // Note: Length = state.tail
        if( state.arraysize>=(2*strt_arraysize) && (state.tail<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        return data;
        
    }
    
    
    
    // --------------------POP_FRONT()-------------------
    template<typename L>
    L SDAL<L>::pop_front(){
        
        if(length()==0){
            throw std::runtime_error("SDAL<E>.pop_front(): No elements to pop (Empty List)");
        }
        L data=state.array[0];
        size_t x =0;
        while(x<state.arraysize-1){
            state.array[x]=state.array[x+1];
            x++;
        }
        state.tail--;
        
        // if fewer than 1/2 the array is being used then
        // allocate new array which is 75% of current array
        // tail < arraysize * 0.50
        
        // Need to check if the array needs to be decreased
        // Note: Length = state.tail
        if( state.arraysize>=(2*strt_arraysize) && (state.tail<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        
        return data;
        
    }    
    
    //-----------------REMOVE (size_t position)-------------------
    template<typename L>
    L SDAL<L>::remove( size_t position) {
        
        if(position<0 || position >=length()){
            throw std::runtime_error("SDAL<E>.remove(): Position out of range");
        }
        L data = state.array[position];
        size_t x=position;
        
        while(x<state.tail-1){
            // Move all entries up a position starting at postion
            state.array[x]=state.array[x+1];
            x++;
        }
        
        // Decrement Tail
        state.tail--;
        
        // Need to check if the array needs to be decreased
        // Note: Length = state.tail
        if( state.arraysize>=(2*strt_arraysize) && (state.tail<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        return data;
        
    }
    
    
    
    //----------- ITEM_AT( size_t position) ------------------
    template<typename L>
    L SDAL<L>::item_at( size_t position ) const {
        
        if(position<0 || position >=length()){
            throw std::runtime_error("SDAL<E>.item_at(): Position out of range");
        }
        return state.array[position];
        
    }
    
    
    
    //-------------- PEEK BACK --------------------------
    template<typename L>
    L SDAL<L>::peek_back() {
        
        if ( length() == 0 ) {
            throw std::runtime_error("SDAL<E>.peek_back(): Empty List");
        }
        return  state.array[length()-1];
        
    }
    
    
    
    //--------- PEEK_FRONT(size_T position) --------------
    template<typename L>
    L SDAL<L>::peek_front() {
        
        if ( length() == 0  ) {
            throw std::runtime_error("SDAL<E>.peek_front(): Empty List");
        }
        return state.array[0];
        
    }
    
    
    //------------------ CLEAR() --------------------------
    template<typename L>
    void SDAL<L>::clear() {
        
        // Just reset the number of items in array
        state.tail=0;
        
    }
    
    
    
   
    
    template<typename L>
    void SDAL<L>::push_back( const L& element ) {
        
        // Check if Array is full
        if(state.tail==state.arraysize){
            // Need to expand Array Size since Full
            state.array=expandarray(state.array);
        }
        
        // Array expanded write new Element
        state.array[state.tail]=element;
        state.tail++;
        
    }
    
    
    
   
    
    template<typename L>
    void SDAL<L>::push_front( const L& element ) {
        
        // Check if Array is full
        if(state.tail==state.arraysize){
            state.array=expandarray(state.array);
        }
        
        for( size_t x=state.tail; x>0; x--) {
            // Move elements downward ( Array[tail] = Array[tail-1] )
            // To make room at addr[0] for new element
            state.array[x]=state.array[x-1];
        }
        
        // Write new Element to array
        state.array[0] = element;
        state.tail++;
        
    }
    
    
    
    
    
    
    
    template<typename L>
    void SDAL<L>:: insert( L element, size_t position ) {
        
        if (position<0 || position > length() ){
            throw std::runtime_error("SDAL<E>.insert(): Out of range position");
        }
        
        
        if ( position == length() )
        {
            // then inserting at the back of the list
            this->push_back( element );
            return;
        }
        
        
        // Check if Array is full
        if(state.tail==state.arraysize){
            // Need to expand Array Size since Full
            state.array=expandarray(state.array);
        }
        
        
        // Only need to move the elements required not the full array
        //for(size_t x=arraysize-1; x>position;x--){
        //   array[x]=array[x-1];
        //}
        for( size_t x=state.tail; x>position; x--) {
            // Move elements downward ( Array[tail] = Array[tail-1] )
            // To make room at addr[positon] for new element
            state.array[x]=state.array[x-1];
        }
        
        // write new element
        state.array[position]=element;
        state.tail++;
        
    }
    
    
    
    
    //---------- replace(const L& element,size_t position ) -------------------
    template<typename L>
    L SDAL<L>:: replace(const L& element, size_t position ) {
        if(position<0 || position >=length()){
            
            throw std::runtime_error("SDAL<E>.replace(): Out of range position");
            
        }
        
        L data = state.array[position];
        state.array[position]=element;
        
        return data;
        
    }
    
    
    //------ contains(const L& element,bool equals(const L& a, const L& b)) const ----
    template<typename L>
    bool SDAL<L>:: contains(const L& element,bool equals(const L& x, const L& y)) const {
        
        if(length()==0){
            throw std::runtime_error("SDAL<E>.contains(): Empty List");
        }
        
        for(size_t x=0; x< state.arraysize; x++){
            if(equals(state.array[x],element)){
                return true;
            }
        }
        
        return false;
    }
    
    
    
    
    //------- std::ostream& SDAL<L>::print(std::ostream &out) -------------
    template<typename L>
    std::ostream&  SDAL<L>::print(std::ostream &out) const{
        
        if(state.tail==0){
            
            out<<"<empty list>"<<std::endl;
            
            return out;
        }
        out<<"[";
        for(size_t x=0; x<state.tail; x++){
            out<<state.array[x];
            if(state.tail!= x+1){
                
                out<<",";
            }
            
            
        }
        out<<"]"<<std::endl;
        
        return out;
        
    }
    
    
    //---------------- contents() -------------------------
    template<typename L>
    L* SDAL<L>::contents() {
        
        if(length()==0){
            throw std::runtime_error("SDAL<E>.contents(): Empty List");
        }
        
        size_t cur_length;
        cur_length = length();
        
        L *newarray = new L[length()];
        for(size_t x=0; x<cur_length; x++){
            newarray[x]=state.array[x];
        }
        
        // BUG - array created was of size length but writing arraysize
        //       arraysize > length   potentially
        //for(size_t x=0; x< state.arraysize; x++){
        //   newarray[x]=state.array[x];
        //}
        return newarray;
        
    }
    
}


namespace cop3530
{
    
    template <typename DataT>
    class SDAL_Iter
    {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = SDAL_Iter;
        using self_reference = SDAL_Iter&;
        
    private:
        typename SDAL<DataT>::Node* here;
        int current_idx;
        
    public:
        explicit SDAL_Iter( typename SDAL<DataT>::Node* start = nullptr ) : here( start ), current_idx( 0 ) {}
        // Copy Constructor
        SDAL_Iter( const SDAL_Iter& src ) : here( src.here ), current_idx( src.current_idx ) {}
        
        reference operator*() const { return here->array[current_idx]; }
        pointer operator->() const { return &here->array[current_idx]; }
        
        // Assignment to Source
        self_reference operator=( SDAL_Iter<DataT> const& src ) {
            here = src.here;
            current_idx = src.current_idx;
            return *this;
        }
        
        // Increment - so array indx incremented
        self_reference operator++() {
            current_idx++;
            if (current_idx == here->tail)
                here = NULL;
            return *this;
        } // preincrement
        
        // post increment itr++   return curent itr .. then increment itr
        // pre-increment ++itr    increment itr first then return data at itr
        
        // Increment - so array indx incremented
        self_type operator++(int) {
            SDAL_Iter<DataT> temp(*this);
            current_idx++;
            if (current_idx == here->tail)
                here = NULL;
            return temp;
        } // postincrement
        
        bool operator==( SDAL_Iter<DataT> const& rhs ) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return true;
            } else {
                return (here == rhs.here) && (current_idx == rhs.current_idx);
            }
        }
        bool operator!=( SDAL_Iter<DataT> const& rhs) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return false;
            } else {
                return (here != rhs.here) || (current_idx != rhs.current_idx);
            }
        }
    }; // end SDAL_Iter
}



#endif /* SDAL_h */

