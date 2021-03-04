#include "CGameRegister.h"
#include <iostream>
#include <vector>
#include <memory>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>

class CRenderer
{
public:
    CRenderer( const std::shared_ptr< CGameRegister > & gRegister , 
               const CGameRegister::PlayMode & mode , 
               const size_t & colorIndex )
        : m_register( gRegister ) , m_mode( mode ) , m_colorIndex( colorIndex )
    {
        tcgetattr( fileno( stdin ) , &terminal );
        terminal.c_lflag &= ~ICANON & ~ECHO;
        tcsetattr( fileno( stdin ) , TCSANOW , &terminal );
    }

    ~CRenderer()
    {
        tcgetattr( fileno( stdin ) , &terminal );
        terminal.c_lflag |= ICANON | ECHO;
        tcsetattr( fileno( stdin ) , TCSANOW,  &terminal );
    }

    enum StickTo : char {
        LEFT = 0 , MIDDLE , RIGHT
    };

    void Render( size_t remCards ) const
    {
        RefreshSize();
        system( "clear" );

        if( m_register->Finished() )
        {
            std::string tmp = m_register->m_hand1.empty() ? "1" : "2";
            PrintToPos( "Hráč " + tmp + " vyhrál!" , StickTo::MIDDLE );
        }
        else if( m_mode == CGameRegister::PlayMode::NORMAL_MODE )
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
        else
        {
            for( size_t i = 0 ; i < CCard::m_totalColors ; i++ )
                PrintToPos(
                    i == m_colorIndex ? PLAYER1_COLOR + std::string( CCard::m_colorsArray[ i ] ) + TERMINAL_RESET : std::string( CCard::m_colorsArray[ i ] ) ,
                    StickTo::MIDDLE
                );
        }
    }

private:
    void RefreshSize() const
    {
        ioctl( STDOUT_FILENO, TIOCGWINSZ, &m_window );
    }

    void PrintTopCard( size_t remCards ) const
    {
        PrintToPos(
            "Top card: " + 
            m_register->m_lastCard->Stringify() + 
            " - remaining cards: " + 
            std::to_string( remCards ) + 
            " - color: " + 
            CCard::m_colorsArray[ m_register->m_actColor ] , 
            StickTo::MIDDLE
        );
    }

    void PrintMargin( size_t size ) const
    { 
        for( size_t i = 0 ; i < size ; i++ ) std::cout << " ";
    }

    void PrintToPos( const std::string & str , StickTo stick ) const
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

    struct termios terminal;
    mutable struct winsize m_window;
    const std::shared_ptr< CGameRegister > & m_register;
    const CGameRegister::PlayMode & m_mode;
    const size_t & m_colorIndex;

    static constexpr const char * PLAYER1_COLOR  = "\033[0;32m";
    static constexpr const char * PLAYER2_COLOR  = "\033[0;34m";
    static constexpr const char * CHOSEN_CARD    = "\033[0;33m";
    static constexpr const char * TERMINAL_RESET = "\033[0m";
};