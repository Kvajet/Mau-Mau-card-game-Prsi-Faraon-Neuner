#pragma once
#include <iostream>
#include "CCard.h"

class CAce : public CCard
{
public:
    CAce( Color color )
    {
        m_color = color;
        m_type = BasicType::ACE;
    }

    void Action() const override
    {
        std::cout << "Ace - " << m_color << "\n";
    }

private:
};