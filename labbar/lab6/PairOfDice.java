import java.util.Scanner;

public class PairOfDice{
    private Die FirstDie;
    private Die SecondDie;
    private int sides;

    //skapar ett tärningspar med givet antal sidor
    public PairOfDice(int num){
        this.FirstDie=new Die(num);
        this.SecondDie=new Die(num);
        this.sides=num;
    }
    
    //slå båda tärningar samtidigt och returnera resultatet (summan)
    public int pairRoll(){
        int value1= this.FirstDie.roll();
        int value2= this.SecondDie.roll();
        return value1+value2;
    }

    public int getFirst(){
        return this.FirstDie.get();
    }

    public int getSecond(){
        return this.SecondDie.get();
    }

    public String toString(){
        return("Pair of Dice : \nNumber of sides on dice: " + this.sides + 
                "\nFirst dice value: " + this.getFirst()+
                "\nSecond dice value: " + this.getSecond());
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Number of sides: ");
        int sides = sc.nextInt();
        var pair=new PairOfDice(sides);

        var roll=pair.pairRoll();
        System.out.println("\nRolled the dice: " + roll);

        System.out.println("\ntoString: \n"+ pair.toString());
    }
}