#pragma once

#include "string.hpp"

#define BASE_DEBUG_ARGS __FILE__, __FUNCTION__, __LINE__
#define BASE_DEBUG_INFO base::str_debug_info(BASE_DEBUG_ARGS)

namespace base
{
    std::string str_debug_info(const char *file, const char *function, int line)
    {
        return to_string(
            "in file: \"", file,
            "\", function: \"", function,
            "\", line: ", line);
    }

} // namespace base
