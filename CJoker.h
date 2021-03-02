#pragma once
#include "CCard.h"

class CJoker : public CCard
{
public:
    CJoker( Color color )
    {
        m_color = color;
        m_type = BasicType::JOKER;
    }

    void Action() const override
    {
        std::cout << "Joker - " << m_color << "\n";
    }

private:
};