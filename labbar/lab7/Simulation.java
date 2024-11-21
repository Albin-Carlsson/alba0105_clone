import java.util.Random;

public class Simulation {
    private Store store;
    private int time;
    private int intensity;
    private int maxGroceries;
    private int thresholdForNewRegister;
    private int totalCustomers;
    private float waitingTime;
    private int maxTime;


    public Simulation(int numRegisters, int intensity, int maxGroceries, int thresholdForNewRegister) {
        if(numRegisters<=0){
            throw new IllegalArgumentException("Registers must be bigger than 0\n");
        }
        this.store = new Store(numRegisters);
        this.time = 0;
        this.intensity = intensity;
        this.maxGroceries = maxGroceries;
        this.thresholdForNewRegister = thresholdForNewRegister;
        this.totalCustomers=0;
        this.waitingTime=0.0f;
        this.maxTime=0;
    }

    public void step() {
        time++;
        Random rand = new Random();

        // Generate new customer
        if (rand.nextInt(100) < intensity) {
            int groceries = rand.nextInt(maxGroceries) + 1;
            Customer newCustomer = new Customer(time, groceries);
            store.newCustomer(newCustomer);
        }

        // Process store steps
        store.step();

        // Check average queue length and open new register if needed
        if (store.getAverageQueueLength() > thresholdForNewRegister) {
            store.openNewRegister();
        }
        
        //array of getdonecustomers
        Customer[] doneCustomers=store.getDoneCustomers();
      
        this.totalCustomers+=doneCustomers.length;
        
        //waiting time
        for(Customer customer: doneCustomers){
            this.waitingTime+= (float) this.time - customer.bornTime;
            if(this.time-customer.bornTime>this.maxTime){
                this.maxTime=this.time-customer.bornTime;
            }
        }
   
        //getting max time
    }

    public int getTime() {
        return time;
    }


    public String toString() {
        String str=new String();
        String strCustomers=new String();
        int groceries=0;
        int numberOfRegisters=store.getNumberOfRegisters();

        //första kassan som är alltid öppen
        if(numberOfRegisters!=0){
            for(int j=0; j<numberOfRegisters; j++){

                strCustomers=new String();
                if(store.registers[j].isOpen()&& store.registers[j].hasCustomers()){
                    groceries=store.registers[j].getFirstCustomer().getGroceries();
                    for(int i=0; i<store.registers[j].getQueueLength(); i++){
                        strCustomers+="@";
                    }
                    str+="[" + groceries+  "]" + strCustomers+ "\n";
                }
                else if (store.registers[j].isOpen()){
                    str+="[ ]\n";
                }
                else{
                    str += "X [ ]\n";
                }
            }
        }


        float wait=0.0f;        
        if (this.totalCustomers > 0) {
            wait= this.waitingTime / this.totalCustomers;
        } else {
            wait = this.waitingTime;  //behåller samma
        }

        str+="Number of customers served: " + this.totalCustomers + "\n"+
             "Max waiting time: " + this.maxTime + "\n"+ 
             "Average waiting time: " + String.format("%.1f", wait) + "\n"
             + this.time + "\n";
        return str;

    }
}