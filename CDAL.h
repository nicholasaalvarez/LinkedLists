//
//  CDAL.h
//  COP3503
//
//  Created by Nicholas Alvarez on 9/8/17.
//  Copyright © 2017 Nick Alvarez. All rights reserved.
//

#ifndef CDAL_h
#define CDAL_h
#include<iostream>
#include <stdexcept>
#include <exception>
#include "List.h"


// Template and Class CDAL
// NOTE: Must only have one empty array in the chain
namespace cop3530
{
    
    
    template <typename DataT>
    class CDAL_Iter;
    
    template <typename L>
    class CDAL : public List<L>{
        
    public:
        // type aliases for prettier code
        using self_type = CDAL;
        using self_reference = CDAL&;
        
    public:
        
        // constructor
        CDAL();
        
        // copy constructor/assignment
        CDAL( const CDAL<L>& src );
        CDAL<L>& operator=( const CDAL<L>& src );
        
        // move constructor/assignment
        CDAL( const CDAL<L>&& src );
        //      CDAL<L>& operator=( const CDAL<L>&& src );
        CDAL<L>& operator=( CDAL<L>&& src );
        
        // destructors
        ~CDAL();
        
        //--------------------------------------------------
        // Iterator - type aliases
        //--------------------------------------------------
        //using size_t = std::size_t;
        using value_type = L;
        using iterator = CDAL_Iter<L>;
        using const_iterator = CDAL_Iter<L const>;
        
        // iterators over a non-const List
        // dereferenced iterator can be read or written
        iterator begin() { return CDAL_Iter<L>(head); }
        iterator end() { return CDAL_Iter<L>(NULL); }
        
        // iterators over a const List
        // dereferenced iterator can be read but not written
        const_iterator begin() const { return CDAL_Iter<L const>(head); }
        const_iterator end() const { return CDAL_Iter<L const>(NULL); }
        
        
        //-------------------------------------------------------
        //------------------ METHODS ----------------------------
        //-------------------------------------------------------
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
        
        // Used for test
        //size_t get_countnodes () { return countnodes; }
        
        struct Node {
            L*      data;
            Node*   next;
            size_t  tail;
        };
        
    private:
        Node*  head;        // Head Node
        size_t countnodes;  // num_of_nodes
        
        //------------------ Create Node Method ----------------------------
        // Method addNode() - this method creates a new node
        // Add node method  - Each array in the node has 50 slots
        // The chain starts off containing just a single Node / array
        // When the last array element is used (filled), and a new item is
        // inserted, then a new Node / array is added to the chain.
        void addNode() {
            
            countnodes++;       // increment number of nodes
            Node* temp=head;    // Set ptr temp to head node
            while( temp->next != NULL ) {
                temp=temp->next;
            }
            // now temp points to the last node
            Node* newnode = new Node();  // Create New Node
            newnode->next = NULL;        // Set next ptr to NULL
            newnode->data = new L[50];   // Set Data to new Array[50]
            temp->next=newnode;          // Link in new node
            
        }
        
        //---- --------------- Deallocate Method ----------------------------
        // Because we don't want the list to waste too much memory, whenever
        // the number of unused Nodes > 1, then remove the excess Nodes.
        // NOTE: At MAX can only have one unused Node.
        void deallocate() {
            
            // Note: countnodes = Total number of Nodes
            //std::cout <<" Entering deallocate... "<<std::endl;
            size_t nodesused=1;
            size_t tempindex= (head->tail)-1;
            
            // Compute the actual number of Nodes Used based
            // on the Tail which contains number of entries in List
            while(tempindex>49){
                tempindex=tempindex-50;
                nodesused++;
            }
            
            // Compute number of unused nodes
            size_t unusednodes = countnodes - nodesused;
            
            if ( unusednodes > 2 )
            {
                // Need to remove all of the unused nodes
                // Can only have one unused node MAX
                size_t nodestoremove = unusednodes-1;
                Node* temp = head;
                
                // Proceed through the Used Nodes
                for(size_t i=0; i<nodesused-1; i++){
                    temp=temp->next;
                }
                // now...Temp -> points UnusedNode1
                
                // Now Proceed to remove the number of Nodes
                // so that only one Unused Node remains.
                for(size_t x=0; x< nodestoremove; x++){
                    
                    // deleting (Points to UnusedNode2)
                    Node* deleting = temp->next;
                    
                    // temp->next (Now points to the next unused Node)
                    // Note: if removing the last node then
                    //       temp->next->next should equal to NULL
                    temp->next= temp->next->next;
                    
                    // Remove both the array and the Node
                    delete [] deleting->data;
                    delete deleting;
                    countnodes--;                 // Decrement Total Number of Nodes
                    unusednodes--;                // Decrement Total Unused Nodes
                }
                
            }
            
        }
        
        
    };
    
    
    // Constructor
    template <typename L>
    CDAL<L>::CDAL()
    {
        head = new Node();         // Create initial node
        head->data = new L[50];    // set data ptr to new array[50]
        head->next = NULL;         // set next ptr to NULL
        head->tail = 0;            // tail 0 represents Empty LIST - number of entries
        countnodes = 1;            // Number of Nodes = 1
    }
    
