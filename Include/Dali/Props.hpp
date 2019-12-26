#ifndef DALI_PROPS_HPP
#define DALI_PROPS_HPP
#include <memory>
#include "Dali/Component.hpp"

namespace Dali {
  class Props {
    public:
      using Component = Component;

      template<typename P, typename = std::enable_if_t<
        !std::is_base_of_v<Props, std::decay_t<P>>>>
      Props(P&& props);

      Props(const Props& props);

      Props(Props&&) = default;

      std::unique_ptr<Component> build() const;

      Props& operator =(const Props& props);

      Props& operator =(Props&& props) = default;

    private:
      struct BaseEntry {
        virtual ~BaseEntry() = default;
        virtual std::unique_ptr<BaseEntry> clone() = 0;
        virtual std::unique_ptr<Component> build() = 0;
      };
      template<typename P>
      struct Entry final : BaseEntry {
        P props;

        template<typename F>
        Entry(F&& props);
        std::unique_ptr<BaseEntry> clone() override;
        std::unique_ptr<Component> build() override;
      };
      std::unique_ptr<BaseEntry> entry;
  };

  inline std::unique_ptr<Component> build(Props& props) {
    return props.build();
  }

  template<typename P, typename>
  Props::Props(P&& props)
    : entry(std::make_unique<Entry<std::decay_t<P>>>(
        std::forward<P>(props))) {}

  inline Props::Props(const Props& props)
    : entry(props.entry->clone()) {}

  inline std::unique_ptr<Component> Props::build() const {
    return entry->build();
  }

  inline Props& Props::operator =(const Props& props) {
    entry = props.entry->clone();
    return *this;
  }

  template<typename P>
  template<typename F>
  Props::Entry<P>::Entry(F&& props)
    : props(std::forward<F>(props)) {}

  template<typename P>
  std::unique_ptr<Props::BaseEntry> Props::Entry<P>::clone() {
    return std::make_unique<Entry>(props);
  }

  template<typename P>
  std::unique_ptr<Component> Props::Entry<P>::build() {
    return std::make_unique<Component>(
      std::make_unique<typename P::Component>());
  }
}

#endif
