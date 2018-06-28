package service.pool;

import org.apache.thrift.transport.TSocket;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.GenericObjectPool;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * ʵ�����ӳ�
 * 
 * <br/><B>PROJECT : </B> thrift
 * <br/><B>SUPPORT : </B> <a href="http://www.exp-blog.com" target="_blank">www.exp-blog.com</a> 
 * @version   2015-12-28
 * @author    EXP: 272629724@qq.com
 * @since     jdk�汾��jdk1.6
 */
public class GenericConnectionProvider implements ConnectionProvider {
	
	public static final Logger logger = LoggerFactory.getLogger(GenericConnectionProvider.class);
	/** �����IP��ַ */
	private String serviceIP = "127.0.0.1";
	/** ����Ķ˿� */
	private int servicePort = 9813;
	/** ���ӳ�ʱ���� */
	private int conTimeOut = 3000;
	/** ���ӳ������������,Ĭ��Ϊ8 */
	private int maxActive = 5;
	/** ���ӳ��������е�������,Ĭ��Ϊ8 */
	private int maxIdle = 5;
	/** ���ӳ������ٿ��е�������,Ĭ��Ϊ0 */
	private int minIdle = 2;
	/** �����ӳ���Դ�ľ�ʱ�����������������ʱ�䣬��ʱ���ܳ��쳣����λ��������;Ĭ��Ϊ-1.��ʾ������ʱ */
	private long maxWait = 3000;
	/** ���������������ӡ���Դʱ���Ƿ���������Ч�������Ч������ӳ����Ƴ��������Ի�ȡ������ȡ��Ĭ��Ϊfalse�����鱣��Ĭ��ֵ,�Ƿ�ִ��PoolableObjectFactory.validateObject����*/
	private boolean testOnBorrow = false;
	/** �����ӳء��黹������ʱ���Ƿ��⡰���ӡ��������Ч�ԡ�Ĭ��Ϊfalse�����鱣��Ĭ��ֵ */
	private boolean testOnReturn = false;
	/** ���������������ӡ�����ʱ���Ƿ������Ŀ��г�ʱ��Ĭ��Ϊfalse����������ӡ����г�ʱ�����ᱻ�Ƴ� */
	private boolean testWhileIdle = false;
	/** �������ӳء���active�����ﵽ��ֵʱ���������ӡ���Դ�ľ�ʱ�����ӳ���Ҫ��ȡ���ֶ�, Ĭ��Ϊ1��
       -> 0 : �׳��쳣��
       -> 1 : ������ֱ���п���������Դ
       -> 2 : ǿ�ƴ����µ�������Դ */
	private byte whenExhaustedAction = 1;
	/** ���󻺴�� */
	private ObjectPool objectPool = null;
	
	private static GenericConnectionProvider gcp = null;
	
	private GenericConnectionProvider() {
		ThriftPoolableObjectFactory thriftPoolableObjectFactory = new ThriftPoolableObjectFactory(serviceIP, servicePort, conTimeOut);	
		GenericObjectPool.Config config = new GenericObjectPool.Config();
		config.maxActive = maxActive;
		config.maxIdle = maxIdle;
		config.minIdle = minIdle;
		config.maxWait = maxWait;
		config.testOnBorrow = testOnBorrow;
		config.testOnReturn = testOnReturn;
		config.testWhileIdle = testWhileIdle;
		config.whenExhaustedAction = whenExhaustedAction;
		objectPool = new GenericObjectPool(thriftPoolableObjectFactory, config);
	}
	
	public static GenericConnectionProvider init() {
		if(gcp == null) {
			gcp = new GenericConnectionProvider();
		}
		return gcp;
	}

	public TSocket getConnection() {
		try {
			System.out.println(objectPool.getNumActive() + "/" + objectPool.getNumIdle());
            TSocket socket = (TSocket)objectPool.borrowObject();
            System.out.println(objectPool.getNumActive() + "/" + objectPool.getNumIdle() + "\n");
            return socket;
        }catch(Exception e) {
            throw new RuntimeException("error getConnection()", e);
        }
	}

	public void closeConnection(TSocket socket) {
		try {
            objectPool.returnObject(socket);
        }catch(Exception e) {
            throw new RuntimeException("error closeConnection()", e);
        }
	}
	
	public void destroyPool() {
		try {
			objectPool.close();
		}catch(Exception e) {
            throw new RuntimeException("error destroyPool()", e);
        }
	}

}