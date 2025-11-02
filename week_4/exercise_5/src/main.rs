use std::io;

struct Student {
    name: String,
    score: i32,
}

impl Student {
    fn did_pass(&self) {
        if self.score < 50 {
            println!("{} failed woefully. They should go and learn work.", self.name);
        } else {
            println!("{} passed.", self.name);
        }
    }
}

fn main() {
    let mut name = String::new();
    let mut score = String::new();

    println!("Input name:");
    io::stdin().read_line(&mut name).expect("Failed to read name");

    println!("Input score:");
    io::stdin().read_line(&mut score).expect("Failed to read score");

    let score: i32 = score.trim().parse().unwrap();

    let student = Student {
        name: name.trim().to_string(),
        score,
    };

    student.did_pass();
}
