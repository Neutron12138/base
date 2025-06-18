#pragma once

namespace base
{
    /// @brief 关闭内存对齐的对象，更加紧凑
    class alignas(1) CompactObject
    {
    };

} // namespace base
