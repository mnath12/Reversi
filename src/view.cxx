#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 36;
static ge211::Color const square_sprite_color {0, 255, 0};
static ge211::Color const move_sprite_color {255, 0, 0};
static ge211::Color const black_player_sprite_color {0, 0, 0};
static ge211::Color const white_player_sprite_color {255, 255, 255};
static ge211::Color const white_turn_sprite_color {255, 255, 255};
static ge211::Color const black_turn_sprite_color {0, 0, 0};
static ge211::Color const game_over_sprite_color {211, 211, 211};
int offset = 5;

View::View(Model const& model)
        : model_(model),
        // You may want to add sprite initialization here
          square_sprite({ grid_size-offset, grid_size-offset}, square_sprite_color),
          move_sprite({grid_size-offset,grid_size-offset}, move_sprite_color),
          game_over_sprite({grid_size-offset,grid_size-offset}, game_over_sprite_color),
          white_turn_sprite(grid_size * (.5/2), white_turn_sprite_color),
          black_turn_sprite(grid_size * (.5/2), black_turn_sprite_color),
          black_player_sprite(grid_size * (.75/2), black_player_sprite_color),
          white_player_sprite(grid_size * (.75/2), white_player_sprite_color)

{ }

// Citation: I talked to Ravi about this and based on my talk, I realized that the mouse position had to be converted
// to round down in order to account for the fact that screen_to_board only works with corner positions on the screen
void View::draw(Sprite_set& set, Position mouse_posn)
{
    // TODO write this for sure
    for (Position posn : model_.all_positions()) {
        set.add_sprite(square_sprite, board_to_screen(posn));
        if (model_[posn] == Player::light) {
            set.add_sprite(white_player_sprite, board_to_screen(posn), 4);
        } else if (model_[posn] == Player::dark) {
            set.add_sprite(black_player_sprite, board_to_screen(posn), 4);
        }
    }
    if (model_.is_game_over()) {
        for (Position posn : model_.all_positions()) {
            if (model_[posn] == model_.winner()) {
                set.add_sprite(game_over_sprite, board_to_screen(posn), 2);
            }
    }}
    Position board_mouse_pos = screen_to_board({(mouse_posn.x/grid_size)*grid_size, (mouse_posn.y/grid_size)*grid_size});
    if (model_.find_move(board_mouse_pos) != nullptr) {
        Move valid_move = *model_.find_move(board_mouse_pos);
        Position_set pos_to_gain = valid_move.second;
        for (Position posn: pos_to_gain){
            set.add_sprite(move_sprite, board_to_screen(posn), 1);
        }
    }

    if (model_.turn() == Player::light) {
        set.add_sprite(white_turn_sprite, mouse_posn, 2);
    } else if (model_.turn() == Player::dark) {
        set.add_sprite(black_turn_sprite, mouse_posn, 2);
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.all_positions().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

View::Position
View::board_to_screen ( Position logical ) const
{
    Position retval = {grid_size*logical.x, grid_size* logical.y};
    return retval;
}

View::Position
View::screen_to_board(View::Position physical) const
{
    Position retval = {physical.x/grid_size, physical.y/grid_size};
    return retval;
}