use std::io;

fn main(){
    let mut OgPrice = String::new();
    println!("How much was your meal?");
    std::io::stdin().read_line(&mut OgPrice).expect("Wubbalubadubdub broski");
    let input: i32 = OgPrice.trim().parse().expect("Please type a number!");

    if input > 5000 && input <= 10000 {
        let input: f64 = input as f64;
        let new_price: f64 = input - (0.1 * input);
        println!("Congrats! You get a 10% discount!");
        println!("Discounted price is {}", new_price);
    }
    else if input > 10000 {
        let input:f64 = input as f64;
        let new_price: f64 = input - (0.15 * input);
        println!("Wonderful, you got a 15% discount!");
        println!("Discounted price is {}", new_price);
    }
    else {
        println!("Sorry, no discount. Take heart. Pay {}", input);
    }

}