import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

class Item {
    long weight;
    long profit;
    double ratio;

    public Item(long weight, long profit) {
        this.weight = weight;
        this.profit = profit;
        this.ratio = (double) profit / weight;
    }

    @Override
    public String toString() {
        return "Weight: " + weight + ", Profit: " + profit;
    }
}

public class KnapsackGUI extends JFrame {
    private JTextField capacityField;
    private JTextArea outputArea;
    private JTextField weightField;
    private JTextField profitField;
    private DefaultListModel<Item> itemListModel;
    private JLabel statusLabel;

    public KnapsackGUI() {
        setTitle("Knapsack Problem Solver");
        setSize(700, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        getContentPane().setBackground(Color.BLACK);
        setLayout(new BorderLayout(10, 10));

        JPanel inputPanel = new JPanel();
        inputPanel.setBackground(new Color(30, 30, 30));
        inputPanel.setLayout(new GridLayout(5, 2, 5, 5));

        Font labelFont = new Font("Arial", Font.BOLD, 16);

        JLabel weightLabel = new JLabel("Weight:");
        JLabel profitLabel = new JLabel("Profit:");
        JLabel capacityLabel = new JLabel("Capacity:");
        weightLabel.setFont(labelFont);
        profitLabel.setFont(labelFont);
        capacityLabel.setFont(labelFont);

        weightLabel.setForeground(Color.WHITE);
        profitLabel.setForeground(Color.WHITE);
        capacityLabel.setForeground(Color.WHITE);

        weightField = new JTextField();
        profitField = new JTextField();
        capacityField = new JTextField();

        weightField.setBackground(new Color(40, 40, 40));
        weightField.setForeground(Color.WHITE);
        profitField.setBackground(new Color(40, 40, 40));
        profitField.setForeground(Color.WHITE);
        capacityField.setBackground(new Color(40, 40, 40));
        capacityField.setForeground(Color.WHITE);

        JButton addButton = new JButton("Add Item");
        JButton solveButton01 = new JButton("Solve 0-1 Knapsack");
        JButton solveButtonFractional = new JButton("Solve Fractional Knapsack");

        addButton.setBackground(new Color(60, 60, 60));
        addButton.setForeground(Color.WHITE);
        solveButton01.setBackground(new Color(60, 60, 60));
        solveButton01.setForeground(Color.WHITE);
        solveButtonFractional.setBackground(new Color(60, 60, 60));
        solveButtonFractional.setForeground(Color.WHITE);

        itemListModel = new DefaultListModel<>();
        JList<Item> itemList = new JList<>(itemListModel);
        itemList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        itemList.setBackground(new Color(40, 40, 40));
        itemList.setForeground(Color.WHITE);
        itemList.setFont(new Font("Arial", Font.PLAIN, 14));

        outputArea = new JTextArea();
        outputArea.setEditable(false);
        outputArea.setBackground(new Color(40, 40, 40));
        outputArea.setForeground(Color.WHITE);
        outputArea.setFont(new Font("Arial", Font.PLAIN, 14));

        inputPanel.add(weightLabel);
        inputPanel.add(weightField);
        inputPanel.add(profitLabel);
        inputPanel.add(profitField);
        inputPanel.add(capacityLabel);
        inputPanel.add(capacityField);
        inputPanel.add(addButton);

        add(inputPanel, BorderLayout.NORTH);
        add(new JScrollPane(itemList), BorderLayout.CENTER);
        add(new JScrollPane(outputArea), BorderLayout.SOUTH);

        JPanel buttonPanel = new JPanel();
        buttonPanel.setBackground(new Color(30, 30, 30));
        buttonPanel.add(solveButton01);
        buttonPanel.add(solveButtonFractional);
        add(buttonPanel, BorderLayout.EAST);

        statusLabel = new JLabel("Ready");
        statusLabel.setFont(new Font("Arial", Font.BOLD, 16));
        statusLabel.setForeground(Color.WHITE);
        add(statusLabel, BorderLayout.WEST);

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    long weight = Long.parseLong(weightField.getText());
                    long profit = Long.parseLong(profitField.getText());
                    itemListModel.addElement(new Item(weight, profit));
                    weightField.setText("");
                    profitField.setText("");
                    animateStatusLabel("Item added", new Color(46, 204, 113));
                } catch (NumberFormatException ex) {
                    showError("Please enter valid integers for weight and profit.");
                }
            }
        });

        solveButton01.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    long capacity = Long.parseLong(capacityField.getText());
                    Item[] items = new Item[itemListModel.size()];
                    for (int i = 0; i < itemListModel.size(); i++) {
                        items[i] = itemListModel.get(i);
                    }
                    outputArea.setText("0-1 Knapsack Solution:\n");
                    outputArea.append(solveKnapsack01(items, capacity));
                    animateStatusLabel("0-1 Knapsack Solved", new Color(52, 152, 219));
                } catch (NumberFormatException ex) {
                    showError("Please enter a valid integer for capacity.");
                }
            }
        });

        solveButtonFractional.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    long capacity = Long.parseLong(capacityField.getText());
                    Item[] items = new Item[itemListModel.size()];
                    for (int i = 0; i < itemListModel.size(); i++) {
                        items[i] = itemListModel.get(i);
                    }
                    outputArea.setText("Fractional Knapsack Solution:\n");
                    outputArea.append(solveKnapsackFractional(items, capacity));
                    animateStatusLabel("Fractional Knapsack Solved", new Color(155, 89, 182));
                } catch (NumberFormatException ex) {
                    showError("Please enter a valid integer for capacity.");
                }
            }
        });
    }

    private String solveKnapsack01(Item[] items, long capacity) {
        Map<String, Long> dp = new HashMap<>();
        dp.put("0_" + capacity, 0L); // Initial state: max profit with 0 items and full capacity

        for (int i = 0; i < items.length; i++) {
            Item item = items[i];
            Map<String, Long> currentDp = new HashMap<>(dp);
            for (String key : dp.keySet()) {
                String[] parts = key.split("_");
                int index = Integer.parseInt(parts[0]);
                long remainingCapacity = Long.parseLong(parts[1]);
                if (remainingCapacity >= item.weight) {
                    long newProfit = dp.get(key) + item.profit;
                    String newKey = (index + 1) + "_" + (remainingCapacity - item.weight);
                    currentDp.put(newKey, Math.max(currentDp.getOrDefault(newKey, 0L), newProfit));
                }
            }
            dp = currentDp;
        }

        long maxProfit = 0;
        for (Long profit : dp.values()) {
            maxProfit = Math.max(maxProfit, profit);
        }

        StringBuilder result = new StringBuilder("Maximum Profit: " + maxProfit + "\n");
        long w = capacity;
        for (int i = items.length - 1; i >= 0 && w > 0; i--) {
            Item item = items[i];
            String key = (i + 1) + "_" + w;
            if (dp.containsKey(key) && dp.get(key) > dp.getOrDefault(i + "_" + (w - item.weight), 0L)) {
                result.append("Included item with weight: ").append(item.weight)
                        .append(" and profit: ").append(item.profit).append("\n");
                w -= item.weight;
            }
        }

        return result.toString();
    }

    private String solveKnapsackFractional(Item[] items, long capacity) {
        Arrays.sort(items, Comparator.comparingDouble(i -> -i.ratio));

        double totalProfit = 0;
        StringBuilder result = new StringBuilder();
        for (Item item : items) {
            if (capacity - item.weight >= 0) {
                capacity -= item.weight;
                totalProfit += item.profit;
                result.append("Took full item with weight: ").append(item.weight)
                        .append(" and profit: ").append(item.profit).append("\n");
            } else {
                totalProfit += item.profit * ((double) capacity / item.weight);
                result.append("Took fraction of item with weight: ").append(item.weight)
                        .append(" and profit: ").append(item.profit * ((double) capacity / item.weight)).append("\n");
                break;
            }
        }
        result.append("Maximum Profit: ").append(totalProfit).append("\n");

        return result.toString();
    }

    private void animateStatusLabel(String message, Color color) {
        Timer timer = new Timer(20, null);
        timer.addActionListener(new ActionListener() {
            int alpha = 255;

            @Override
            public void actionPerformed(ActionEvent e) {
                alpha -= 5;
                if (alpha <= 0) {
                    alpha = 255;
                    statusLabel.setText(message);
                    statusLabel.setForeground(color);
                    ((Timer) e.getSource()).stop();
                }
                statusLabel.setForeground(new Color(color.getRed(), color.getGreen(), color.getBlue(), alpha));
            }
        });
        timer.start();
    }

    private void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Error", JOptionPane.ERROR_MESSAGE);
        animateStatusLabel("Error", Color.RED);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            KnapsackGUI frame = new KnapsackGUI();
            frame.setVisible(true);
        });
    }
}