    // Copy Constructor  Example Usage: CDAL dst(src);
    template <typename L>
    CDAL<L>::CDAL( const CDAL<L>& src )
    {
        
        // Need to do a Deep copy - Make new nodes
        if (src.head == NULL)
        {
            head       = new Node();   // Create initial node
            head->data = new L[50];    // set data ptr to new array[50]
            head->next = NULL;         // set next ptr to NULL
            countnodes = 1;            // Number of Nodes = 1
        }
        else
        {
            
            Node* SrcPtr;               // will be used to store src Nodes
            SrcPtr = src.head;          // Set to Sourc List head node
            
            head       = new Node();    // Create Head Node
            head->data = new L[50];     // set data ptr to new array[50]
            head->next = NULL;          // set next ptr to NULL
            head->tail = src.head->tail; // get tail - number of entries
            countnodes = 1;             // Number of Nodes (Init with 1)
            
            // Set Indx to Tail-1 (number of entries)
            size_t index= (head->tail)-1;
            
            // Compute the actual number of Nodes Used based
            // on the Tail which contains number of entries in List
            while(index>49){
                index=index-50;
                countnodes++;
            }
            
            // Make a Copy of all the Source Nodes
            size_t numelements = (head->tail)-1;
            size_t maxindx = 49;
            
            Node* CurNode=head;
            for ( size_t i=0; i<countnodes; i++)
            {
                // Need to make new Node/Array on 2nd+ Passes etc...
                if ( i != 0 )
                {
                    // Make a New Node / Array and link in with PrevNode
                    Node* newnode = new Node();  // Create New Node
                    newnode->next = NULL;        // Set next ptr to NULL
                    newnode->data = new L[50];   // Set Data to new Array[50]
                    CurNode->next=newnode;       // Set Next Ptr in Current Node to new node
                    CurNode = newnode;           // Now set CurNode to point to new node created
                }
                
                // Determine number of elements to copy for Node
                if ( numelements > 49 ){
                    maxindx = 49;  // set to max
                    numelements = numelements - 49;
                }
                else {
                    maxindx = numelements;
                    numelements = 0;
                }
                
                // Now copy all of the elements to array for current Node
                for ( size_t indx=0; indx<=maxindx; indx++) {
                    // copy the array data
                    CurNode->data[indx]=SrcPtr->data[indx];
                }
                
                // Proceed to next Node
                if ( SrcPtr->next != NULL )
                    SrcPtr = SrcPtr->next;
                
            }
            // Set Tail to the last node created
            //std::cout<<"Copy Const.. tail->next = "<<tail->next<<std::endl;
            
        }
    }
    
    
    
