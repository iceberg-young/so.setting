/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "setting.hpp"
#include <fstream>

namespace so {
    namespace {
        std::string content(const std::string& path) {
            std::ifstream f(path);
            f.seekg(0, std::ios::end);
            size_t l = f.tellg();
            std::string s(l, 0);
            f.seekg(0);
            f.read(&s[0], l);
            return s;
        }
    }

    json load(std::string text, const std::function<revise_t>& revise) {
        json f{json::content_type::object};
        while (not text.empty()) {
            auto s = json::parse(text);
            merge(f, s);
            text = revise(f, s);
        }
        return f;
    }

    json load_file(const std::string& path, const std::function<revise_t>& revise) {
        auto wrap = not revise
          ? std::function<revise_t>{
            [](const json&, const json&)->std::string {
                return "";
            }
          }
          : std::function<revise_t>{
            [&revise](const json& f, const json& s)->std::string {
                auto next = revise(f, s);
                return next.empty() ? "" : content(next);
            }
          };
        return load(content(path), wrap);
    }

    json& merge(json& fundamental, const json& supplementary) {
        if (not is::object(supplementary)) return fundamental;

        for (auto& s : supplementary.as_object()) {
            auto& f = fundamental(s.first);
            is::object(f) and is::object(s.second)
              ? merge(f, s.second)
              : f = s.second;
        }
        return fundamental;
    }
}
