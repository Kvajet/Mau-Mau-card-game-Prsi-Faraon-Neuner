#include "CCard.h"
#include "CGameRegister.h"
#include <memory>
#include <vector>
#include <ctime>

class CDeck
{
public:
    CDeck( const std::shared_ptr< CGameRegister > & gameRegister ,
           std::vector< std::shared_ptr< CCard > > & hand1 ,
           std::vector< std::shared_ptr< CCard > > & hand2 ,
           CGameRegister::PlayMode & mode ,
           const size_t & colorIndex );
    void Draw( bool innerCall = false );
    void Play();
    size_t RemainingCardsInPile() const;

private:
    void Generate();
    void DropCard( std::vector< std::shared_ptr < CCard > > & hand , size_t index , bool innerCall = false );
    std::shared_ptr< CCard > DrawOne();
    void Randomize();
    bool HasCounterplay() const;
    void ActionSeven();
    void ActionJoker();
    void ActionAce();
    void Reserve();

    size_t m_usedCards = 0;
    std::vector< std::shared_ptr< CCard > > m_pile;
    std::vector< std::shared_ptr< CCard > > m_randBuffer;
    std::vector< std::shared_ptr< CCard > > m_usedCardsVec;

    std::shared_ptr< CGameRegister > m_register;
    std::vector< std::shared_ptr< CCard > > & m_hand1;
    std::vector< std::shared_ptr< CCard > > & m_hand2;

    CGameRegister::PlayMode & m_mode;
    const size_t & m_colorIndex;

    static size_t const TOTAL_CARDS = 32;
    static size_t const START_CARDS = 4;
};