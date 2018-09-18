package service.client;

import org.apache.thrift.protocol.TBinaryProtocol;
import org.apache.thrift.protocol.TProtocol;
import org.apache.thrift.transport.TSocket;
import org.apache.thrift.transport.TTransport;

import service.demo.Hello;

/**
 * 
 * <br/><B>PROJECT : </B> thrift
 * <br/><B>SUPPORT : </B> <a href="http://www.exp-blog.com" target="_blank">www.exp-blog.com</a> 
 * @version   2015-12-28
 * @author    EXP: 272629724@qq.com
 * @since     jdk�汾��jdk1.6
 */
public class HelloServiceClient {

	public static void main(String[] args) { 
		try {
			TTransport transport = new TSocket("172.168.8.36", 9813, 3000);
	        transport.open(); 
	        TProtocol protocol = new TBinaryProtocol(transport); 
	        Hello.Client client = new Hello.Client(protocol); 
	        long s = System.currentTimeMillis();
			//for(int i=0; i<10000; i++) {
	        	String str = client.helloString("test");
	        	System.out.println(str);
	        //}	
			long e = System.currentTimeMillis();
			System.out.println("��ʱ��" + (e-s)/1000 + "��");
			transport.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
		
        //ThreadTest tt1 = new ThreadTest();
        //tt1.start();
    }
	
}

class ThreadTest extends Thread  {
	
	TTransport transport = null;
	Hello.Client client = null;
	
	public ThreadTest() {
		try {
			//���õ��õķ����ַΪ172.168.8.36���˿�Ϊ9813 socketTimeout��connectionTimeoutΪ3��
			transport = new TSocket("172.168.63.235", 9813, 3000);
	        transport.open(); 
	        //���ô���Э��Ϊ TBinaryProtocol 
	        TProtocol protocol = new TBinaryProtocol(transport); 
	        client = new Hello.Client(protocol); 
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

	public void run() {
		try {
			long s = System.currentTimeMillis();
			for(int i=0; i<100000; i++) {
	        	String str = client.helloString("test");
	        	//System.out.println(str);
	        }	
			long e = System.currentTimeMillis();
			System.out.println("��ʱ��" + (e-s)/1000 + "��");
			
			transport.close();
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

}
