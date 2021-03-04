#include "CCard.h"

CCard::CCard( Color color , BasicType type )
    : m_color( color ) , m_type( type )
{
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
