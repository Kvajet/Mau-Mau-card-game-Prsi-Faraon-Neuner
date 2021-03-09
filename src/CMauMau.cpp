#include "CMauMau.h"

CMauMau::CMauMau()
    : m_register( std::make_shared< CGameRegister >( m_hand1 , m_hand2 , m_input , m_player1handIndex , m_player2handIndex ) ) , 
      m_deck( std::make_shared< CDeck >( m_register , m_hand1 , m_hand2 , m_mode , m_colorIndex ) ) ,
      m_renderer( std::make_unique< CRenderer >( m_register , m_mode , m_colorIndex ) )
{
}

void CMauMau::Play()
{
    while( m_input != 'l' && ! m_register->m_finished )
    {
        m_renderer->Render( m_deck->RemainingCardsInPile() );
        ResolveInput();
    }
    m_renderer->Render( m_deck->RemainingCardsInPile() );
}

void CMauMau::ResolveInput()
{
    m_input = getchar();
    size_t & playerIndex = m_register->player ? m_player2handIndex : m_player1handIndex;
    size_t handSize = m_register->player ? m_hand2.size() : m_hand1.size();

    switch( m_input )
    {
        case 'w':
            if( m_mode == CGameRegister::PlayMode::NORMAL_MODE )
                playerIndex = ( playerIndex - 1 ) % handSize;
            else if( m_mode == CGameRegister::PlayMode::JOKER_MODE )
                m_colorIndex = ( m_colorIndex - 1 ) % CCard::m_totalColors;
            break;
        case 's':
            if( m_mode == CGameRegister::PlayMode::NORMAL_MODE )
                playerIndex = ( playerIndex + 1 ) % handSize;
            else if( m_mode == CGameRegister::PlayMode::JOKER_MODE )
                m_colorIndex = ( m_colorIndex + 1 ) % CCard::m_totalColors;
            break;
        // develop feature only
        // case 'e':
        //     m_register->ChangePlayer();
        //     break;
        case 'd':
            if( m_mode == CGameRegister::PlayMode::NORMAL_MODE ) m_deck->Draw();
            break;
        case 'r':
            m_deck->Play();
            break;
        default:
            break;
    }

    if( ! m_hand1.size() || ! m_hand2.size() )
        m_register->m_finished = true;
}