//
//  Tester.cpp
//  COP3530
//
//  Created by Nicholas Alvarez on 11/7/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SSLL.h"
#include "SDAL.h"
#include "PSLL.h"
#include "CDAL.h"
#include "CBL.h"
using namespace std;

template <typename L>
bool test_is_empty ( cop3530::List<L>& ll )
{
    bool chkexception=false;
    ll.clear();
    if ( !ll.is_empty() ) return false;
    if (  ll.is_full()  ) return false;
    try
    {
        // Empty so should throw an exception
        ll.pop_front();
    } catch( std::exception& e) {
        //    std::cout <<" Exception Detected (Pass)"<<endl;
        //    std::cout <<e.what()<<endl;
        // set to true since exception found
        chkexception = true;
    }
    
    // push element
    ll.push_front ( 5 );
    if ( ll.length() != 1 ) return false;
    
    // check empty
    if (  ll.is_empty() ) return false;
    ll.clear();
    if ( ll.length() != 0 ) return false;
    if ( !ll.is_empty() ) return false;
    
    // Passed all tests
    return chkexception;
}

template <typename L>
bool test_push_front ( cop3530::List<L>& ll )
{
    
    ll.clear();
    ll.push_front ( 5 );
    
    // if is_empty true -> return false
    if (  ll.is_empty() ) return false;
    if ( ll.peek_front() != 5 )  return false;
    if ( ll.peek_back()  != 5 )  return false;
    ll.push_front ( 20 );
    
    //std::cout <<" Peek front "<<ll.peek_front()<<endl;
    //std::cout <<" Length     "<<ll.length()<<endl;
    
    if ( ll.peek_front() != 20 ) return false;
    if ( ll.peek_back()  != 5 )  return false;
    ll.push_front( 21 );
    ll.push_front( 22 );
    ll.push_front( 23 );
    ll.push_front( 24 );
    ll.push_front( 25 );
    if ( ll.peek_front() != 25 ) return false;
    if ( ll.peek_back()  != 5 )  return false;
    if ( ll.length()     != 7 )  return false;
    
    
    // Now Check larger sequences
    ll.clear();
    for ( int x=0; x<200; x++) {
        // Need to push 49 into list first so
        // at end of loop heads points to 0
        ll.push_front( 199-x );
    }
    
    for ( int x=0; x<200; x++) {
        if ( ll.item_at(x) != x ) return false;
    }
    
    // Passed all tests
    return true;
}


template <typename L>
bool test_push_back  ( cop3530::List<L>& ll )
{
    ll.clear();
    ll.push_back ( 5 );
    // if is_empty true -> return false
    if (  ll.is_empty() ) return false;
    if ( ll.peek_back()  != 5 )  return false;
    if ( ll.peek_front() != 5 )  return false;
    ll.push_back ( 20 );
    if ( ll.peek_front() != 5  ) return false;
    if ( ll.peek_back()  != 20 )  return false;
    ll.push_back( 21 );
    ll.push_back( 22 );
    ll.push_back( 23 );
    ll.push_back( 24 );
    ll.push_back( 25 );
    if ( ll.peek_back()  != 25 ) return false;
    if ( ll.peek_front() != 5 )  return false;
    if ( ll.length()     != 7 )  return false;
    
    // Now Check larger sequences
    ll.clear();
    for ( int x=0; x<200; x++) {
        // Since appended to list no need to subtract
        ll.push_back( x );
    }
    
    for ( int x=0; x<200; x++) {
        if ( ll.item_at(x) != x ) return false;
    }
    
    // Passed all tests
    return true;
}

template <typename L>
bool test_insert ( cop3530::List<L>& ll )
{
    ll.clear();
    ll.push_front( 1 );
    ll.push_front( 2 );
    ll.push_front( 3 );
    ll.push_front( 4 );
    ll.push_front( 5 );
    if ( ll.length()     != 5 )  return false;
    if ( ll.peek_front() != 5 )  return false;
    
    // Now insert 20 at position 0
    // List -> Head->5 4 3 2 1
    // List -> Data -   5 4 3 2 1   length=5
    // CBL     Indx   5 4 3 2 1 0
    // CBL            H         T
    ll.insert( 20, 0 );
    // List -> Data -    20 5 4 3 2 1
    //     Posittion -    0 1 2 3 4 5
    // CBL     Indx     6 5 4 3 2 1 0   length=6
    // CBL              H           T
    
    // List -> Head->20 5 4 3 2 1
    
    if ( ll.peek_front() != 20 )  return false;
    if ( ll.item_at(0)   != 20 )  return false;
    if ( ll.pop_front()  != 20 )  return false;
    
    // List -> Data -       5 4 3 2 1
    //     Posittion -      0 1 2 3 4
    // CBL     Indx     6 5 4 3 2 1 0   length=6
    // CBL                H           T
    
    //std::cout <<" Peek front "<<ll.peek_front()<<endl;
    //std::cout <<" item at(0) "<<ll.item_at(0)<<endl;
    
    // List -> Head->5 4 3 2 1
    if ( ll.peek_front() != 5 )  return false;
    
    // Now insert 20 at position 1
    ll.insert( 20, 1 );
    // List -> Head-> 5 20 4 3 2 1
    if ( ll.length()     != 6  )  return false;
    if ( ll.item_at(1)   != 20 )  return false;
    if ( ll.peek_front() != 5  )  return false;
    if ( ll.peek_back()  != 1  )  return false;
    if ( ll.item_at(0)   != 5  )  return false;
    if ( ll.item_at(2)   != 4  )  return false;
    
    // Now insert 21 at position 2
    ll.insert( 21, 2 );
    // List -> Pos#-> 0  1  2 3 4 5 6
    // List -> Head-> 5 20 21 4 3 2 1
    if ( ll.length()     != 7  )  return false;
    if ( ll.item_at(1)   != 20 )  return false;
    if ( ll.item_at(2)   != 21 )  return false;
    if ( ll.peek_front() != 5  )  return false;
    if ( ll.peek_back()  != 1  )  return false;
    if ( ll.item_at(0)   != 5  )  return false;
    if ( ll.item_at(3)   != 4  )  return false;
    
    // Passed all tests
    return true;
}

