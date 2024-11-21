import java.util.Scanner;

//skapar klassen MyDie
public class MyDieTest {

    public static void main(String[] args) {
        //tar emot inputen
        Scanner sc= new Scanner(System.in); 
        System.out.print("Number of sides: ");
        int sides=sc.nextInt();
        Die die= new Die(sides);
        int sum=0;

        for(int i=0; i<10; i++){
            sum+=die.roll();
        }

        System.out.println("Sum of rolls:" + sum);
        
    }
}
