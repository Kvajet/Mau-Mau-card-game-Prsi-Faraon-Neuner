#pragma once
#include "CAce.h"
#include "CJoker.h"
#include "CSeven.h"
#include "CBasicCard.h"
#include <memory>
#include <vector>

class CGameRegister
{
public:
    enum PlayMode : char {
        NORMAL_MODE = 0 , JOKER_MODE
    };

    CGameRegister( const std::vector< std::shared_ptr< CCard > > & hand1 ,
                   const std::vector< std::shared_ptr< CCard > > & hand2 , 
                   const char & input ,
                   size_t & player1handIndex , 
                   size_t & player2handIndex )
        : m_hand1( hand1 ) , m_hand2( hand2 ) , m_input( input ) , m_player1handIndex( player1handIndex ) , m_player2handIndex( player2handIndex )
    {
    }

    void AssignCard( const std::shared_ptr< CCard > & card )
    {
        m_lastCard = card;
        if( IsLastSpecial() ) m_lastResolved = false;
    }

    bool Finished() const
    {
        return m_finished;
    }

    void ChangePlayer()
    {
        player = ! player;
    }

    bool IsLastSpecial() const
    {
        CCard::BasicType type = m_lastCard->Type();
        return ( type == CCard::BasicType::JOKER || type == CCard::BasicType::ACE || type == CCard::BasicType::SEVEN );
    }

    // for CRenderer purposed are public
    CCard::Color m_actColor = CCard::Color::ACORNS;
    std::shared_ptr< CCard > m_lastCard;

    const std::vector< std::shared_ptr< CCard > > & m_hand1;
    const std::vector< std::shared_ptr< CCard > > & m_hand2;

    bool m_finished = false;
    bool m_lastResolved = false;
    size_t m_sevenAmplifier = 1;
    size_t player = 0;
    const char & m_input;
    size_t & m_player1handIndex , & m_player2handIndex;

private:
    bool m_isLastBlocking = false;
};
