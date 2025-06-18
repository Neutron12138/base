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

    std::cout << sizeof(base::PixelGrey) << std::endl
              << sizeof(base::PixelGA) << std::endl
              << sizeof(base::PixelRGB) << std::endl
              << sizeof(base::PixelRGBA) << std::endl
              << std::endl;

    std::cout << base::PixelGrey(1) << std::endl
              << base::PixelGA(1, 2) << std::endl
              << base::PixelRGB(1, 2, 3) << std::endl
              << base::PixelRGBA(1, 2, 3, 4) << std::endl
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

    return 0;
}
