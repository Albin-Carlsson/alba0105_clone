import java.util.Scanner;


//skapar Die classen som innehåller en int med antal sidor och value
public class Die {  
  private int numberOfSides;
  private int value;

  //sätter en die antal sidor till 6
  public Die() {
    this.numberOfSides = 6;
  }

  //sätter en die antal sidor till någon int
  public Die(int numberOfSides) {
    if(numberOfSides<=0 || numberOfSides >12){
      throw new IllegalArgumentException("Illegal number of sides for die");
    }
    this.numberOfSides = numberOfSides;

  }

  //man slår tärningen mha random, sätter in den i value
  public int roll(){
    this.value= (int) (Math.random() * numberOfSides) + 1;
    return value;
}

  //returnerar tärningens value
  public int get() {
      return value;
  }

  public boolean equals(Die otherDie){
    if (otherDie==null){
      return false;
    }
    //lika- om de har samma värde, identiska om de pekar på samma plats i minnet
    return this.numberOfSides ==otherDie.get();
  }

  public static void main(String [] args) {
      Scanner sc = new Scanner(System.in);
      System.out.print("Number of sides: ");
      int sides = sc.nextInt();
      Die d = new Die(sides);
      System.out.println("Alea iacta est: " + d.roll());
  }
}