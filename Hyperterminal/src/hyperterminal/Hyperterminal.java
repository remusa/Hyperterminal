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
import javafx.scene.input.KeyCode;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;

import static javafx.geometry.HPos.CENTER;

/**
 * @author rms
 */
public class Hyperterminal extends Application {

    private SerialPortCommunication serialPortCommunication;
    private OutputStream outputStream;

    private ExecutorService executor;

    private static final int MAX_DATA_POINTS = 50;

    //Keyboard key pressed
    private Label lbKeyPressed;
    private TextField tfKeyPressed;

    //Calibrate NTC
    private TextField tfCalibrateNTC;

    //Chart temperature LM35
    private int xSeriesDataTemperature = 0;
    private Series<Number, Number> seriesTemperature = new Series<>();
    private ConcurrentLinkedQueue<Number> dataTemperature = new ConcurrentLinkedQueue<>();
    private Label lbTemperature;
    private NumberAxis xAxisTemperature;

    //Chart resistance LM35
    private int xSeriesDataResistance = 0;
    private Series<Number, Number> seriesResistance = new Series<>();
    private ConcurrentLinkedQueue<Number> dataResistance = new ConcurrentLinkedQueue<>();
    private Label lbResistance;
    private NumberAxis xAxisResistance;

    //Chart temperature NTC
    private int xSeriesDataTemperatureNTC = 0;
    private Series<Number, Number> seriesTemperatureNTC = new Series<>();
    private ConcurrentLinkedQueue<Number> dataTemperatureNTC = new ConcurrentLinkedQueue<>();
    private Label lbTemperatureNTC;
    private NumberAxis xAxisTemperatureNTC;

    private void init(Stage primaryStage) {
        // serial port
        serialPortCommunication = new SerialPortCommunication();
        serialPortCommunication.initialize();

        // key pressed
        lbKeyPressed = new Label();
        lbKeyPressed.setText("Teclado: ");
        tfKeyPressed = new TextField("Teclado: \n");

        // calibrate NTC
        tfCalibrateNTC = new TextField("20");

        // temperature LM35
        lbTemperature = new Label();
        lbTemperature.setText("0 °C");
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
//        chartTemperature.setLegendVisible(false);
        chartTemperature.setId("chartTemperature");
        chartTemperature.setAnimated(true);
        chartTemperature.setTitle("Temperatura LM35");
        chartTemperature.setHorizontalGridLinesVisible(true);
        seriesTemperature.setName("Temperatura");
        chartTemperature.getData().add(seriesTemperature);

        // resistance LM35
        lbResistance = new Label();
        lbResistance.setText("0 Ω");
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
//        chartResistance.setLegendVisible(false);
        chartResistance.setId("chartResistance");
        chartResistance.setAnimated(true);
        chartResistance.setTitle("Resistencia LM35");
        chartResistance.setHorizontalGridLinesVisible(true);
        seriesResistance.setName("Resistencia");
        chartResistance.getData().add(seriesResistance);

        // temperature NTC
        lbTemperatureNTC = new Label();
        lbTemperatureNTC.setText("0 °C");
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
//        chartTemperatureNTC.setLegendVisible(false);
        chartTemperatureNTC.setId("chartTemperatureNTC");
        chartTemperatureNTC.setAnimated(true);
        chartTemperatureNTC.setTitle("Temperatura NTC");
        chartTemperatureNTC.setHorizontalGridLinesVisible(true);
        seriesTemperatureNTC.setName("Temperatura");
        chartTemperatureNTC.getData().add(seriesTemperatureNTC);

        // setup pane
        GridPane root = new GridPane();
        root.setId("root");
        root.setHgap(10);
        root.setVgap(10);

        // add elements to pane
        root.add(chartTemperature, 0, 0, 1, 1);
        root.add(lbTemperature, 0, 1, 1, 1);

        root.add(chartResistance, 1, 0, 1, 1);
        root.add(lbResistance, 1, 1, 1, 1);

        root.add(chartTemperatureNTC, 0, 2, 1, 1);
        root.add(lbTemperatureNTC, 0, 3, 1, 1);
        root.add(tfCalibrateNTC, 0, 4, 1, 1);

//        root.add(lbKeyPressed, 1, 2, 1, 1);
        root.add(tfKeyPressed, 1, 2, 1, 1);

        // alignment
        root.setHalignment(lbTemperature, CENTER);
        root.setHalignment(lbResistance, CENTER);
        root.setHalignment(lbTemperatureNTC, CENTER);
        root.setHalignment(tfCalibrateNTC, CENTER);

        // CSS and show
        Scene scene = new Scene(root, 800, 450);
        File f = new File("resources/stylesheet.css");
        scene.getStylesheets().clear();
        scene.getStylesheets().add("file:///" + f.getAbsolutePath().replace("\\", "/"));
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

        executor = Executors.newCachedThreadPool(new ThreadFactory() {
            @Override
            public Thread newThread(Runnable r) {
                Thread thread = new Thread(r);
                thread.setDaemon(true);
                return thread;
            }
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
                            int mValueData = Integer.parseInt(arrReceivedData[1]);
                            System.out.println(mTypeData + "," + mValueData);

                            switch (mTypeData) {
                                case "temp_LM35":
                                    dataTemperature.add(mValueData);
                                    Platform.runLater(new Runnable() {
                                        @Override
                                        public void run() {
                                            lbTemperature.setText(mValueData + " °C");
                                        }
                                    });
                                    break;

                                case "res_LM35":
                                    dataResistance.add(mValueData);
                                    Platform.runLater(new Runnable() {
                                        @Override
                                        public void run() {
                                            lbResistance.setText(mValueData + " Ω");
                                        }
                                    });
                                    break;

                                case "temp_NTC":
                                    dataTemperatureNTC.add(mValueData);
                                    Platform.runLater(new Runnable() {
                                        @Override
                                        public void run() {
                                            lbTemperatureNTC.setText(mValueData + " °C");
                                        }
                                    });
                                    break;

                                case "key":
                                    Platform.runLater(new Runnable() {
                                        @Override
                                        public void run() {
//                                            lbKeyPressed.setText(lbKeyPressed.getText() + mValueData);
                                            tfKeyPressed.appendText(String.valueOf(mValueData));
                                        }
                                    });
                                    break;
                            }
                        } catch (ArrayIndexOutOfBoundsException e) {
                            System.out.println("Error: " + e.getLocalizedMessage());
                        }

                    }
                } catch (NumberFormatException | NullPointerException e) {
                    System.out.println("Error: " + e.getLocalizedMessage());
                }

