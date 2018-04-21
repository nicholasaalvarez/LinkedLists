//
//  List.h
//  COP3530
//
//  Created by Nicholas Alvarez on 11/7/17.
//  Copyright © 2017 Nicholas Alvarez. All rights reserved.
//

#ifndef _LIST_H_
#define _LIST_H_

namespace cop3530
{
    template <typename L>
    class List {
    public:
        
        //------------------------------------------------------------------------------//
        //-----    METHODS   -----------------------------------------------------------//
        //------------------------------------------------------------------------------//
        virtual L pop_back() = 0;
        virtual L pop_front() = 0;
        virtual bool is_empty() const = 0;
        virtual bool is_full() const = 0;
        virtual size_t length() const = 0;
        virtual L remove( size_t position ) = 0;
        virtual L item_at( size_t position ) const = 0;
        virtual void push_back( const L& element ) = 0;
        virtual void push_front(const L& element ) = 0;
        virtual L peek_back() = 0;
        virtual L peek_front() = 0;
        virtual void clear() = 0;
        virtual bool contains(const L& element,bool equals(const L& x, const L& y)) const = 0 ;
        virtual void insert( const L element, size_t position ) = 0;
        virtual L replace(const L& element,size_t position ) = 0;
        virtual L *contents()=0;
        virtual std::ostream& print(std::ostream& out) const = 0;
        
        virtual ~List() {};
        
    };
    
    
}
#endif

