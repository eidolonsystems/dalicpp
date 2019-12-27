#include <iostream>
#include <doctest/doctest.h>
#include "Dali/Dali.hpp"

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
  auto component = Dali::Component<typename Props::Component>();
//  build_children(props);
  return component;
}

template<typename C>
void update(C& component) {}

struct ClickCounter {
  class Component {
    public:
      Component()
        : counter(0) {}

      auto render(const ClickCounter& props) {
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
    auto component = build(Dali::HBox{
      .children = {
        ClickCounter{},
        Dali::Label{
          .text = "world"
        }
      }
    });
  }
}
