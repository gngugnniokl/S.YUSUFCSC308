fn main() {
    // Manually initialize the vector with values from 1 to 20
    let numbers = vec![
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
];

    let is_even = |x: u32| x % 2 == 0;
\
    let mut even_numbers = Vec::new();
    for num in &numbers {
        if is_even(*num) {
            even_numbers.push(*num);
        }
    }

    println!("Even numbers: {:?}", even_numbers);
}