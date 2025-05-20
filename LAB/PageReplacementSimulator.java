import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class PageReplacementSimulator extends JFrame {
    private JTextField referenceStringInput, frameInput;
    private JButton fifoButton, optimalButton, lruButton;
    private JTextArea resultArea;
    private JTable table;
    private DefaultTableModel tableModel;
    private int frames;
    private String referenceString;

    public PageReplacementSimulator() {
        setTitle("Page Replacement Simulator");
        setSize(1000, 600);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel inputPanel = new JPanel(new GridLayout(2, 2));
        inputPanel.add(new JLabel("Reference String (comma-separated):"));
        referenceStringInput = new JTextField();
        inputPanel.add(referenceStringInput);
        inputPanel.add(new JLabel("Number of Frames:"));
        frameInput = new JTextField();
        inputPanel.add(frameInput);
        add(inputPanel, BorderLayout.NORTH);

        JPanel buttonPanel = new JPanel();
        fifoButton = new JButton("FIFO");
        optimalButton = new JButton("Optimal");
        lruButton = new JButton("LRU");

        buttonPanel.add(fifoButton);
        buttonPanel.add(optimalButton);
        buttonPanel.add(lruButton);
        add(buttonPanel, BorderLayout.CENTER);

        resultArea = new JTextArea(5, 30);
        resultArea.setEditable(false);
        add(new JScrollPane(resultArea), BorderLayout.SOUTH);

        tableModel = new DefaultTableModel();
        table = new JTable(tableModel);
        JScrollPane tableScrollPane = new JScrollPane(table);
        add(tableScrollPane, BorderLayout.EAST);

        fifoButton.addActionListener(e -> performPageReplacement("FIFO"));
        optimalButton.addActionListener(e -> performPageReplacement("Optimal"));
        lruButton.addActionListener(e -> performPageReplacement("LRU"));
    }

    private void performPageReplacement(String algorithm) {
        referenceString = referenceStringInput.getText().trim();
        try {
            frames = Integer.parseInt(frameInput.getText().trim());
            int[] pages = Arrays.stream(referenceString.split(","))
                    .mapToInt(Integer::parseInt)
                    .toArray();

            prepareTable(pages.length);

            int pageFaults;
            switch (algorithm) {
                case "FIFO":
                    pageFaults = fifoPageReplacement(pages, frames);
                    break;
                case "Optimal":
                    pageFaults = optimalPageReplacement(pages, frames);
                    break;
                case "LRU":
                    pageFaults = lruPageReplacement(pages, frames);
                    break;
                default:
                    throw new IllegalArgumentException("Invalid algorithm");
            }

            int pageHits = pages.length - pageFaults;
            double hitRatio = (double) pageHits / pages.length;
            double faultRatio = (double) pageFaults / pages.length;

            resultArea.setText("Algorithm: " + algorithm + "\n" +
                    "Page Faults: " + pageFaults + "\n" +
                    "Page Hits: " + pageHits + "\n" +
                    "Hit Ratio: " + String.format("%.2f", hitRatio) + "\n" +
                    "Fault Ratio: " + String.format("%.2f", faultRatio));
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Please enter valid numbers.");
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Error: " + ex.getMessage());
        }
    }

    private void prepareTable(int columns) {
        tableModel.setRowCount(0);
        tableModel.setColumnCount(columns);
        for (int i = 0; i < frames; i++) {
            tableModel.addRow(new Object[columns]);
        }
    }

    private void updateTable(int step, int[] frameContent) {
        for (int i = 0; i < frames; i++) {
            if (i < frameContent.length) {
                tableModel.setValueAt(frameContent[i] == -1 ? "" : frameContent[i], i, step);
            } else {
                tableModel.setValueAt("", i, step);
            }
        }
    }

    private int fifoPageReplacement(int[] pages, int capacity) {
        Queue<Integer> queue = new LinkedList<>();
        int[] frameContent = new int[capacity];
        Arrays.fill(frameContent, -1);
        int pageFaults = 0;

        for (int i = 0; i < pages.length; i++) {
            if (!queue.contains(pages[i])) {
                pageFaults++;
                if (queue.size() == capacity) {
                    int removed = queue.poll();
                    for (int j = 0; j < capacity; j++) {
                        if (frameContent[j] == removed) {
                            frameContent[j] = -1;
                            break;
                        }
                    }
                }
                queue.add(pages[i]);
                for (int j = 0; j < capacity; j++) {
                    if (frameContent[j] == -1) {
                        frameContent[j] = pages[i];
                        break;
                    }
                }
            }
            updateTable(i, frameContent.clone());
        }
        return pageFaults;
    }

    private int optimalPageReplacement(int[] pages, int capacity) {
        int[] frameContent = new int[capacity];
        Arrays.fill(frameContent, -1);
        int pageFaults = 0;

        for (int i = 0; i < pages.length; i++) {
            if (!search(pages[i], frameContent)) {
                pageFaults++;
                if (isFrameFull(frameContent)) {
                    int replaceIndex = predict(pages, frameContent, i + 1);
                    frameContent[replaceIndex] = pages[i];
                } else {
                    for (int j = 0; j < capacity; j++) {
                        if (frameContent[j] == -1) {
                            frameContent[j] = pages[i];
                            break;
                        }
                    }
                }
            }
            updateTable(i, frameContent.clone());
        }
        return pageFaults;
    }

    private int predict(int[] pages, int[] frameContent, int startIndex) {
        int farthest = startIndex, replaceIndex = -1;
        for (int i = 0; i < frameContent.length; i++) {
            int j;
            for (j = startIndex; j < pages.length; j++) {
                if (frameContent[i] == pages[j]) {
                    if (j > farthest) {
                        farthest = j;
                        replaceIndex = i;
                    }
                    break;
                }
            }
            if (j == pages.length)
                return i;
        }
        return replaceIndex == -1 ? 0 : replaceIndex;
    }

    private boolean isFrameFull(int[] frameContent) {
        for (int frame : frameContent) {
            if (frame == -1)
                return false;
        }
        return true;
    }

    private boolean search(int page, int[] frameContent) {
        for (int frame : frameContent) {
            if (frame == page)
                return true;
        }
        return false;
    }

    private int lruPageReplacement(int[] pages, int capacity) {
        LinkedHashMap<Integer, Integer> lruCache = new LinkedHashMap<>(capacity, 0.75f, true);
        int[] frameContent = new int[capacity];
        Arrays.fill(frameContent, -1);
        int pageFaults = 0;

        for (int i = 0; i < pages.length; i++) {
            if (!lruCache.containsKey(pages[i])) {
                pageFaults++;
                if (lruCache.size() == capacity) {
                    int leastUsed = lruCache.entrySet().iterator().next().getKey();
                    lruCache.remove(leastUsed);
                    for (int j = 0; j < capacity; j++) {
                        if (frameContent[j] == leastUsed) {
                            frameContent[j] = -1;
                            break;
                        }
                    }
                }
                for (int j = 0; j < capacity; j++) {
                    if (frameContent[j] == -1) {
                        frameContent[j] = pages[i];
                        break;
                    }
                }
            }
            lruCache.put(pages[i], i);
            updateTable(i, frameContent.clone());
        }
        return pageFaults;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            PageReplacementSimulator simulator = new PageReplacementSimulator();
            simulator.setVisible(true);
        });
    }
}
