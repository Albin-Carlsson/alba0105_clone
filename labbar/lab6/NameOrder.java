import java.util.Scanner;

public class NameOrder {
    public static void main(String[] args) {
        // Skapa en Scanner för att läsa in namn från användaren
        Scanner sc = new Scanner(System.in);

        // Läs in de två namnen från användaren
        System.out.print("Enter the first name: ");
        String name1 = sc.nextLine();
        
        System.out.print("Enter the second name: ");
        String name2 = sc.nextLine();

        // Använd compareTo() för att bestämma utskriftsordning
        if (name1.compareTo(name2) < 0) {
            System.out.println("Names in order: " + name1 + ", " + name2);
        } else if (name1.compareTo(name2) > 0) {
            System.out.println("Names in order: " + name2 + ", " + name1);
        } else {
            System.out.println("The names are identical: " + name1);
        }

    }
}