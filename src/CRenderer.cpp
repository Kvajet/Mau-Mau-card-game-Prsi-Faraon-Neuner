#include "CRenderer.h"

CRenderer::CRenderer( const std::shared_ptr< CGameRegister > & gRegister , 
                      const CGameRegister::PlayMode & mode , 
                      const size_t & colorIndex )
    : m_register( gRegister ) , m_mode( mode ) , m_colorIndex( colorIndex )
{
    tcgetattr( fileno( stdin ) , &terminal );
    terminal.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr( fileno( stdin ) , TCSANOW , &terminal );
}

CRenderer::~CRenderer()
{
    tcgetattr( fileno( stdin ) , &terminal );
    terminal.c_lflag |= ICANON | ECHO;
    tcsetattr( fileno( stdin ) , TCSANOW,  &terminal );
}

void CRenderer::Render( size_t remCards ) const
{
    RefreshSize();
    system( "clear" );

    if( m_register->m_finished )                              PrintFinishScreen();
    else if( m_mode == CGameRegister::PlayMode::NORMAL_MODE ) PrintNormalMode( remCards );
    else                                                      PrintJokerMode();
}

void CRenderer::RefreshSize() const
{
    ioctl( STDOUT_FILENO, TIOCGWINSZ, &m_window );
}

void CRenderer::PrintTopCard( size_t remCards ) const
{
    PrintToPos(
        "Top card: " + 
        m_register->m_lastCard->Stringify() + 
        " - remaining cards: " + 
        std::to_string( remCards ) + 
        " - color: " + 
        CCard::m_colorsArray[ m_register->m_actColor ] + 
        " - m_lastResolved: " + 
        std::to_string( m_register->m_lastResolved ), 
        StickTo::MIDDLE
    );
}

void CRenderer::PrintMargin( size_t size ) const
{ 
    for( size_t i = 0 ; i < size ; i++ ) std::cout << " ";
}

void CRenderer::PrintToPos( const std::string & str , StickTo stick ) const
{
    size_t margin = ( m_window.ws_col - str.length() ) / 2;
    switch( stick )
    {
        case StickTo::LEFT:                                                  break;
        case StickTo::MIDDLE: PrintMargin( margin );                         break;
        case StickTo::RIGHT:  PrintMargin( m_window.ws_col - str.length() ); break;
    }
    std::cout << str << "\n";
}

void CRenderer::PrintNormalMode( size_t remCards ) const
{
    PrintTopCard( remCards );

    size_t index = 0;
    size_t playerIndex = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;
    std::string defPrefix = m_register->player ? PLAYER1_COLOR : PLAYER2_COLOR;
    for( const auto & it : m_register->player ? m_register->m_hand2 : m_register->m_hand1 )
    {
        PrintToPos(
            ( playerIndex == index ? CHOSEN_CARD : defPrefix ) + it->Stringify() + TERMINAL_RESET , 
            m_register->player ? StickTo::RIGHT : StickTo::LEFT );
        index++;
    }
}

void CRenderer::PrintJokerMode() const
{
    for( size_t i = 0 ; i < CCard::m_totalColors ; i++ )
        PrintToPos(
            i == m_colorIndex ? PLAYER1_COLOR + std::string( CCard::m_colorsArray[ i ] ) + TERMINAL_RESET : std::string( CCard::m_colorsArray[ i ] ) ,
            StickTo::MIDDLE
        );
}

void CRenderer::PrintFinishScreen() const
{
    std::string tmp = m_register->m_hand1.empty() ? "1" : "2";
    PrintToPos( "Hráč " + tmp + " vyhrál!" , StickTo::MIDDLE );
}