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
    CRenderer( const std::shared_ptr< CGameRegister > & gRegister )
        : m_register( gRegister )
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

        if( m_register->m_finished )
        {
            std::string tmp = m_register->m_hand1.empty() ? "1" : "2";
            PrintToPos( "Hráč " + tmp + " vyhrál!" , StickTo::MIDDLE );
        }
        else
        {
            PrintTopCard( remCards );

            size_t index = 0;
            size_t playerIndex = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;
            std::string defPrefix = m_register->player ? "\033[0;32m" : "\033[0;34m";
            for( const auto & it : m_register->player ? m_register->m_hand2 : m_register->m_hand1 )
            {
                std::string tmp = ( playerIndex == index ? "\033[0;33m" : defPrefix ) + it->Stringify() + "\033[0m";
                PrintToPos( tmp , m_register->player ? StickTo::RIGHT : StickTo::LEFT );
                index++;
            }
        }
    }

private:

    void RefreshSize() const
    {
        ioctl( STDOUT_FILENO, TIOCGWINSZ, &m_window );
    }

    void PrintTopCard( size_t remCards ) const
    {
        PrintToPos( "Top card: " + m_register->m_lastCard->Stringify() + " - remaining cards: " + std::to_string( remCards ) , StickTo::MIDDLE );
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
            case StickTo::LEFT:
                std::cout << str;
                break;
            case StickTo::MIDDLE:
                PrintMargin( margin );
                std::cout << str;
                PrintMargin( margin );
                break;
            case StickTo::RIGHT:
                PrintMargin( m_window.ws_col - str.length() );
                std::cout << str;
                break;
        }
        std::cout << "\n";
    }

    struct termios terminal;
    mutable struct winsize m_window;
    const std::shared_ptr< CGameRegister > & m_register;
};