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

        template<typename key_t>
        bool is_set(const json& pool, key_t key) {
            if (is::array(pool) or is::object(pool)) {
                try {
                    return not is::null(pool[key]);
                }
                catch (std::out_of_range) {
                    // return false;
                }
            }
            return false;
        }
    }

    json setting::load(std::string text, const std::function<revise_t>& revise, bool liberal) {
        json f{json::content_type::object};
        while (not text.empty()) {
            try {
                auto s = json::parse(text);
                text = revise(f, s);
                merge(f, std::move(s));
            }
            catch (json_parse_error) {
                if (not liberal) throw;
                json null;
                text = revise(f, null);
            }
        }
        return f;
    }

    json setting::load_file(const std::string& path, const std::function<revise_t>& revise, bool liberal) {
        auto wrap = not revise
          ? std::function<revise_t>{
            [](json&, json&)->std::string {
                return "";
            }
          }
          : std::function<revise_t>{
            [&revise](json& f, json& s)->std::string {
                auto next = revise(f, s);
                return next.empty() ? "" : content(next);
            }
          };
        return load(content(path), wrap, liberal);
    }

    json& merge(json& fundamental, json&& supplementary) {
        if (not is::object(fundamental)) {
            throw std::logic_error{"Only object can be merged."};
        }
        if (not is::object(supplementary)) return fundamental;

        auto& f = fundamental.as_object();
        for (auto& s : supplementary.as_object()) {
            auto r = f.insert(std::move(s));
            if (not r.second
              and is::object(r.first->second)
              and is::object(s.second)) {
                merge(r.first->second, std::move(s.second));
            }
        }
        return fundamental;
    }

    namespace is {
        bool set(const json& pool, size_t index) {
            return is_set(pool, index);
        }

        bool set(const json& pool, const std::string& key) {
            return is_set(pool, key);
        }
    }
}