template <typename L>
bool test_replace( cop3530::List<L>& ll )
{
    ll.clear();
    ll.push_front( 7 );
    // List -> Head-> 7
    ll.push_back ( 18 );
    // List -> Head-> 7 18
    ll.push_front( 20 );
    // List -> Head-> 20 7 18
    ll.push_back ( 17 );
    // List -> Head-> 20 7 18 17
    ll.push_front( 25 );
    // List -> Head-> 25 20 7 18 17
    ll.push_back ( 8 );
    // List -> Head-> 25 20 7 18 17 8
    if ( ll.length()     != 6  )  return false;
    if ( ll.peek_front() != 25 )  return false;
    
    //std::cout <<" Peek front "<<ll.peek_front()<<endl;
    
    // Replace position 0 with 15 should return 25
    if ( ll.replace( 15, 0) != 25 ) return false;
    // List -> Head-> 15 20 7 18 17 8
    if ( ll.item_at(0) != 15 )  return false;
    
    // Replace position 5 with 50 should return 8
    if ( ll.replace( 50, 5) != 8 ) return false;
    // List -> Head-> 15 20 7 18 17 50
    if ( ll.item_at(5) != 50 )  return false;
    
    // Replace position 1 with 38 should return 8
    if ( ll.replace( 38, 1) != 20 ) return false;
    // List -> Head-> 15 38 7 18 17 50
    if ( ll.item_at(1) != 38 )  return false;
    
    // Replace position 4 with 19 should return 17
    if ( ll.replace( 19, 4) != 17 ) return false;
    // List -> Head-> 15 38 7 18 19 50
    if ( ll.item_at(4) != 19 )  return false;
    
    return true;
    
}

template <typename L>
bool test_simple ( cop3530::List<L>& ll )
{
    
    ll.clear();
    std::cout <<" Simple Test Start "<<endl;
    ll.push_front( 5 );
    std::cout <<" Length = "<<ll.length()<<std::endl;
    ll.insert( 6, 1 );
    std::cout <<" Exit Length = "<<ll.length()<<std::endl;
    std::cout <<" itemAT(0) = "<<ll.item_at(0)<<std::endl;
    std::cout <<" itemAT(1) = "<<ll.item_at(1)<<std::endl;
    
    return true;
    
}

template <typename L>
bool test_remove( cop3530::List<L>& ll )
{
    
    int x;
    ll.clear();
    
    for ( x=0; x<50; x++) {
        // Need to push 49 into list first so
        // at end of loop heads points to 0
        ll.push_front( 49-x );
    }
    //      Pos# -> 0 .. 49
    // List Head -> 0 .. 49
    
    for ( x=50; x<100; x++) {
        // Since appended to list no need to subtract
        ll.push_back( x );
    }
    // List Pos# -> 0 .. 49 50..99
    // List Head -> 0 .. 49 50..99
    
    //std::cout <<endl;
    //std::cout <<" Peek front "<<ll.peek_front()<<endl;
    //std::cout <<" Peek back  "<<ll.peek_back()<<endl;
    //std::cout <<" length     "<<ll.length()<<endl;
    //std::cout <<" item at(49)"<<ll.item_at(49)<<endl;
    
    if ( ll.peek_front() != 0   )  return false;
    if ( ll.peek_back()  != 99  )  return false;
    if ( ll.length()     != 100 )  return false;
    
    //int z=ll.remove(49);
    //std::cout <<" remove(49)"<<z<<endl;
    //z=ll.remove(48);
    //std::cout <<" remove(48)"<<z<<endl;
    
    // Now start to remove first 50 items
    for ( x=0; x<50; x++) {
        
        if ( ll.remove(49-x) != 49-x ) {
            return false;
        }
        
    }
    
    if ( ll.length() != 50 ) return false;
    
    // now remove remaining 50 items
    for ( x=0; x<50; x++) {
        // Remove starting at position 49 -> 0
        if ( ll.remove(0) != 50+x ) {
            return false;
        }
    }
    
    if ( ll.length() != 0) return false;
    return true;
}



bool testContainsEquals(const int& x, const int& y) {
    if (x == y) return true;
    return false;
}


template <typename L>
bool test_contains( cop3530::List<L>& ll )
{
    
    // Clear list to start
    ll.clear();
    
    ll.push_front( 21 );
    ll.push_front( 22 );
    ll.push_front( 23 );
    ll.push_front( 24 );
    
    // If 7 is in the list return false since no 7 in list
    if ( ll.contains(7, testContainsEquals) ) return false;
    
    // If 22 not in the list return false
    if ( !(ll.contains(22, testContainsEquals)) ) return false;
    
    // if 10 is in the list return fals
    if ( ll.contains(10, testContainsEquals) ) return false;
    
    // If 24 not in the list return false
    if ( !(ll.contains(24, testContainsEquals)) ) return false;
    // If 21 not in the list return false
    if ( !(ll.contains(21, testContainsEquals)) ) return false;
    // If 23 not in the list return false
    if ( !(ll.contains(23, testContainsEquals)) ) return false;
    
    // else return true
    return true;
    
}


