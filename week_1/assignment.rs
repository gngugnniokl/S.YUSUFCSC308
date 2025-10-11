use std::io;

fn main(){
    println!("What is your energy consumption. (Measured in Kilowatt-hours)");
    let mut energy_consumption = String::new();
    io::stdin().read_line(&mut energy_consumption).expect("Failed to read line");
    let energy_consumption: i32 = energy_consumption.trim().parse().expect("Please type a number!");

    if energy_consumption > 100 && energy_consumption <= 200 {
        println!("Your energy bill is: {}" , 25 * energy_consumption);
    }
    else if energy_consumption > 200 {
        println!("Your energy bill is: {}" , 30 * energy_consumption);
    }
    else 
    {
        println!("Your energy bill is: {}" , 20 * energy_consumption);
    }
}