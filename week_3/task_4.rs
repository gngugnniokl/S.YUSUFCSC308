fn main() {
    let s1 = String::from("hi");
    let s2 = String::from("amazing");

    let result = longest(&s1, &s2);
    println!("The longer string is: {}", result);
}

fn longest<'a>(a: &'a String, b: &'a String) -> &'a String {
    if a.len() > b.len() {
        a
    } else {
        b
    }
}
