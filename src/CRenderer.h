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
    enum StickTo : char {
        LEFT = 0 , MIDDLE , RIGHT
    };

    CRenderer( const std::shared_ptr< CGameRegister > & gRegister , 
               const CGameRegister::PlayMode & mode , 
               const size_t & colorIndex );
    ~CRenderer();
    void Render( size_t remCards ) const;

private:
    void RefreshSize() const;
    void PrintTopCard( size_t remCards ) const;
    void PrintMargin( size_t size ) const;
    void PrintToPos( const std::string & str , StickTo stick ) const;
    void PrintNormalMode( size_t remCards ) const;
    void PrintJokerMode() const;
    void PrintFinishScreen() const;

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