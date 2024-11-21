

public class Customer {
    public int bornTime;
    private int groceries;
    
    public Customer(int bornTime, int groceries){
        this.bornTime=bornTime;
        this.groceries=groceries;
    }

    public int getGroceries(){
        return this.groceries;
    }

    public void serve(){
        if(this.groceries>0){
            this.groceries--;
        }
        else{
            throw new IllegalArgumentException("\nNo groceries left.\n");
        }
    }
    
    public boolean isDone(){
        return this.groceries==0;
    }

    public static void main(String args[]) {
        Customer c = new Customer(0, 3);
        c.serve();
        c.serve();
        c.serve();
        if(c.isDone()) {
            System.out.println("The customer is done, just as expected!");
        } else {
            System.out.println("The customer is not done, but should be...");
        }
    }
}
