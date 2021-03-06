/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include "json.hpp"
#include <functional>

namespace so {
    class setting {
     public:
        using revise_t = std::string(json& fundamental, json& supplementary);

     public:
        static
        json load(std::string text, const std::function<revise_t>& revise, bool liberal = false);

        static
        json load_file(const std::string& path, const std::function<revise_t>& revise, bool liberal = false);
    };

    json& merge(json& fundamental, json&& supplementary);

    namespace is {
        bool set(const json& pool, size_t index);

        bool set(const json& pool, const std::string& key);

        inline bool set(const json& pool, const char* key) {
            return set(pool, std::string{key});
        }
    }
}
