struct circle{
    name: String,
    radius: f64,
}
impl circle{
    const pi:f64 = std::f64::consts::PI;
    fn calc_cir(&self){
    println!("The circumference of {} is {}",self.name, 2.0 * Self::pi * self.radius );
    }
    fn calc_are(&self){
    println!("The area of {} is {}",self.name,  Self::pi * (self.radius * self.radius) );
    }
}
fn main() {
    let circle = circle{
        name: String::from("Randy"),
        radius: 4.5,
        };
    circle.calc_cir();
    circle.calc_are();

}
