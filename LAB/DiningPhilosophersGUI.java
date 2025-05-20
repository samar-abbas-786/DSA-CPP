import javax.swing.*;
import java.awt.*;
import java.util.concurrent.Semaphore;
import java.util.Random;

public class DiningPhilosophersGUI extends JPanel {
    private static final int NUM_PHILOSOPHERS = 19;
    private static final Semaphore[] chopsticks = new Semaphore[NUM_PHILOSOPHERS];
    private static final Philosopher[] philosophers = new Philosopher[NUM_PHILOSOPHERS];

    private static final Color THINKING_COLOR = new Color(100, 149, 237);
    private static final Color EATING_COLOR = new Color(50, 205, 50);
    private static final Color TABLE_COLOR = new Color(139, 69, 19);
    private static final Color CHOPSTICK_COLOR = new Color(106, 90, 205);
    private static final Color BACKGROUND_COLOR = new Color(30, 30, 30);
    private static final Color TEXT_COLOR = Color.WHITE;

    private static final int WINDOW_WIDTH = 1000;
    private static final int WINDOW_HEIGHT = 800;
    private static final int TABLE_RADIUS = 200;
    private static final int PHILOSOPHER_RADIUS = 40;
    private static final int CHOPSTICK_WIDTH = 10;
    private static final int CHOPSTICK_HEIGHT = 60;

    private final JTextArea statusArea = new JTextArea(20, 30);

    static {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            chopsticks[i] = new Semaphore(1);
        }
    }

    public DiningPhilosophersGUI() {
        setPreferredSize(new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT));
        setBackground(BACKGROUND_COLOR);

        statusArea.setEditable(false);
        statusArea.setBackground(new Color(50, 50, 50));
        statusArea.setForeground(TEXT_COLOR);
        statusArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane scrollPane = new JScrollPane(statusArea);
        scrollPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        setLayout(new BorderLayout());
        add(scrollPane, BorderLayout.EAST);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int centerX = WINDOW_WIDTH / 2 - 100;
        int centerY = WINDOW_HEIGHT / 2;

        g.setColor(TABLE_COLOR);
        g.fillOval(centerX - TABLE_RADIUS, centerY - TABLE_RADIUS, TABLE_RADIUS * 2, TABLE_RADIUS * 2);

        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            double angle = 2 * Math.PI * i / NUM_PHILOSOPHERS;
            int x = centerX + (int) (TABLE_RADIUS * Math.cos(angle)) - PHILOSOPHER_RADIUS;
            int y = centerY + (int) (TABLE_RADIUS * Math.sin(angle)) - PHILOSOPHER_RADIUS;

            g.setColor(philosophers[i].isEating ? EATING_COLOR : THINKING_COLOR);
            g.fillOval(x, y, PHILOSOPHER_RADIUS * 2, PHILOSOPHER_RADIUS * 2);

            g.setColor(TEXT_COLOR);
            g.setFont(new Font("Arial", Font.BOLD, 16));
            String num = Integer.toString(i + 1);
            int textWidth = g.getFontMetrics().stringWidth(num);
            g.drawString(num, x + PHILOSOPHER_RADIUS - textWidth / 2, y + PHILOSOPHER_RADIUS + 5);

            int chopX = centerX + (int) ((TABLE_RADIUS + 40) * Math.cos(angle));
            int chopY = centerY + (int) ((TABLE_RADIUS + 40) * Math.sin(angle));
            g.setColor(CHOPSTICK_COLOR);

            if (!philosophers[i].isHoldingLeftChopstick) {
                g.fillRect(chopX - 5, chopY - 20, CHOPSTICK_WIDTH, CHOPSTICK_HEIGHT);
            }
        }
    }

    private void logStatus(String message) {
        SwingUtilities.invokeLater(() -> {
            statusArea.append(message + "\n");
            statusArea.setCaretPosition(statusArea.getDocument().getLength());
            repaint();
        });
    }

    class Philosopher extends Thread {
        private final int id;
        private final Random random = new Random();
        private boolean isEating = false;
        private boolean isHoldingLeftChopstick = true;
        private boolean isHoldingRightChopstick = true;

        Philosopher(int id) {
            this.id = id;
        }

        private void think() throws InterruptedException {
            logStatus("Philosopher " + (id + 1) + " is THINKING.");
            isEating = false;
            Thread.sleep(random.nextInt(3000) + 2000);
        }

        private void eat() throws InterruptedException {
            logStatus("Philosopher " + (id + 1) + " is EATING.");
            isEating = true;
            Thread.sleep(random.nextInt(3000) + 2000);
        }

        @Override
        public void run() {
            while (true) {
                try {
                    think();

                    if (id % 2 == 0) {
                        chopsticks[(id + 1) % NUM_PHILOSOPHERS].acquire();
                        logStatus("Philosopher " + (id + 1) + " picked up RIGHT chopstick.");
                        isHoldingRightChopstick = false;

                        chopsticks[id].acquire();
                        logStatus("Philosopher " + (id + 1) + " picked up LEFT chopstick.");
                        isHoldingLeftChopstick = false;
                    } else {
                        chopsticks[id].acquire();
                        logStatus("Philosopher " + (id + 1) + " picked up LEFT chopstick.");
                        isHoldingLeftChopstick = false;

                        chopsticks[(id + 1) % NUM_PHILOSOPHERS].acquire();
                        logStatus("Philosopher " + (id + 1) + " picked up RIGHT chopstick.");
                        isHoldingRightChopstick = false;
                    }

                    eat();

                    chopsticks[id].release();
                    chopsticks[(id + 1) % NUM_PHILOSOPHERS].release();
                    logStatus("Philosopher " + (id + 1) + " put down both chopsticks.");
                    isHoldingLeftChopstick = true;
                    isHoldingRightChopstick = true;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public void startSimulation() {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            philosophers[i] = new Philosopher(i);
            philosophers[i].start();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Dining Philosophers");
            DiningPhilosophersGUI panel = new DiningPhilosophersGUI();
            frame.add(panel);
            frame.pack();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setVisible(true);
            panel.startSimulation();
        });
    }
}