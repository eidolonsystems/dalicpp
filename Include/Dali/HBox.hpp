#ifndef DALI_HBOX_HPP
#define DALI_HBOX_HPP
#include <vector>
#include "Dali/Props.hpp"

namespace Dali {
  struct HBox {
    std::vector<Props> children;

    class Component {
      public:
        auto render(const HBox& props) const {
        }
    };
  };
}

#endif
