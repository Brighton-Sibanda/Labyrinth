#include "door.hxx"


Door::Door(bool state_change,std::vector<int> current, std::vector<int> dst)
          : door_pos(current),
            destination(dst),
            changes_model_state(state_change)


{}