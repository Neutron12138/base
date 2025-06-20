#include <iostream>
#include "../base/base.hpp"

int main()
{
    std::cout << base::read_from_file("1.txt") << std::endl
              << std::endl;

    base::Logger logger;
    logger.logu("uuu");
    logger.logd("ddd");
    logger.logi("iii");
    logger.logw("www");
    logger.loge("eee");
    std::cout << std::endl;

    std::cout << (sizeof(base::PixelGrey) == sizeof(base::UInt8)) << std::endl
              << (sizeof(base::PixelGA) == 2 * sizeof(base::UInt8)) << std::endl
              << (sizeof(base::PixelRGB) == 3 * sizeof(base::UInt8)) << std::endl
              << (sizeof(base::PixelRGBA) == 4 * sizeof(base::UInt8)) << std::endl
              << std::is_trivial_v<base::PixelGrey> << std::endl
              << std::is_trivial_v<base::PixelGA> << std::endl
              << std::is_trivial_v<base::PixelRGB> << std::endl
              << std::is_trivial_v<base::PixelRGBA> << std::endl
              << std::endl;

    constexpr base::PixelGrey p1(1);
    constexpr base::PixelGA p2(1, 2);
    constexpr base::PixelRGB p3(1, 2, 3);
    constexpr base::PixelRGBA p4(1, 2, 3, 4);

    std::cout << p1 << std::endl
              << p2 << std::endl
              << p3 << std::endl
              << p4 << std::endl
              << std::endl;

    try
    {
        base::FastImage::load_from_file("114.jpg");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl
                  << std::endl;
    }

    base::FastImageRef image = base::FastImage::load_from_file("wall.jpg");
    std::cout << "width: " << image->get_width() << std::endl
              << "height: " << image->get_height() << std::endl
              << "format: " << static_cast<base::Int32>(image->get_format()) << std::endl;
    base::UInt8 *data = const_cast<base::UInt8 *>(image->get_raw_pixels());
    base::PixelRGB *pixels = reinterpret_cast<base::PixelRGB *>(data);
    std::cout << pixels[0] << ", " << pixels[1] << std::endl;
    image->save_as_png("wall_2.png");

    return 0;
}
