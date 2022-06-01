#include "door.hxx"


Door::Door(bool state_change,std::vector<int> current, std::vector<int> dst)
          :changes_model_state(state_change),
          door_pos(current),
          destination(dst)


{}