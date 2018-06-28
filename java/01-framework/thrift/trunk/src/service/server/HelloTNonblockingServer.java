package service.server;

import java.net.InetSocketAddress;

import org.apache.thrift.TProcessor;
import org.apache.thrift.protocol.TCompactProtocol;
import org.apache.thrift.server.TNonblockingServer;
import org.apache.thrift.server.TServer;
import org.apache.thrift.transport.TFramedTransport;
import org.apache.thrift.transport.TNonblockingServerSocket;

import service.demo.Hello;
import service.demo.HelloServiceImpl;

/**
 * 
 * <br/><B>PROJECT : </B> thrift
 * <br/><B>SUPPORT : </B> <a href="http://www.exp-blog.com" target="_blank">www.exp-blog.com</a> 
 * @version   2015-12-28
 * @author    EXP: 272629724@qq.com
 * @since     jdk�汾��jdk1.6
 */
public class HelloTNonblockingServer {

	public static void main(String[] args) {
		try { 
			//������
			TProcessor tprocessor = new Hello.Processor<Hello.Iface>(new HelloServiceImpl());
			//����ͨ�� - ��������ʽ  
			TNonblockingServerSocket serverTransport = new TNonblockingServerSocket(new InetSocketAddress("172.168.8.36", 9812));
			//�첽IO����Ҫʹ��TFramedTransport�������ֿ黺���ȡ��  
			TNonblockingServer.Args tArgs = new TNonblockingServer.Args(serverTransport);
			tArgs.processor(tprocessor);
			tArgs.transportFactory(new TFramedTransport.Factory());
			//ʹ�ø��ܶȶ�����Э�� 
			tArgs.protocolFactory(new TCompactProtocol.Factory());
			//ʹ�÷�����ʽIO������˺Ϳͻ�����Ҫָ��TFramedTransport���ݴ���ķ�ʽ
			TServer server = new TNonblockingServer(tArgs);
			System.out.println("HelloTNonblockingServer start....");
			server.serve(); // ��������
		} catch (Exception e) { 
            e.printStackTrace(); 
        } 
	}
}
