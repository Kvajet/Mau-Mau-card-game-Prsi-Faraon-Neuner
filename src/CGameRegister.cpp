#include "CGameRegister.h"

CGameRegister::CGameRegister( const std::vector< std::shared_ptr< CCard > > & hand1 ,
                              const std::vector< std::shared_ptr< CCard > > & hand2 , 
                              const char & input ,
                              size_t & player1handIndex , 
                              size_t & player2handIndex )
    : m_hand1( hand1 ) , 
      m_hand2( hand2 ) , 
      m_input( input ) , 
      m_player1handIndex( player1handIndex ) , 
      m_player2handIndex( player2handIndex )
{
}

void CGameRegister::AssignCard( const std::shared_ptr< CCard > & card , const std::vector< std::shared_ptr< CCard > > & pile , bool startCall )
{
    m_lastCard = card;
    CCard::BasicType type = card->Type();

    if( type == CCard::BasicType::JOKER )
    {
        m_actColor = card->CColor();
        m_lastResolved = false;
    }
    else if( startCall &&
             ( type == CCard::BasicType::ACE || type == CCard::BasicType::SEVEN ) && 
             ( card->CColor() == pile.front()->CColor() ) )
        m_lastResolved = false;
    else if( ! startCall && ( type == CCard::BasicType::ACE || type == CCard::BasicType::SEVEN ) )
        m_lastResolved = false;
}

void CGameRegister::ChangePlayer()
{
    player = ! player;
}

bool CGameRegister::IsLastSpecial() const
{
    CCard::BasicType type = m_lastCard->Type();
    return ( type == CCard::BasicType::JOKER || type == CCard::BasicType::ACE || type == CCard::BasicType::SEVEN );
}