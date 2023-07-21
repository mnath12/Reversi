#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    // TODO: initialize `next_moves_` to `turn_`'s available moves
    compute_next_moves_();
}

Model::Rectangle
Model::all_positions() const
{
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
        throw Client_logic_error("Model::play_move: no such move");
    }

    // TODO: actually execute the move, advance the turn, refill
    // `next_moves_`, etc.
    really_play_move_(*movep);
    compute_next_moves_();
}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//

// Citation: I consulted with Ravi for help on this function. From the discussion I realized that the while loop
// should iterate forever unless certain conditions are met and I also discussed what order I should check the conditions in
Position_set
Model::find_flips_(Position current, Dimensions dir) const
{
    // TODO: HELPER FUNCTION
    Position_set ps;
    //Position iter_pos = current;

    int i = 1;

    while(true) {
        Position iter_pos = current.right_by(dir.width*i);
        iter_pos = iter_pos.down_by(dir.height*i);
        if (!board_.good_position(iter_pos)) {
            return Position_set();
        } else if (board_[iter_pos] == turn_) {
            return ps;
        } else if (board_[iter_pos] == other_player(turn_)) {
            ps[iter_pos] = true;
        } else if (board_[iter_pos] == Player::neither) {
            return Position_set();
        }
        i++;
    }

}

Position_set
Model::evaluate_position_(Position pos) const
{
    // TODO: HELPER FUNCTION
    if (board_[pos] == Player::neither){
        Position_set ps = Position_set();
        for (Dimensions direction : board_.all_directions()) {
            Position_set result = find_flips_(pos, direction);
            ps |= result;
        }
        if (ps == Position_set()) {
            return Position_set();
        } else {
            ps[pos] = true;
        }
        return ps;
    } else {
        return Position_set();
    }

}

void
Model::compute_next_moves_()
{
    // TODO: HELPER FUNCTION
    // Before evaluating every board position, we need to check whether
    // any of the four center positions (board_.center_positions()) are
    // unoccupied, which would indicate that we are still in the opening
    // phase of the game.
    next_moves_.clear();
    for (Position center_pos : board_.center_positions()) {
        if ( board_[center_pos] == Player::neither ) {
            next_moves_ [ center_pos ] = { center_pos };
        }
    }
    // if, after adding any unoccupied center positions, next_moves_ is
    // non-empty, then we are still in the opening phase and should return
    // without checking the rest of the board.
    if (!next_moves_.empty()) {
        return;
    } else {
        for ( Position pos : board_.all_positions() ) {
            if (evaluate_position_(pos) != Position_set()) {
                next_moves_ [ pos ] = evaluate_position_(pos);
            }
        }
    }
}

bool
Model::advance_turn_()
{
    // TODO: HELPER FUNCTION
    turn_ = other_player(turn());
    compute_next_moves_();
    return !next_moves_.empty();
}

void
Model::set_game_over_()
{
    // TODO: HELPER FUNCTION
    turn_ = Player::neither;
    // Count the number of tiles occupied by each player (light & dark) and set the winner accordingly
    int light_tiles = board_.count_player(Player::light);
    int dark_tiles = board_.count_player(Player::dark);
    if ( light_tiles > dark_tiles) {
        winner_ = Player::light;
    } else if (light_tiles < dark_tiles) {
        winner_ = Player::dark;
    } else {
        winner_ = Player::neither;
    }
}

void
Model::really_play_move_(Move move)
{
    // TODO: HELPER FUNCTION
    board_.set_all(move.second, turn());
    bool call_1 = advance_turn_();
    bool call_2 = advance_turn_();
    if (call_1) {
        turn_ = other_player(turn());
    } else {
        turn_ = turn();
    }
    if (!(call_1) && !(call_2)) {
        set_game_over_();
    }
}
