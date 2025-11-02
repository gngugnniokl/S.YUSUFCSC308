use std::io;

fn main(){
  //input capture
    println!("Input a sentence!");
    let mut word = String::new();
    io::stdin().read_line(&mut word).expect("Failed to read line");
    let input = word.trim();

  //space detection
  let mut space_count = 0;
  let mut last_index: Option<usize> = None;

    for (pos,space) in input.char_indices() {
        if space == ' '{
        space_count += 1;
        last_index = Some(pos);
    }
}
println!(" Your number of spaces are {}",space_count);

if let Some(position) = last_index{
  let triangulated = &input[position + 1..];
  println!("The last word is {}",triangulated)
}
else {
  println!("Oof. Something went wrong");
}

}
