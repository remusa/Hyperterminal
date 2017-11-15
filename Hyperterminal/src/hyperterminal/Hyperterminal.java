/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hyperterminal;

import arduino.SerialPortCommunication;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.chart.AreaChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.chart.XYChart.Series;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.OutputStream;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * @author rms
 */
public class Hyperterminal extends Application {

    private SerialPortCommunication serialPortCommunication;
    private OutputStream outputStream;

    private ExecutorService executor;

    private static final int MAX_DATA_POINTS = 25;

    // Keyboard key pressed
    private Label lbKeyPressed;
    private TextField tfKeyPressed;

    // Chart temperature LM35
    private int xSeriesDataTemperature = 0;
    private Series<Number, Number> seriesTemperature = new Series<>();
    private ConcurrentLinkedQueue<Number> dataTemperature = new ConcurrentLinkedQueue<>();
    private NumberAxis xAxisTemperature;
    //    private Label lbTemperature;

    // Chart resistance LM35
    private int xSeriesDataResistance = 0;
    private Series<Number, Number> seriesResistance = new Series<>();
    private ConcurrentLinkedQueue<Number> dataResistance = new ConcurrentLinkedQueue<>();
    private NumberAxis xAxisResistance;
    //    private Label lbResistance;

    // Chart temperature NTC
    private int xSeriesDataTemperatureNTC = 0;
    private Series<Number, Number> seriesTemperatureNTC = new Series<>();
    private ConcurrentLinkedQueue<Number> dataTemperatureNTC = new ConcurrentLinkedQueue<>();
    private NumberAxis xAxisTemperatureNTC;
    //    private Label lbTemperatureNTC;

    // Chart lumens LDR
    private int xSeriesDataLumensLDR = 0;
    private Series<Number, Number> seriesLumensLDR = new Series<>();
    private ConcurrentLinkedQueue<Number> dataLumensLDR = new ConcurrentLinkedQueue<>();
    private NumberAxis xAxisLumensLDR;
    //    private Label lbLumensLDR;

    // Animation motion sensor PIR
    private Label lbAnimation;
    private Image imgAnimationMotion;
    private Image imgAnimationStopped;
    private ImageView ivAnimation;
    private boolean mMotionDetected;

    // Color LDR
    private Label lbColor;
    private Image imgColorWhite;
    private Image imgColorBlack;
    private Image imgColorBlue;
    private Image imgColorRed;
    private Image imgColorYellow;
    private ImageView ivColor;
    private String mLastColor;

