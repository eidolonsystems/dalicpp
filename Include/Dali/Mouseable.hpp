#ifndef DALI_MOUSEABLE_HPP
#define DALI_MOUSEABLE_HPP
#include <functional>

namespace Dali {
  template<typename C>
  struct Mouseable {
    std::function<void ()> on_click = [] {};
    C body;

    class Component {
      public:
        auto render(const Mouseable& props) const {
          return body;
        }
    };
  };
}

#endif
