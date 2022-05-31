#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Model::Rectangle all, Model::vector co,
               Model::vector
               sh,Model::vector sp,Model::vector tr, std::vector<int> trophy,
               Model::vector wall, Model::Position door_pos, Model::vector);

protected:
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;
};
