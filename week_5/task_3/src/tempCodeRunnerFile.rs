use std::process::Command;

fn main() {
    let status = Command::new("echo")
        .arg("Hello from child process!")
        .status()
        .unwrap();

    println!("Success: {}", status.success());
}