    // Copy Assignment Example Usage: CDAL dst;
    //                                ....do a bunch of stuff with dst...
    //                                ....now I don't need dst anymore, so reuse it...
    //                                dst = src;
    template <typename L>
    CDAL<L>& CDAL<L>::operator=( const CDAL<L>& src )
    {
        
        // Need to deallocate all of the current Nodes / Arrays
        clear(); // NOTE: clears all nodes except the head node
        
        // Clear the head Node and array
        if ( head->data != nullptr ) {
            delete [] head->data;  // Delete Array (Head Node)
        }
        delete head;              // Delete Head Node
        
        // Now..Need to do a Deep copy - Make new nodes
        if (src.head == NULL)
        {
            head       = new Node();   // Create initial node
            head->data = new L[50];    // set data ptr to new array[50]
            head->next = NULL;         // set next ptr to NULL
            countnodes = 1;            // Number of Nodes = 1
        }
        else
        {
            
            Node* SrcPtr;               // will be used to store src Nodes
            SrcPtr = src.head;          // Set to Sourc List head node
            
            head       = new Node();    // Create Head Node
            head->data = new L[50];     // set data ptr to new array[50]
            head->next = NULL;          // set next ptr to NULL
            head->tail = src.head->tail; // get tail - number of entries
            countnodes = 1;             // Number of Nodes (Init with 1)
            
            // Set Indx to Tail-1 (number of entries)
            size_t index= (head->tail)-1;
            
            // Compute the actual number of Nodes Used based
            // on the Tail which contains number of entries in List
            while(index>49){
                index=index-50;
                countnodes++;
            }
            
            // Make a Copy of all the Source Nodes
            size_t numelements = (head->tail)-1;
            size_t maxindx = 49;
            
            Node* CurNode=head;
            for ( size_t i=0; i<countnodes; i++)
            {
                // Need to make new Node/Array on 2nd+ Passes etc...
                if ( i != 0 )
                {
                    // Make a New Node / Array and link in with PrevNode
                    Node* newnode = new Node();  // Create New Node
                    newnode->next = NULL;        // Set next ptr to NULL
                    newnode->data = new L[50];   // Set Data to new Array[50]
                    CurNode->next=newnode;       // Set Next Ptr in Current Node to new node
                    CurNode = newnode;           // Now set CurNode to point to new node created
                }
                
                // Determine number of elements to copy for Node
                if ( numelements > 49 ){
                    maxindx = 49;  // set to max
                    numelements = numelements - 49;
                }
                else {
                    maxindx = numelements;
                    numelements = 0;
                }
                
                // Now copy all of the elements to array for current Node
                for ( size_t indx=0; indx<=maxindx; indx++) {
                    // copy the array data
                    CurNode->data[indx]=SrcPtr->data[indx];
                }
                
                // Proceed to next Node
                if ( SrcPtr->next != NULL )
                    SrcPtr = SrcPtr->next;
                
            }
            
        }
        // Return Reference to destination
        return *this;
    }
    
    
    // Move constructor
    template <typename L>
    CDAL<L>::CDAL( const CDAL<L>&& src )
    {
        
        // Set all Head Nodes to Source Head Node
        head       = src.head;       // set to Source Head Node
        
        // Need to compute number of Nodes
        countnodes = 1;              // Number of Nodes (Init with 1)
        size_t tmpindx = head->tail;
        // Compute number of Nodes
        while ( tmpindx > 50 )
        {
            countnodes++;
            tmpindx = tmpindx - 50;  // Every Node contains 50 Elements
        }
    }
    
    
    // Move Assignment
    template <typename L>
    //  CDAL<L>& CDAL<L>::operator=( const CDAL<L>&& src )
    CDAL<L>& CDAL<L>::operator=( CDAL<L>&& src )
    {
        
        // Need to deallocate all of the current Nodes / Arrays
        clear(); // NOTE: clears all nodes except the head node
        
        // Clear the head Node and array
        if ( head->data != nullptr ) {
            delete [] head->data;  // Delete Array (Head Node)
        }
        delete head;              // Delete Head Node
        
        // assign head to source Head Node
        head = src.head;
        
        // Need to compute number of Nodes
        countnodes = 1;              // Number of Nodes (Init with 1)
        size_t tmpindx = head->tail;
        // Compute number of Nodes
        while ( tmpindx > 50 )
        {
            countnodes++;
            tmpindx = tmpindx - 50;  // Every Node contains 50 Elements
        }
        
      
        // Set source variables to NULL since move has
        // taken ownership of them
        src.head = nullptr;
        return *this;
    }
    
    
    // destructors
    template <typename L>
    CDAL<L>::~CDAL() {
        
        clear(); // clears all nodes except the head node
        
        // Clear the head node and array
        if ( head != nullptr ) {
            if ( head->data != nullptr ) {
                delete [] head->data;
            }
        }
        if ( head != nullptr ) {
            delete head;
        }
        
    }
    
    
    //--------------------------------------------------------------
    //-------------------- METHODS ---------------------------------
    //--------------------------------------------------------------
    
