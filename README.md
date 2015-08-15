so.setting
==========

When using JSON for configuration file, there is a scenario (*gap?*) that
the program brings a *default* configuration, while the user can provides
a *custom* one to override **part** of it.

This library is aimed to such scenario.


API
---

See [setting.hpp](include/setting.hpp).

- Merge 2 JSON objects.

  ```cpp
  so::json&  so::merge(so::json& fundamental, so::json supplementary);
  ```

  For each element in `supplementary`:

  - If there is a corresponding element (*with the same key*) in `fundamental`,
    and both elements are `object`, the process will **recur** on that pair.

  - Otherwise, **insert** it into `fundamental` if its key does not exist yet.

  Elements in `fundamental` that are not `object` will leave no touch.

  > **Tip!**
  > Both `fundamental` and `supplementary` should be `object` type.

- Load JSON from string.

  ```cpp
  static
  so::json  so::setting::load(std::string text, std::function<so::setting::revise_t> revise);
  ```

  The `text` will be parsed as the *fundamental*.

  The `revise` function will be called repeatedly.
  It is expected to return a JSON text, which will be parsed
  as the *supplementary*, and then merged to the *fundamental*.
  The process will stop when `revise` returns an empty text.
  
  > **Note!**
  > The `revise` cannot be a `nullptr`.

- Load JSON from file.

  ```cpp
  static
  so::json  so::setting::load_file(std::string path, std::function<so::setting::revise_t> revise);
  ```
  
  The file located at `path` will be parsed as the *fundamental*.

  The `revise` function will be called repeatedly.
  It is expected to return the path of a file, which will be parsed
  as the *supplementary*, and then merged to the *fundamental*.
  The process will stop when `revise` returns an empty path.

  > **Note!**
  > The `revise` could be a `nullptr`.

- Check if an index/key present.

  ```cpp
  bool  so::is::set(so::json pool, size_t index);
  bool  so::is::set(so::json pool, std::string key);
  ```

  > **Tip!**
  > `null` will be treated as not set.
  > So that user can *logically delete* a key by assign `null` to it.


License
-------
![LGPLv3]

Copyright (C) 2015  Iceberg YOUNG

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


---

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
