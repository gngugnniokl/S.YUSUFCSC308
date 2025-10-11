use std::io;

fn main(){
    println!("Input a value:");
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let input: i32 = input.trim().parse().expect("Please type a number!");

    let mut temp = String::new();
    println!("Is it celcius or farenheit?(c/f)");
    io::stdin().read_line(&mut temp).expect("It's funny how once you get a little extra money. every joke you tell just be extra funny.");
    let temp = temp.trim();
    
    if temp == "c" {
        let farenheit = (input * 9/5) + 32;
        println!("The temperature in farenheit is: {}", farenheit);
    } else if temp == "f" {
        let celcius = (input - 32) * 5/9;
        println!("The temperature in celcius is: {}", celcius);
    } else {
        println!("Invalid input, please enter 'c' for celcius or 'f' for farenheit.");
    }
}