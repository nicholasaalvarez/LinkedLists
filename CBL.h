//
//  CBL.h
//  COP3530
//
//  Created by Nicholas Alvarez on 11/8/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//

#ifndef CBL_h
#define CBL_h
#include<iostream>
#include <stdexcept>
#include <exception>
#include"List.h"

// Template and Class SDAL
namespace cop3530
{
    
    template <typename DataT>
    class CBL_Iter;
    
    template <typename L>
    class CBL : public List<L>{
    public:
        // type aliases for prettier code
        using self_type = CBL;
        using self_reference = CBL&;
        
    public:
        
        // constructors
        CBL(size_t size);
        CBL();
        
        // copy constructor/assignment
        CBL( const  CBL<L>& src );
        CBL<L>& operator=( const  CBL<L>& src );
        
        // move constructor/assignment
        CBL( const CBL<L>&& src );
        //      CBL<L>& operator=( const  CBL<L>&& src );
        CBL<L>& operator=( CBL<L>&& src );
        
        // destructor
        ~CBL();
        
        //--------------------------------------------------
        // type aliases
        //--------------------------------------------------
        //using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = L;
        using iterator = CBL_Iter<L>;
        using const_iterator = CBL_Iter<L const>;
        
        // iterators over a non-const List
        // derefereced iterator can be read or written
        iterator begin() { return CBL_Iter<L>(&state); }
        iterator end() { return CBL_Iter<L>(NULL); }
        
        // iterators over a const List
        // dereferenced valued can be read but not written
        const_iterator begin() const { return CBL_Iter<L>(state); }
        const_iterator end()   const { return CBL_Iter<L>(NULL); }
        
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
            L*      array;      // Pointer to Array of Type L
            size_t  arraysize;  // current depth of array
            size_t  tail;       // Tail buffer array index
            size_t  head;       // Head buffer array index
        };
        
    private:
        //------------------- Variables -------------------------
        // Container for array and state; packaging this way enables iterator functionality
        Node    state;
        size_t  strt_arraysize; // Starting Array Size
        
        //----- Have to create a expand array and decrease array ----------
        
