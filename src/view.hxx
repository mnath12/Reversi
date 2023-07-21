#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // We added an argument here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, Position mouse_posn);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    // TODO: Add any public member functions you need.
    Position board_to_screen (Position logical ) const;
    Position  screen_to_board (Position physical) const;

private:
    Model const& model_;

    // TODO: Add any additional private members you need, such as helper
    // functions or sprites.
    void add_player_sprite(ge211::Sprite_set& set) const;
    ge211::Rectangle_sprite const square_sprite;
    ge211::Rectangle_sprite const move_sprite;
    ge211::Rectangle_sprite const game_over_sprite;
    ge211::Circle_sprite const white_turn_sprite;
    ge211::Circle_sprite const black_turn_sprite;
    ge211::Circle_sprite const black_player_sprite;
    ge211::Circle_sprite const white_player_sprite;





};
