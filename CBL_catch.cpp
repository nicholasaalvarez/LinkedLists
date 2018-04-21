//
//  CBL_catch.cpp
//  COP3530
//
//  Created by Nicholas Alvarez on 11/13/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "CBL.h"
#include <iostream>



// Create Char List Obj
cop3530::CBL  <char>  list;

using namespace std;
typename cop3530::CBL<char>::iterator itr;


TEST_CASE( "List Clear Test" ) {
    
    list.clear();
    REQUIRE( list.is_empty() == true );
    list.push_front ( 'B' );
    REQUIRE( list.length() == 1 );
    list.clear();
    REQUIRE( list.length() == 0 );
    
}


TEST_CASE( "Exceptions Test" ) {
    
    list.clear();
    REQUIRE_THROWS( list.pop_front() );
    list.push_front('a');
    REQUIRE_THROWS( list.insert('b', 2) );
    list.pop_front();
    REQUIRE_THROWS( list.pop_back() );
    REQUIRE_THROWS( list.pop_back() );
    list.push_front('a');
    list.push_front('b');
    list.push_front('c');
    list.push_front('d');
    list.push_front('e');
    REQUIRE( list.length() == 5 );
    REQUIRE_THROWS( list.replace('T',19) );
    REQUIRE_THROWS( list.remove(6) );
    
}


TEST_CASE( "List Empty/Full Test ") {
    
    list.clear();
    REQUIRE( list.is_empty() == true  );
    REQUIRE( list.is_full()  == false );
    list.push_front ( 5 );
    REQUIRE( list.length() == 1 );
    REQUIRE( list.is_empty() == false);
    REQUIRE( list.is_full()  == false );
    
}


TEST_CASE( "List Push-Front/Pop-Back Test [Char]" ) {
    
    list.clear();
    list.push_front('N');
    
    REQUIRE ( list.is_empty()   == false );
    REQUIRE ( list.peek_front() == 'N'   );
    REQUIRE ( list.pop_front()  == 'N'   );
    
    // Push to List ->  "z,y..a"
    // So list front should start with 'a'
    for ( char a='z'; a>='a'; a-- ) {
        //std::cout <<"Char For loop a= "<<a<<std::endl;
        list.push_front(a);
    }
    // Check that 26 letters were pushed
    REQUIRE ( list.length() == 26 );
    
    // Now check the List was pushed correctly
    for ( char a='z'; a>='a'; a-- ) {
        REQUIRE ( list.pop_back() == a );
    }
    
    // length should be zero
    REQUIRE ( list.length() == 0 );
}


TEST_CASE( "List Push-Back/Pop-Front Test [Char]" ) {
    
    list.clear();
    
    // Push to List ->  "a,b,.z"
    // So list front should start with 'a'
    for ( char a='a'; a<='z'; a++ ) {
        //std::cout <<"Char For loop a= "<<a<<std::endl;
        list.push_back(a);
    }
    // Check that 26 letters were pushed
    REQUIRE ( list.length() == 26 );
    
    // Now check the List was pushed correctly
    for ( char a='a'; a<='z'; a++ ) {
        REQUIRE ( list.pop_front() == a );
    }
    // length should be zero
    REQUIRE ( list.length() == 0 );
    
}

TEST_CASE( "List Insert-At/Item-At Test [Char]" ) {
    
    list.clear();
    
    // Insert to List ->  "a,b,c,..z"
    // So list front should start with 'a'
    // a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    size_t pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        //std::cout <<"Insert at = "<<pos<<" Char= "<<a<<std::endl;
        list.insert(a, pos);
        pos++;
    }
    // Check that 26 letters were pushed
    REQUIRE ( list.length() == 26 );
    //list.print( std::cout );
    
    // Now check the List was pushed correctly
    pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        //std::cout <<"Item at = "<<pos<<" Char= "<<list.item_at(pos)<<std::endl;
        REQUIRE ( list.item_at(pos) == a );
        pos++;
    }
    // length should be zero
    REQUIRE ( list.length() == 26 );
    
}