template <typename L>
bool test_contents ( cop3530::List<L>& ll )
{
    
    bool retval = true;
    ll.clear();
    
    for ( int x=0; x<100; x++) {
        // Need to push 10 into list first so
        // at end of loop heads points to 0
        ll.push_front( 99-x );
    }
    
    if ( ll.peek_front() != 0   ) return false;
    if ( ll.peek_back()  != 99  )  return false;
    if ( ll.length()     != 100 )  return false;
    
    //L* newarray = new L[ll.length()];
    //newarray = ll.contents();
    L* newarray = ll.contents();
    
    // Print the Array for Debug
    // Now Check larger sequences
    ll.clear();
    for ( int x=0; x<100; x++) {
        // check the contents of array
        if ( newarray[x] != x ) {
            retval = false;
            break;
        }
    }
    delete [] newarray;
    return retval;
}



template <typename L>
bool test_iterator_CBL( cop3530::CBL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // Make New List DST (dst) using the Copy Constructor
    cop3530::CBL<L> dst(ll);
    
    // Dst is copy of the ll (CBL List)
    if ( dst.peek_front() != 610 ) return false;
    
    using namespace std;
    typename cop3530::CBL<L>::iterator itr;
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> 610 620 630 640
    int chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //                Verify LL Iterator
    // ----------------------------------------------------------
    // Now Iterate over the LL List and Update each element
    // of the List by writing by curr_element+5
    // Now Read and Update (+5) the LL List
    // LL List Should Read  --> 610 620 630 640
    // LL List Should Write --> 615 625 635 645
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //std::cout<<"LL List -> "<<*itr<<" "<<std::endl;
        *itr = *itr+5;
    }
    
    // Now check the LL List to verify values were
    // written via Iterator to the LL List
    // LL List Should Read --> 615 625 635 645
    chk_int = 615;
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //cout<<*itr<<" ";
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    
    // ----------------------------------------------------------
    //          Check DST List via DST Iterator
    // ----------------------------------------------------------
    // Now Check that DST List has not been updated, since
    // it was the LL List that was updated via the Iterator
    // DST List Should Read  --> 610 620 630 640
    chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //               Check the Const Iterators
    // ----------------------------------------------------------
    // makes a copy of mutable lists (LL and DST) to
    // a constant list immutable List
    cop3530::CBL<L> const const_ll  = ll;
    cop3530::CBL<L> const const_dst = dst;
    
    // LL  List Should Read --> 615 625 635 645
    // DST List Should Read --> 610 620 630 640
    using namespace std;
    typename cop3530::SDAL<L>::const_iterator const_itr;
    // NOTE: Not working.. not sure why... comment out for now.
    
    //    for(const_itr  = const_ll.begin();
    //        const_itr != const_ll.end();
    //       const_itr++)
    //    {
    //       cout<<*const_itr<<" ";
    //    }
    
    
    // ----------------------------------------------------------
    //               Check the Copy-Assignement
    // ----------------------------------------------------------
    // Added two more entries to List
    ll.push_front( 605 );
    ll.push_front( 595 );
    // Now call the copy-assignment operator to assign LL
    // Should now pick up the two new entries 650 and 660
    dst = ll;
    // Dst List Should Now Read --> 595, 605, + Old LL-List
    // Dst List Should Now Read --> 595, 605, 615, 625, 635, 645
    if ( dst.length() != 6 ) return false;  // Length should be 6
    chk_int = 595;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    return true;
    
}



template <typename L>
bool test_iterator_SDAL( cop3530::SDAL<L>& ll )
{
    // Clear Sourc List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // Make New List DST (dst) using the Copy Constructor
    cop3530::SDAL<L> dst(ll);
    
    // Dst is copy of the ll (PSLL List)
    if ( dst.peek_front() != 610 ) return false;
    
    using namespace std;
    typename cop3530::SDAL<L>::iterator itr;
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> 610 620 630 640
    int chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //                Verify LL Iterator
    // ----------------------------------------------------------
    // Now Iterate over the LL List and Update each element
    // of the List by writing by curr_element+5
    // Now Read and Update (+5) the LL List
    // LL List Should Read  --> 610 620 630 640
    // LL List Should Write --> 615 625 635 645
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //std::cout<<"LL List -> "<<*itr<<" "<<std::endl;
        *itr = *itr+5;
    }
    
    // Now check the LL List to verify values were
    // written via Iterator to the LL List
    // LL List Should Read --> 615 625 635 645
    chk_int = 615;
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //cout<<*itr<<" ";
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    
    // ----------------------------------------------------------
    //          Check DST List via DST Iterator
    // ----------------------------------------------------------
    // Now Check that DST List has not been updated, since
    // it was the LL List that was updated via the Iterator
    // DST List Should Read  --> 610 620 630 640
    chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //               Check the Const Iterators
    // ----------------------------------------------------------
    // makes a copy of mutable lists (LL and DST) to
    // a constant list immutable List
    cop3530::SDAL<L> const const_ll  = ll;
    cop3530::SDAL<L> const const_dst = dst;
    
    // LL  List Should Read --> 615 625 635 645
    // DST List Should Read --> 610 620 630 640
    using namespace std;
    typename cop3530::SDAL<L>::const_iterator const_itr;
    // NOTE: Not working.. not sure why... comment out for now.
    /*
     for(const_itr = const_ll.begin();
     const_itr != const_ll.end();
     const_itr++)
     {
     cout<<*const_itr<<" ";
     }
     */
    
    
    // ----------------------------------------------------------
    //               Check the Copy-Assignement
    // ----------------------------------------------------------
    // Added two more entries to List
    ll.push_front( 605 );
    ll.push_front( 595 );
    // Now call the copy-assignment operator to assign LL
    // Should now pick up the two new entries 650 and 660
    dst = ll;
    // Dst List Should Now Read --> 595, 605, + Old LL-List
    // Dst List Should Now Read --> 595, 605, 615, 625, 635, 645
    if ( dst.length() != 6 ) return false;  // Length should be 6
    chk_int = 595;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    return true;
    
}

