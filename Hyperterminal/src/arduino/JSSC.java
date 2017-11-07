package arduino;

import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

public class JSSC {

    public static SerialPort serialPort;

    public void initialize() {
        serialPort = new SerialPort("COM1");

        try {
            serialPort.openPort();

            serialPort.setParams(SerialPort.BAUDRATE_9600,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);

            serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                    SerialPort.FLOWCONTROL_RTSCTS_OUT);

            serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
        } catch (SerialPortException ex) {
            System.out.println("There are an error on writing string to port т: " + ex);
        }

    }

    public static class PortReader implements SerialPortEventListener {

        @Override
        public void serialEvent(SerialPortEvent event) {
            if (event.isRXCHAR() && event.getEventValue() > 0) {
                try {
                    String receivedData = serialPort.readString(event.getEventValue());
                    System.out.println("Received response: " + receivedData);
                } catch (SerialPortException ex) {
                    System.out.println("Error in receiving string from COM-port: " + ex);
                }
            }
        }

    }




//    private static final String PORTNAME = "COM1";
//    private BufferedReader input;
//    private OutputStream output;
//    private static final int DATA_RATE = 9600;
//
//    public void initialize() {
//        SerialPort serialPort = new SerialPort(PORTNAME);
//
//        if (serialPort == null) {
//            System.out.println("Could not find COM port.");
//            return;
//        }
//
//        try {
//            serialPort.openPort();
//            serialPort.setParams(DATA_RATE,
//                    SerialPort.DATABITS_8,
//                    SerialPort.STOPBITS_1,
//                    SerialPort.PARITY_NONE);
//            input = new BufferedReader(new InputStreamReader(serialPort.addEventListener()));
//        } catch (Exception e) {
//            System.err.println(e.toString());
//        }
//    }

}