    //--------------- IS_FULL() ------------------
    template<typename L>
    bool CDAL<L>::is_full() const {
        return false;
    }
    
    
    // -------------- IS_EMPTY() -----------------
    template<typename L>
    bool CDAL<L>::is_empty() const {
        
        if ( length() == 0 ) {
            return true;
        }
        return false;
    }
    
    
    //--------------- LENGTH() --------------------
    template<typename L>
    size_t CDAL<L>::length() const {
        return head->tail;
    }
    
    
    //----------------POP_BACK()-------------------
    template<typename L>
    L CDAL<L>:: pop_back()  {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CDAL<E>.pop_back(): Empty List ");
        }
        
        size_t popindex = (head->tail)-1;  // Set element to remove -1 to get array indx
        head->tail = (head->tail)-1;    // update tail - decrement
        //tail--;                       // update tail - decrement
        
        // Find the number of the node that contains pop element
        size_t nodes=0;
        while( popindex>49 ) {
            popindex=popindex-50;
            nodes++;
        }
        
        // now progress to the node that contains the pop element
        Node* temp = head;
        for(size_t i=0; i<nodes; i++){
            temp=temp->next;
        }
        
        L* arraypop = temp->data;     // Access array of the node
        L data = arraypop[popindex];  // set return data to current element
        if ( length() != 0  )
            deallocate();              // call deallocate to check
        return data;
        
    }
    
    
    // --------------------POP_FRONT()--------------------------//
    template<typename L>
    L CDAL<L>::pop_front(){
        
        if ( length() == 0 ) {
            throw std::runtime_error("CDAL<E>.pop_front(): Empty List ");
        }
        
        L data = head->data[0];
        size_t i =0;
        Node* temp=head;
        Node* nextnode;
        
        size_t count=0;
        while(count< ((head->tail)-1) ) {
            
            if(i==49){
                // Get Next Node
                nextnode=temp->next;
                L datashiftleft=nextnode->data[0];
                // Write first entry of next node to
                // last entry of current node
                temp->data[49]=datashiftleft;
                // Update pointer to next node
                temp=temp->next;
                i=0;
            }
            else{
                // Shift data up
                temp->data[i]=temp->data[i+1];
                i++;
            }
            count++;
            
        }
        
        // Decrement Tail
        head->tail = (head->tail)-1;
        
        // If length >0 call deallocate method
        if ( length() != 0  )
            deallocate();
        
        return data;
        
    }
    
    
    //------------------- REMOVE(siz_t position) ----------------------
    template<typename L>
    L CDAL<L>::remove( size_t position) {
        
        if ( length()==0 || position<0 || position >= length()) {
            throw std::runtime_error("CDAL<E>.remove(): Empty List");
        }
        
        if ( position<0 || position >= length()) {
            throw std::runtime_error("CDAL<E>.remove(): Position out of range");
        }
        
        size_t removingindex = position;
        size_t current= position;
        size_t nodestogothrough = 0;
        size_t tail;
        // get the tail from Head Node
        tail = head->tail;
        
        while(removingindex>49){
            
            removingindex=removingindex-50;
            nodestogothrough++;
            
        }
        Node* temp=head;
        for(size_t i=0; i<nodestogothrough;i++){
            
            temp=temp->next;
            
        }
        // Temp now points to node that contains element to be removed
        // removingindex -> index for current array
        L* removingarray = temp->data;
        L dataremove = removingarray[removingindex];
        size_t i= removingindex;
        Node* nextnode;
        while(current<tail-1){
            
            if (i==49) {
                
                nextnode=temp->next;
                L datashiftleft= nextnode->data[0];
                temp->data[49]=datashiftleft;
                temp=temp->next;
                i=0;
                
            }
            else{
                
                temp->data[i]=temp->data[i+1];
                i++;
                
            }
            current++;
        }
        tail--;
        head->tail = tail;
        
        // If length >0 call deallocate method
        if ( length() != 0  )
            deallocate();
        
        return dataremove;
    }
    
    
    //---------------- ITEM_AT(size_t position) ---------------------
    template<typename L>
    L CDAL<L>::item_at( size_t position ) const {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CDAL<E>.item_at(): Empty List");
        }
        
        if( position<0 || position >= length()){
            throw std::runtime_error("CDAL<E>.item_at(): Position out of range");
        }
        
        size_t nodestogothrough = 0;
        while(position>49){
            position=position-50;
            nodestogothrough++;
        }
        Node* temp = head;
        for(size_t i=0; i<nodestogothrough;i++){
            temp=temp->next;
        }
        // Now temp is pointing to current Node
        L* arrayposition = temp->data;
        return arrayposition[position];
        
    }
    
    
    //---------------- PEEK BACK --------------------------
    template<typename L>
    L CDAL<L>::peek_back() {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CDAL<E>.peek_back(): Empty List");
        }
        
        // Set temp node pointer to head node
        Node* temp = head;
        
        // Now go to last node and set temp ptr and array
        for ( size_t node=1; node<countnodes; node++ )
        {
            temp = temp->next;           // update ptr to next node
        }
        // now temp is pointing to last node
        L* node_array = temp->data;  // set ptr to array
        
        // Compute the current max element for current node based on tail
        // Will need to subtract offset based on node number
        size_t max_element = ((head->tail)-1) - ((countnodes-1)*50);
        return node_array[max_element]; // return item at tail node
        
    }
    
    
    //--------------- PEEK_FRONT( ) ----------------------
    template<typename L>
    L CDAL<L>::peek_front() {
        
        if ( length() == 0  ) {
            throw std::runtime_error("CDAL<E>.peek_front(): Empty List");
        }
        
        // Set temp node pointer to head node
        L* node_array = head->data;  // get ptr to head array
        return node_array[0];        // Return data element[0] of head node
        
    }
    
    
    //----------------- CLEAR() ----------------------------
    template<typename L>
    void CDAL<L>::clear() {
        
        
        if ( head==nullptr){
            return;
        }
        
        if(head->tail==0){
            // Empty List
            return;
        }
        
        // NOTE: This Method deletes all Nodes / Arrays
        //       excepth the Head Node.  It does reset
        //       Head Node to Null and Tail = 0.
        // Delete all nodes except initial node
        Node* next_node = head->next;
        for ( size_t node=0; node<countnodes; node++ )
        {
            
            if ( node == 0 ) {
                // set Next Node to Null and Tail=0
                head->next = NULL;
                head->tail = 0;
            }
            else {
                
                // ptr deleting = Node to be deleted
                Node* deleting = next_node;
                if ( node != countnodes-1 )
                {
                    // Then -> Not the final node so need to increment pointer
                    next_node = next_node->next;
                }
                delete [] deleting->data;
                delete deleting;
                
            }
            
        }
        // reset countnodes back to 1
        countnodes = 1;
        
    }
    
    
    //------------ push_back( const L&  element )) -----------
    template<typename L>
    void CDAL<L>::push_back( const L& element ) {
        
        // Check if new node needs to be added
        size_t indx;
        // Modules X=0  Mode(0/50)  =  0
        // Modules X=1  Mode(1/50)  =  1
        // Modules X=49 Mode(49/50) = 49
        indx = ((head->tail)-1)%50;
        if ( head->tail != 0 && ( indx==49) ) {
            addNode();
        }
        
        head->tail = head->tail + 1;
        //tail++;
        size_t pushposition = (head->tail)-1;
        size_t nodestogothrough = 0;
        while(pushposition>49){
            pushposition=pushposition-50;
            nodestogothrough++;
        }
        Node* temp = head;
        for(size_t i=0; i<nodestogothrough; i++){
            temp=temp->next;
        }
        L* arrayinsert = temp->data;
        arrayinsert[pushposition]=element;
        
    }
    
    
    //------------ push_front( const L& element ) ---------------------
    template<typename L>
    void CDAL<L>::push_front( const L& element ) {
        
        // When we push into front we know all elements will need to be shifted
        // down by 1.   If an array is full, meaning all elements of array are
        // used then we need to take last element (49) of Node N and copy it to
        // the first element location of Node N+1, etc...
        
        // Need to check if a new Node needs to be added
        // if current element ends at array element [49] then need new Node
        // Can use modulus or compute as follows:
        
        // Compute the current in use max element for current node
        // subtract offset based on node number
        //max_element = (tail-1) - ((countnodes-1)*50);
        
        // Using Modulus      if ( (tail-1)%50)==49 ) then ends on array element 49
        // Using max_element  if ( max_element ) then ends on array element 49
        //
       
        
        // Check if New Node needs to be added
        size_t indx;
        indx = ((head->tail)-1)%50;
        if ( (head->tail != 0) && (indx==49) ) {
            // Need to Add a new Node since adding a new element to list
            // and no current locations available in last node's array.
            addNode();
        }
        
        // Setup Node pointer to start at the head node
        Node* temp = head;
        L* insertarray= temp->data;
        L data0;
        L data49 =0 ;
        
        // Now loop through all of the Nodes and move the data
        // Example: if countnodes=3  then node 0,1,2
        for ( size_t node=0; node<countnodes; node++ )
        {
            
            if ( node==0 )
            {
                // Store the endpoints for the current array of node
                data0  = element;
                data49 = insertarray[49];    // Current node array[49]
            }
            else
            {
                // Shift data for all other nodes
                data0  = data49;   // Prev Node's Array element[49]
                data49 = insertarray[49]; // Store current array element[49];
            }
            
            // Need to shift array down so need a loop that cycles through
            // all current elements. So for each node willMOVE  move 49 elements.
            // Note: Blindly moving all 49 elements (0->48) independent of tail location.
            for ( size_t i=49; i>=1; i-- )
            {
                // shift array right towards bottom
                // [49]<-[48];  [48]<-[47] .... [1]<-[0];
                insertarray[i] = insertarray[i-1];
            }
            // Now array has been shift so write new element to array[0]
            insertarray[0] =  data0;  // This is new element for node 0 and
            // PrevNode Array[49] for all other nodes
            
            // Update Node Pointer to Next Node if more nodes still need to be process
            // if node == countnodes-1 then at Max Node no need to increment pointer
            if ( node != (countnodes-1) )
            {
                temp = temp->next;       // update ptr to next node
                insertarray= temp->data; // set insertarray to new array
            }
            
        }
        
        // Now update the tail location since all elements have been moved
        head->tail = (head->tail) + 1;
        //tail++;
        return;
        
    }
    
    
    //------------------ INSERT(const L& Element, size_t position) --------------------------
    template<typename L>
    void CDAL<L>:: insert( L element, size_t position ) {
        
        if( position<0 || position>length()){
            throw std::runtime_error("CDAL<E>.insert(): Position out of range");
        }
        
        if ( position == length() )
        {
            // then inserting at the back of the list
            this->push_back( element );
            return;
        }
        
        
        size_t indx;
        size_t indx_strt;
        indx = ((head->tail)-1)%50;
        if ( head->tail != 0 && ( indx==49) ) {
            // Need to add a new node since at end of current array
            addNode();
        }
        
        // compute insertion node where 1st node=0, 2nd node=1
        size_t indexinsertion   = position;
        size_t    insert_node_num  = 0;   // 1st node
        while(indexinsertion>49) {
            indexinsertion=indexinsertion-50;
            insert_node_num++;
        }
       
        
        Node* temp = head;
        for(size_t i=0; i<insert_node_num; i++){
            temp=temp->next;
        }
        // Temp points to insertion node
        L* arrayinsert = temp->data;
        
        // Data0 is the current insertion element
        L data0;
        L data49 = 0;
        
        // Now loop through all of the Nodes and move the data
        // Example: if countnodes=3  then node 0,1,2
        size_t loopnum = 0;
        for ( size_t node=insert_node_num; node<countnodes; node++ )
        {
            
            if ( loopnum == 0 )
            {
                // First Time through the loop so store the element at the
                // insertion position for the current array at this starting node.
                data0  = element;          // store element   t at insertion
                data49 = arrayinsert[49];  // store last element just in case more nodes
            }
            else
            {
                // Shift data for all other nodes
                data0  = data49;          // Prev Node's Array element[49]
                data49 = arrayinsert[49]; // Store current array element[49];
            }
            
            // When loopnum = 0 need to shift array down starting at indexinsertion + 1
            if ( loopnum == 0 )
                indx_strt = indexinsertion+1;
            else
                indx_strt = 1;
            
            // Need to shift array down from indexposition all the way to end of array.
            // for-loop starts at bottom element and works upwards to indexinsertion + 1
            for ( size_t i=49; i>=indx_strt; i-- )
            {
                // shift array right towards bottom
                // [49]<-[48];  [48]<-[47] .... [1]<-[0];
                arrayinsert[i] = arrayinsert[i-1];
            }
            
            // Now array has been shift so write new element to array[0]
            if ( loopnum == 0 )
                // if first time through the loop need to write new element
                arrayinsert[indexinsertion] = element; // This is new element for node 0 and
            else
                arrayinsert[0] =  data0;
            
            // Update Node Pointer to Next Node if more nodes still need to be process
            // if node == countnodes-1 then at Max Node no need to increment pointer
            if ( node != (countnodes-1) )
            {
                // More nodes to process
                temp        = temp->next; // update ptr to next node
                arrayinsert = temp->data; // set insertarray to new array
            }
            
        }
        
        // Now update the tail location since all elements have been moved
        head->tail = (head->tail) +1;
        //tail++;
        
        return;
        
    }
    
   
    
    
    //-------------- replace(const L& element,size_t position ) ---------------------------------
    template<typename L>
    L CDAL<L>:: replace(const L& element, size_t position ) {
        
        if( length()==0 || position<0 || position>=length()) {
            throw std::runtime_error("CDAL<E>.replace(): Position out of range or list empty");
        }
        size_t countnode=0;
        while(position>49){
            position=position-50;
            countnode++;
        }
        Node* temp=head;
        for(size_t i = 0; i<countnode;i++){
            temp=temp->next;
        }
        // Now temp points to node where element needs to be replaced
        
        L* arrayatposition = temp->data;
        L data = arrayatposition[position];  // Get current data at position
        arrayatposition[position]=element;   // store new element
        
        return data;
        
    }
    
    
    //--------- contains(const L& element,bool equals(const L& a, const L& b)) const ---------
    template<typename L>
    bool CDAL<L>:: contains(const L& element,bool equals(const L& x, const L& y)) const {
        
        if ( length() == 0 ) {
            throw std::runtime_error("CDAL<E>.contains(): Empty List ");
        }
        
        Node* temp    = head;  // Temp pointer to head
        L* node_array = temp->data;
        
        size_t max_element = head->tail;
        size_t indx=0;
        
        // Now loop through all of the Nodes and move the data
        //for ( size_t node=0; node<countnodes; node++ ) {
        for ( size_t i=0; i<max_element; i++ ) {
            
            // i represent list entry o -> Tail
            
            // compute the array index
            indx = i % 50;
            
            //std::cout <<" Array Check i= "<<i<<" Indx = "<<indx<<std::endl;
            
            if ( (i!=0) && (indx==0) )
            {
                // Starting New Node ....
                temp      = temp->next;   // update ptr to next node
                node_array= temp->data;   // set insertarray to new array
            }
            
            //std::cout <<" Array Check indx= "<<indx<<" DAta = "<<node_array[indx]<<std::endl;
            // Check each element of Node array if it contains element
            if(equals(node_array[indx],element)) {
                return true;
            }
            
        }
        return false;
        
        
    }
    
    
    //----------------------- std::ostream&  CDAL<L>::print(std::ostream &out)---------------------------
    template<typename L>
    std::ostream&  CDAL<L>::print(std::ostream &out) const{
        
        if(length()==0){
            out<<"<empty list>"<< std::endl;
            return out;
        }
        
        Node* temp=head;
        size_t x=0;
        size_t current=0;
        out<< "[";
        
        while(current<head->tail){
            
            if(x==49){
                out<< temp->data[x];
                temp=temp->next;
                x=0;
            }
            else{
                out<<temp->data[x];
                x++;
            }
            
            if(current+1 !=head->tail){
                out<<",";
            }
            current++;
            
        }
        out<<"]"<<std::endl;
        return out;
        
    }
    
    
    //-----------------------contents()--------------------------------------
    template<typename L>
    L *CDAL<L>::contents() {
        
        if( length()==0 ){
            throw std::runtime_error("CDAL<E>.contents(): Empty List ");
        }
        
        L *copyarray = new L[length()];  // Create new array that contains all nodes
        Node* temp = head;              // Temp pointer to head
        L* node_array = temp->data;
        size_t max_element;
        
        // Now loop through all of the Nodes and move the data
        for ( size_t node=0; node<countnodes; node++ ) {
            
            // Compute the current in use max element for current node
            // subtract offset based on node number
            if ( node == (countnodes-1) ) {
                // Last Node
                max_element = ((head->tail)-1) - ((countnodes-1)*50);
            }
            else
            {
                // All elements of array used since not last node
                max_element = 49;
            }
            
            for ( size_t i=0; i<=max_element; i++ )
            {
                // copy Node array to copy array
                copyarray[i+(node*50)] = node_array[i];
            }
            
            // Update Node Pointer to Next Node if more nodes still need to be process
            // if node == countnodes-1 then at Max Node no need to increment pointer
            if ( node != (countnodes-1) )
            {
                temp      = temp->next;   // update ptr to next node
                node_array= temp->data;   // set insertarray to new array
            }
            
        }
        return copyarray;
        
    }
    
    
}


