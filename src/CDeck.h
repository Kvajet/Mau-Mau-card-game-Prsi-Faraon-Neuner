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
           const size_t & colorIndex )
        : m_register( gameRegister ) , m_hand1( hand1 ) , m_hand2( hand2 ) , m_mode( mode ) , m_colorIndex( colorIndex )
    {
        Reserve();
        std::srand( std::time( nullptr ) );

        Generate();
        Randomize();

        for( size_t i = 0 ; i < START_CARDS ; i++ )
        {
            m_hand1.push_back( DrawOne() );
            m_hand2.push_back( DrawOne() );
        }
        
        m_register->AssignCard( m_pile.back() );
        m_usedCardsVec.push_back( m_pile.back() );
        m_pile.pop_back();

        if( m_register->m_lastCard->Type() == CCard::BasicType::JOKER ) m_register->m_actColor = m_pile.front()->CColor();
    }

    void Draw( bool innerCall = false )
    {
        if( m_register->IsLastSpecial() && m_register->m_lastCard->Type() != CCard::BasicType::JOKER && ! innerCall )
            return;

        if( m_pile.size() )
        {
            if( m_register->player ) m_hand2.push_back( DrawOne() );
            else                     m_hand1.push_back( DrawOne() );

            if( ! innerCall ) m_register->ChangePlayer();
        }
        if( ! m_pile.size() && m_usedCardsVec.size() > 1 )
        {
            std::shared_ptr< CCard > lastCardHolder = m_usedCardsVec.back();
            m_usedCardsVec.pop_back();

            while( m_usedCardsVec.size() )
            {
                m_pile.push_back( m_usedCardsVec.back() );
                m_usedCardsVec.pop_back();
            }
            
            m_usedCardsVec.push_back( lastCardHolder );
        }
    }

    void Play()
    {
        if( m_mode == CGameRegister::PlayMode::JOKER_MODE )
        {
            m_register->m_actColor = ( CCard::Color )m_colorIndex;
            m_mode = CGameRegister::PlayMode::NORMAL_MODE;
            return;
        }

        if( m_register->IsLastSpecial() && ! m_register->m_lastResolved )
        {
            if( HasCounterplay() )
            {
                if( m_register->m_lastCard->Type() == CCard::BasicType::SEVEN )
                {
                    std::vector< std::shared_ptr < CCard > > & hand = m_register->player ? m_hand2 : m_hand1; 
                    size_t index = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;

                    if( hand[ index ]->Type() == CCard::BasicType::SEVEN )
                    {
                        m_register->m_sevenAmplifier++;
                        DropCard( hand , index );
                    }
                }
                else
                {
                    std::vector< std::shared_ptr < CCard > > & hand = m_register->player ? m_hand2 : m_hand1; 
                    size_t index = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;

                    if( hand[ index ]->Type() == CCard::BasicType::ACE )
                    {
                        DropCard( hand , index );
                    }
                }
            }
            else
            {
                if( m_register->m_lastCard->Type() == CCard::BasicType::SEVEN )      ActionSeven();
                else if( m_register->m_lastCard->Type() == CCard::BasicType::JOKER ) ActionJoker();
                else                                                                 m_register->ChangePlayer();
            }
        }
        else
        {
            std::vector< std::shared_ptr < CCard > > & hand = m_register->player ? m_hand2 : m_hand1; 
            size_t index = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;

            if( hand[ index ]->Type() == CCard::BasicType::JOKER )
            {
                m_mode = CGameRegister::PlayMode::JOKER_MODE;
                DropCard( hand , index , true );
                return;
            }

            DropCard( hand , index );
        }
    }

    size_t RemainingCardsInPile() const
    {
        return m_pile.size();
    }

private:
    void Generate()
    {
        for( char i = CCard::Color::ACORNS ; i <= CCard::Color::BELLS ; i++ )
            for( char k = CCard::BasicType::UNTER ; k <= CCard::BasicType::SEVEN ; k++ )
                m_pile.push_back( std::make_shared< CCard >( static_cast< CCard::Color >( i ) , static_cast< CCard::BasicType >( k ) ) );
    }

    void DropCard( std::vector< std::shared_ptr < CCard > > & hand , 
                   size_t index , bool innerCall = false )
    {
        std::shared_ptr< CCard > currentCard = hand[ index ];

        if( currentCard == m_register->m_lastCard || 
            innerCall || 
            ( m_register->m_lastCard->Type() == CCard::BasicType::JOKER && m_register->m_actColor == currentCard->CColor() ) )
        {
            m_register->m_lastCard = currentCard;
            hand.erase( hand.begin() + index );
            m_usedCardsVec.push_back( currentCard );
            if( index >= hand.size() ) m_register->player ? m_register->m_player2handIndex-- : m_register->m_player1handIndex--;
            m_register->ChangePlayer();
        }
    }

    std::shared_ptr< CCard > DrawOne()
    {
        std::shared_ptr< CCard > tmp = m_pile.back();
        m_pile.pop_back();
        m_usedCards++;

        return tmp;
    }

    void Randomize()
    {
        unsigned int remainingCards = TOTAL_CARDS - m_usedCards;

        m_randBuffer = m_pile;
        m_pile.clear();

        int rand;
        while( remainingCards )
        {
            rand = std::rand() % remainingCards;
            auto it = m_randBuffer.begin() + rand;
            m_pile.push_back( *it );
            m_randBuffer.erase( it );
            remainingCards--;
        }
    }

    bool HasCounterplay() const
    {
        const std::vector< std::shared_ptr< CCard > > & hand = m_register->player ? m_hand2 : m_hand1;

        switch( m_register->m_lastCard->Type() )
        {
            case CCard::BasicType::SEVEN:
                for( const auto & it : hand )
                    if( it->Type() == CCard::BasicType::SEVEN ) return true;
                break;
            case CCard::BasicType::ACE:
                for( const auto & it : hand )
                    if( it->Type() == CCard::BasicType::ACE ) return true;
                break;
            case CCard::BasicType::JOKER: break;
            default:                      break;
        }

        return false;
    }

    void ActionSeven()
    {
        for( size_t i = 0 ; i < 2 * m_register->m_sevenAmplifier ; i++ ) Draw( true );
        m_register->ChangePlayer();
        m_register->m_lastResolved = true;
        m_register->m_sevenAmplifier = 1;
        m_register->m_lastResolved = true;
    }

    void ActionJoker()
    {
        std::vector< std::shared_ptr < CCard > > & hand = m_register->player ? m_hand2 : m_hand1; 
        size_t index = m_register->player ? m_register->m_player2handIndex : m_register->m_player1handIndex;

        if( hand[ index ]->CColor() == m_register->m_actColor )
            DropCard( hand , index );
    }

    void ActionAce()
    {
        m_register->ChangePlayer();
        m_register->m_lastResolved = true;
    }

    void Reserve()
    {
        m_pile.reserve( TOTAL_CARDS );
        m_randBuffer.reserve( TOTAL_CARDS );
        m_usedCardsVec.reserve( TOTAL_CARDS );
        m_hand1.reserve( TOTAL_CARDS );
        m_hand2.reserve( TOTAL_CARDS );
    }

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