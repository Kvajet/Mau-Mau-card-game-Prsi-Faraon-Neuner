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

    friend bool operator == ( const std::shared_ptr< CCard > & card1 , const std::shared_ptr< CCard > & card2 )
    {
        return ( card1->m_color == card2->m_color || card1->m_type == card2->m_type );
    }

    friend std::ostream & operator << ( std::ostream & os , const std::shared_ptr< CCard > & card )
    {
        os << "type: " << card->m_type << " color: " << card->m_color;

        return os;
    }

    std::string Stringify() const
    {
        return std::string( m_cardNamesArray[ m_type ] ) + " - " + std::string( m_colorsArray[ m_color ] );
    }

    BasicType Type() const
    {
        return m_type;
    }

    Color CColor() const
    {
        return m_color;
    }

    const char * TranslateColor( size_t index )
    {
        return m_colorsArray[ index ];
    }

protected:
    Color m_color;
    BasicType m_type;
    
    const char * const m_cardNamesArray[ 8 ] = {
        "spodek" , "osma" , "devítka" , "desítka" , "král" , "eso" , "měnič" , "sedma"
    };

    const char * const m_colorsArray[ 4 ] = {
        "žaludy" , "zelený" , "červený" , "kule"
    };
};