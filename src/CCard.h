#pragma once
#include <iostream>
#include <memory>
#include <cstring>

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

    CCard( Color color , BasicType type );

    friend bool operator == ( const std::shared_ptr< CCard > & card1 , const std::shared_ptr< CCard > & card2 )
    {
        return ( card1->m_color == card2->m_color || card1->m_type == card2->m_type );
    }

    friend std::ostream & operator << ( std::ostream & os , const std::shared_ptr< CCard > & card )
    {
        os << "type: " << card->m_type << " color: " << card->m_color;

        return os;
    }

    std::string Stringify() const;
    BasicType Type() const;
    Color CColor() const;

    static const size_t m_totalColors = 4;
    static const size_t m_totalTypes  = 8;
    static constexpr const char * const m_colorsArray[ m_totalColors ] = {
        "žaludy" , "zelený" , "červený" , "kule"
    };
    static constexpr const char * const m_cardNamesArray[ m_totalTypes ] = {
        "spodek" , "osma" , "devítka" , "desítka" , "král" , "eso" , "měnič" , "sedma"
    };
private:
    Color m_color;
    BasicType m_type;
};