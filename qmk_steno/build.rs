use std::io::{Read, Write};
use std::{env, io::Seek};

extern crate cbindgen;

use steno_engine::dictionary::{packed, simple};

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    println!("cargo:rerun-if-changed=src/interface.rs");
    cbindgen::Builder::new()
        .with_crate(crate_dir)
        .with_language(cbindgen::Language::C)
        .generate()
        .expect("Unable to generate bindings")
        .write_to_file("qmk_steno.h");

    let json_paths = [
        "/home/philip/python/steno/steno-dictionaries/dictionaries/top-10000-project-gutenberg-words.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/dict.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/fingerspelling.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/numbers.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/punctuation-di.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/plover-use.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/code.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/python.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/git.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/vim.json",
        // "/home/philip/python/steno/steno-dictionaries/dictionaries/computer-use.json",
        // "/home/philip/rust/steno_engine/words.json",
        "/home/philip/rust/steno_engine/word_parts.json",
        "/home/philip/rust/steno_engine/fingerspelling.json",
        "/home/philip/rust/steno_engine/numbers.json",
        "/home/philip/rust/steno_engine/punctuation.json",
        // "/home/philip/.config/plover/main.json",
        "/home/philip/.config/plover/commands.json",
        "/home/philip/.config/plover/user.json",
    ];
    for path in json_paths {
        println!("cargo:rerun-if-changed={path}");
    }
    let upd = simple::Dictionary::from_json(json_paths).expect("Unable to create dictionary");
    let d: packed::Dictionary<Vec<u8>> = upd.into();
    let mut f = std::fs::OpenOptions::new()
        .create(true)
        .read(true)
        .write(true)
        .truncate(true)
        .open("dict.in")
        .unwrap();
    f.write_all(&d.to_bytes()).unwrap();
    f.rewind().unwrap();
    let mut content = Vec::new();
    f.read_to_end(&mut content).unwrap();
    // Verify the result.
    packed::Dictionary::from_bytes(content.as_ref()).unwrap();
}