        // Whenever an item is added and the backing array is full,
        // allocate a new array 150% the size of the original,
        // copy the items over to the new array, and deallocate the original one.
        L*  expandarray(L array[]){
            
            // Compute the size of the new array
            size_t biggersize = state.arraysize * 1.5;
            
            // Create new Array where expanded is pointer to New Array
            L* expanded = new L[biggersize];
            
            // Copy the current array to new Expanded Array
            //for(size_t i=0; i<biggersize; i++ ){
            //
            //   if ( i < state.arraysize )
            //      expanded[i] = array[i];
            //   else
            //      expanded[i] = 0;
            //
            //}
            
            size_t cur_length = length();
            size_t wrptr = 0;  // Put tail at adrs0 of new array
            size_t rdptr = state.tail;
            
            // Need to Copy old array into new smaller array
            // Start at Tail Location -> Head Location (Using Length)
            for ( size_t i=0; i<cur_length; i++)
            {
                // Need to move elements to new array
                //std::cout <<"CBL: Copy Array Wrptr= "<<wrptr<<" RdPtr = "<<rdptr<<" Data[Rdptr]= "<<array[rdptr]<<std::endl;
                expanded[wrptr] = array[rdptr];
                wrptr++;
                rdptr = ( rdptr + 1 ) % state.arraysize;
            }
            
            // Delete Current Array
            delete[] array;
            state.arraysize=biggersize;
            
            // Now need to translate Head and Tail
            // to the new array that was copied
            state.head = cur_length;
            state.tail = 0;
            
            // Return pointer to the new Expanded Array
            return expanded;
            
        }
        
        
        // Because we don't want the list to waste too much memory,
        // whenever the array's size is ≥ (2*Strt_Size) and fewer than half the slots are used,
        // allocate a new array 75% the size of the original, copy the items over to the
        // new array, and deallocate the original one.
        L* decrease(L array[]) {
            
            //std::cout <<"CBL: Entering DECREASE  Head = "<<state.head<<" Tail = "<<state.tail<<std::endl
            //std::cout <<"ArraySize = "<<state.arraysize<<std::endl;
            //std::cout <<"CBL: Entering DECREASE  length = "<<length()<<" StrtSize "<<strt_arraysize<<std::endl;
            
            // Compute the size of the new array (75% of current array)
            size_t smallersize = state.arraysize * .75;
            
            // Create new Array where decrease is pointer to New Array
            L* decreased= new L[smallersize];
            
            size_t cur_length = length();
            size_t wrptr = 0;  // Put tail at adrs0 of new array
            size_t rdptr = state.tail;
            
            // Need to Copy old array into new smaller array
            // Start at Tail Location -> Head Location (Using Length)
            for ( size_t i=0; i<cur_length; i++)
            {
                // Need to move elements to new array
                //std::cout <<"CBL: Copy Array Wrptr= "<<wrptr<<" RdPtr = "<<rdptr<<" Data[Rdptr]= "<<array[rdptr]<<std::endl;
                decreased[wrptr]=array[rdptr];
                wrptr++;
                rdptr = ( rdptr + 1 ) % state.arraysize;
            }
            
            // Delete current Array
            delete[] array;
            state.arraysize=smallersize;
            
            // Now need to translate Head and Tail
            // to the new array that was copied
            state.head = cur_length;
            state.tail = 0;
            
            //std::cout <<"CBL: Exit DECREASE  Head = "<<state.head<<" Tail = "<<state.tail<<std::endl;
            //std::cout <<" ArraySize = "<<state.arraysize<<std::endl;
            //std::cout <<"CBL: Exit DECREASE  Length = "<<length()<<std::endl;
            // Return pointer to Decresed Array
            return decreased;
            
        }
        
        
        // Method to translate a List Position -> Indx
        // using the CBL current head and tail pointers (indexes)
        size_t compute_indx( size_t position ) const {
            
            // ----------------------------------------------------------------------------
            // Array Indx         [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
            // current Tail/Head       T                           H  -> points to next wr
            // Element posiiton        6   5   4   3   2   1   0
            //                         This example has 7 entries
            // ----------------------------------------------------------------------------
            // Array INdx         [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
            // current Tail/Head       H       T
            // Element posiiton    0           7   6   5   4   3   2   1
            //                         This example has 8 entries
            // ----------------------------------------------------------------------------
            size_t indx     = state.tail;  // Indx     = Tail Index
            size_t pos_indx = length()-1;  // Pos_indx = Element Position at Tail Index
            while ( pos_indx != position )
            {
                indx = (indx + 1) % state.arraysize;  // Increment Tail
                pos_indx--;                           // Derement positon
            }
            return indx;
            
        }
        
    };
    
    
    // Constructor - size provided
    template <typename L>
    CBL<L>::CBL(size_t size) {
        // Create array of Type L[Size]
        // NOTE: array = pointer to the first addres &L[0]
        state.array = new L[size];
        state.arraysize=size;
        state.tail=0;
        state.head=0;
        strt_arraysize = size;
    }
    
    // Constructor - Start with fixed size 50
    template <typename L>
    CBL<L>::CBL() {
        // Create array of Type L[50]
        // NOTE: array = pointer to the first addres &L[0]
        state.array = new L[50];
        state.arraysize=50;
        state.tail=0;
        state.head=0;
        strt_arraysize = 50;
    }
    
    // Copy Constructor  Example Usage: CBL dst(src);
    template <typename L>
    CBL<L>::CBL( const CBL<L>& src )
    {
        state.array = new L[src.state.arraysize];
        state.arraysize=src.state.arraysize;
        state.head=src.state.head;
        state.tail=src.state.tail;
        // Note: Assign Start Arraysize to the
        //       current source array size
        strt_arraysize = src.state.arraysize;
        
        // Copy entire contents of array
        //for ( size_t i=0; i<src.state.tail; i++)
        for ( size_t i=0; i<state.arraysize; i++)
            state.array[i]=src.state.array[i];
    }
    
    
    // Copy Assignment Example Usage: CBL dst;
    //                                ....do a bunch of stuff with dst...
    //                                ....now I don't need dst anymore, so reuse it...
    //                                dst = src;
    template <typename L>
    CBL<L>& CBL<L>::operator=( const CBL<L>& src )
    {
        // Check to see if need to create new array
        // if the array size are different
        if (state.arraysize != src.state.arraysize) {
            delete [] state.array;
            state.array = new L[src.state.arraysize];
            state.arraysize=src.state.arraysize;
        }
        // Assign Head and Tail array indexes
        state.head=src.state.head;
        state.tail=src.state.tail;
        // Note: Assign Start Arraysize to the
        //       current source array size
        strt_arraysize = src.state.arraysize;
        
        // Copy contents of array
        //for ( size_t i=0; i<src.state.tail; i++)
        for ( size_t i=0; i<state.arraysize; i++)
            state.array[i]=src.state.array[i];
        
        return *this;
    }
    
    
    // Move constructor
    template <typename L>
    CBL<L>::CBL( const CBL<L>&& src )
    {
        //std::cout <<"CBL: Entering Move Constructor ..."<<std::endl;
        // take over the source array
        state.array     = src.state.array;
        state.head      = src.state.head;
        state.tail      = src.state.tail;
        state.arraysize = src.state.arraysize;
        strt_arraysize  = src.state.arraysize;
        
        // Find an article in Google that described this issue
        // Release any allocated memory from the source object so
        // that the destructor does not free the memory more than once
        //src.array = nullptr;
    }
    
    
    // Move Assignment
    template <typename L>
    //  CBL<L>& CBL<L>::operator=( const CBL<L>&& src )
    CBL<L>& CBL<L>::operator=( CBL<L>&& src )
    {
        
        // delete our current array since no longer
        // needed will be using the source array
        if ( state.array != nullptr ) {
            delete [] state.array;
        }
        
        // now use the array from source
        state.array     = src.state.array;
        state.head      = src.state.head;
        state.tail      = src.state.tail;
        state.arraysize = src.state.arraysize;
        strt_arraysize  = src.state.arraysize;
        
        // Find an article in Google that described this issue
        // Set all source object variables to NULL since the
        // move has taken ownerhsip of them
        src.state.array = nullptr;
        return *this;
    }
    
    
    // Destructor
    template <typename L>
    CBL<L>::~CBL() {
        if ( state.array != nullptr ) {
            delete[] state.array;
        }
    }
    
    
    //--------------------------------------------------------------
    //-----------------------METHODS--------------------------------
    //--------------------------------------------------------------
    
    //------------ IS_FULL()-----------------------
    template<typename L>
    bool CBL<L>::is_full() const{
        return false; //Never full
    }
    
    
    // -----------IS_EMPTY()---------------------
    template<typename L>
    bool CBL<L>::is_empty() const {
        
        if(length()==0){
            return true;
        }
        return false;
        
    }
    
    
    //----------------LENGTH()------------------
    template<typename L>
    size_t CBL<L>::length() const {
        
        size_t indx = state.tail;
        size_t size = 0;
        
        while ( indx != state.head )
        {
            // ----------------------------------------------------------------------------
            // array            [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
            // remove at             T                           H  -> points to next wr
            // Element posiiton      6   5   4   3   2   1   0
            //                       This example has 7 entries
            // ----------------------------------------------------------------------------
            // array            [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
            // remove at             H       T
            // Element posiiton  0           7   6   5   4   3   2   1
            //                       This example has 8 entries
            // ----------------------------------------------------------------------------
            indx = (indx+1)%state.arraysize;  // modulo math for wrap around
            size++;
        }
        // now... size indicates how many elements in array
        return size;
    }
    
    
    //------------------ POP_BACK() -----------------
    template<typename L>
    L CBL<L>:: pop_back() {
        
        if ( length()==0 ) {
            throw std::runtime_error("CBL.pop_back(): No elements to pop (Empty List) "); // throw an exception
        }
        
        // Return Data at the Tail Position
        L data = state.array[state.tail];
        // Need to move tail forward - do modulu math for wrap around
        state.tail = (state.tail + 1) % state.arraysize;
        
        // Need to check if the array needs to be decreased
        if( state.arraysize>=(2*strt_arraysize) && (length()<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        return data;
        
    }
    
    
    
    // --------------------POP_FRONT()-------------------
    template<typename L>
    L CBL<L>::pop_front(){
        
        if ( length()==0 ){
            throw std::runtime_error("CBL<E>.pop_front(): No elements to pop (Empty List) ");
        }
        
        // Decrement Head pointer first since head pointer
        // points to the next Write Posiiton
        
        //std::cout <<"CBL: Pop_Front Length = "<<length()<<" Head = "<<state.head<<std::endl;
        
        // Need to guard for wrap around
        if ( state.head == 0 )
            state.head = state.arraysize-1;   // Wrap Around case
        else
            state.head--;
        
        //std::cout <<"CBL: Pop_Front Length = "<<length()<<" Head = "<<state.head<<std::endl;
        
        // Now look up the data store in Head position
        
        // Front of the CBL List is the head ptr
        L data=state.array[state.head];
        
        // if arraysize > 2 * Starting Array Size "AND"
        // if fewer than 1/2 the array is being used then
        // allocate new array which is 75% of current array
        
        // Need to check if the array needs to be decreased
        if( state.arraysize>=(2*strt_arraysize) && (length()<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        return data;
        
    }
    
    
    //----------------- REMOVE( size_t position ) -------------------
    template<typename L>
    L CBL<L>::remove( size_t position) {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CBL<E>.remove(): Empty List");
        }
        
        if ( position<0 || position >= length()){
            throw std::runtime_error("CBL<E>.remove(): Position out of range");
        }
        
        // -------------------------------------------------------
        //  -- Example current Length=7 and remove position 4
        // array      [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
        // remove at       T       R                   H -> points to next write position
        // position        6   5   4   3   2   1   0   X
        //  ---> after remove operation
        // position            5   4   3   2   1   0   X
        // remove at           T   R                   H
        //
        // // current length = 7
        // positon = 4 / indx = 3
        // so need indx 3 <- indx 2
        // so need indx 2 <- indx 1
        // number of array elements to move = length - (position+1)
        // elements to move = 7 - 5 = 2
        //  tail_m1 <= tail then increment address
        // -------------------------------------------------------
        
        // Debug Prints
        //std::cout <<"CBL: Remove Strt : Head = "<<state.head<<" Tail = "<<
        //    state.tail<<" ArraySize = "<<state.arraysize<<std::endl;
        //std::cout <<"CBL: Remove Strt : Length = "<<length()<<std::endl;
        
        // Declaration for return data
        L data;
        
        // If position is at tail location then same as Pop Back
        if ( position == length()-1 )
        {
            // Note: Array size management will be done by POP_BACK
            //std::cout <<"CBL: Remove : executing pop_back "<<std::endl;
            data = this->pop_back();
            return data;
        }
        
        // If position is at head location then same as Pop front
        if ( position == 0 )
        {
            // Note: Array size management will be done by POP_FRONT
            //std::cout <<"CBL: Remove : executing pop_front "<<std::endl;
            data = this->pop_front();
            return data;
        }
        
        
        // Since position not equal to Tail or Head then need
        // to remove element somewhere in the list between Head -> Tail
        //
        // Translate position to array index for Insert Position
        size_t remove_pos_indx = compute_indx ( position );
        //std::cout <<"CBL: Remove : Remove pos "<<position<<" Indx = "<<remove_pos_indx<<std::endl;
        
        // Compute number of elements to move downwards
        // Starting writing at Tail-1 Indx
        size_t elements_to_move = length() - (position+1);
        //std::cout <<"CBL: Remove : elements to move "<<elements_to_move<<std::endl;
        
        // Reading data from remove position and this will be
        // the location where the write takes place since
        // will need to move the array elements up
        // Data at remove position
        data = state.array[remove_pos_indx];
        
        // Compute Tail+1 Indx
        size_t tail_p1_indx = state.tail;
        tail_p1_indx = ( tail_p1_indx + 1 ) % state.arraysize;
        
        //std::cout <<"CBL: Remove : tail_p1_indx "<<tail_p1_indx<<std::endl;
        
        // Now will need to move elements upward
        // start at array[tail_p1_indx] = array[tail]
        // start at tail_p1_indx+1 <-- tail+1
        // start at tail_p1_indx+2 <-- tail+2
        //
        // so need indx 3 <- indx 2
        // so need indx 2 <- indx 1    Cur Tail = 1
        //   wrptr     rdptr
        //  tail_p1 <= tail then increment address
        size_t wrptr = remove_pos_indx;
        size_t rdptr = remove_pos_indx;
        // Subtract 1 from RdPtr Rmv_pos_indx - 1
        if ( rdptr == 0 )
            rdptr = state.arraysize-1;   // Wrap Around case
        else
            rdptr--;
        
        //std::cout <<"CBL: MODIFING ARRAY !!!!!  "<<std::endl;
        
        // Now need to move all entries up
        // Move elements upward ( Array[tail_m1_indx] = Array[tail] )
        // To make room at addr[positon] for new element
        for( size_t x=0; x<elements_to_move; x++) {
            
            //std::cout <<"REMOVE CBL: wrptr="<<wrptr<<" RdPtr="<<rdptr<<" Rd Data= "<<state.array[rdptr]<<std::endl;
            state.array[wrptr]=state.array[rdptr];
            wrptr = rdptr;
            // Subtract 1 from RdPtr
            if ( rdptr == 0 )
                rdptr = state.arraysize-1;  // Wrap Around case
            else
                rdptr--;
        }
        
        // Update Tail Pointer Upward
        state.tail = tail_p1_indx;
        //std::cout <<"CBL: Remove Before Decrease : Length = "<<length()<<std::endl;
        
        // Check if array needs to be decreased since removing an element
        if( state.arraysize>=(2*strt_arraysize) && (length()<(state.arraysize*0.5)) ){
            state.array=decrease(state.array);
        }
        
        return data;
        
    }
    
    
    //----------- ITEM_AT(size_t position) ------------------
    template<typename L>
    L CBL<L>::item_at( size_t position ) const {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CBL<E>.item_at(): Empty List");
        }
        
        if ( position<0 || position >= length()){
            throw std::runtime_error("CBL<E>.item_at(): Position out of range");
        }
        
        // Need to translate position -> to array index since CBL not fixed array
        size_t indx = compute_indx ( position );
        /*
         // -----------------------------------------------------------------------
         // Not sure why the call above does not work.....
         size_t indx     = state.tail;  // Indx     = Tail Index
         size_t pos_indx = length()-1;  // Pos_indx = Element Position at Tail Index
         while ( pos_indx != position )
         {
         indx = (indx + 1) % state.arraysize;  // Increment Tail
         pos_indx--;                           // Derement positon
         }
         // -----------------------------------------------------------------------
         // now indx is the array element for position
         */
        
        // Now .. indx contains the array indx corresponding to position
        return state.array[indx];
        
    }
    
    
    //------------------- PEEK BACK --------------------------
    template<typename L>
    L CBL<L>::peek_back() {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CBL<E>.peek_back(): Empty List");
        }
        return state.array[state.tail]; // Tail is back in circular buffer
        
    }
    
    
    //------------- PEEK_FRONT(size_t position) --------------
    template<typename L>
    L CBL<L>::peek_front() {
        
        if ( length() == 0  ) {
            throw std::runtime_error("CBL<E>.peek_front(): Empty List");
        }
        
        // Need to decrement current Head indx to before accessing Array
        size_t rdptr = state.head;
        
        // Need to guard for wrap around
        if ( rdptr == 0 )
            rdptr = state.arraysize-1;   // Wrap Around case
        else
            rdptr--;
        
        return state.array[rdptr];
        
    }
    
    
    //------------------ CLEAR () --------------------------
    template<typename L>
    void CBL<L>::clear() {
        
        // Reset both Head and Tail Pointers
        state.head=0;
        state.tail=0;
        
    }
    
    
    //---------- push_back( const L& element ) --------------
    template<typename L>
    void CBL<L>::push_back( const L& element ) {
        
        // Check if Array is full
        if( length() == state.arraysize-1 ) {
            // Need to expand Array Size since Full
            state.array=expandarray(state.array);
        }
        
        // ------------------------------------------------------------
        //  ---- Example for Push_Back current Length=7
        //  ---> Before Push operation
        // Array Indx    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
        // before push        T                           H -> points to next write position
        // position List      6   5   4   3   2   1   0   X
        //  ---> After Push operation
        // Array Indx    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
        // position       7   6   5   4   3   2   1   0   X
        // remove at      T                               H
        // ------------------------------------------------------------
        
        // Compute new Tail Position
        // Need to guard for wrap around
        if ( state.tail == 0 )
            state.tail = state.arraysize-1;   // Wrap Around case
        else
            state.tail--;
        
        //for( size_t x=state.head+1; x>0; x--) {
        // Move elements downward ( Array[tail] = Array[tail-1] )
        // To make room at addr[0] for new element
        //   state.array[x]=state.array[x-1];
        //}
        
        // Write new Element to CBL Array Tail position
        state.array[state.tail]=element;
        
    }
    
    
    
    //-------------- push_front( const L& element ) -------------------
    template<typename L>
    void CBL<L>::push_front( const L& element ) {
        
        // Check if Array is full
        if ( length() == state.arraysize-1 ) {
            state.array=expandarray(state.array);
        }
        
        // Write new Element into current CBL Head Position
        state.array[state.head]=element;
        // Increment Head Index
        state.head= (state.head+1)%state.arraysize;  // Modulo Math
        
        // Debug Prints
        // std::cout <<"CBL:push_front: Head = "<<state.head<<" Tail = "<<
        //     state.tail<<" ArraySize = "<<state.arraysize<<std::endl;
    }
    
    
    //---------------- Insert ( const L& element ) -------------------
    template<typename L>
    void CBL<L>:: insert( L element, size_t position ) {
        
        if(position<0 || position > length()) {
            throw std::runtime_error("CBL<E>.insert(): Out of range position");
        }
        
        
        if ( position == length() )
        {
            // then inserting at the back of the list
            this->push_back( element );
            return;
        }
        
        // Check if Array is full
        if ( length() == state.arraysize-1 ) {
            // Need to expand Array Size since Full
            state.array=expandarray(state.array);
        }
        
        
        // --------------------------------------------------------------------------------------
        //    ---- Example for Insert (position=4) current Length=7
        //    ---> Before Insert operation
        //   Array Indx    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
        //   before push        T       I                   H -> points to next write position
        //   position List      6   5   4   3   2   1   0   X
        //    ---> After Push operation
        //   Array Indx    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9]
        //   position       7   6   5   4   3   2   1   0   X
        //   remove at      T           I                   H
        //
        //    Inserting at positin 4 -> Indx[3]
        //    So need   Indx[3] = New Element   Pos=4
        //              Indx[2] = Indx[3]       Pos=5
        //              Indx[1] = Indx[2]       Pos=6  Indx 1 = current Tail
        //              Indx[0] = Indx[1]       Pos=7  Indx 0 = New Tail (current Tail-1)
        // --------------------------------------------------------------------------------------
        //  So need a loop that goes from Tail Position -> Insert Position
        //  Tail Position+1 = length() ->  Insert Position
        //   for example         7,  6,  5,  4
        //   Array Indx          0,  1,  2,  3
        
        // Translate position to array index for Insert Position
        size_t insert_pos_indx = compute_indx ( position );
        //std::cout <<"CBL: Insert  Length = "<<length()<<" Position = "<<position<<" Indx = "<<insert_pos_indx<<std::endl;
        //std::cout <<"CBL: Insert = Head "<<state.head<<" Data = "<<state.array[insert_pos_indx]<<std::endl;
        
        // Compute number of elements to move downwards
        // Starting writing at Tail-1 Indx
        size_t elements_to_move = length() - position;
        //std::cout <<"CBL: Insert = elements to move "<<elements_to_move<<std::endl;
        
        // Compute Tail-1 Indx
        size_t tail_m1_indx = state.tail;
        if ( tail_m1_indx == 0 )
            tail_m1_indx = state.arraysize-1;   // Wrap Around case
        else
            tail_m1_indx--;
        
        //std::cout <<"CBL: Insert = tail_m1_indx "<<tail_m1_indx<<std::endl;
        
        // Now will need to move elements downward
        // start at tail_m1_indx   <-- tail
        // start at tail_m1_indx+1 <-- tail+1
        // start at tail_m1_indx+2 <-- tail+2
        size_t wrptr = tail_m1_indx;
        size_t rdptr = state.tail;
        
        // Move elements downward ( Array[tail_m1_indx] = Array[tail] )
        // To make room at addr[positon] for new element
        for( size_t x=0; x<elements_to_move; x++) {
            //std::cout <<"CBL: Insert = wrptr= "<<wrptr<<" Rdptr ="<<rdptr<<" DAta = "<<state.array[rdptr]<<std::endl;
            state.array[wrptr]=state.array[rdptr];
            wrptr = ( wrptr + 1 ) % state.arraysize;  // Modulo Math
            rdptr = ( rdptr + 1 ) % state.arraysize;  // Modulo Math
        }
        
        // Write New Element at Insert Position Indx
        state.array[insert_pos_indx]=element;
        // Update Tail Pointer downward
        state.tail = tail_m1_indx;
        
    }
    
    
    
    //---------- Replace (const L& element, size_t position ) -------------------
    template<typename L>
    L CBL<L>:: replace(const L& element, size_t position ) {
        
        if (position<0 || position >=length()){
            throw std::runtime_error("CBL<E>.replace(): Out of range position");
        }
        
        size_t rdptr = compute_indx ( position );
        L data = state.array[rdptr];
        state.array[rdptr]=element;
        
        return data;
    }
    
    
    //------ Contains (const L& element,bool equals(const L& a, const L& b)) const ----
    template<typename L>
    bool CBL<L>:: contains(const L& element,bool equals(const L& x, const L& y)) const {
        
        if ( length()==0 ){
            throw std::runtime_error("CBL<E>.contains): Empty List ");
        }
        
        size_t rdptr = state.tail;
        
        // Check if Data in Array
        while ( rdptr != state.head ) {
            
            //std::cout <<"CBL: Equals Rdptr = "<<rdptr<<" Data = "<<state.array[rdptr]<<std::endl;
            if(equals(state.array[rdptr],element)){
                return true;
            }
            
            // Decrement Rd Index
            rdptr = ( rdptr + 1 ) % state.arraysize;
        }
        return false;
        
    }
    
    
    
    //------- std::ostream& CBL<L>::print(std::ostream &out) -------------
    template<typename L>
    std::ostream&  CBL<L>::print(std::ostream &out) const{
        
        if(length()==0){
            out<<"<empty list>"<<std::endl;
            return out;
        }
        
        // Compute Head-1 Index
        size_t rdptr = state.head;
        if ( rdptr == 0 )
            rdptr = state.arraysize-1;   // Wrap Around case
        else
            rdptr--;
        
        // Compute Tail-1 Index
        size_t stop_indx  = state.tail;
        if ( stop_indx == 0 )
            stop_indx = state.arraysize-1;   // Wrap Around case
        else
            stop_indx--;
        
        out<<"[";
        // Now proceed from Head-1 -> Tail-1
        while ( rdptr != stop_indx)
        {
            
            //std::cout <<"OSTREAM CBL: RdPtr = "<<rdptr<<" Rd Data = "<<state.array[rdptr]<<std::endl;
            out<<state.array[rdptr];
            if( rdptr != state.tail ){
                out<<",";
            }
            
            // Decrement RdPtr (Head) back towards the Tail
            if ( rdptr == 0 )
                rdptr = state.arraysize-1;   // Wrap Around case
            else
                rdptr--;
            
        }
        out<<"]"<<std::endl;
        return out;
        
    }
    
    
    //---------------- contents() -------------------------
    template<typename L>
    L* CBL<L>::contents() {
        
        if ( length()==0 ){
            throw std::runtime_error("CBL<E>.contents): Empty List ");
        }
        
        // Declare New Array
        L *newarray = new L[length()];
        
        size_t wrptr = 0;
        size_t rdptr = state.head;
        
        // Comptute Head-1 Index
        if ( rdptr == 0 )
            rdptr = state.arraysize-1;   // Wrap Around case
        else
            rdptr--;
        
        // Compute Tail-1 Index
        size_t stop_indx  = state.tail;
        if ( stop_indx == 0 )
            stop_indx = state.arraysize-1;   // Wrap Around case
        else
            stop_indx--;
        
        // No Copy Elements to new Array
        while ( rdptr != stop_indx )
        {
            // Copy elements to new array
            newarray[wrptr]=state.array[rdptr];
            wrptr++;
            
            // Comtute Head-1 Index
            // NOTE: Need to decrement Head Indx since want to
            //       write Data at Head Indx first and Tail Indx Last
            if ( rdptr == 0 )
                rdptr = state.arraysize-1;   // Wrap Around case
            else
                rdptr--;
        }
        return newarray;
        
    }
    
}