    private void init(Stage primaryStage) {
        // serial port
        serialPortCommunication = new SerialPortCommunication();
        serialPortCommunication.initialize();

        // key pressed
        lbKeyPressed = new Label();
        lbKeyPressed.setText("Teclado: ");
        tfKeyPressed = new TextField("Teclado: \n");

        // temperature LM35
//        lbTemperature = new Label();
//        lbTemperature.setText("0 °C");
        xAxisTemperature = new NumberAxis(0, MAX_DATA_POINTS, MAX_DATA_POINTS / 10);
        xAxisTemperature.setForceZeroInRange(false);
        xAxisTemperature.setAutoRanging(false);
        xAxisTemperature.setTickLabelsVisible(false);
        xAxisTemperature.setTickMarkVisible(false);
        xAxisTemperature.setMinorTickVisible(false);
        xAxisTemperature.setLabel("Tiempo");
        NumberAxis yAxisTemperature = new NumberAxis();
        yAxisTemperature.setLabel("Temperatura");
        final XYChart<Number, Number> chartTemperature = new AreaChart<Number, Number>(xAxisTemperature, yAxisTemperature) {
            // Override to remove symbols on each data point
            @Override
            protected void dataItemAdded(Series<Number, Number> series, int itemIndex, Data<Number, Number> item) {
            }
        };
        chartTemperature.setId("chartTemperature");
        chartTemperature.setAnimated(false);
//        chartTemperature.setTitle("Temperatura LM35");
//        chartTemperature.setLegendVisible(false);
        chartTemperature.setTitle("Temperatura");
        chartTemperature.setHorizontalGridLinesVisible(true);
        seriesTemperature.setName("Temperatura");
        chartTemperature.getData().add(seriesTemperature);

        // resistance LM35
//        lbResistance = new Label();
//        lbResistance.setText("0 Ω");
        xAxisResistance = new NumberAxis(0, MAX_DATA_POINTS, MAX_DATA_POINTS / 10);
        xAxisResistance.setForceZeroInRange(false);
        xAxisResistance.setAutoRanging(false);
        xAxisResistance.setTickLabelsVisible(false);
        xAxisResistance.setTickMarkVisible(false);
        xAxisResistance.setMinorTickVisible(false);
        xAxisResistance.setLabel("Tiempo");
        NumberAxis yAxisResistance = new NumberAxis();
        yAxisResistance.setLabel("Resistencia");
        final XYChart<Number, Number> chartResistance = new AreaChart<Number, Number>(xAxisTemperature, yAxisResistance) {
            // Override to remove symbols on each data point
            @Override
            protected void dataItemAdded(Series<Number, Number> series, int itemIndex, Data<Number, Number> item) {
            }
        };
        chartResistance.setId("chartResistance");
        chartResistance.setAnimated(false);
//        chartResistance.setTitle("Resistencia LM35");
//        chartResistance.setLegendVisible(false);
        chartResistance.setTitle("Resistencia");
        chartResistance.setHorizontalGridLinesVisible(true);
        seriesResistance.setName("Resistencia");
        chartResistance.getData().add(seriesResistance);

        // temperature NTC
//        lbTemperatureNTC = new Label();
//        lbTemperatureNTC.setText("0 °C");
        xAxisTemperatureNTC = new NumberAxis(0, MAX_DATA_POINTS, MAX_DATA_POINTS / 10);
        xAxisTemperatureNTC.setForceZeroInRange(false);
        xAxisTemperatureNTC.setAutoRanging(false);
        xAxisTemperatureNTC.setTickLabelsVisible(false);
        xAxisTemperatureNTC.setTickMarkVisible(false);
        xAxisTemperatureNTC.setMinorTickVisible(false);
        xAxisTemperatureNTC.setLabel("Tiempo");
        NumberAxis yAxisTemperatureNTC = new NumberAxis();
        yAxisTemperatureNTC.setLabel("Temperatura");
        final XYChart<Number, Number> chartTemperatureNTC = new AreaChart<Number, Number>(xAxisTemperature, yAxisTemperatureNTC) {
            // Override to remove symbols on each data point
            @Override
            protected void dataItemAdded(Series<Number, Number> series, int itemIndex, Data<Number, Number> item) {
            }
        };
        chartTemperatureNTC.setId("chartTemperatureNTC");
        chartTemperatureNTC.setAnimated(false);
//        chartTemperatureNTC.setTitle("Temperatura NTC");
//        chartTemperatureNTC.setLegendVisible(false);
        chartTemperatureNTC.setTitle("Temperatura");
        chartTemperatureNTC.setHorizontalGridLinesVisible(true);
        seriesTemperatureNTC.setName("Temperatura");
        chartTemperatureNTC.getData().add(seriesTemperatureNTC);

        // lumens LDR
        xAxisLumensLDR = new NumberAxis(0, MAX_DATA_POINTS, MAX_DATA_POINTS / 10);
        xAxisLumensLDR.setForceZeroInRange(false);
        xAxisLumensLDR.setAutoRanging(false);
        xAxisLumensLDR.setTickLabelsVisible(false);
        xAxisLumensLDR.setTickMarkVisible(false);
        xAxisLumensLDR.setMinorTickVisible(false);
        xAxisLumensLDR.setLabel("Tiempo");
        NumberAxis yAxisLumensLDR = new NumberAxis();
        yAxisLumensLDR.setLabel("Lúmenes");
        final XYChart<Number, Number> chartLumensLDR = new AreaChart<Number, Number>(xAxisLumensLDR, yAxisLumensLDR) {
            // Override to remove symbols on each data point
            @Override
            protected void dataItemAdded(Series<Number, Number> series, int itemIndex, Data<Number, Number> item) {
            }
        };
        chartLumensLDR.setId("chartLumensLDR");
        chartLumensLDR.setAnimated(false);
//        chartLumensLDR.setTitle("Lúmenes LDR");
//        chartLumensLDR.setLegendVisible(false);
        chartLumensLDR.setTitle("Lúmenes");
        chartLumensLDR.setHorizontalGridLinesVisible(true);
        seriesLumensLDR.setName("Lúmenes");
        chartLumensLDR.getData().add(seriesLumensLDR);

        // animation PIR
        mMotionDetected = false;
        lbAnimation = new Label();
        imgAnimationMotion = new Image("resources/animationMotion2.gif");
        imgAnimationStopped = new Image("resources/animationStopped.jpg");
        ivAnimation = new ImageView();
        ivAnimation.setImage(imgAnimationStopped);
        lbAnimation.setGraphic(ivAnimation);

        // label color LDR
        mLastColor = "white";
        lbColor = new Label();
        imgColorWhite = new Image("resources/colorWhite.png");
        imgColorBlack = new Image("resources/colorBlack.png");
        imgColorBlue = new Image("resources/colorBlue.png");
        imgColorRed = new Image("resources/colorRed.png");
        imgColorYellow = new Image("resources/colorYellow.png");
        ivColor = new ImageView();
        ivColor.setImage(imgColorWhite);
        lbColor.setGraphic(ivColor);

        // setup pane
        GridPane root = new GridPane();
        root.setId("root");
        root.setHgap(10);
        root.setVgap(10);

        // add elements to pane
        root.add(chartTemperature, 0, 0, 1, 1);
//        root.add(lbTemperature, 0, 1, 1, 1);
        root.add(chartResistance, 1, 0, 1, 1);
//        root.add(lbResistance, 1, 1, 1, 1);
        root.add(chartTemperatureNTC, 0, 2, 1, 1);
//        root.add(lbTemperatureNTC, 0, 3, 1, 1);
        root.add(chartLumensLDR, 1, 2, 1, 1);
//        root.add(lbKeyPressed, 1, 2, 1, 1);
        root.add(lbAnimation, 3, 0, 1, 1);
//        root.add(tfKeyPressed, 1, 4, 1, 1);
        root.add(lbColor, 3, 2, 1, 1);

        // alignment
//        GridPane.setHalignment(lbTemperature, CENTER);
//        GridPane.setHalignment(lbResistance, CENTER);
//        GridPane.setHalignment(lbTemperatureNTC, CENTER);

        // CSS and show
        Scene scene = new Scene(root, 800, 450);
        scene.getStylesheets().clear();
        scene.getStylesheets().add("resources/stylesheet.css");
        primaryStage.setScene(scene);
    }

