import java.util.ArrayList;

public class Store {
    Register registers[];

    public Store(int registersLength) {
        if (registersLength == 0) {
            throw new IllegalArgumentException("Must be at least 1!\n");
        }

        this.registers = new Register[registersLength];

        for (int i = 0; i < registersLength; i++) {
            this.registers[i] = new Register();
        }

        this.registers[0].open();
    }

    public int getNumberOfRegisters() {
        return this.registers.length;
    }

    public int getRegisterLength(int index){
        if(index>=0 && index <registers.length){
            return this.registers[index].getQueueLength();
        } else {
            throw new IndexOutOfBoundsException("Invalid register index.");
        }
    }

    public int getAverageQueueLength(){
        int length=this.registers.length;
        int openRegisters=0;

        if (length==0){
            throw new IllegalArgumentException("There is no store!\n");
        }
        int sum=0;

        for(int i=0; i<length; i++){
            if(this.registers[i].isOpen()){
                sum+=this.registers[i].getQueueLength();
                openRegisters++;
            }
        }

        double result = (double) sum / openRegisters;
        int roundedResult = (int) Math.round(result);  // Cast the result to int
        return roundedResult; 
    }


    public void newCustomer(Customer c) {
        if (this.registers.length == 0) {
            throw new IllegalStateException("No registers available.");
        }
    
        Register shortestQueue = null;
    
        for (int i = 0; i < this.registers.length; i++) {
            if (this.registers[i].isOpen() && (shortestQueue == null || this.registers[i].getQueueLength() < shortestQueue.getQueueLength())) {
                shortestQueue = this.registers[i];
            }
        }
    
        if (shortestQueue != null) {
            shortestQueue.addToQueue(c);
        } else {
            throw new IllegalStateException("No open registers available.");
        }
    }

    public void step(){
        //TODO: implementera tiden
        for (Register r : registers) {
            if (r.isOpen() && r.hasCustomers()) {
                r.step();
            }
        }
    }

    public void openNewRegister(){
        for(Register r : this.registers) {
            if(!r.isOpen()){
                r.open();
                return;
            }
        }
    }

    public Customer[] getDoneCustomers() {
        var customerArray = new ArrayList<Customer>();
        for (Register r : this.registers) {
            if (r.currentCustomerIsDone()) {
                var customer = r.removeCurrenCustomer();
                customerArray.add(customer);
            }
        }
        return customerArray.toArray(new Customer[0]);
    }

    public static void main(String[] args) {
        // Step 1: Create a store with 3 registers
        Store store = new Store(3);

        // Step 2: Create customers with different grocery counts
        Customer customer1 = new Customer(0, 5); // bornTime 0, 5 groceries
        Customer customer2 = new Customer(1, 2); // bornTime 1, 2 groceries
        Customer customer3 = new Customer(2, 3); // bornTime 2, 3 groceries

        // Step 3: Add customers to the store
        store.newCustomer(customer1);
        store.newCustomer(customer2);
        store.newCustomer(customer3);

        
        System.out.println("Average queue length: " + store.getAverageQueueLength());
        // Step 4: Process each step, checking for done customers
        for (int i = 0; i < 10; i++) {
            System.out.println("Step " + (i + 1));
            store.step();
            Customer[] doneCustomers = store.getDoneCustomers();
            for (Customer c : doneCustomers) {
                System.out.println("Customer done: " + c + "Array length of customers done length" + doneCustomers.length);

            }
        }

        // Display the final average queue length
    }
}
