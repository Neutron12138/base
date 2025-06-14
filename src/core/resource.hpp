#pragma once

#include "noncopyable_object.hpp"

namespace base
{
    /// @brief 不可拷贝的资源对象
    class Resource : public NoncopyableObject
    {
    };

} // namespace base
