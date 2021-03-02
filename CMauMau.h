#include "CDeck.h"

class CMauMau
{
public:
    CMauMau()
        : m_register( std::make_shared< CGameRegister >( m_hand1 , m_hand2 ) ) , m_deck( std::make_shared< CDeck >( m_register , m_hand1 , m_hand2 ) )
    {
    }

    void Play()
    {
        while( true )
        {
            // if( m_register->Finished() )
            // TODO - MOVE CONTROLS
        }
    }

private:
    size_t player1handIndex = 0; // TODO - check range of hand size
    size_t player2handIndex = 0;

    std::vector< std::shared_ptr< CCard > > m_hand1;
    std::vector< std::shared_ptr< CCard > > m_hand2;

    std::shared_ptr< CGameRegister > m_register;
    std::shared_ptr< CDeck > m_deck;
};