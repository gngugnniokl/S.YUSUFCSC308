fn main() {
    let mut message = String::from("Hello");

    show_message(&message);
    add_note(&mut message);

    println!("Final message: {}", message);
}

fn show_message(msg: &String) {
    println!("Current message: {}", msg);
}

fn add_note(msg: &mut String) {
    msg.push_str(", world!");
}
