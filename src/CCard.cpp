#include "CCard.h"

CCard::CCard( Color color , BasicType type )
    : m_color( color ) , m_type( type )
{
}

bool operator == ( const std::shared_ptr< CCard > & card1 , const std::shared_ptr< CCard > & card2 )
{
    return ( card1->m_color == card2->m_color || card1->m_type == card2->m_type );
}

std::ostream & operator << ( std::ostream & os , const std::shared_ptr< CCard > & card )
{
    os << "type: " << card->m_type << " color: " << card->m_color;

    return os;
}

std::string CCard::Stringify() const
{
    return m_cardNamesArray[ m_type ] + std::string( " - " ) + m_colorsArray[ m_color ];
}

CCard::BasicType CCard::Type() const
{
    return m_type;
}

CCard::Color CCard::CColor() const
{
    return m_color;
}
