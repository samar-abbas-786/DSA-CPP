import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;

public class PageReplacementGUI extends JFrame {
    private JTextArea outputArea;
    private JTextField pagesInputField;
    private JTextField frameSizeInputField;

    public PageReplacementGUI() {
        setTitle("Page Replacement Algorithms (LRU and OPT)");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        // Dark theme colors
        Color bgColor = new Color(30, 30, 30);
        Color textColor = new Color(200, 200, 200);
        Color buttonColor = new Color(60, 63, 65);

        // Set frame background color
        getContentPane().setBackground(bgColor);

        // Input panel
        JPanel inputPanel = new JPanel(new GridBagLayout());
        inputPanel.setBackground(bgColor);

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;

        JLabel pagesLabel = new JLabel("Pages (comma separated):");
        pagesLabel.setForeground(textColor);
        gbc.gridx = 0;
        gbc.gridy = 0;
        inputPanel.add(pagesLabel, gbc);

        pagesInputField = new JTextField(20);
        pagesInputField.setBackground(bgColor);
        pagesInputField.setForeground(textColor);
        gbc.gridx = 1;
        inputPanel.add(pagesInputField, gbc);

        JLabel frameSizeLabel = new JLabel("Frame Size:");
        frameSizeLabel.setForeground(textColor);
        gbc.gridx = 0;
        gbc.gridy = 1;
        inputPanel.add(frameSizeLabel, gbc);

        frameSizeInputField = new JTextField(5);
        frameSizeInputField.setBackground(bgColor);
        frameSizeInputField.setForeground(textColor);
        gbc.gridx = 1;
        inputPanel.add(frameSizeInputField, gbc);

        add(inputPanel, BorderLayout.NORTH);

        // Output area
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        outputArea.setLineWrap(true);
        outputArea.setWrapStyleWord(true);
        outputArea.setBackground(bgColor);
        outputArea.setForeground(textColor);

        JScrollPane scrollPane = new JScrollPane(outputArea);
        scrollPane.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        add(scrollPane, BorderLayout.CENTER);

        // Button panel
        JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 10));
        buttonPanel.setBackground(bgColor);

        JButton lruButton = new JButton("Run LRU Page Replacement");
        lruButton.setBackground(buttonColor);
        lruButton.setForeground(textColor);

        JButton optButton = new JButton("Run OPT Page Replacement");
        optButton.setBackground(buttonColor);
        optButton.setForeground(textColor);

        lruButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                outputArea.setText("");
                int[] pages = parsePages();
                int frameSize = parseFrameSize();
                if (pages != null && frameSize > 0) {
                    runLRU(pages, frameSize);
                }
            }
        });

        optButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                outputArea.setText("");
                int[] pages = parsePages();
                int frameSize = parseFrameSize();
                if (pages != null && frameSize > 0) {
                    runOPT(pages, frameSize);
                }
            }
        });

        buttonPanel.add(lruButton);
        buttonPanel.add(optButton);
        add(buttonPanel, BorderLayout.SOUTH);
    }

    private int[] parsePages() {
        try {
            String[] pageStrings = pagesInputField.getText().trim().split(",");
            int[] pages = new int[pageStrings.length];
            for (int i = 0; i < pageStrings.length; i++) {
                pages[i] = Integer.parseInt(pageStrings[i].trim());
            }
            return pages;
        } catch (NumberFormatException e) {
            outputArea.setText("Invalid page reference string. Please enter comma-separated integers.");
            return null;
        }
    }

    private int parseFrameSize() {
        try {
            return Integer.parseInt(frameSizeInputField.getText().trim());
        } catch (NumberFormatException e) {
            outputArea.setText("Invalid frame size. Please enter an integer.");
            return -1;
        }
    }

    private void runLRU(int[] pages, int frameSize) {
        java.util.List<Integer> frames = new ArrayList<>(frameSize);
        LinkedList<Integer> recentUseOrder = new LinkedList<>();
        int pageFaults = 0;

        outputArea.append("LRU Page Replacement:\n");
        for (int i = 0; i < pages.length; i++) {
            int page = pages[i];
            outputArea.append("Step " + (i + 1) + ": ");

            if (frames.contains(page)) {
                recentUseOrder.remove((Integer) page);
                recentUseOrder.add(page);
                outputArea.append(frames + " (Hit)\n");
            } else {
                pageFaults++;
                if (frames.size() == frameSize) {
                    int lruPage = recentUseOrder.removeFirst();
                    frames.remove((Integer) lruPage);
                }
                frames.add(page);
                recentUseOrder.add(page);
                outputArea.append(frames + " (Page Fault)\n");
            }
        }
        outputArea.append("\nTotal Page Faults (LRU): " + pageFaults + "\n");
        outputArea.append("Total Page Hits (LRU): " + (pages.length - pageFaults) + "\n\n");
    }

    private void runOPT(int[] pages, int frameSize) {
        java.util.List<Integer> frames = new ArrayList<>(frameSize);
        int pageFaults = 0;

        outputArea.append("Optimal Page Replacement:\n");
        for (int i = 0; i < pages.length; i++) {
            int page = pages[i];
            outputArea.append("Step " + (i + 1) + ": ");

            if (frames.contains(page)) {
                outputArea.append(frames + " (Hit)\n");
            } else {
                pageFaults++;
                if (frames.size() == frameSize) {
                    int pageToReplace = findOptimalPage(frames, pages, i + 1);
                    frames.remove((Integer) pageToReplace);
                }
                frames.add(page);
                outputArea.append(frames + " (Page Fault)\n");
            }
        }
        outputArea.append("\nTotal Page Faults (OPT): " + pageFaults + "\n");
    }

    private int findOptimalPage(java.util.List<Integer> frames, int[] pages, int startIdx) {
        Map<Integer, Integer> nextUse = new HashMap<>();

        for (int frame : frames) {
            nextUse.put(frame, Integer.MAX_VALUE);
            for (int j = startIdx; j < pages.length; j++) {
                if (pages[j] == frame) {
                    nextUse.put(frame, j);
                    break;
                }
            }
        }

        int pageToReplace = frames.get(0);
        int farthestIdx = nextUse.get(pageToReplace);
        for (int frame : frames) {
            int nextIdx = nextUse.get(frame);
            if (nextIdx > farthestIdx) {
                pageToReplace = frame;
                farthestIdx = nextIdx;
            }
        }
        return pageToReplace;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            PageReplacementGUI gui = new PageReplacementGUI();
            gui.setVisible(true);
        });
    }
}
