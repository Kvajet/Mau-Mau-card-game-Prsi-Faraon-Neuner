#pragma once
#include "CDeck.h"
#include "CRenderer.h"

class CMauMau
{
public:
    CMauMau();
    void Play();

private:
    void ResolveInput();

    char m_input = 0;
    CGameRegister::PlayMode m_mode = CGameRegister::PlayMode::NORMAL_MODE;
    size_t m_colorIndex = 0;
    size_t m_player1handIndex = 0;
    size_t m_player2handIndex = 0;

    std::vector< std::shared_ptr< CCard > > m_hand1;
    std::vector< std::shared_ptr< CCard > > m_hand2;

    std::shared_ptr< CGameRegister > m_register;
    std::shared_ptr< CDeck > m_deck;
    std::unique_ptr< CRenderer > m_renderer;
};