//
//  CBL_Iter.h
//  COP3530
//
//  Created by Nicholas Alvarez on 11/8/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//
namespace cop3530
{
    
    template <typename DataT>
    class CBL_Iter
    {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = CBL_Iter;
        using self_reference = CBL_Iter&;
        
    private:
        typename CBL<DataT>::Node* here;
        size_t current_idx;
        size_t last_idx;
        
    public:
        
        explicit CBL_Iter( typename CBL<DataT>::Node* start = nullptr ) : here( start ), current_idx( 0 ), last_idx ( 0 )  {}
        
        // Copy Constructor
        CBL_Iter( const CBL_Iter& src ) : here( src.here ), current_idx( src.current_idx ), last_idx ( src.last_idx )  {}
        
        reference operator*() const { return here->array[current_idx]; }
        pointer operator->() const { return &here->array[current_idx]; }
        
        self_reference operator=( CBL_Iter<DataT> const& src ) {
            
            // Assign NODE
            here        = src.here;
            
            //current_idx = src.current_idx;
            //last_idx    = src.last_idx;
            // Need to subract one from Head since for CBL the Head
            // location is the first empty location to write.
            // So decrement Head by 1 for actual data head location
            if ( here->head == 0 )
                current_idx = src.here->arraysize - 1;
            else
                current_idx = src.here->head- 1;
            
            // The last indx is the Tail - 1 locationn since Tail
            // indx actually contains the last data of the list
            if ( here->tail == 0 )
                last_idx = src.here->arraysize - 1;
            else
                last_idx = src.here->tail - 1;
            
            return *this;
        }
        
