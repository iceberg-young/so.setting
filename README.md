so.setting
==========

When using JSON in configuration files, there is a scenario (*gap?*) that
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

- Load JSON iteratively.

  - From string.

    ```cpp
    static
    so::json  so::setting::load(std::string text, std::function<so::setting::revise_t> revise, bool liberal);
    ```

    - The `text` will be parsed as the first *supplementary*.
  
    - The `revise` is expected to return a JSON text,
      which will be parsed as subsequent *supplementary*.
  
      > **Note!**
      > The `revise` cannot be a `nullptr`.

  - From file.
  
    ```cpp
    static
    so::json  so::setting::load_file(std::string path, std::function<so::setting::revise_t> revise, bool liberal);
    ```
    
    - File content of the `path` will be parsed as first *supplementary*.
  
    - The `revise` is expected to return a file path,
      content of which will be parsed as subsequent *supplementary*.
  
      > **Tip!**
      > The `revise` could be a `nullptr`.

  #### Iterating Details

  `load` and `load_file` will start from an empty `object` as *fundamental*.

  1. Give *fundamental* and *supplementary* to `revise` for modifying/reference.

  2. Merge *supplementary* to *fundamental*.

  3. Parse next *supplementary* returned by `revise` to repeat the process,
     until `revise` returns an empty string.

     > **Tip!**
     > If `liberal` is true, `json_parse_error` will be suppressed,
     > and *supplementary* will be `null` if parse failed.

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
