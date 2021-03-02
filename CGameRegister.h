#include "CAce.h"
#include "CJoker.h"
#include "CSeven.h"
#include "CBasicCard.h"
#include <memory>
#include <vector>

class CGameRegister
{
public:
    CGameRegister( const std::vector< std::shared_ptr< CCard > > & hand1 , const std::vector< std::shared_ptr< CCard > > & hand2 )
        : m_hand1( hand1 ) , m_hand2( hand2 )
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

    // bool - true => player continues, false => second player plays
    bool Play()
    {
        if( m_isLastBlocking && HasCounterplay() )
            return false;
    }

private:
    CCard::Color m_actColor;
    std::shared_ptr< CCard > m_lastCard;
    size_t player = 0;
    bool m_finished = false;
    bool m_isLastBlocking = false;

    const std::vector< std::shared_ptr< CCard > > & m_hand1;
    const std::vector< std::shared_ptr< CCard > > & m_hand2;
};