namespace cop3530
{
    
    template <typename DataT>
    class CDAL_Iter
    {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataT;
        using reference = DataT&;
        using pointer = DataT*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = CDAL_Iter;
        using self_reference = CDAL_Iter&;
        
    private:
        typename CDAL<DataT>::Node* here;
        size_t current_idx;
        size_t tail;
        
    public:
        explicit CDAL_Iter( typename CDAL<DataT>::Node* start = nullptr ) : here( start ), current_idx( 0 ), tail ( 0 )  {}
        // Copy Constructor
        CDAL_Iter( const CDAL_Iter& src ) : here( src.here ), current_idx ( src.current_idx), tail ( src.tail ) {}
        
        reference operator*() const { return here->data[current_idx]; }
        pointer operator->() const { return &here->data[current_idx]; }
        
        self_reference operator=( CDAL_Iter<DataT> const& src ) {
            here = src.here;
            current_idx = src.current_idx;
            tail        = src.tail;
            return *this;
        }
        
        self_reference operator++() {
            current_idx++;
            tail++;
            if ( tail == here->tail) {
                here = NULL;
            }
            else if ( current_idx == 50 ) 
            {
                // Proceed to next Node 
                here = here->next; 
                // reset array indx back to 0 (New Array / New Node)
                current_idx = 0; 
            }
            return *this;
        } // preincrement
        
        self_type operator++(int) {
            CDAL_Iter<DataT> temp(*this);
            current_idx++;
            tail++;
            if ( tail == here->tail ) {
                here = NULL;
            }
            else if ( current_idx == 50 ) 
            {
                // Proceed to next Node 
                here = here->next; 
                // reset array indx back to 0 (New Array / New Node)
                current_idx = 0; 
            }
            return temp;
        } // postincrement
        
        
        bool operator==( CDAL_Iter<DataT> const& rhs ) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return true;
            } else {
                return (here == rhs.here) && (tail == rhs.tail);
            }
        }
        
        bool operator!=( CDAL_Iter<DataT> const& rhs) const {
            if ((here == NULL) && (rhs.here == NULL)) {
                return false;
            } else {
                return (here != rhs.here) || (tail != rhs.tail);
            }
        }
        

    }; // end CDAL_Iter
    
}

#endif /* CDAL_h */
