use std::{process::Command, fs};

fn main() {
    // Run the command and capture output
    let out = Command::new("echo")
        .arg("Rust Process Management")
        .output()
        .expect("failed to run command");

    // Write stdout directly to output.txt
    fs::write("output.txt", out.stdout).expect("failed to write file");
}