TEST_CASE( "List Replace-At/Peek (Front/Back) Test [Char]" ) {
    
    list.clear();
    
    // Insert to List ->  "a,b,c,..z"
    // So list front should start with 'a'
    // a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    size_t pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        //std::cout <<"Char For loop a= "<<a<<std::endl;
        list.insert(a, pos);
        pos++;
    }
    // Check that 26 letters were pushed
    REQUIRE ( list.length() == 26 );
    REQUIRE ( list.peek_front() == 'a' );
    REQUIRE ( list.peek_back()  == 'z' );
    
    // Now Make some letters capital
    REQUIRE ( list.replace('G',6 ) == 'g' );
    REQUIRE ( list.replace('A',0 ) == 'a' );
    REQUIRE ( list.replace('T',19) == 't' );
    REQUIRE ( list.replace('O',14) == 'o' );
    REQUIRE ( list.replace('R',17) == 'r' );
    REQUIRE ( list.replace('S',18) == 's' );
    
    // Now check the List elements were replaced
    pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        
        if ( a == 'g' )
            REQUIRE ( list.item_at(pos) == 'G' );
        else if ( a == 'a' )
            REQUIRE ( list.item_at(pos) == 'A' );
        else if ( a == 't' )
            REQUIRE ( list.item_at(pos) == 'T' );
        else if ( a == 'o' )
            REQUIRE ( list.item_at(pos) == 'O' );
        else if ( a == 'r' )
            REQUIRE ( list.item_at(pos) == 'R' );
        else if ( a == 's' )
            REQUIRE ( list.item_at(pos) == 'S' );
        else
            REQUIRE ( list.item_at(pos) == a );
        
        // Increment position
        pos++;
        
    }
    // length should be zero
    REQUIRE ( list.length() == 26 );
    
}


TEST_CASE( "List Remove Test [Char]" ) {
    
    list.clear();
    
    // Insert to List ->  "a,b,c,..Z"
    // So list front should start with 'a'
    // a b c d e f g h i j k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    size_t pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        //std::cout <<"Char For loop a= "<<a<<std::endl;
        list.insert(a, pos);
        pos++;
    }
    // Check that 26 letters were pushed
    REQUIRE ( list.length() == 26 );
    REQUIRE ( list.peek_front() == 'a' );
    REQUIRE ( list.peek_back()  == 'z' );
    
    // Now remove some letters capital
    // a b c d e f h i j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7 8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(6 ) == 'g' );
    
    // b c d e f h i j  k  l   m  n  o  p  q  r  s  t  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(0 ) == 'a' );
    
    // b c d e f h i j  k  l   m  n  o  p  q  r  s  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(17) == 't' );
    
    // b c d e f h i j  k  l   m  n  p  q  r  s  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(12) == 'o' );
    
    // b c d e f h i j  k  l   m  n  p  q  s  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(14) == 'r' );
    
    // b c d e f h i j  k  l   m  n  p  q  u  v  w  x  y  z
    // 0 1 2 3 4 5 6 7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
    REQUIRE ( list.remove(14) == 's' );
    
    // Now check the List elements were remove
    pos=0;
    for ( char a='a'; a<='z'; a++ ) {
        
        if ( (a != 'g') &&
            (a != 'a') &&
            (a != 't') &&
            (a != 'o') &&
            (a != 'r') &&
            (a != 's')  ) {
            REQUIRE ( list.item_at(pos) == a );
            pos++;
        }
    }
    // length should be zero
    REQUIRE ( list.length() == 20 );
    
}