template <typename L>
bool test_iterator_CDAL( cop3530::CDAL<L>& ll )
{
    // Clear Sourc List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // Make New List DST (dst) using the Copy Constructor
    cop3530::CDAL<L> dst(ll);
    
    // Dst is copy of the ll (PSLL List)
    if ( dst.peek_front() != 610 ) return false;
    
    using namespace std;
    typename cop3530::CDAL<L>::iterator itr;
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> 610 620 630 640
    int chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst ITR List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //                Verify LL Iterator
    // ----------------------------------------------------------
    // Now Iterate over the LL List and Update each element
    // of the List by writing by curr_element+5
    // Now Read and Update (+5) the LL List
    // LL List Should Read  --> 610 620 630 640
    // LL List Should Write --> 615 625 635 645
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //std::cout<<"LL List -> "<<*itr<<" "<<std::endl;
        *itr = *itr+5;
    }
    
    // Now check the LL List to verify values were
    // written via Iterator to the LL List
    // LL List Should Read --> 615 625 635 645
    chk_int = 615;
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //cout<<*itr<<" ";
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    
    // ----------------------------------------------------------
    //          Check DST List via DST Iterator
    // ----------------------------------------------------------
    // Now Check that DST List has not been updated, since
    // it was the LL List that was updated via the Iterator
    // DST List Should Read  --> 610 620 630 640
    chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //               Check the Const Iterators
    // ----------------------------------------------------------
    // makes a copy of mutable lists (LL and DST) to
    // a constant list immutable List
    cop3530::CDAL<L> const const_ll  = ll;
    cop3530::CDAL<L> const const_dst = dst;
    
    // LL  List Should Read --> 615 625 635 645
    // DST List Should Read --> 610 620 630 640
    using namespace std;
    typename cop3530::CDAL<L>::const_iterator const_itr;
    // NOTE: Not working.. not sure why... comment out for now.
    
    // for(const_itr = const_ll.begin();
    // const_itr != const_ll.end();
    // const_itr++)
    // {
    //    cout<<*const_itr<<" ";
    // }
    //
    
    
    // ----------------------------------------------------------
    //               Check the Copy-Assignement
    // ----------------------------------------------------------
    // Added two more entries to List
    ll.push_front( 605 );
    ll.push_front( 595 );
    // Now call the copy-assignment operator to assign LL
    // Should now pick up the two new entries 650 and 660
    dst = ll;
    // Dst List Should Now Read --> 595, 605, + Old LL-List
    // Dst List Should Now Read --> 595, 605, 615, 625, 635, 645
    if ( dst.length() != 6 ) return false;  // Length should be 6
    chk_int = 595;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    return true;
    
}




template <typename L>
bool test_iterator_SSLL ( cop3530::SSLL<L>& ll )
{
    
    
    // Clear Sourc List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // Make New List DST (dst) using the Copy Constructor
    cop3530::SSLL<L> dst(ll);
    
    // Dst is copy of the ll (PSLL List)
    if ( dst.peek_front() != 610 ) return false;
    
    using namespace std;
    typename cop3530::SSLL<L>::iterator itr;
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> 610 620 630 640
    int chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //                Verify LL Iterator
    // ----------------------------------------------------------
    // Now Iterate over the LL List and Update each element
    // of the List by writing by curr_element+5
    // Now Read and Update (+5) the LL List
    // LL List Should Read  --> 610 620 630 640
    // LL List Should Write --> 615 625 635 645
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //std::cout<<"LL List -> "<<*itr<<" "<<std::endl;
        *itr = *itr+5;
    }
    
    // Now check the LL List to verify values were
    // written via Iterator to the LL List
    // LL List Should Read --> 615 625 635 645
    chk_int = 615;
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //cout<<*itr<<" ";
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    
    // ----------------------------------------------------------
    //          Check DST List via DST Iterator
    // ----------------------------------------------------------
    // Now Check that DST List has not been updated, since
    // it was the LL List that was updated via the Iterator
    // DST List Should Read  --> 610 620 630 640
    chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //               Check the Const Iterators
    // ----------------------------------------------------------
    // makes a copy of mutable lists (LL and DST) to
    // a constant list immutable List
    cop3530::SSLL<L> const const_ll  = ll;
    cop3530::SSLL<L> const const_dst = dst;
    
    // LL  List Should Read --> 615 625 635 645
    // DST List Should Read --> 610 620 630 640
    using namespace std;
    typename cop3530::PSLL<L>::const_iterator const_itr;
    // NOTE: Not working.. not sure why... comment out for now.
    /*
     for(const_itr = const_ll.begin();
     const_itr != const_ll.end();
     const_itr++)
     {
     cout<<*const_itr<<" ";
     }
     */
    
    
    // ----------------------------------------------------------
    //               Check the Copy-Assignement
    // ----------------------------------------------------------
    // Added two more entries to List
    ll.push_front( 605 );
    ll.push_front( 595 );
    // Now call the copy-assignment operator to assign LL
    // Should now pick up the two new entries 650 and 660
    dst = ll;
    // Dst List Should Now Read --> 595, 605, + Old LL-List
    // Dst List Should Now Read --> 595, 605, 615, 625, 635, 645
    if ( dst.length() != 6 ) return false;  // Length should be 6
    chk_int = 595;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    return true;
    
}