        self_reference operator++() {
            
            // For CBL need to decrement Current Indx (Head) and
            // check when index equals last_indx (Tail-1)
            if ( current_idx == 0 )
                current_idx = here->arraysize - 1;
            else
                current_idx = current_idx - 1;
            
            // Check if at last read
            if ( current_idx == last_idx ) {
                here = NULL;
            }
            
            return *this;
        } // preincrement
        
        
        self_type operator++(int) {
            
            // Store object first since post increment
            CBL_Iter<DataT> temp(*this);
            
            // For CBL need to decrement Current Indx (Head) and 
            // check when index equals last_indx (Tail-1) 
            // NOTE: Need to guard for wrap back around when the 
            //       index is at zero.  If it is, set to arraysize - 1
            if ( current_idx == 0 )
                current_idx = here->arraysize - 1; 
            else
                current_idx = current_idx - 1; 
            
            // Check if at last read 
            if ( current_idx == last_idx ) {
                here = NULL;
            }
            
            return temp;
        } // postincrement
        
        
        bool operator==( CBL_Iter<DataT> const& rhs ) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return true;
            } else {
                return (here == rhs.here) && (last_idx == rhs.last_idx);
            }
        }
        
        bool operator!=( CBL_Iter<DataT> const& rhs) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return false;
            } else {
                return (here != rhs.here) || (last_idx != rhs.last_idx);
            }
        }
        
    }; // end CBL_Iter
}

#endif /* CBL_h */