                //send data
                tfCalibrateNTC.setOnKeyReleased(event -> {
                    if (event.getCode() == KeyCode.ENTER) {
                        try {
//                            outputStream = serialPortCommunication.serialPort.getOutputStream();
//                            int calibrate = Integer.parseInt(tfCalibrateNTC.getText());
//                            outputStream.write(calibrate);
//                            System.out.println("calibrate " + calibrate);
//                            outputStream.close();
                            outputStream = serialPortCommunication.serialPort.getOutputStream();
                            String messageString = tfCalibrateNTC.getText();
                            outputStream.write(messageString.getBytes());
                            System.out.println(messageString);
                            outputStream.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                });

//                tfCalibrateNTC.textProperty().addListener(new ChangeListener<String>() {
//                    @Override
//                    public void changed(ObservableValue<? extends String> observable, String oldValue, String newValue) {
//                        try {
//                            outputStream = serialPortCommunication.serialPort.getOutputStream();
//                            String messageString = tfCalibrateNTC.getText();
//                            outputStream.write(messageString.getBytes());
//                            System.out.println(messageString);
//                            outputStream.close();
//                        } catch (IOException e) {
//                            e.printStackTrace();
//                        }
//                    }
//                });

                Thread.sleep(100);
                executor.execute(this);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
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
                    ) {
                break;
            }
            seriesTemperature.getData().add(new Data<>(xSeriesDataTemperature++, dataTemperature.remove()));
            seriesResistance.getData().add(new Data<>(xSeriesDataResistance++, dataResistance.remove()));
            seriesTemperatureNTC.getData().add(new Data<>(xSeriesDataTemperatureNTC++, dataTemperatureNTC.remove()));
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
        // update
        xAxisTemperature.setLowerBound(xSeriesDataTemperature - MAX_DATA_POINTS);
        xAxisTemperature.setUpperBound(xSeriesDataTemperature - 1);
        xAxisResistance.setLowerBound(xSeriesDataResistance - MAX_DATA_POINTS);
        xAxisResistance.setUpperBound(xSeriesDataResistance - 1);
        xAxisTemperatureNTC.setLowerBound(xSeriesDataTemperatureNTC - MAX_DATA_POINTS);
        xAxisTemperatureNTC.setUpperBound(xSeriesDataTemperatureNTC - 1);
    }

    public static void main(String[] args) {
        launch(args);
    }

}
