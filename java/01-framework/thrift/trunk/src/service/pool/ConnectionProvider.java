package service.pool;

import org.apache.thrift.transport.TSocket;

/**
 * ���ӳؽӿ�
 * 
 * <br/><B>PROJECT : </B> thrift
 * <br/><B>SUPPORT : </B> <a href="http://www.exp-blog.com" target="_blank">www.exp-blog.com</a> 
 * @version   2015-12-28
 * @author    EXP: 272629724@qq.com
 * @since     jdk�汾��jdk1.6
 */
public interface ConnectionProvider {

	/**
     * ȡ���ӳ��е�һ������
     * @return
     */
    public TSocket getConnection();
    
    /**
     * ��������
     * @param socket
     */
    public void closeConnection(TSocket socket);
    
    /**
     * �ͷ����ӳ�
     */
    public void destroyPool();

}
