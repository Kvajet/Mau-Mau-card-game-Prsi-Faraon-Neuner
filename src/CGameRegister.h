#pragma once
#include "CCard.h"
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
                   size_t & player2handIndex );
    void AssignCard( const std::shared_ptr< CCard > & card , const std::vector< std::shared_ptr< CCard > > & pile , bool startCall = false );
    void ChangePlayer();
    bool IsLastSpecial() const;

    CCard::Color m_actColor = CCard::Color::ACORNS;
    std::shared_ptr< CCard > m_lastCard;

    const std::vector< std::shared_ptr< CCard > > & m_hand1;
    const std::vector< std::shared_ptr< CCard > > & m_hand2;

    bool m_lastResolved = true;
    size_t m_sevenAmplifier = 1;
    size_t player = 0;
    const char & m_input;
    size_t & m_player1handIndex , & m_player2handIndex;
    bool m_finished = false;

private:
};
