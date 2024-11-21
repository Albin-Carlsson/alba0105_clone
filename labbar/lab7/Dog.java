
public class Dog extends Animal{
    @Override
    public void feed(Object animal) {  // More general parameter type (Object instead of Animal)
        System.out.println("Feeding a dog");
    }

    public static void main(String[] args) {
        System.out.println("arr");
    }

}


