#ifndef DALI_COMPONENT_HPP
#define DALI_COMPONENT_HPP
#include <memory>

namespace Dali {
  class Component {
    public:
      template<typename C>
      Component();

    private:
      Component(const Component&) = delete;
      Component& operator =(const Component&) = delete;
  };
}

#endif
