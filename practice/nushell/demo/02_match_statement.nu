#!/usr/bin/env nu

def random_file [path] {
    let files = (ls $path)
    let num_files = ($files | length)

    match $num_files { 
        0 => null
        _ => {
            let rand_file = (random int 0..($num_files - 1))
                ($files | get $rand_file)
        } 
    }
}


random_file ..
