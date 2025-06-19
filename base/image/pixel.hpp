#pragma once

#include <iostream>
#include "../core/type.hpp"
#include "../core/compact_object.hpp"

namespace base
{
    /// @brief 灰度像素
    class PixelGrey : public CompactObject
    {
    public:
        /// @brief 灰度
        UInt8 grey = 0;

    public:
        PixelGrey() = default;
        PixelGrey(UInt8 g) : grey(g) {}
    };

    /// @brief 灰度、透明度像素
    class PixelGA : public PixelGrey
    {
    public:
        /// @brief 透明度
        UInt8 alpha = 0;

    public:
        PixelGA() = default;
        PixelGA(UInt8 g, UInt8 a)
            : PixelGrey(g), alpha(a) {}
    };

    /// @brief RGB像素
    class PixelRGB : public CompactObject
    {
    public:
        /// @brief 红色
        UInt8 red = 0;
        /// @brief 绿色
        UInt8 green = 0;
        /// @brief 蓝色
        UInt8 blue = 0;

    public:
        PixelRGB() = default;
        PixelRGB(UInt8 r, UInt8 g, UInt8 b)
            : red(r), green(g), blue(b) {}
    };

    /// @brief RGBA像素
    class PixelRGBA : public PixelRGB
    {
    public:
        /// @brief 透明度
        UInt8 alpha = 0;

    public:
        PixelRGBA() = default;
        PixelRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a)
            : PixelRGB(r, g, b), alpha(a) {}
    };

    std::ostream &operator<<(std::ostream &os, const PixelGrey &pixel)
    {
        os << "( " << static_cast<Int32>(pixel.grey) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelGA &pixel)
    {
        os << "( " << static_cast<Int32>(pixel.grey) << ", "
           << static_cast<Int32>(pixel.alpha) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelRGB &pixel)
    {
        os << "( " << static_cast<Int32>(pixel.red) << ", "
           << static_cast<Int32>(pixel.green) << ", "
           << static_cast<Int32>(pixel.blue) << " )";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const PixelRGBA &pixel)
    {
        os << "( " << static_cast<Int32>(pixel.red) << ", "
           << static_cast<Int32>(pixel.green) << ", "
           << static_cast<Int32>(pixel.blue) << ", "
           << static_cast<Int32>(pixel.alpha) << " )";
        return os;
    }

} // namespace base
