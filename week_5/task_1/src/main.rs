fn main() {

    let multiply = |a: u64, b: u64| a * b;

    let number = 6;
    let mut result = 1;

    for i in 1..=number {
        result = multiply(result, i);
    }

    println!("Factorial of {} is {}", number, result);
}
