import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HammingCodeGUI {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Hamming Code Generator and Error Detection");
        frame.setSize(500, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(10, 1));

        JLabel dataBitsLabel = new JLabel("Enter Data Bits (d3 d2 d1 d0):");
        JTextField dataBitsInput = new JTextField();

        JLabel codewordLabel = new JLabel("Generated Codeword:");
        JTextField codewordOutput = new JTextField();
        codewordOutput.setEditable(false);

        JLabel receivedBitsLabel = new JLabel("Enter Received Bits (r3 r2 r1 r0 p2 p1 p0):");
        JTextField receivedBitsInput = new JTextField();

        JLabel errorLabel = new JLabel("Error Detection:");
        JTextField errorOutput = new JTextField();
        errorOutput.setEditable(false);

        JLabel correctedCodeLabel = new JLabel("Corrected Codeword:");
        JTextField correctedCodeOutput = new JTextField();
        correctedCodeOutput.setEditable(false);

        JButton generateButton = new JButton("Generate Codeword");
        JButton detectErrorButton = new JButton("Detect and Correct Error");

        panel.add(dataBitsLabel);
        panel.add(dataBitsInput);
        panel.add(generateButton);
        panel.add(codewordLabel);
        panel.add(codewordOutput);
        panel.add(receivedBitsLabel);
        panel.add(receivedBitsInput);
        panel.add(detectErrorButton);
        panel.add(errorLabel);
        panel.add(errorOutput);
        panel.add(correctedCodeLabel);
        panel.add(correctedCodeOutput);

        frame.add(panel);
        frame.setVisible(true);

        // Logic for "Generate Codeword" button
        generateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String dataBitsString = dataBitsInput.getText();
                if (dataBitsString.length() != 4) {
                    JOptionPane.showMessageDialog(frame, "Please enter exactly 4 data bits (d3 d2 d1 d0).");
                    return;
                }

                int[] dataBits = new int[4];
                try {
                    for (int i = 0; i < 4; i++) {
                        dataBits[i] = Character.getNumericValue(dataBitsString.charAt(i));
                        if (dataBits[i] != 0 && dataBits[i] != 1) {
                            throw new NumberFormatException();
                        }
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter valid binary digits (0 or 1).");
                    return;
                }

                int[] parityBits = new int[3];
                parityBits[2] = dataBits[1] ^ dataBits[2] ^ dataBits[3];
                parityBits[1] = dataBits[0] ^ dataBits[1] ^ dataBits[2];
                parityBits[0] = dataBits[0] ^ dataBits[2] ^ dataBits[3];

                int[] codeword = new int[7];
                codeword[0] = dataBits[0];
                codeword[1] = dataBits[1];
                codeword[2] = dataBits[2];
                codeword[3] = dataBits[3];
                codeword[4] = parityBits[2];
                codeword[5] = parityBits[1];
                codeword[6] = parityBits[0];

                StringBuilder codewordBuilder = new StringBuilder();
                for (int bit : codeword) {
                    codewordBuilder.append(bit);
                }
                codewordOutput.setText(codewordBuilder.toString());
            }
        });

        // Logic for "Detect and Correct Error" button
        detectErrorButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String receivedBitsString = receivedBitsInput.getText();
                if (receivedBitsString.length() != 7) {
                    JOptionPane.showMessageDialog(frame,
                            "Please enter exactly 7 received bits (r3 r2 r1 r0 p2 p1 p0).");
                    return;
                }

                int[] receivedBits = new int[7];
                try {
                    for (int i = 0; i < 7; i++) {
                        receivedBits[i] = Character.getNumericValue(receivedBitsString.charAt(i));
                        if (receivedBits[i] != 0 && receivedBits[i] != 1) {
                            throw new NumberFormatException();
                        }
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter valid binary digits (0 or 1).");
                    return;
                }

                // Calculate syndrome bits
                int[] syndrome = new int[3];
                syndrome[2] = receivedBits[3] ^ receivedBits[2] ^ receivedBits[1] ^ receivedBits[6]; // P2
                syndrome[1] = receivedBits[0] ^ receivedBits[2] ^ receivedBits[1] ^ receivedBits[5]; // P1
                syndrome[0] = receivedBits[0] ^ receivedBits[3] ^ receivedBits[2] ^ receivedBits[4]; // P0

                // Determine the error position from the syndrome
                int errorPosition = syndrome[0] * 1 + syndrome[1] * 2 + syndrome[2] * 4;

                if (errorPosition == 0) {
                    // No error detected
                    errorOutput.setText("No error detected.");
                    correctedCodeOutput.setText(receivedBitsString);
                } else if (errorPosition >= 1 && errorPosition <= 7) {
                    // Single-bit error detected
                    errorOutput.setText("Single error detected at position " + errorPosition);
                    receivedBits[errorPosition - 1] ^= 1; // Correct the error

                    StringBuilder correctedCodeBuilder = new StringBuilder();
                    for (int bit : receivedBits) {
                        correctedCodeBuilder.append(bit);
                    }
                    correctedCodeOutput.setText(correctedCodeBuilder.toString());
                } else {
                    // Multiple errors detected (syndrome is inconsistent)
                    errorOutput.setText("Multiple errors detected. Correction not possible.");
                    correctedCodeOutput.setText("Correction not possible.");
                }
            }
        });
    }
}
