use std::io;

fn main() {
    println!("What would you like to say?");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let words: Vec<&str> = input.trim().split_whitespace().collect();
    if words.is_empty() {
        println!("No words");
        return;
    }

    let mut longest = words[0];
    let mut shortest = words[0];

    for &word in &words {
        if word.len() > longest.len() {
            longest = word;
        }
        if word.len() < shortest.len() {
            shortest = word;
        }
    }
    println!("Do you want to see the longest or shortest word?");
    let mut response = String::new();
    io::stdin().read_line(&mut response).expect("Failed to read line");
    let answer = response.trim();
    if answer == "long" || answer == "l"{
    println!("The longest word is: {}", longest);
    }
    else if answer == "short" || answer == "s"{
    println!("The shortest word is: {}", shortest);
    }
    else {
        println!("Invalid input");
    }
}