template <typename L>
bool test_iterator_PSLL ( cop3530::PSLL<L>& ll )
{
    
    // Clear Sourc List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // Make New List DST (dst) using the Copy Constructor
    cop3530::PSLL<L> dst(ll);
    
    // Dst is copy of the ll (PSLL List)
    if ( dst.peek_front() != 610 ) return false;
    
    using namespace std;
    typename cop3530::PSLL<L>::iterator itr;
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> 610 620 630 640
    int chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //                Verify LL Iterator
    // ----------------------------------------------------------
    // Now Iterate over the LL List and Update each element
    // of the List by writing by curr_element+5
    // Now Read and Update (+5) the LL List
    // LL List Should Read  --> 610 620 630 640
    // LL List Should Write --> 615 625 635 645
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //std::cout<<"LL List -> "<<*itr<<" "<<std::endl;
        *itr = *itr+5;
    }
    
    // Now check the LL List to verify values were
    // written via Iterator to the LL List
    // LL List Should Read --> 615 625 635 645
    chk_int = 615;
    for(itr = ll.begin();
        itr != ll.end();
        itr++)
    {
        //cout<<*itr<<" ";
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    
    // ----------------------------------------------------------
    //          Check DST List via DST Iterator
    // ----------------------------------------------------------
    // Now Check that DST List has not been updated, since
    // it was the LL List that was updated via the Iterator
    // DST List Should Read  --> 610 620 630 640
    chk_int = 610;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    
    // ----------------------------------------------------------
    //               Check the Const Iterators
    // ----------------------------------------------------------
    // makes a copy of mutable lists (LL and DST) to
    // a constant list immutable List
    cop3530::PSLL<L> const const_ll  = ll;
    cop3530::PSLL<L> const const_dst = dst;
    
    // LL  List Should Read --> 615 625 635 645
    // DST List Should Read --> 610 620 630 640
    using namespace std;
    typename cop3530::PSLL<L>::const_iterator const_itr;
    // NOTE: Not working.. not sure why... comment out for now.
    /*
     for(const_itr = const_ll.begin();
     const_itr != const_ll.end();
     const_itr++)
     {
     cout<<*const_itr<<" ";
     }
     */
    
    
    // ----------------------------------------------------------
    //               Check the Copy-Assignement
    // ----------------------------------------------------------
    // Added two more entries to List
    ll.push_front( 605 );
    ll.push_front( 595 );
    // Now call the copy-assignment operator to assign LL
    // Should now pick up the two new entries 650 and 660
    dst = ll;
    // Dst List Should Now Read --> 595, 605, + Old LL-List
    // Dst List Should Now Read --> 595, 605, 615, 625, 635, 645
    if ( dst.length() != 6 ) return false;  // Length should be 6
    chk_int = 595;
    for(itr = dst.begin();
        itr != dst.end();
        itr++)
    {
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
        if ( *itr != chk_int ) return false;
        chk_int = chk_int+10;
    }
    return true;
    
}



template <typename L>
bool test_iterator_const ( cop3530::SSLL<L>& ll )
{
    
    // Clear list to start
    ll.clear();
    
    ll.push_front( 21 );
    ll.push_front( 22 );
    ll.push_front( 23 );
    ll.push_front( 24 );
    
    // makes a copy of mutable list to a constant list
    cop3530::SSLL<L> const const_ll = ll;
    
    using namespace std;
    typename cop3530::SSLL<L>::const_iterator const_itr;
    
    for(const_itr = const_ll.begin();
        const_itr != const_ll.end();
        const_itr++)
    {
        cout<<*const_itr<<" ";
    }
    return true;
    
}




template <typename L>
void test_print( cop3530::List<L>& ll )
{
    
    // Clear list to start
    ll.clear();
    std::cout <<" ******** Testing Print Method *********** "<<endl;
    // Should display [Empty List]
    ll.print( std::cout );
    
    ll.push_front( 21 );
    ll.push_front( 22 );
    ll.push_front( 23 );
    ll.push_front( 24 );
    
    // Should display [21,22,23,24]
    ll.print( std::cout );
    ll.pop_front( ); // Pop 21
    
    // Should display [22,23,24]
    ll.print( std::cout );
    ll.pop_back( );  // Pop 24
    
    // Should display [22,23]
    ll.print( std::cout );
    ll.pop_front( ); // Pop 22
    
    // Should display [23]
    ll.print( std::cout );
    ll.pop_back( );  // Pop 23
    
    // Should display [Empty List]
    ll.print( std::cout );
    return;
    
}


