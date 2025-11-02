struct bank{
    balance: i32,
}
impl bank{
    fn withdraw(&self,subtracted: i32){
    
    println!("You have taken out {}", subtracted);
    println!("Your remaining balance is {}", self.balance - subtracted)
    
    }
    fn deposit(&self, deposit:i32){
    println!("You just deposited {}",deposit);
    println!("Your new balance is {}",deposit + self.balance);
    }
    fn check(&self){
    println!("Your balance is {}", self.balance)
    }
}
fn main() {
    let bank = bank{
        balance: 7000,
        };
        bank.withdraw(600);
        bank.deposit(24);
        bank.check();

}