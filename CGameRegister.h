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
    }

    bool Finished() const
    {
        return m_finished;
    }

    bool HasCounterplay() const
    {
        if( m_lastCard->Type() == CCard::BasicType::SEVEN )
        {
            for( const auto & it : ( player ) ? m_hand1 : m_hand2 )
                if( it->Type() == CCard::BasicType::SEVEN ) return true;
        }
        else
        {
            for( const auto & it : ( player ) ? m_hand1 : m_hand2 )
                if( it->Type() == CCard::BasicType::ACE ) return true;
        }
        return false;
    }

    void ChangePlayer()
    {
        player = ! player;
    }

    bool IsLastSpecial() const
    {
        CCard::BasicType type = m_lastCard->Type();
        return type == CCard::BasicType::JOKER || type == CCard::BasicType::ACE || type == CCard::BasicType::SEVEN;
    }

    // bool - true => player continues, false => second player plays
    bool Play()
    {
        if( m_isLastBlocking && HasCounterplay() )
            return false;
    }

    // for CRenderer purposed are public
    CCard::Color m_actColor;
    std::shared_ptr< CCard > m_lastCard;

    const std::vector< std::shared_ptr< CCard > > & m_hand1;
    const std::vector< std::shared_ptr< CCard > > & m_hand2;

    bool m_finished = false;
    size_t player = 0;
    const char & m_input;
    size_t & m_player1handIndex , & m_player2handIndex;

private:
    bool m_isLastBlocking = false;
};
