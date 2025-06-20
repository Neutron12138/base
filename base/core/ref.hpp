#pragma once

#include <memory>
#include <functional>

namespace base
{
    /// @brief 对象引用，同std::shared_ptr
    /// @tparam T 对象类型
    template <typename T>
    using Ref = std::shared_ptr<T>;

    /// @brief 对象弱引用，同std::weak_ptr
    /// @tparam T 对象类型
    template <typename T>
    using WeakRef = std::weak_ptr<T>;

    /// @brief 独占引用，同std::unique_ptr
    /// @tparam T 对象类型
    template <typename T>
    using UniqueRef = std::unique_ptr<T>;

    /// @brief 引用包装器，同std::reference_wrapper
    /// @tparam T 对象类型
    template <typename T>
    using RefWrapper = std::reference_wrapper<T>;

} // namespace base
