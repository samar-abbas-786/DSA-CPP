import java.util.Scanner;

public class Hello {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        boolean wrong = true;
        while (wrong) {
            System.out.println("Enter the Number");
            int x = sc.nextInt();
            if (x > 90) {
                System.out.println("Guess no. is Smaller");
            } else if (x < 90) {
                System.out.println("Guess no. is Larger");
            } else {
                System.out.println("Boooooommmmmmmmmm");
                wrong = false;
            }
        }
        sc.close();

    }
}