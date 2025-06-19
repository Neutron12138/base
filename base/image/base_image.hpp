#pragma once

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#endif
#include <stb_image_resize2.h>

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include <stb_image_write.h>

#include "../core/type.hpp"
#include "../others/resource.hpp"
#include "pixel.hpp"

namespace base
{
    class BaseImage;
    using BaseImageRef = Ref<BaseImage>;
    using BaseImageWeakRef = WeakRef<BaseImage>;

    /// @brief 基础图像类
    class BaseImage : public Resource
    {
    public:
        /// @brief 格式
        enum class Format : Int32
        {
            None,
            Grey,
            GA,
            RGB,
            RGBA,
        };

        /// @brief 资源类型
        enum class ResourceType : Int64
        {
            /// @brief 无
            None,
            /// @brief 快速图像
            FastImage,
        };

    private:
        /// @brief 宽度
        Size m_width = 0;
        /// @brief 高度
        Size m_height = 0;
        /// @brief 格式
        Format m_format = Format::None;

    public:
        BaseImage() = default;
        BaseImage(Size width, Size height, Format format)
            : m_width(width), m_height(height), m_format(format) {}
        ~BaseImage() override = default;

    public:
        Size get_width() const { return m_width; }
        Size get_height() const { return m_height; }
        Format get_format() const { return m_format; }

        /// @brief 获取原始像素数据（UInt8）
        /// @return 原始像素数据
        virtual const UInt8 *get_raw_pixels() const = 0;

    protected:
        /// @brief 设置图像宽度
        /// @param width 图像宽度
        void _set_width(Size width) { m_width = width; }

        /// @brief 设置图像高度
        /// @param height 图像高度
        void _set_height(Size height) { m_height = height; }

        /// @brief 设置图像格式
        /// @param format 图像格式
        void _set_channels(Format format) { m_format = format; }

    public:
        /// @brief 将图像保存为PNG格式
        /// @param filename 文件名
        virtual void save_as_png(const std::string &filename)
        {
            bool success = stbi_write_png(
                filename.data(), m_width, m_height, static_cast<Int32>(m_format), get_raw_pixels(), 0);

            if (!success)
                throw std::runtime_error(to_string("Failed to save image as png, filename: \"", filename, "\""));
        }

        /// @brief 将图像保存为JPG格式
        /// @param filename 文件名
        /// @param quality 质量
        virtual void save_as_jpg(const std::string &filename, int quality)
        {
            bool success = stbi_write_jpg(
                filename.data(), m_width, m_height, static_cast<Int32>(m_format), get_raw_pixels(), quality);

            if (!success)
                throw std::runtime_error(to_string("Failed to save image as jpg, filename: \"", filename, "\""));
        }
    };

} // namespace base
