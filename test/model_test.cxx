#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

// These pass with the starter code and should continue
// to pass.

TEST_CASE("Passes with starter code")
{
    Model m(8, 8);
    CHECK(m.all_positions() == Model::Rectangle {0, 0, 8, 8});
    CHECK_FALSE(m.is_game_over());
    CHECK(m.turn() == Player::dark);
    CHECK(m.winner() == Player::neither);
    CHECK(m[{0, 0}] == Player::neither);
    CHECK(m.find_move({0, 0}) == nullptr);
    CHECK_THROWS_AS(m.play_move({0, 0}), Client_logic_error);
}

// This fails with the starter code, but should pass.
TEST_CASE("Fails with starter code")
{
    Model m(6);
    CHECK(m.find_move({2, 2}));
}

// This fails with the starter code, but should pass.
TEST_CASE("Throws with starter code")
{
    Model m(4);
    m.play_move({1, 1});
}

// YOU NEED MANY MORE TESTS!


///
/// Example of how to set up and use Test_access
///

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    // Sets the player at `posn` to `player`.
    void set_player(Model::Position posn, Player player);
    // Gives direct access to `model.next_moves_` so our tests can modify it:
    Move_map& next_moves();
    Board & board ()
    {
        return model . board_ ;
    }
    Position_set
    find_flips ( Model :: Position p ,
                 Model :: Dimensions d )
    {
        return model . find_flips_ (p , d );
    }
};

// Example of using Test_access to modify the model state to set up our test.
TEST_CASE("Small Game")
{
    ///
    /// SETUP
    ///

    Model model(4, 4);
    Test_access access(model);

    // Use Test_access to place pieces on the board without going through
    // Model::play_move():
    access.set_player({1, 1}, Player::dark);
    access.set_player({2, 1}, Player::dark);
    access.set_player({1, 2}, Player::dark);
    access.set_player({2, 2}, Player::dark);

    // Use Test_access to set `model.next_moves_` to allow the particular
    // (illegal) move that we'd like to try:
    access.next_moves()[{0, 0}] = Position_set {{0, 0}};

    ///
    /// TEST OPERATION
    ///

    // Now we can play the move, because model.next_moves_ says so:
    model.play_move({0, 0});

    ///
    /// CHECKS
    ///

    // Check that the game is over and Dark won:
    CHECK(model.turn() == Player::neither);
    CHECK(model.winner() == Player::dark);

    // Construct the set of board positions that should contain Player::dark:
    Position_set darks {{0, 0}, {1, 1}, {2, 1}, {1, 2}, {2, 2}};

    // Go through each position on the board, confirming that the positions in
    // the `darks` set contain Player::dark and all other positions contain
    // Player::neither.

    for (auto posn : model.all_positions()) {
        Player expected = darks[posn] ? Player::dark : Player::neither;
        CHECK(model[posn] == expected);
    }
}



TEST_CASE( " simple flips case " )
{
    Model model;
    Test_access t { model };
    t . board ()[{2 , 2}] = Player :: dark ;
    t . board ()[{2 , 3}] = Player :: light ;
    Position_set f ;
    f = t . find_flips ({2 , 4} , {0 , 1});
    CHECK ( f . empty ());
    f = t . find_flips ({2 , 4} , {0 , -1});
    CHECK ( f == Position_set {{2 , 3}});
}

TEST_CASE("play move 0") {
    Model model(4, 4);
    Test_access access(model);

    ///
    /// TEST OPERATION
    ///

    access.next_moves()[{1, 1}] = Position_set {{1, 1}};

    // Now we can play the move, because model.next_moves_ says so:
    model.play_move({1, 1});

    ///
    /// CHECKS
    ///

    // Construct the set of board positions that should contain Player::dark:
    Position_set darks {{1, 1}};

    // Go through each position on the board, confirming that the positions in
    // the `darks` set contain Player::dark and all other positions contain
    // Player::neither.
    for (auto posn : model.all_positions()) {
        Player expected = darks[posn] ? Player::dark : Player::neither;
        CHECK(model[posn] == expected);
    }
}

TEST_CASE("clicking on occupied square does nothing") {
    Model model(4, 4);
    Test_access access(model);

    ///
    /// TEST OPERATION
    ///
    access.set_player({1, 1}, Player::dark);

    access.next_moves()[{1, 1}] = Position_set {{1, 1}};

    // Now we can play the move, because model.next_moves_ says so:
    model.play_move({1, 1});

    ///
    /// CHECKS
    ///

    // Construct the set of board positions that should contain Player::dark:
    Position_set darks {{1, 1}};

    // Go through each position on the board, confirming that the positions in
    // the `darks` set contain Player::dark and all other positions contain
    // Player::neither.
    for (auto posn : model.all_positions()) {
        Player expected = darks[posn] ? Player::dark : Player::neither;
        CHECK(model[posn] == expected);
    }
}


TEST_CASE("tie"){
    ///
    /// SETUP
    ///

    Model model(2, 2);
    Test_access access(model);

    // Use Test_access to place pieces on the board without going through
    // Model::play_move():
    access.set_player({0, 0}, Player::dark);
    access.set_player({0, 1}, Player::dark);
    access.set_player({1, 0}, Player::light);
    access.set_player({1, 1}, Player::light);


    ///
    /// CHECKS
    ///

    CHECK(model.winner() == Player::neither);
}

TEST_CASE( "empty next moves"){
    Model model(4, 4);
    Test_access access(model);

    // Use Test_access to place pieces on the board without going through
    // Model::play_move():
    access.set_player({1, 1}, Player::dark);
    access.set_player({1, 2}, Player::dark);
    access.set_player({2, 1}, Player::dark);
    access.set_player({2, 2}, Player::dark);

    access.next_moves()[{0, 0}] = Position_set {{0, 0}};

    model.play_move({0, 0});
    CHECK(access.next_moves().empty());

}
///
/// Member function definitions for Test_access
///

Test_access::Test_access(Model& model)
        : model(model)
{ }

void
Test_access::set_player(Model::Position posn, Player player)
{
    model.board_[posn] = player;
}

Move_map&
Test_access::next_moves()
{
    return model.next_moves_;
}
