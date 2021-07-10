//---------------------SimpleClock(主类)
import javax.swing.*;
import java.awt.*;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
public class Clock  implements Runnable{
    private volatile boolean running;
    private SimpleClock clock;
    public Clock(SimpleClock clock){
        this.clock=clock;
        this.running=true;
    }
    @Override
    public void run() {
        while(running){
            displayClock();
            sleep();
        }
    }
    public void displayClock(){
        Calendar cal = new GregorianCalendar();
        int h = cal.get(Calendar.HOUR); 	        //获取当前时
        int m = cal.get(Calendar.MINUTE);     		//获取当前分
        int s = cal.get(Calendar.SECOND);     		//获取当前秒
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                clock.setClock(h,m,s);
            }
        });
    }
    public void sleep() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
        }
    }
    public synchronized void setRunning(boolean running) {
        this.running = running;
    }
}
//---------------------Clock(Runnable-控制主类中相关钟表组件的线程)

import javax.swing.*;
import java.awt.*;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class Clock  implements Runnable{
    private volatile boolean running;
    private SimpleClock clock;
    public Clock(SimpleClock clock){
        this.clock=clock;
        this.running=true;
    }
    @Override
    public void run() {
        while(running){
            displayClock();
            sleep();
        }
    }
    public void displayClock(){
        Calendar cal = new GregorianCalendar();
        int h = cal.get(Calendar.HOUR); 	        //获取当前时
        int m = cal.get(Calendar.MINUTE);     		//获取当前分
        int s = cal.get(Calendar.SECOND);     		//获取当前秒

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                clock.setClock(h,m,s);
            }
        });
    }
    public void sleep() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
        }
    }
    public synchronized void setRunning(boolean running) {
        this.running = running;
    }
}
//---------------------Timer(Runnable-控制主类中相关时间显示组件的线程)
import javax.swing.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class Timer implements Runnable {

    private volatile boolean running;

    private SimpleClock clock;

    private SimpleDateFormat timeFormat;



    public Timer(SimpleClock clock) {
        this.clock = clock;
        this.running = true;
        this.timeFormat = new SimpleDateFormat("h:mm:ss a");
    }

    @Override
    public void run() {
        while (running) {
            displayTime();
            sleep();
        }

    }

    public void displayTime() {
        final Calendar calendar = Calendar.getInstance();
        Date date = calendar.getTime();
        final String s = timeFormat.format(date);

        Calendar cal = new GregorianCalendar();

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                clock.setText(s);
            }
        });
    }

    public void sleep() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
        }
    }

    public synchronized void setRunning(boolean running) {
        this.running = running;
    }

}



