package arduino;

import jssc.SerialPort;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class JSSC {

    private static final String PORTNAME = "COM1";
    private BufferedReader input;
    private OutputStream output;
    private static final int DATA_RATE = 9600;

    public void initialize() {
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
//            input = new BufferedReader(new InputStreamReader(serialPort.));
//            output = serialPort.getOutputStream();
//        } catch (Exception e) {
//            System.err.println(e.toString());
//        }
    }

}
