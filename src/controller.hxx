#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Model::Rectangle all,
               Model::vector coin,
               Model::vector shooter,
               Model::vector spike,
               Model::vector treasure,
               std::vector<int> trophy,
               Model::vector wall,
               Model::vector door_pos,
               Model::vector arrow);

protected:
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;
};