// Test Deallocate Method - PSLL Class
bool test_psll_deallocate( cop3530::PSLL<int>& ll )
{
    
    // Clear list to start
    ll.clear();
    //std::cout <<" ******** Testing Deallocate Method *********** "<<endl;
    //std::cout <<"  list_size = "<<ll.length()<<endl;
    //std::cout <<"  pool_size = "<<ll.get_pool_size()<<endl;
    
    int x;
    for ( x=0; x<50; x++) {
        // Need to push 49 into list first so
        // at end of loop heads points to 0
        ll.push_front( 49-x );
    }
    ll.pop_front( );
    if ( ll.get_pool_size() != 1 ) return false;
    ll.push_front( 7 );
    if ( ll.get_pool_size() != 0 ) return false;
    
    for ( x=0; x<150; x++) {
        ll.push_front( x );
    }
    // Now List=200 and Pool Size=0
    if ( ll.length()        != 200 ) return false;
    if ( ll.get_pool_size() != 0   ) return false;
    
    // now pop 50  -> List=150 / Pool=50
    for ( x=0; x<50; x++) {
        ll.pop_front( );
    }
    if ( ll.length()        != 150 ) return false;
    if ( ll.get_pool_size() != 50  ) return false;
    
    // NOTE: At this time 50 Nodes all ready in Free Pool so
    //       no more nodes will be added to Free Pool
    
    // now pop 10  -> List=140 / Pool=50 (10 Nodes deleted)
    for ( x=0; x<10; x++) {
        ll.pop_front( );
    }
    if ( ll.length()        != 140 ) return false;
    if ( ll.get_pool_size() != 50  ) return false;
    
    // now pop 40  -> List=100 / Pool=50 (40 Nodes deleted)
    for ( x=0; x<40; x++) {
        ll.pop_front( );
    }
    
    if ( ll.length()        != 100 ) return false;
    if ( ll.get_pool_size() != 50  ) return false;
    
    // Note: Pool Node 50 > (100/2)  Fails.. so no deallocation
    //  -> List=100  / Pool=50  Is 50 > (100/2)  = 50 (NO)
    
    // At this time the List < 100 so no deallocation will take place
    for ( x=0; x<10; x++) {
        ll.pop_front( );
    }
    if ( ll.length()        != 90  ) return false;
    if ( ll.get_pool_size() != 50  ) return false;
    // ----------------------------------------------------------------
    
    // Pop 90 -> List=90->0 / Pool=50
    for ( x=0; x<90; x++) {
        ll.pop_front( );
    }
    if ( ll.length()        != 0   ) return false;
    if ( ll.get_pool_size() != 50  ) return false;
    
    // Push 50 -> List=0 -> 100  / Pool=50 -> 0
    for ( x=0; x<50; x++) {
        ll.push_front(x);
    }
    if ( ll.length()        != 50  ) return false;
    if ( ll.get_pool_size() != 0   ) return false;
    
    // now make sure that clear routine resets all
    ll.clear();
    if ( ll.length()        != 0 ) return false;
    if ( ll.get_pool_size() != 0 ) return false;
    
    return true;
    
}


// Test Deallocate Method - SDAL Class
template <typename L>
bool test_sdal_deallocate( cop3530::SDAL<L>& ll )
{
    
    // Clear list to start
    ll.clear();
    //std::cout <<" ******** Testing Deallocate Method *********** "<<endl;
    //std::cout <<"  list_size = "<<ll.length()<<endl;
    //std::cout <<"  pool_size = "<<ll.get_pool_size()<<endl;
    
    size_t x;
    for ( x=0; x<50; x++) {
        // Need to push 50 elements into list so
        // array is full
        ll.push_front( 49-x );
    }
    if ( ll.length() != 50 ) return false;
    
    return true;
}

template <typename L>
bool test_move_CBL( cop3530::CBL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // create a new CBL list object
    cop3530::CBL<L> ll2;
    // Now use move assignment to take over ll
    ll2 = std::move(ll);
    
    if ( ll2.length() != 4 ) return false;
    
    int chk_int = 610;
    for ( int x=0; x<4; x++ )
    {
        //std::cout <<" Peek front "<<ll2.item_at(x)<<endl;
        if ( ll2.item_at(x) != chk_int ) return false;
        chk_int = chk_int + 10;
    }
    return true;
    
}

template <typename L>
bool test_move_SSLL( cop3530::SSLL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // create a new CBL list object
    cop3530::SSLL<L> ll2;
    // Now use move assignment to take over ll
    ll2 = std::move(ll);
    
    if ( ll2.length() != 4 ) return false;
    
    int chk_int = 610;
    for ( int x=0; x<4; x++ )
    {
        //std::cout <<" Peek front "<<ll2.item_at(x)<<endl;
        if ( ll2.item_at(x) != chk_int ) return false;
        chk_int = chk_int + 10;
    }
    return true;
}

template <typename L>
bool test_move_PSLL( cop3530::PSLL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // create a new CBL list object
    cop3530::PSLL<L> ll2;
    // Now use move assignment to take over ll
    ll2 = std::move(ll);
    
    if ( ll2.length() != 4 ) return false;
    
    int chk_int = 610;
    for ( int x=0; x<4; x++ )
    {
        //std::cout <<" Peek front "<<ll2.item_at(x)<<endl;
        if ( ll2.item_at(x) != chk_int ) return false;
        chk_int = chk_int + 10;
    }
    return true;
}

template <typename L>
bool test_move_SDAL ( cop3530::SDAL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // create a new CBL list object
    cop3530::SDAL<L> ll2;
    // Now use move assignment to take over ll
    ll2 = std::move(ll);
    
    if ( ll2.length() != 4 ) return false;
    
    int chk_int = 610;
    for ( int x=0; x<4; x++ )
    {
        //std::cout <<" Peek front "<<ll2.item_at(x)<<endl;
        if ( ll2.item_at(x) != chk_int ) return false;
        chk_int = chk_int + 10;
    }
    return true;
}