    public void start(Stage stage) {
        stage.setTitle("Hyperterminal");
        init(stage);
        stage.show();

        stage.setOnCloseRequest((WindowEvent t) -> {
            Platform.exit();
            System.exit(0);
        });

        executor = Executors.newCachedThreadPool(r -> {
            Thread thread = new Thread(r);
            thread.setDaemon(true);
            return thread;
        });

        AddToQueue addToQueue = new AddToQueue();
        executor.execute(addToQueue);
        prepareTimeline();
    }

    private class AddToQueue implements Runnable {

        public void run() {
            try {
                try {
                    String mReceivedData = serialPortCommunication.getData();

                    if (!"".equals(mReceivedData) && mReceivedData != null) {

                        String[] arrReceivedData = mReceivedData.split(",");

                        try {
                            String mTypeData = arrReceivedData[0];
                            String mValueDataS = arrReceivedData[1];
                            int mValueData = 0;

                            try {
                                mValueData = Integer.parseInt(mValueDataS);
                            } catch (NumberFormatException e) {
//                                System.out.println("Error: " + e.getMessage());
                            }

                            switch (mTypeData) {

                                case "temp_LM35":
                                    dataTemperature.add(mValueData);
//                                    Platform.runLater(() -> lbTemperature.setText(mValueData + " °C"));
                                    break;

                                case "res_NTC":
                                    dataResistance.add(mValueData);
//                                    Platform.runLater(() -> lbResistance.setText(mValueData + " Ω"));
                                    break;

                                case "temp_NTC":
                                    dataTemperatureNTC.add(mValueData);
//                                    Platform.runLater(() -> lbTemperatureNTC.setText(mValueData + " °C"));
                                    break;

                                case "numberEntered":
                                    System.out.println("numberEntered: " + String.valueOf(mValueData));
//                                    Platform.runLater(() -> tfCalibrateNTC.setText(String.valueOf(mValueData)));
                                    break;

//                                case "key":
//                                    if (mValueDataS.equals("<-")) {
//                                        try {
//                                            Platform.runLater(() -> tfKeyPressed.setText("" + tfKeyPressed.getText().substring(0, tfKeyPressed.getText().length() - 1)));
//                                        } catch (Exception e) {
//                                            System.out.println("Error: no values");
//                                        }
//                                    } else {
//                                        Platform.runLater(() -> tfKeyPressed.appendText(String.valueOf(mValueData)));
//                                    }
//                                    break;

//                                case "eeprom_NTC_T0":
//                                    System.out.println("eeprom_NTC_T0: " + String.valueOf(mValueData));
//                                    Platform.runLater(() -> taEEPROM.appendText("\tNTC_T0: " + String.valueOf(mValueData) + "\n"));
//                                    break;

//                                case "eeprom_NTC_B":
//                                    System.out.println("eeprom_NTC_B: " + String.valueOf(mValueData));
//                                    Platform.runLater(() -> taEEPROM.appendText("\tNTC_B: " + String.valueOf(mValueData) + "\n"));
//                                    break;

                                case "motionPIR":
//                                    System.out.println("motionPIR: " + String.valueOf(mValueData));
                                    if (mValueData == 1) {
                                        mMotionDetected = true;
                                    } else if (mValueData == 0) {
                                        mMotionDetected = false;
                                    }

                                    if (mMotionDetected && ivAnimation.getImage() != imgAnimationMotion) {
                                        ivAnimation.setImage(imgAnimationMotion);
                                    } else if (!mMotionDetected && ivAnimation.getImage() != imgAnimationStopped) {
                                        ivAnimation.setImage(imgAnimationStopped);
                                    }

                                    break;

                                case "luxes":
//                                    Platform.runLater(() -> System.out.println("fotoresistance: " + String.valueOf(mValueData)));
                                    dataLumensLDR.add(mValueData);
                                    break;

                                case "color":
                                    if (!mLastColor.equals(mValueDataS)) {
//                                        System.out.println("mLastColor " + mLastColor);

                                        switch (mValueDataS) {
                                            case "white":
                                                ivColor.setImage(imgColorWhite);
                                                break;
                                            case "black":
                                                ivColor.setImage(imgColorBlack);
                                                break;
                                            case "blue":
                                                ivColor.setImage(imgColorBlue);
                                                break;
                                            case "red":
                                                ivColor.setImage(imgColorRed);
                                                break;
                                            case "yellow":
                                                ivColor.setImage(imgColorYellow);
                                                break;
                                        }

                                        mLastColor = mValueDataS;
                                    }

                                    break;

                            }
                        } catch (ArrayIndexOutOfBoundsException e) {
//                            System.out.println("Error: " + e.getMessage());
                        }

                    }
                } catch (NumberFormatException | NullPointerException e) {
                    System.out.println("Error: " + e.getMessage());
                }

                Thread.sleep(1);
                executor.execute(this);
            } catch (InterruptedException e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    //-- Timeline gets called in the JavaFX Main thread
    private void prepareTimeline() {
        // Every frame to take any data from queue and add to chart
        new AnimationTimer() {
            @Override
            public void handle(long now) {
                addDataToSeries();
            }
        }.start();
    }

    private void addDataToSeries() {
        for (int i = 0; i < 20; i++) {
            if (dataTemperature.isEmpty()
                    || dataResistance.isEmpty()
                    || dataTemperatureNTC.isEmpty()
                    || dataLumensLDR.isEmpty()
                    ) {
                break;
            }
            seriesTemperature.getData().add(new Data<>(xSeriesDataTemperature++, dataTemperature.remove()));
            seriesResistance.getData().add(new Data<>(xSeriesDataResistance++, dataResistance.remove()));
            seriesTemperatureNTC.getData().add(new Data<>(xSeriesDataTemperatureNTC++, dataTemperatureNTC.remove()));
            seriesLumensLDR.getData().add(new Data<>(xSeriesDataLumensLDR++, dataLumensLDR.remove()));
        }

        // remove points to keep us at no more than MAX_DATA_POINTS
        if (seriesTemperature.getData().size() > MAX_DATA_POINTS) {
            seriesTemperature.getData().remove(0, seriesTemperature.getData().size() - MAX_DATA_POINTS);
        }
        if (seriesResistance.getData().size() > MAX_DATA_POINTS) {
            seriesResistance.getData().remove(0, seriesResistance.getData().size() - MAX_DATA_POINTS);
        }
        if (seriesTemperatureNTC.getData().size() > MAX_DATA_POINTS) {
            seriesTemperatureNTC.getData().remove(0, seriesTemperatureNTC.getData().size() - MAX_DATA_POINTS);
        }
        if (seriesLumensLDR.getData().size() > MAX_DATA_POINTS) {
            seriesLumensLDR.getData().remove(0, seriesLumensLDR.getData().size() - MAX_DATA_POINTS);
        }

        // update
        xAxisTemperature.setLowerBound(xSeriesDataTemperature - MAX_DATA_POINTS);
        xAxisTemperature.setUpperBound(xSeriesDataTemperature - 1);
        xAxisResistance.setLowerBound(xSeriesDataResistance - MAX_DATA_POINTS);
        xAxisResistance.setUpperBound(xSeriesDataResistance - 1);
        xAxisTemperatureNTC.setLowerBound(xSeriesDataTemperatureNTC - MAX_DATA_POINTS);
        xAxisTemperatureNTC.setUpperBound(xSeriesDataTemperatureNTC - 1);
        xAxisLumensLDR.setLowerBound(xSeriesDataLumensLDR - MAX_DATA_POINTS);
        xAxisLumensLDR.setUpperBound(xSeriesDataLumensLDR - 1);
    }

    public static void main(String[] args) {
        launch(args);
    }

}
