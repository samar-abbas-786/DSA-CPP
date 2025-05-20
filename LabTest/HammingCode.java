import java.util.Scanner;

public class HammingCode {

    public static int[] generateCodeword(int[] dataword) {
        int a3 = dataword[0];
        int a2 = dataword[1];
        int a1 = dataword[2];
        int a0 = dataword[3];

        // Calculate parity bits
        int r0 = a2 ^ a1 ^ a0;
        int r1 = a3 ^ a2 ^ a1;
        int r2 = a1 ^ a0 ^ a3;

        // Generate the codeword
        return new int[] { a3, a2, a1, a0, r2, r1, r0 };
    }

    public static int calculateSyndrome(int[] receivedCodeword) {
        int b3 = receivedCodeword[0];
        int b2 = receivedCodeword[1];
        int b1 = receivedCodeword[2];
        int b0 = receivedCodeword[3];
        int q2 = receivedCodeword[4];
        int q1 = receivedCodeword[5];
        int q0 = receivedCodeword[6];

        // Calculate syndrome bits
        int s0 = b2 ^ b1 ^ b0 ^ q0;
        int s1 = b3 ^ b2 ^ b1 ^ q1;
        int s2 = b1 ^ b0 ^ b3 ^ q2;

        // Combine syndrome bits into a single integer
        return (s2 << 2) | (s1 << 1) | s0;
    }

    public static int[] correctError(int[] receivedCodeword, int syndrome, int[] generatedCodeword) {
        // Error map for positions
        int[] errorMap = { -1, 6, 5, 2, 4, 3, 0, 1 }; // -1 indicates no error

        if (syndrome == 0) {
            System.out.println("No error in received codeword: ");
            return receivedCodeword;
        } else if (syndrome > 0 && syndrome < errorMap.length) {
            int errorPosition = errorMap[syndrome];
            System.out.println("Error detected at position: " + errorPosition);

            // Correct the error if valid
            if (errorPosition != -1) {
                receivedCodeword[errorPosition] ^= 1;

                // Verify if the corrected codeword matches the generated codeword
                boolean isCorrected = true;
                for (int i = 0; i < receivedCodeword.length; i++) {
                    if (receivedCodeword[i] != generatedCodeword[i]) {
                        isCorrected = false;
                        break;
                    }
                }

                if (isCorrected) {
                    System.out.println("Corrected codeword: ");
                    return receivedCodeword;
                } else {
                    System.out.println("Cannot be corrected. Multiple errors detected.");
                    return null;
                }
            }
        }
        System.out.println("Cannot be corrected. Multiple errors detected.");
        return null;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Input dataword
        System.out.print("Enter 4-bit dataword: ");
        String datawordStr = scanner.nextLine();
        int[] dataword = new int[4];
        for (int i = 0; i < 4; i++) {
            dataword[i] = Character.getNumericValue(datawordStr.charAt(i));
        }

        // Generate codeword
        int[] generatedCodeword = generateCodeword(dataword);
        System.out.print("Generated codeword: ");
        for (int bit : generatedCodeword) {
            System.out.print(bit);
        }
        System.out.println();

        // Input received codeword
        System.out.print("Enter 7-bit received codeword: ");
        String receivedCodewordStr = scanner.nextLine();
        int[] receivedCodeword = new int[7];
        for (int i = 0; i < 7; i++) {
            receivedCodeword[i] = Character.getNumericValue(receivedCodewordStr.charAt(i));
        }

        // Calculate syndrome and correct error
        int syndrome = calculateSyndrome(receivedCodeword);
        int[] correctedCodeword = correctError(receivedCodeword, syndrome, generatedCodeword);

        // Print corrected codeword if available
        if (correctedCodeword != null) {
            System.out.print("Corrected codeword: ");
            for (int bit : correctedCodeword) {
                System.out.print(bit);
            }
            System.out.println();
        }

        scanner.close();
    }
}
