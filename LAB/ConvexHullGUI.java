import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Stack;

public class ConvexHullGUI extends JPanel {
    private final ArrayList<Point> points = new ArrayList<>();
    private final ArrayList<String> pointLabels = new ArrayList<>();
    private final ArrayList<Point> hull = new ArrayList<>();
    private final JTextArea logArea;

    public ConvexHullGUI(JTextArea logArea) {
        this.logArea = logArea;
        setBackground(Color.DARK_GRAY);

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                String label = "P";
                points.add(e.getPoint());
                pointLabels.add(label);
                logArea.append(label + " -> (" + e.getX() + ", " + e.getY() + ")\n");

                computeConvexHull();
                repaint();
            }
        });
    }

    public void computeConvexHull() {
        hull.clear();
        logArea.append("\n--- Computing Convex Hull ---\n");

        if (points.size() < 3) {
            logArea.append("Need at least 3 points to compute a convex hull.\n");
            return;
        }

        // Step 1: Find the lowest Y-coordinate point (pivot)
        Point pivot = Collections.min(points,
                (p1, p2) -> p1.y != p2.y ? Integer.compare(p1.y, p2.y) : Integer.compare(p1.x, p2.x));
        logArea.append("Pivot (Lowest Y-Coordinate): (" + pivot.x + ", " + pivot.y + ")\n");

        // Step 2: Sort points based on polar angle with pivot
        points.sort((p1, p2) -> {
            int orientation = orientation(pivot, p1, p2);
            if (orientation == 0) {
                return Double.compare(pivot.distance(p1), pivot.distance(p2));
            }
            return orientation > 0 ? -1 : 1; // Sort counterclockwise
        });

        logArea.append("Points sorted based on polar angle.\n");

        // Step 3: Construct convex hull using a stack
        Stack<Point> stack = new Stack<>();
        for (Point p : points) {
            while (stack.size() > 1 && orientation(stack.get(stack.size() - 2), stack.peek(), p) <= 0) {
                Point removed = stack.pop();
                logArea.append("Removing " + getLabel(removed) + " (" + removed.x + ", " + removed.y
                        + ") - Not part of convex hull.\n");
            }
            stack.push(p);
            logArea.append("Adding " + getLabel(p) + " (" + p.x + ", " + p.y + ") to convex hull.\n");
        }

        hull.addAll(stack);
        logArea.append("Convex Hull Computation Complete!\n");
        repaint();
    }

    // Clears all points and hull
    public void clearScreen() {
        points.clear();
        pointLabels.clear();
        hull.clear();
        logArea.setText("Screen cleared. Add new points.\n");
        repaint();
    }

    // Determines orientation of triplet (p, q, r)
    private int orientation(Point p, Point q, Point r) {
        int val = (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
        return Integer.compare(val, 0);
    }

    // Get label of a point
    private String getLabel(Point p) {
        int index = points.indexOf(p);
        return index >= 0 ? pointLabels.get(index) : "?";
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.LIGHT_GRAY); // Light gray for points

        // Draw points and labels
        for (int i = 0; i < points.size(); i++) {
            Point p = points.get(i);
            String label = pointLabels.get(i);

            g.fillOval(p.x - 3, p.y - 3, 6, 6); // Draw point
            g.setColor(Color.WHITE); // Label color
            g.drawString(label, p.x + 5, p.y - 5); // Draw label
            g.setColor(Color.LIGHT_GRAY); // Reset point color
        }

        // Draw Convex Hull
        g.setColor(Color.CYAN);
        for (int i = 0; i < hull.size(); i++) {
            Point p1 = hull.get(i);
            Point p2 = hull.get((i + 1) % hull.size());
            g.drawLine(p1.x, p1.y, p2.x, p2.y);
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Convex Hull (Graham's Scan)");
        JTextArea logArea = new JTextArea(10, 50);
        logArea.setEditable(false);
        logArea.setBackground(Color.BLACK); // Dark background for logs
        logArea.setForeground(Color.WHITE); // White text for logs
        JScrollPane scrollPane = new JScrollPane(logArea);

        ConvexHullGUI panel = new ConvexHullGUI(logArea);
        JButton clearButton = new JButton("Clear Screen");

        // Set dark theme for button
        clearButton.setBackground(Color.DARK_GRAY);
        clearButton.setForeground(Color.WHITE);
        clearButton.setFocusPainted(false);

        // Clear the screen when button is clicked
        clearButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                panel.clearScreen();
            }
        });

        JPanel controlPanel = new JPanel();
        controlPanel.setBackground(Color.BLACK); // Dark background for control panel
        controlPanel.add(clearButton);

        frame.setLayout(new BorderLayout());
        frame.add(panel, BorderLayout.CENTER);
        frame.add(controlPanel, BorderLayout.NORTH);
        frame.add(scrollPane, BorderLayout.SOUTH);

        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
    }
}