TEST_CASE( "List Contains [Char]" ) {
    
    list.clear();
    
    // Push NICK into the List
    list.push_back('N');
    list.push_back('i');
    list.push_back('c');
    list.push_back('k');
    
    //list.print( std::cout );
    
    // Check if Z in list
    bool b = list.contains('Z', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b == 0  );
    
    // Check if N in list
    b = list.contains('N', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    
    // Check if A in list
    b = list.contains('A', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b == 0  );
    
    // Check if i in list
    b = list.contains('i', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    
    // Check if C in list
    b = list.contains('C', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b == 0  );
    
    // Check if c in list
    b = list.contains('c', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    // Check if M in list
    b = list.contains('M', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b == 0  );
    
    // Check if k in list
    b = list.contains('k', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
}


TEST_CASE( "List Contents [Char]" ) {
    
    list.clear();
    
    // Push NICK into the List
    list.push_back('N');
    list.push_back('i');
    list.push_back('c');
    list.push_back('k');
    
    char * arr = list.contents();
    char expected[4] = {'N', 'i', 'c', 'k'};
    for(size_t i = 0; i < list.length(); i++) {
        REQUIRE(*(arr+i) == expected[i]);
    }
    delete[] arr;
    
}



TEST_CASE( "Iterator Test ") {
    
    list.clear();
    // Push to List ->  "z,y..a"
    // So list front should start with 'a'
    for ( char a='z'; a>='a'; a-- ) {
        //std::cout <<"Char For loop a= "<<a<<std::endl;
        list.push_front(a);
    }
    
    // Post Increment Iterator
    char a = 'a';
    for(itr  = list.begin();
        itr != list.end();
        itr++)
    {
        REQUIRE ( *itr == a );
        a++; // increment character
    }
    
}


TEST_CASE( "Copy Constructor/Assignment Test ") {
    
    list.clear();
    list.push_front ( 'F' );
    list.push_front ( 'E' );
    list.push_front ( 'D' );
    list.push_front ( 'C' );
    list.push_front ( 'B' );
    list.push_front ( 'A' );
    REQUIRE( list.length() == 6 );
    
    // Make New List DST (dst) using the Copy Constructor
    // dST <- list  Copy list to dst Object
    cop3530::CBL<char> dst(list);  // -> using Copy Constructor
    
    list.push_back  ( 'G' );
    list.push_back  ( 'H' );
    list.push_back  ( 'I' );
    list.push_back  ( 'J' );
    REQUIRE( list.length() == 10 );
    
    // Check new list (dst)
    // Dst is copy of the list (CBL List)
    REQUIRE( dst.peek_front() == 'A' );
    REQUIRE( dst.length()     ==  6  );
    
    // Check that J is in list list but dst list
    // since it was added after the copy constructor was called
    
    // Check if J in list
    bool b = list.contains('J', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    // Check if J in dst
    b = dst.contains('J', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b == 0  );
    
    // ----------------------------------------------------------
    //                Check the Copy-Constructor
    // ----------------------------------------------------------
    // Now check that copy of new list DST (dst)  was
    // performed by the Copy Constructor using an Iterator
    // that will iterator over the new Dst List
    // NOTE: DST List Should Read --> A B C D E F
    char a = 'A';
    for(itr  = dst.begin();
        itr != dst.end();
        itr++)
    {
        // char a = start with 'A' and then gets incremented to
        //          'B' -> 'C' -> 'D' -> 'E' -> 'F'
        //          which is used to to make list was copied correctly
        REQUIRE ( *itr == a );
        a++; // increment character
        //std::cout<<"Dst List -> "<<*itr<<" "<<std::endl;
    }
    
    // Now use the Copy Assignment to re-copy the list to include
    // the characters  'G' 'H' 'I' and 'J'
    dst = list;  // Copy Assignment called in this line
    
    // New length should be 10 since 4 characters added after
    // the initial copy constructor was called
    REQUIRE( dst.length() == 10 );
    
    // Check if J in dst
    b = dst.contains('J', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    b = dst.contains('I', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    b = dst.contains('H', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
    b = dst.contains('G', [](const char& a, const char& b) {
        return a == b;
    });
    REQUIRE ( b );
    
}


