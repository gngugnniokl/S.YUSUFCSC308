use std::{process::Command, thread, time::Duration};

fn main() {
    let mut child = Command::new("ping")
        .arg("google.com")
        .spawn()
        .expect("Failed to spawn ping");

    println!("Ping running with PID: {}", child.id());
    println!("Check it in top: top -p {}", child.id());

    thread::sleep(Duration::from_secs(5));

    child.kill().expect("Failed to kill ping");
    let status = child.wait().expect("Failed to get exit status");

    println!("Ping exit status: {:?}", status);
}
