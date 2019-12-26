#ifndef DALI_COMPONENT_HPP
#define DALI_COMPONENT_HPP
#include <memory>

namespace Dali {
  class Component {
    public:
      template<typename C>
      Component(std::unique_ptr<C> component);

    private:
      Component(const Component&) = delete;
      Component& operator =(const Component&) = delete;
  };

  template<typename C>
  Component::Component(std::unique_ptr<C> component) {}
}

#endif
