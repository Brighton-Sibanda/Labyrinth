#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller(Model::vector_of_doors door,
               Model::vector all,
               Model::vector coin,
               std::vector<Shooter> shooter,
               Model::vector spike,
               Model::vector treasure,
               Model::Position trophy,
               Model::vector wall,
               Model::vector arrow);
    ge211::Dims<int> initial_window_dimensions() const override;

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_mouse_down(ge211::Mouse_button, ge211::Posn<int>) override;
    void on_frame(double dt) override;

private:
    Model model_;
    View view_;
};


