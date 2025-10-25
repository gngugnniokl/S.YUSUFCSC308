fn main() {
    let mut name = String::from("Firstname ");
    add_surname_to_firstname(&mut name);
    println!("{}", name);
}

fn add_surname_to_firstname(name: &mut String) {
    name.push_str("Lastname");
}
