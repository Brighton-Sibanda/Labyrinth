#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Model::vector_of_doors door,
               Model::Rectangle all,
               Model::vector coin,
               std::vector<Shooter> shooter,
               Model::vector spike,
               Model::vector treasure,
               Model::Position trophy,
               Model::vector wall,
               Model::vector arrow);

protected:
    void draw(ge211::Sprite_set& set) override;

private:
    Model model_;
    View view_;
};
