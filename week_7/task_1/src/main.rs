use std::process::Command;

fn main() {

    let mut sleep_child = Command::new("sleep")
        .arg("5")
        .spawn()
        .expect("Could not run sleep");

    let mut ls_child = Command::new("ls")
        .arg("-la")
        .spawn()
        .expect("Could not run ls");


    let mut echo_child = Command::new("echo")
        .arg("Hello from child")
        .spawn()
        .expect("Could not run echo");

    println!("Sleep child PID: {}", sleep_child.id());
    println!("ls child PID: {}", ls_child.id());
    println!("echo child PID: {}", echo_child.id());

    let _ = sleep_child.wait();
    let _ = ls_child.wait();
    let _ = echo_child.wait();
}
