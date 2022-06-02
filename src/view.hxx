#pragma once

#include "model.hxx"

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);
    std::string initial_window_title() const;
    ge211::Dims<int> initial_window_dimensions() const;
private:
    Model const& model_;
    ge211::Rectangle_sprite gen_sprite;
};
