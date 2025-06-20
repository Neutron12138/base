#pragma once

#include <iostream>
#include "../core/type.hpp"

namespace base
{
    /// @brief 灰度像素
    class PixelGrey
    {
    public:
        /// @brief 灰度
        UInt8 grey;

    public:
        PixelGrey() = default;
        constexpr PixelGrey(UInt8 g) : grey(g) {}
        ~PixelGrey() = default;
    };

    /// @brief 灰度、透明度像素
    class PixelGA : public PixelGrey
    {
    public:
        /// @brief 透明度
        UInt8 alpha;

    public:
        PixelGA() = default;
        constexpr PixelGA(UInt8 g, UInt8 a)
            : PixelGrey(g), alpha(a) {}
        ~PixelGA() = default;
    };

    /// @brief RGB像素
    class PixelRGB
    {
    public:
        /// @brief 红色
        UInt8 red;
        /// @brief 绿色
        UInt8 green;
        /// @brief 蓝色
        UInt8 blue;

    public:
        PixelRGB() = default;
        constexpr PixelRGB(UInt8 r, UInt8 g, UInt8 b)
            : red(r), green(g), blue(b) {}
        ~PixelRGB() = default;
    };

    /// @brief RGBA像素
    class PixelRGBA : public PixelRGB
    {
    public:
        /// @brief 透明度
        UInt8 alpha;

    public:
        PixelRGBA() = default;
        constexpr PixelRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a)
            : PixelRGB(r, g, b), alpha(a) {}
        ~PixelRGBA() = default;
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