template <typename L>
bool test_move_CDAL ( cop3530::CDAL<L>& ll )
{
    // Clear Source List (LL) to start
    ll.clear();
    
    ll.push_front( 640 );
    ll.push_front( 630 );
    ll.push_front( 620 );
    ll.push_front( 610 );
    
    // create a new CBL list object
    cop3530::CDAL<L> ll2;
    // Now use move assignment to take over ll
    ll2 = std::move(ll);
    
    if ( ll2.length() != 4 ) return false;
    
    int chk_int = 610;
    for ( int x=0; x<4; x++ )
    {
        //std::cout <<" Peek front "<<ll2.item_at(x)<<endl;
        if ( ll2.item_at(x) != chk_int ) return false;
        chk_int = chk_int + 10;
    }
    return true;
    
}

/*
 // Test Deallocate Method - CDAL Class
 template <typename L>
 bool test_cdal_deallocate( cop3530::CDAL<L>& ll )
 {
 
 // Clear list to start
 ll.clear();
 //std::cout <<" ******** Testing Deallocate Method *********** "<<endl;
 //std::cout <<"  list_size = "<<ll.length()<<endl;
 //std::cout <<"  pool_size = "<<ll.get_pool_size()<<endl;
 
 size_t x;
 for ( x=0; x<50; x++) {
 // Need to push 49 into list first so
 // at end of loop heads points to 0
 ll.push_front( 150-x );
 }
 if ( ll.length() != 50 ) return false;
 if ( ll.get_countnodes() != 1 ) return false;
 
 // Push 50 more elements - should create new node
 for ( x=0; x<50; x++) {
 ll.push_front( 99-x );
 }
 if ( ll.length() != 100 ) return false;
 if ( ll.get_countnodes() != 2 ) return false;
 
 // Push 50 more elements - should create new node
 for ( x=0; x<50; x++) {
 ll.push_front( 49-x );
 }
 if ( ll.length() != 150 ) return false;
 if ( ll.get_countnodes() != 3 ) return false;
 
 // Now Pop 20
 for ( x=0; x<20; x++) {
 ll.pop_front( );
 }
 if ( ll.length() != 130 ) return false;
 if ( ll.get_countnodes() != 3 ) return false;
 
 // Now Pop 30 - Should not deallocate
 for ( x=0; x<30; x++) {
 ll.pop_front( );
 }
 if ( ll.length() != 100 ) return false;
 if ( ll.get_countnodes() != 3 ) return false;
 
 // Now Pop 50 - Should deallocate one node
 for ( x=0; x<50; x++) {
 ll.pop_front( );
 }
 if ( ll.length() != 50 ) return false;
 if ( ll.get_countnodes() != 2 ) return false;
 return true;
 
 }
 */


