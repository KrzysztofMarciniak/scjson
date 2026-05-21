# scjson

`scjson` is a small JSON library written in C99.

It is simple, portable, and has no external dependencies. It uses POSIX.1-2008 where needed.

## Public API
[api.md](https://github.com/KrzysztofMarciniak/scjson/blob/master/api.md)

## Name

- `s` = simple
- `c` = C
- `json` = JSON

## Layout

- `scjson.h` — public API
- `internal/` — internal implementation
- `internal/tests/` — internal tests
- `example/` — example programs

## Build

```sh
git clone https://github.com/KrzysztofMarciniak/scjson
cd scjson
make -j $(nproc)
sudo make install
````

## Example

```sh
cd example
make
./example.bin
./example_error.bin
```
Example work that can be done (`main.c`):
```text
sh-5.3$ ./example.bin 
--- PART 1: Parsing and Validating Existing JSON ---
name: scjson
version: 1
active: true

--- PART 2: Modifying an Existing Array ---
Original feature count: 3
Successfully added 'auto-updates' to features.
Updated feature count: 4
  feature[0] = parser
  feature[1] = pretty printer
  feature[2] = hash map
  feature[3] = auto-updates

--- PART 3: Serializing Modified JSON ---
Raw JSON string:
{"active":true,"version":1,"features":["parser","pretty printer","hash map","auto-updates"],"name":"scjson"}

Pretty JSON string:
{
  "active": true,
  "version": 1,
  "features": [
    "parser",
    "pretty printer",
    "hash map",
    "auto-updates"
  ],
  "name": "scjson"
}

--- PART 4: Creating JSON Manually ---
{
  "enabled": true,
  "version": 2,
  "tags": [
    "c99",
    "json",
    "minimal"
  ],
  "title": "scjson"
}
sh-5.3$ 
```
Example error handling (`example_error.c`):

```text
sh-5.3$ ./example_error.bin 
Parse error: Unexpected token at line 4, column 15 (pos 57)
    "active": tru,      // <-- typo! should be "true"
              ^
sh-5.3$ 
```

## License
BSD 3-Clause License
