#pragma once
#include "CCard.h"

class CSeven : public CCard
{
public:
    CSeven( Color color )
    {
        m_color = color;
        m_type = BasicType::SEVEN;
    }

    void Action() const override
    {
        std::cout << "Seven - " << m_color << "\n";
    }

private:
};