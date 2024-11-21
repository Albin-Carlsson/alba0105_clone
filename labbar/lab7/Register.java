
public class Register {
    private boolean open;
    private Queue queue;

    public Register(){
        this.open=false;
        this.queue=new Queue();
    }

    //öppnar en kasa
    public void open(){
        this.open=true;
    }

    //stänger en kassa
    public void close(){
        this.open=false;
    }

    //kollar om kassan är öppen
    public boolean isOpen(){
        return this.open;
    }

    //låter customern få en vara scannad
    public void step(){
        if (this.queue.length()==0){
            return;
        }
        //TODO: fix time  
        this.queue.first().serve();
    }

    //kollar om kassan har customers
    public boolean hasCustomers(){
        return !(this.queue.length()==0);
    }

    public Customer getFirstCustomer() {
        return this.queue.first();
    }

    //kollar om den som är först i kön är klar
    public boolean currentCustomerIsDone(){
        if(this.queue.first()!=null){
            return this.queue.first().isDone();
        }
        return false;
    }
    
    //lägger en customer sist i kön
    public void addToQueue(Customer c){
        this.queue.enqueue(c);
    }

    //tar bort customer som är först i kön och returnerar de
    public Customer removeCurrenCustomer(){
       return this.queue.dequeue();
    }

    //tar längden på kön
    public int getQueueLength(){
        return this.queue.length();
    }

    public static void main(String[] args) {
        Register register = new Register();
        register.open();  // Open register

        // Create and add customers
        Customer customer1 = new Customer(0, 5);
        Customer customer2 = new Customer(1, 3);
        Customer customer3 = new Customer(2, 4);
        register.addToQueue(customer1);
        register.addToQueue(customer2);
        register.addToQueue(customer3);

        // Process customers for 5 steps
        for (int i = 0; i < 5; i++) {
            System.out.println("Step " + (i + 1) + " - Queue length: " + register.getQueueLength());
            register.step();  // Process one customer
        }

        // Check if the first customer is done
        if (register.currentCustomerIsDone()) {
            Customer doneCustomer = register.removeCurrenCustomer();
            System.out.println("Customer done: " + doneCustomer);
        }

        // Final queue status
        System.out.println("Final queue length: " + register.getQueueLength());
        register.close();  // Close register
    }
}
