/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#pragma once

#include "json.hpp"
#include <functional>

namespace so {
    using revise_t = std::string(const json& fundamental, const json& supplementary);

    json load(std::string text, const std::function<revise_t>& revise);

    json load_file(const std::string& path, const std::function<revise_t>& revise);

    json& merge(json& fundamental, const json& supplementary);

    namespace is {
        bool set(const json& pool, size_t index);

        bool set(const json& pool, const std::string& key);

        inline bool set(const json& pool, const char* key) {
            return set(pool, std::string{key});
        }
    }
}
