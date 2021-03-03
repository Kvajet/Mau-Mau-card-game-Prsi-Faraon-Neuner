#include "CDeck.h"
#include "CRenderer.h"

class CMauMau
{
public:
    CMauMau()
        : m_register( std::make_shared< CGameRegister >( m_hand1 , m_hand2 , m_input , m_player1handIndex , m_player2handIndex ) ) , 
          m_deck( std::make_shared< CDeck >( m_register , m_hand1 , m_hand2 ) ) ,
          m_renderer( std::make_unique< CRenderer >( m_register ) )
    {
    }

    void Play()
    {
        while( m_input != 'l' )
        {
            m_renderer->Render( m_deck->RemainingCardsInPile() );
            ResolveInput();
        }
    }

private:
    void ResolveInput()
    {
        m_input = getchar();
        size_t & playerIndex = m_register->player ? m_player2handIndex : m_player1handIndex;
        size_t handSize = m_register->player ? m_hand2.size() : m_hand1.size();

        switch( m_input )
        {
            case 'w':
                if( playerIndex ) playerIndex--;
                break;
            case 's':
                if( playerIndex + 1 < handSize ) playerIndex++;
                break;
            case 'e':
                m_register->ChangePlayer();
                break;
            case 'd':
                m_deck->Draw();
                break;
            case 'r':
                m_deck->Play();
                break;
            default:
                break;
        }
    }

    char m_input = 0;
    size_t m_player1handIndex = 0; // TODO - check range of hand size
    size_t m_player2handIndex = 0;

    std::vector< std::shared_ptr< CCard > > m_hand1;
    std::vector< std::shared_ptr< CCard > > m_hand2;

    std::shared_ptr< CGameRegister > m_register;
    std::shared_ptr< CDeck > m_deck;
    std::unique_ptr< CRenderer > m_renderer;
};