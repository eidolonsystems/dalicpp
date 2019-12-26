#ifndef DALI_LABEL_HPP
#define DALI_LABEL_HPP
#include <string>

namespace Dali {
  struct Label {
    std::string text;

    class Component {
      public:
        auto build(const Label& props) const {
        }
    };
  };
}

#endif
