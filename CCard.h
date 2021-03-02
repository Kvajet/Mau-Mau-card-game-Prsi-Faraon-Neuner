#pragma once
#include <iostream>
#include <memory>

/**
 * @class CCard
 * Abstract class for cards implementation
 */
class CCard
{
public:
    enum Color : char {
        ACORNS = 0 , LEAVES , HEARTS , BELLS
    };

    enum BasicType : char {
        UNTER = 0 , EIGHT , NINE , TEN , KING , ACE , JOKER , SEVEN 
    };

    virtual void Action() const
    {
        std::cout << "I am CCard :) \n";
    }

    bool operator == ( const std::shared_ptr< CCard > & card )
    {
        return ( this->m_color == card->m_color || this->m_type == card->m_type );
    }

    BasicType Type() const
    {
        return m_type;
    }

protected:
    Color m_color;
    BasicType m_type;
};