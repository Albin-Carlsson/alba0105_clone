

public class Queue {
    //skapar en nod i kön
    private static class Node{
        Customer element;
        Node next;
        
        Node(Customer element){
            this.element=element;
            this.next=null;
        }


    }
    
    private Node first;
    private Node last;
    private int length;

    public Queue(){
        this.first=null;
        this.last=null;
        this.length=0;
    }

    public int length(){
        return this.length;
    }

    //lägger en customer i queuen
    public void enqueue(Object c){
        var customer = new Node((Customer) c);
        if(this.length==0){
            this.first= customer;
            this.last= customer;
        }
        else {
            var last= this.last;
            last.next=customer;
            this.last=customer;
        }
        this.length++;
    }

    public Customer first(){
        if(this.first!=null){
            return this.first.element;
        }
        return null;
    }

    public Customer dequeue(){
        if (this.length==0){
            return null;
        }
        Node toRemove=this.first;

        if(this.length==1){
            this.first=null;
            this.last=null;
            this.length=0;
            return toRemove.element;
        }
        
        this.first=toRemove.next;
        this.length=this.length-1;
        return toRemove.element;
    }

    public static void main(String[] args) {
        var customer1=new Customer(0,3);
        var customer2=new Customer(0,2);
        var queue=new Queue();
        queue.enqueue(customer1);
        queue.enqueue(customer2);
        queue.enqueue(queue);
        if(customer1==queue.dequeue()){
            System.out.println("First customer has left");
            System.out.println("Length of queue (should be 1): " + queue.length());
        }
        else{
            System.out.println(("First customer failed"));
        }
        if(customer2==queue.dequeue()){
            System.out.println("Second customer left!");
        }

        System.out.println("Length of queue (should be 0): " + queue.length());

    }


}
