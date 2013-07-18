
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

namespace igloo_example {
 
  struct Position
  {
  };
  
  inline bool operator==(const Position&, const Position&)
  {
    return true;
  }
  
  
  struct Player
  {
    Player(const char* name) : name_(name) {}

    const std::string name_;
  };
  
  inline bool operator==(const Player& lhs, const Player& rhs)
  {
    return lhs.name_ == rhs.name_;
  }

  inline std::ostream& operator<<(std::ostream& stm, const Player& player)
  {
    stm << "{ name_: " << player.name_ << " }" << std::endl;
    return stm;
  }
  
  Player PlayerOne("One");  
  Player PlayerTwo("Two");

  struct Game
  {
    typedef std::vector<Position> PositionCollection;
    
    const PositionCollection& Positions() const
    {
      return positions_;
    }
    
    void Select(const Player* player)
    {
      player_ = player;
    }
    
    const Player& NextPlayer()
    {
      return *player_;
    }
    
    PositionCollection positions_;
    const Player* player_;
  };
  
  Position EmptyPosition;

  
Context(ANewlyStartedGame)
{
  Spec(ShouldHaveAnEmptyBoard)
  {
    Assert::That(game.Positions(), Has().All().EqualTo(EmptyPosition));
  }
  
  Context(PlayerOneIsSelectedToStart)
  {
    void SetUp()
    {
      Root().game.Select(&PlayerOne);
    }
    
    Spec(ItShouldBePlayerOnesTurn)
    {
      Assert::That(Parent().game.NextPlayer(), Equals(PlayerOne));
    }

    Context(PlayerTwoIsSelectedToStart)
    {
      void SetUp()
      {
        Root().game.Select(&PlayerTwo);
      }

      Spec(ItShouldBePlayerTwosTurn)
      {
        Assert::That(Root().game.NextPlayer(), Equals(PlayerTwo));
      }
    };
  };  
  
  Game game;
};
}