int main() {
    
    printf(" \n");
    printf(" ....... Begin to Test Methods .......\n");
    printf(" \n");
    
    // Do something with SSLL<L> here
    cop3530::SSLL <int>  lss;
    cop3530::PSLL <int>  pss;
    cop3530::SDAL <int>  sss;
    cop3530::CDAL <int>  css;
    cop3530::CBL  <int>  cbs;
    
    // SDAL with constructor size=10
    cop3530::SDAL <int>  sss_10(10);
    // CBL with constructor size=20
    cop3530::CBL  <int>  cbs_20(20);
    
    cop3530::SSLL<char> list;
    list.push_front( 'X' );
    
    //  cop3530::SSLL<char> const const_list = list;
    //  cop3530::SSLL<char>::iterator iter = list.begin();
    //  std::cout << *iter << std::endl;        // prints an X
    //  *iter = 'Y';
    //  std::cout << *iter << std::endl;        // prints a Y
    
    //    cop3530::SSLL<char>::const_iterator const_iter = const_list.begin();
    //    std::cout << *const_iter << std::endl;  // prints an X
    //    *const_iter = 'Z';  // ILLEGAL!  Won't compile!  Denotes constant element
    
    cout <<" ******** Start Test for -> SSLL Class *********** "<<endl;
    cout <<"  (1)  Test -> is_empty        Result -> "<<(test_is_empty       (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (2)  Test -> push_front      Result -> "<<(test_push_front     (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (3)  Test -> push_back       Result -> "<<(test_push_back      (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (4)  Test -> insert          Result -> "<<(test_insert         (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (5)  Test -> replace         Result -> "<<(test_replace        (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (6)  Test -> remove          Result -> "<<(test_remove         (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (7)  Test -> contains        Result -> "<<(test_contains       (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (8)  Test -> contents        Result -> "<<(test_contents       (lss) ? "Pass" : "Fail")<<endl;
    cout <<"  (9)  Test -> iterator        Result -> "<<(test_iterator_SSLL  (lss) ? "Pass" : "Fail")<<endl;
    //  cout <<"  (10) Test -> const_iterator  Result -> "<<(test_iterator_const (lss) ? "Pass" : "Fail")<<endl;
    test_print(lss);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> PSLL Class *********** "<<endl;
    cout <<"  (1)  Test -> is_empty    Result -> "<<(test_is_empty       (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (2)  Test -> push_front  Result -> "<<(test_push_front     (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (3)  Test -> push_back   Result -> "<<(test_push_back      (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (4)  Test -> insert      Result -> "<<(test_insert         (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (5)  Test -> replace     Result -> "<<(test_replace        (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (6)  Test -> remove      Result -> "<<(test_remove         (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (7)  Test -> contains    Result -> "<<(test_contains       (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (8)  Test -> contents    Result -> "<<(test_contents       (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (9)  Test -> iterator    Result -> "<<(test_iterator_PSLL  (pss) ? "Pass" : "Fail")<<endl;
    cout <<"  (10) Test -> deallocate  Result -> "<<(test_psll_deallocate(pss) ? "Pass" : "Fail")<<endl;
    test_print(pss);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> SDAL Class (Default StartSize=50) *********** "<<endl;
    cout <<"  (1)  Test -> is_empty    Result -> "<<(test_is_empty      (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (2)  Test -> push_front  Result -> "<<(test_push_front    (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (3)  Test -> push_back   Result -> "<<(test_push_back     (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (4)  Test -> insert      Result -> "<<(test_insert        (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (5)  Test -> replace     Result -> "<<(test_replace       (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (6)  Test -> remove      Result -> "<<(test_remove        (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (7)  Test -> contains    Result -> "<<(test_contains      (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (9)  Test -> contents    Result -> "<<(test_contents      (sss) ? "Pass" : "Fail")<<endl;
    cout <<"  (10) Test -> iterator    Result -> "<<(test_iterator_SDAL (sss) ? "Pass" : "Fail")<<endl;
    test_print(sss);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> SDAL Class (StartSize=10) *********** "<<endl;
    cout <<"  (1) Test -> is_empty    Result -> "<<(test_is_empty      (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (2) Test -> push_front  Result -> "<<(test_push_front    (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (3) Test -> push_back   Result -> "<<(test_push_back     (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (4) Test -> insert      Result -> "<<(test_insert        (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (5) Test -> replace     Result -> "<<(test_replace       (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (6) Test -> remove      Result -> "<<(test_remove        (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (7) Test -> contains    Result -> "<<(test_contains      (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (8) Test -> contents    Result -> "<<(test_contents      (sss_10) ? "Pass" : "Fail")<<endl;
    cout <<"  (9) Test -> iterator    Result -> "<<(test_iterator_SDAL (sss_10) ? "Pass" : "Fail")<<endl;
    test_print(sss_10);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> CDAL Class *********** "<<endl;
    cout <<"  (1)  Test -> is_empty    Result -> "<<(test_is_empty       (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (2)  Test -> push_front  Result -> "<<(test_push_front     (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (3)  Test -> push_back   Result -> "<<(test_push_back      (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (4)  Test -> insert      Result -> "<<(test_insert         (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (5)  Test -> replace     Result -> "<<(test_replace        (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (6)  Test -> remove      Result -> "<<(test_remove         (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (7)  Test -> contains    Result -> "<<(test_contains       (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (8)  Test -> contents    Result -> "<<(test_contents       (css) ? "Pass" : "Fail")<<endl;
    cout <<"  (9)  Test -> iterator    Result -> "<<(test_iterator_CDAL  (css) ? "Pass" : "Fail")<<endl;
    //  cout <<"  (10) Test -> deallocate  Result -> "<<(test_cdal_deallocate(css) ? "Pass" : "Fail")<<endl;
    test_print(css);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> CBL Class (Default StartSize=50) *********** "<<endl;
    cout <<"  (1) Test -> is_empty    Result -> "<<(test_is_empty       (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (2) Test -> push_front  Result -> "<<(test_push_front     (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (3) Test -> push_back   Result -> "<<(test_push_back      (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (4) Test -> insert      Result -> "<<(test_insert         (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (5) Test -> replace     Result -> "<<(test_replace        (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (6) Test -> remove      Result -> "<<(test_remove         (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (7) Test -> contains    Result -> "<<(test_contains       (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (8) Test -> contents    Result -> "<<(test_contents       (cbs) ? "Pass" : "Fail")<<endl;
    cout <<"  (9) Test -> iterator    Result -> "<<(test_iterator_CBL   (cbs) ? "Pass" : "Fail")<<endl;
    test_print(cbs);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    cout <<" "<<endl;
    
    cout <<" ******** Start Test for -> CBL Class (StartSize=20) *********** "<<endl;
    cout <<"  (1)  Test -> is_empty    Result -> "<<(test_is_empty       (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (2)  Test -> push_front  Result -> "<<(test_push_front     (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (3)  Test -> push_back   Result -> "<<(test_push_back      (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (4)  Test -> insert      Result -> "<<(test_insert         (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (5)  Test -> replace     Result -> "<<(test_replace        (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (6)  Test -> remove      Result -> "<<(test_remove         (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (7)  Test -> contains    Result -> "<<(test_contains       (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (8)  Test -> contents    Result -> "<<(test_contents       (cbs_20) ? "Pass" : "Fail")<<endl;
    cout <<"  (9)  Test -> iterator    Result -> "<<(test_iterator_CBL   (cbs_20) ? "Pass" : "Fail")<<endl;
    test_print(cbs_20);
    cout <<" ------------------------------------------------ "<<endl;
    cout <<" "<<endl;
    cout <<" "<<endl;
    cout <<" ******** Start Test for -> MOVE Assignment *********** "<<endl;
    cout <<"  (1) Test -> move_assign SSL   Result -> "<<(test_move_SSLL  (lss)   ? "Pass" : "Fail")<<endl;
    cout <<"  (2) Test -> move_assign PSLL  Result -> "<<(test_move_PSLL  (pss)   ? "Pass" : "Fail")<<endl;
    cout <<"  (3) Test -> move_assign SDAL  Result -> "<<(test_move_SDAL  (sss)   ? "Pass" : "Fail")<<endl;
    cout <<"  (4) Test -> move_assign CDAL  Result -> "<<(test_move_CDAL  (css)   ? "Pass" : "Fail")<<endl;
    cout <<"  (5) Test -> move_assign CBL   Result -> "<<(test_move_CBL   (cbs)   ? "Pass" : "Fail")<<endl;
    cout <<" "<<endl;
    
}
