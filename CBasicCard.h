#pragma once
#include "CCard.h"

class CBasicCard : public CCard 
{
public:
    CBasicCard( Color color , BasicType type )
    {
        m_color = color;
        m_type = type;
    }

    void Action() const override
    {
        std::cout << m_type << " - " << m_color << "\n";
    }

private:
};