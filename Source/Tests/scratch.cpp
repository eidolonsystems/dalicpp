#include <iostream>
#include <doctest/doctest.h>
#include "Dali/Dali.hpp"

template<typename T, typename P>
constexpr decltype(std::declval<T>().prebuild(std::declval<P>()), true) has_prebuild(int) {
  return true;
}

template<typename T, typename P>
constexpr auto has_prebuild(...) {
  return false;
}

template<typename T, typename P>
constexpr auto has_prebuild_v = has_prebuild<T, P>(0);

template<typename Component, typename Props>
auto prebuild(const Component& component, Props& props) {
  if constexpr(has_prebuild_v<Component, Props>) {
    return component.prebuild(props);
  }
}

template<typename T, typename P>
constexpr decltype(std::declval<T>().postbuild(std::declval<P>()), true) has_postbuild(int) {
  return true;
}

template<typename T, typename P>
constexpr auto has_postbuild(...) {
  return false;
}

template<typename T, typename P>
constexpr auto has_postbuild_v = has_postbuild<T, P>(0);

template<typename Component, typename Props>
void postbuild(const Component& component, const Props& props) {
  if constexpr(has_postbuild_v<Component, Props>) {
    return component.postbuild(props);
  }
}

template<typename T>
constexpr decltype(std::declval<T>().children, true) has_children(int) {
  return true;
}

template<typename T>
constexpr auto has_children(...) {
  return false;
}

template<typename T>
constexpr auto has_children_v = has_children<T>(0);

template<typename Props>
void build_children(Props& props) {
  if constexpr(has_children_v<Props>) {
    for(auto& child : props.children) {
      build(child);
    }
  }
}

template<typename Props>
auto build(Props props) {
  auto component = std::make_unique<typename Props::Component>();
  prebuild(*component, props);
  component->build(props);
  build_children(props);
  postbuild(*component, props);
  return component;
}

template<typename C>
void update(C& component) {}

struct ClickCounter {
  class Component {
    public:
      Component()
        : counter(0) {}

      auto build(const ClickCounter& props) {
        return Dali::Mouseable<Dali::Label>{
          .on_click = [=] { on_click(); },
          .body = {
            .text = std::to_string(counter)
          }
        };
      }

    private:
      int counter;

      void on_click() {
        ++counter;
        update(*this);
      }
  };
};

TEST_SUITE("Scratch") {
  TEST_CASE("Test build") {
    build(Dali::HBox{
      .children = {
        ClickCounter{},
        Dali::Label{
          .text = "world"
        }
      }
    });
  }
}
